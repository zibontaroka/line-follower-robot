# Line Follower Robot

An Arduino-based line following robot using IR sensors and an L298N motor driver.

## Features
- Line tracking using 5 IR sensors
- Smooth soft turns and 90° sharp turns
- Motor speed control
- Auto stop if line is lost

## Hardware Used
- Arduino UNO
- L298N Motor Driver
- 5x IR Sensors
- 2x DC Motors + Wheels
- Chassis
- Power supply (Battery)

## Wiring
| Arduino Pin | Connected To |
|:------------|:-------------|
| 10          | ENA (Motor A Enable) |
| 9           | IN1 |
| 8           | IN2 |
| 7           | IN3 |
| 6           | IN4 |
| 5           | ENB (Motor B Enable) |
| A4          | Left Sensor |
| A3          | Center Left Sensor |
| A2          | Center Sensor |
| A1          | Center Right Sensor |
| A0          | Right Sensor |

## How It Works
- Sensors detect the black line on white ground.
- Arduino decides movement based on sensor input.
- Motors adjust speed and direction accordingly.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🧠 Author  
**Md Shaifulla Zibon**  
Electrical and Electronics Engineering  
European University of Bangladesh  
GitHub: [@zibontaroka](https://github.com/zibontaroka)
