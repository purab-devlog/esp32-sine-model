This project demonstrates how to deploy a machine learning model on an ESP32 
to generate sine function values. The model is trained in Python, 
converted to TensorFlow Lite, and then integrated into an Arduino (.ino) program 
for execution on ESP32. 
Inputs are sent from a .txt file using Python, and the ESP32 processes them to generate outputs.


Requirements
Hardware:
ESP32 Development Board,
USB cable for communication.
Software:
Arduino IDE (with ESP32 board support),
Python 3.x (with pyserial library).


Setup Instructions :

1. Train and Convert the ML Model (Python)
   
Train a TensorFlow model in Python to predict sine values and conver it to TensorFlow Lite (.tflite). I have named it as CNN above.
Convert .tflite to a C header file (model_data.h) for embedding into ESP32. The file is present in the main folder, you can copy paste it with the same .h extension. Now run a python script to create 
a dataset here "input" script it will save the dataset in the same directory as input_data.txt. Or just save file and copy paste the contents of input_data.txt.

2. Upload Code to ESP32 (Arduino)
Open Arduino IDE, install the ESP32 board first. Go to file --> preferences in additional board manager URLS paste this

http://arduino.esp8266.com/stable/package_esp8266com_index.json
https://dl.espressif.com/dl/package_esp32_index.json

Then go to board manager and search for ESP32 by Espressif and install it. Select ESP32 DEV Module in the board manager. 

Then go to sketch --> include Library --> Manage Library --> search "TensorFlowLite_ESP32" by TensorFLow Authors. Install it.

Once this is done you should be able to run your arduino code. But remember to place the model_data.h file in the same folder as your .ino or arduino program. Failing which there will be an error during compiling. Then run the arduino code saved as .ino file
The ESP32 initializes TensorFlow Lite Micro and waits for inputs via USB/UART. Once you are done uploading the code, hit the reset button to make sure the setup has been completed.

After this open another python script and run send_input. This script will send the input_data.txt to the ESP32 and print the output.


Troubleshooting

No Output on Arduino Serial Monitor?
The Python script handles serial communication, so the output appears in Python, not the Arduino Serial Monitor.

ESP32 Not Responding?
Make sure it's properly connected and the correct COM port is selected.
Try resetting ESP32 after uploading the Arduino code.

Python Script Fails to Open COM Port?
Ensure no other program (like Arduino Serial Monitor) is using the port.
Check the correct COM port number and update send_input.py.
