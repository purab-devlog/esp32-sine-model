#include <Arduino.h>
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/schema/schema_generated.h"

// Include the model data header file
#include "model_data.h"  // This file contains the 'model_data' array

// UART communication configuration
#define RXD2 16        // Receiver PIN 16
#define TXD2 17        // Transmitter PIN 17
#define UART_BAUD_RATE 115200    // Baud rate for serial communication

// Globals for TensorFlow Lite
namespace {
  const tflite::Model* model = nullptr;
  tflite::MicroInterpreter* interpreter = nullptr;
  TfLiteTensor* input = nullptr;
  TfLiteTensor* output = nullptr;

  // Tensor arena size configuration
  constexpr int kTensorArenaSize = 2000;
  uint8_t tensor_arena[kTensorArenaSize];  // Tensor arena for memory allocation
}

void setup() 
{
  // Start Serial communication for debugging
  Serial.begin(UART_BAUD_RATE);

  // Initialize UART communication
  Serial2.begin(UART_BAUD_RATE, SERIAL_8N1, RXD2, TXD2);

  // Initialize TensorFlow Lite model using the model data from model_data.h
  model = tflite::GetModel(model_data);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model version mismatch!");
    return;
  }

  // Set up the TensorFlow Lite interpreter with the required op resolver
  static tflite::MicroMutableOpResolver<1> resolver;
  if (resolver.AddFullyConnected() != kTfLiteOk) {
    Serial.println("Failed to add FullyConnected operation!");
    return;
  }

  // Create the interpreter
  static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, kTensorArenaSize);
  interpreter = &static_interpreter;

  // Allocate tensors for the interpreter
  interpreter->AllocateTensors();

  // Get the input and output tensors
  input = interpreter->input(0);
  output = interpreter->output(0);

  Serial.println("Setup complete!");
}

void loop() 
{
  if (Serial.available()) { 
    String inputString = Serial.readStringUntil('\n'); // Read full line 
    float input_data = inputString.toFloat(); // Convert to float 
    Serial.print("Input: "); 
    Serial.print(input_data); 
    // Run inference on input_data 
    input->data.f[0] = input_data; 
    interpreter->Invoke(); 
    float output_value = output->data.f[0];
    Serial.print(" Output: "); 
    Serial.println(output_value);
    Serial.flush();
  }

  delay(100);
}