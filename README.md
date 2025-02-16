# MakeUofT25-

# EcoFlare 🌱💡

EcoFlare is a smart, eco-friendly fire and charge monitoring system designed to enhance safety and energy efficiency. It mimics the behavior of solar panels using photoresistors (LDRs) to optimize battery charging while reducing wildfire risks through early detection and alerts.

<img src="https://github.com/WisteriaCh/EcoFlare_makeuoft25/blob/main/FinalDesign.JPG" alt="Project Image" width="500">
  *Figure 1. Picture of the project in use.*

## 🚀 Features

- **Fire Detection & Alert**: Uses a flame sensor and buzzer to detect fires and alert users.
- **Smart Solar Charging**: Simulates battery charge based on light intensity from an LDR.
- **Distance Measurement**: Ultrasonic sensor measures distance and alerts when an object is too close.
- **LCD Display**: Provides real-time updates on fire status, battery percentage, and object distance.
- **Energy Efficiency**: Optimizes battery usage based on light availability.

## 🔧 Hardware Components

- Arduino (Uno)
- Flame Sensor (Analog & Digital)
- Light Dependent Resistor (LDR)
- Ultrasonic Sensor (HC-SR04)
- Servo Motor (optional for additional features)
- Buzzer
- LCD Display
- LEDs (for fire and charge alerts)

## 🛠️ Installation & Setup

1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/EcoFlare.git
   cd EcoFlare
   ```

2. Install necessary Arduino libraries:
   - LiquidCrystal
   - Servo

3. Upload the Arduino code:
   - Open `EcoFlare.ino` in Arduino IDE.
   - Select the correct board (Arduino Uno).
   - Compile and upload the code.

4. Assemble the hardware following the circuit diagram in `docs/wiring_diagram.png`.

5. Power up and test the system!

## 📊 How It Works

- The flame sensor detects fire and triggers an alert with a buzzer and red LED.
- The LDR simulates solar charging and updates battery levels accordingly.
- The system mimics the behavior of solar panels to efficiently manage energy and contribute to wildfire prevention.
- The ultrasonic sensor detects objects and alerts the user if an object is too close.
- The LCD displays system status, battery percentage, and detected distances.
