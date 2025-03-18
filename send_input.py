import serial
import time
try:
    # Open Serial connection with safe parameters
    ser = serial.Serial('COM3', 115200, timeout=1, dsrdtr=True, rtscts=True)
    # Wait for ESP32 to initialize
    time.sleep(5)
    # Open the input file
    with open("input_data.txt", "r") as file:
        for line in file:
            value = line.strip()
            # Ensure the line is a valid number before sending
            try:
                float_value = float(value)  # Validate input
                send_data = f"{float_value}\n".encode()  # Convert to bytes
                ser.write(send_data)  # Send data to ESP32
                ser.flush()
                time.sleep(0.5)  # Give ESP32 time to process
                # Read ESP32 response
                response = ser.readline().decode().strip()
                if response:
                    print("ESP32 Response:", response)
            except ValueError:
                print(f"Skipping invalid value: {value}")
except serial.SerialException as e:
    print(f"Serial error: {e}")
finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()
