🤖 Line-Following Robot with Memory-Based Turning
This project implements a line-following robot using an Arduino microcontroller. The robot follows a black line on a white surface using IR sensors and PID control for smooth navigation, with memory-based turning to handle sharp turns and temporary line loss.

📄 Features

🤖 Line Following: Utilizes four IR sensors to detect and follow a black line.
🎛️ PID Control: Uses Proportional-Integral-Derivative control for precise tracking.
🧠 Memory-Based Turning: Remembers the last outer sensor to maintain direction when the line is lost.
🔄 Sharp Turn Handling: Adjusts motor speeds for sharp turns.
⚙️ Adjustable Parameters: Tune PID constants and motor speeds for optimal performance.


🛠️ Hardware Requirements

🤖 Microcontroller: Arduino board (e.g., Arduino Uno)
👁️ IR Sensors: 4 IR sensors (L2, L1, R1, R2). ⚠️ Note: Sensor C is damaged and not used.
⚡ Motors: 2 DC motors for left and right wheels.
🖥️ Motor Driver: Compatible driver (e.g., L298N).
🔋 Power Supply: Battery or source for motors and Arduino.


📌 Pin Configuration
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


📦 Software Dependencies

Arduino IDE: For uploading code to the Arduino.
No additional libraries: Uses standard Arduino functions.


🚀 Installation and Setup

Hardware Assembly: Connect IR sensors to analog pins (A0, A1, A3, A4), motor driver to digital pins (5-10), and motors to the driver.
Upload Code: Open Arduino IDE, paste the code, select your board/port, and upload.
Calibration: Align sensors over the line and adjust PID parameters if needed.


🎮 Usage

Power On: Position the robot on the line.
Line Following: It follows the line using sensor data and PID control.
Sharp Turns: Adjusts speeds for sharp turns.
Memory-Based Turning: Continues turning based on the last sensor when the line is lost.


📝 Code Explanation

Sensor Reading: Reads IR sensors and calculates line position error.
PID Control: Adjusts motor speeds for smooth tracking.
Motor Control: Sets motor direction and speed.
Sharp Turn Handling: Manages sharp turns with outer sensors.
Memory Logic: Tracks outer sensor detections with a timeout.


🛡️ Troubleshooting

Not Following Line: Check sensor alignment and line contrast.
Erratic Behavior: Tune PID parameters.
Motors Not Working: Verify connections and power.


🤝 Contributing
Fork this project and submit pull requests with improvements!

📜 License
MIT License. See LICENSE for details.

Notes

Emoji enhance readability and are supported in Markdown.
Copy and paste emoji directly (e.g., 🤖 for robot).
Ensure your platform (e.g., GitHub) supports emoji display.

