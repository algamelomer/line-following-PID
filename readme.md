Line-Following Robot with Memory-Based Turning
This project implements a line-following robot using an Arduino microcontroller. The robot is designed to follow a black line on a white surface using IR sensors for line detection and PID control for smooth navigation. It also incorporates memory-based turning to handle sharp turns and maintain direction when the line is temporarily lost.

Features

Line Following: Utilizes four IR sensors to detect and follow a black line.
PID Control: Employs Proportional-Integral-Derivative control for precise and smooth line tracking.
Memory-Based Turning: Remembers the last detected outer sensor to continue turning correctly even when the line is not detected.
Sharp Turn Handling: Adjusts motor speeds to navigate sharp turns effectively.
Adjustable Parameters: Allows tuning of PID constants and motor speeds for optimal performance.


Hardware Requirements

Microcontroller: Arduino board (e.g., Arduino Uno)
IR Sensors: 4 IR sensors for line detection (L2, L1, R1, R2). Note: Sensor C is damaged and not used.
Motors: 2 DC motors for left and right wheels.
Motor Driver: Compatible motor driver (e.g., L298N) to control the motors.
Power Supply: Battery or power source suitable for the motors and Arduino.


Pin Configuration
IR Sensor Pins

L2: A0
L1: A1
C: A2 (Damaged - not used)
R1: A3
R2: A4

Motor Control Pins

ENA: 9 (PWM for left motor speed)
IN1: 8 (Left motor direction)
IN2: 7 (Left motor direction)
IN3: 6 (Right motor direction)
IN4: 5 (Right motor direction)
ENB: 10 (PWM for right motor speed)


Software Dependencies

Arduino IDE: Required to upload the code to the Arduino board.
No additional libraries: The code uses only standard Arduino functions.


Installation and Setup

Hardware Assembly:

Connect the IR sensors to the specified analog pins (A0, A1, A3, A4).
Connect the motor driver to the digital pins (5 to 10).
Attach the motors to the motor driver outputs.


Upload the Code:

Open the Arduino IDE.
Copy and paste the provided code into a new sketch.
Select your Arduino board and the appropriate port.
Upload the code to the Arduino.


Calibration:

Place the robot on the line and adjust the IR sensors to ensure proper alignment.
Fine-tune the PID parameters (Kp, Ki, Kd) and speed settings (baseSpeed, maxSpeed, sharpTurnSpeed) if needed.




Usage

Power On: Turn on the robot and position it on the line.
Line Following: The robot will automatically follow the line using IR sensor data and PID control.
Sharp Turns: When a sharp turn is detected (via outer sensors), the robot adjusts motor speeds to navigate it.
Memory-Based Turning: If the line is lost temporarily, the robot uses memory of the last detected outer sensor to continue turning.


Code Explanation

Sensor Reading: The readLineSensor() function reads the four IR sensors and calculates an error value based on the line’s position.
PID Control: The PID algorithm computes a correction value to adjust motor speeds and keep the robot on the line.
Motor Control: The setMotorSpeed() function sets motor directions and speeds, clamping them within defined limits.
Sharp Turn Handling: The makeSharpTurn() function adjusts motor speeds for sharp turns when outer sensors are triggered.
Memory Logic: Outer sensor detections are stored with a timeout, enabling the robot to maintain direction during brief line losses.


Troubleshooting

Robot Not Following Line: Verify sensor alignment and ensure the line contrasts well with the surface.
Erratic Behavior: Adjust PID parameters (Kp, Ki, Kd) for smoother control.
Motors Not Working: Check motor driver connections and power supply.
Sensor Malfunction: Test each IR sensor individually to ensure proper operation.


Contributing
Contributions are welcome! Feel free to fork this project, enhance it, and submit pull requests with improvements.

License
This project is licensed under the MIT License. See the LICENSE file for details.
