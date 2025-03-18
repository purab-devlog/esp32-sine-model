#import required packages
import tensorflow as tf
import numpy as np

#Take the input for x and y to train the model
x_data =np.linspace(0, 2 * np.pi, 100).reshape(-1, 1)
y_data = np.sin(x_data)

#This section is the building of the model
#With 1 output and 1 hidden layer
model = tf.keras.Sequential([
    tf.keras.layers.Dense(10, input_dim=1, activation='relu'),
    tf.keras.layers.Dense(1)])

#This compiles the code
model.compile(optimizer='adam', loss='mean_squared_error')
model.fit(x_data, y_data, epochs=100)#epochs is the amount of times the model trains

#This part is used to convert tensorflow into tensorflow lite
#As tensorflow can't run on ESP32
converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()

#This is used to save the converted file as tflite file
#Here it is saved as sine_model.tflite
with open('sine_model.tflite', 'wb') as f:
    f.write(tflite_model)
