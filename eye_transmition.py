import serial
import time

# Update with the correct serial port for your Arduino
arduino_port = '/dev/ttyACM0'  # or '/dev/ttyACM0'
baud_rate = 9600
ser = serial.Serial(arduino_port, baud_rate)

def set_servo_angle(angle):
    if 0 <= angle <= 180:
        ser.write(f"{angle}\n".encode())  # Send the angle to the Arduino
        time.sleep(0.1)  # Give some time for the Arduino to process
        while ser.in_waiting:
            print(ser.readline().decode('utf-8').strip())  # Print response from Arduino
    else:
        print("Angle must be between 0 and 180")

try:
    while True:
        angle = int(input("Enter servo angle (0-180): "))
        set_servo_angle(angle)
except KeyboardInterrupt:
    print("Program terminated")
finally:
    ser.close()  # Close the serial connection
