# Arduino Speed Detector

A speed detection system using dual HC-SR04 ultrasonic sensors to measure the speed of moving objects (like people) passing through a corridor or pathway.

## Overview

This project uses two ultrasonic sensors placed at a known distance apart to calculate the speed of objects passing between them. It includes visual feedback through the Serial Monitor and audio feedback using a buzzer.

## Hardware Requirements

- Arduino board (compatible with Arduino IDE)
- 2x HC-SR04 Ultrasonic Sensors
- 1x Buzzer
- Jumper wires
- Breadboard (optional)

## Pin Configuration

| Component | Pin Type | Pin Number |
|-----------|----------|------------|
| Sensor A  | Trigger  | 9          |
| Sensor A  | Echo     | 10         |
| Sensor B  | Trigger  | 11         |
| Sensor B  | Echo     | 12         |
| Buzzer    | Signal (Longer PIN)   | 13         |
| Buzzer    | Ground   | GND        |

## Features

- Real-time speed measurement
- Configurable speed limit
- Audio feedback:
  - 5 quick beeps for speed limit violation
  - Single beep for acceptable speed
- Serial monitor output for debugging and monitoring
- Adjustable detection threshold

## Configuration

The following constants can be adjusted in the code:

```cpp
const float SENSOR_DISTANCE = 1.0;    // Distance between sensors in meters
const float MAX_ALLOWED_SPEED = 2.0;  // Maximum allowed speed in m/s
const float DETECTION_THRESHOLD = 100; // Detection threshold in cm
```

## Installation

1. Connect the hardware components according to the pin configuration
2. Upload the `Speed-Detector.ino` sketch to your Arduino board
3. Open the Serial Monitor (9600 baud) to view the output

## Usage

1. Place the two ultrasonic sensors at a known distance apart (default 1 meter)
2. Power on the Arduino
3. The system will automatically detect objects passing between the sensors
4. Speed measurements and alerts will be displayed on the Serial Monitor
5. Audio feedback will be provided through the buzzer

## Output Format

The system provides the following information through the Serial Monitor:
- Time elapsed between sensor triggers
- Calculated speed in meters per second
- Speed limit violation warnings
- Detection notifications

## Troubleshooting

- Ensure sensors are properly aligned and have a clear line of sight
- Verify all connections are secure
- Check Serial Monitor for error messages
- Adjust detection threshold if false triggers occur

## License

This project is open source and available under the MIT License.

## Contributing

Feel free to submit issues and enhancement requests! 