#include <ESP32Servo.h>
#include "BluetoothSerial.h"  // Library for Bluetooth communication on ESP32

Servo myServo;  // Create a Servo object
BluetoothSerial SerialBT;  // Create BluetoothSerial object

int servoPin = 18;  // GPIO pin to which the servo is connected
int angle = 90;     // Start the servo at a neutral angle (90 degrees)

void setup() {
  // Attach the servo to the GPIO pin
  myServo.attach(servoPin);

  // Start Bluetooth with a device name (change "ESP32_Servo" if desired)
  SerialBT.begin("ESP32_Servo");

  // Start the servo at the neutral angle (90 degrees)
  myServo.write(angle);
}

void loop() {
  // Check if there is data available from Bluetooth
  if (SerialBT.available()) {
    char receivedChar = SerialBT.read();  // Read the character sent from the smartphone

    // Only process characters between '0' and '9'
    if (receivedChar >= '0' && receivedChar <= '9') {
      // Convert the received character into an integer (0-9) and map it to a servo angle (0-180 degrees)
      int angle = map(receivedChar - '0', 0, 9, 0, 180);
      
      // Move the servo to the new angle
      myServo.write(angle);

      // Send the new angle back to the Bluetooth terminal
      SerialBT.print("Servo angle: ");
      SerialBT.println(angle);
    }
    else if (receivedChar == '\n' || receivedChar == '\r') {
      // Ignore newline and carriage return characters
    }
    else {
      // If invalid data is received, send an error message back
      SerialBT.println("Invalid input. Send a number between 0 and 9.");
    }
  }
}