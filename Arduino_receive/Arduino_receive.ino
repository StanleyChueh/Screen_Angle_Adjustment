#include <Servo.h>

Servo servo1;  // create servo object to control the first servo
Servo servo2;  // create servo object to control the second servo

void setup() {
  Serial.begin(9600);   // initialize serial communication
  servo1.attach(9);     // attaches the first servo on pin 9
  servo2.attach(8);     // attaches the second servo on pin 8
}

void loop() {
  if (Serial.available() > 0) {
    int angle = Serial.parseInt(); // read the angle from the serial port
    if (angle >= 0 && angle <= 180) { // validate the angle
      // Convert angle to microseconds (assuming 1000 to 2000 range)
      int pulseWidth1 = map(angle, 0, 180, 1000, 2000);
      int pulseWidth2 = map(180 - angle, 0, 180, 1000, 2000);

      // Disable interrupts to prevent timing issues
      noInterrupts();
      servo1.writeMicroseconds(pulseWidth1); // set the position of the first servo
      servo2.writeMicroseconds(pulseWidth2); // set the position of the second servo
      // Enable interrupts after setting servo positions
      interrupts();
      
      Serial.print("Servo angles set to: ");
      Serial.print(angle);
      Serial.print(" and ");
      Serial.println(180 - angle);
    }
  }
}
