// === IR sensor pins ===
const int L2 = A0;
const int L1 = A1;
const int C  = A2;  // Damaged - not used
const int R1 = A3;
const int R2 = A4;

// === Motor control pins ===
const int ENA = 9;
const int IN1 = 8;
const int IN2 = 7;
const int IN3 = 6;
const int IN4 = 5;
const int ENB = 10;

// === PID parameters ===
float Kp = 20;   // Reduced for smoother corrections
float Ki = 0.1;  // Small integral term to eliminate steady-state error
float Kd = 12;   // Reduced derivative term

int baseSpeed = 120;        // Reduced base speed for better control
int maxSpeed = 200;         // Reduced max speed
int sharpTurnSpeed = 160;   // Reduced sharp turn speed

float error = 0;
float lastError = 0;
float integral = 0;

// === Memory for outer sensors ===
bool L2_memory = false;  // Remember if L2 detected line
bool R2_memory = false;  // Remember if R2 detected line
unsigned long L2_lastSeen = 0;  // When L2 last saw the line
unsigned long R2_lastSeen = 0;  // When R2 last saw the line
const unsigned long memoryTimeout = 1000;  // How long to remember (1 second)

// === Setup ===
void setup() {
  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // IR sensor pins
  pinMode(L2, INPUT);
  pinMode(L1, INPUT);
  pinMode(C, INPUT);   // Not used but keeping pin setup
  pinMode(R1, INPUT);
  pinMode(R2, INPUT);

  Serial.begin(9600);
}

// === Read sensor and compute error (4 sensors only) ===
int readLineSensor() {
  int sL2 = digitalRead(L2);
  int sL1 = digitalRead(L1);
  // int sC  = digitalRead(C);  // Skip damaged sensor
  int sR1 = digitalRead(R1);
  int sR2 = digitalRead(R2);

  // Invert readings: Black line = 0, White = 1 → (1 - value) to detect line
  int L2_line = 1 - sL2;
  int L1_line = 1 - sL1;
  int R1_line = 1 - sR1;
  int R2_line = 1 - sR2;

  // Update memory for outer sensors
  unsigned long currentTime = millis();
  
  if (L2_line) {
    L2_memory = true;
    L2_lastSeen = currentTime;
  }
  if (R2_line) {
    R2_memory = true;
    R2_lastSeen = currentTime;
  }

  // Clear memory after timeout
  if (currentTime - L2_lastSeen > memoryTimeout) {
    L2_memory = false;
  }
  if (currentTime - R2_lastSeen > memoryTimeout) {
    R2_memory = false;
  }

  // Priority 1: Active outer sensor detection (currently seeing line)
  if (L2_line && !R2_line) {
    return -4;  // Sharp left turn
  }
  if (R2_line && !L2_line) {
    return 4;   // Sharp right turn
  }

  // Priority 2: Memory-based turning (lost line but remember outer sensor)
  if (L2_memory && !L1_line && !R1_line && !R2_line) {
    return -4;  // Continue sharp left based on L2 memory
  }
  if (R2_memory && !L1_line && !R1_line && !L2_line) {
    return 4;   // Continue sharp right based on R2 memory
  }

  // Priority 3: Inner sensors detect line - clear outer memory and use normal PID
  if (L1_line || R1_line) {
    // Clear memory when inner sensors take over
    L2_memory = false;
    R2_memory = false;
    
    // Normal weighted average calculation
    int weights[] = {-2, -1, 1, 2};
    int sensors[] = {L2_line, L1_line, R1_line, R2_line};

    int sum = 0;
    int count = 0;

    for (int i = 0; i < 4; i++) {
      sum += sensors[i] * weights[i];
      count += sensors[i];
    }

    if (count > 0) {
      return sum / count;
    }
  }

  // Priority 4: No line detected anywhere
  if (!L2_line && !L1_line && !R1_line && !R2_line) {
    // If we have memory of an outer sensor, keep turning
    if (L2_memory) return -4;
    if (R2_memory) return 4;
    
    // Otherwise, use last known direction
    return (lastError > 0) ? 3 : -3;
  }

  return 0;  // Fallback
}

// === Set motor directions and speed ===
void setMotorSpeed(int leftSpeed, int rightSpeed) {
  // Direction: Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  // Clamp speeds
  leftSpeed = constrain(leftSpeed, 0, maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, maxSpeed);

  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);
}

// === Sharp turn function ===
void makeSharpTurn(int direction) {
  if (direction < 0) {
    // Sharp left turn - slow left motor, speed up right
    setMotorSpeed(50, sharpTurnSpeed);
  } else {
    // Sharp right turn - slow right motor, speed up left
    setMotorSpeed(sharpTurnSpeed, 50);
  }
}

// === Main Loop ===
void loop() {
  error = readLineSensor();

  // Check for sharp turn conditions
  if (abs(error) >= 4) {
    makeSharpTurn(error);
    lastError = error;
    delay(20);  // Brief delay for sharp turn
    return;
  }

  // Normal PID control for gentle corrections
  integral += error;
  float derivative = error - lastError;

  float correction = Kp * error + Ki * integral + Kd * derivative;

  int leftSpeed = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;

  setMotorSpeed(leftSpeed, rightSpeed);

  lastError = error;

  delay(10); // small delay for stability
}
