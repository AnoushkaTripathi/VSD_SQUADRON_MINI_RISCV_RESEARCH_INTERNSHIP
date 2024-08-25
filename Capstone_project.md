# Moving Average Filter with VSD Squadron MINI
This repository contains an example of how to implement a moving average filter using Arduino. The moving average filter is a simple yet effective way to smooth out noisy sensor data, making it easier to work with and more accurate.

## Code Overview

```cpp
const int numReadings = 35;
int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;

void setup() {
  Serial.begin(115200);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(A1);
  Serial.print(readings[readIndex]);
  Serial.print(",");
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  average = total / numReadings;
  Serial.println(average);
  delay(15);
}



## Explanation

### Variables

- **`const int numReadings = 35;`**  
  This constant defines the number of readings we will average. A higher number results in a smoother output but can also introduce a slight lag.

- **`int readings[numReadings];`**  
  This array stores the last 35 sensor readings.

- **`int readIndex = 0;`**  
  `readIndex` keeps track of where the current reading will be stored in the array.

- **`int total = 0;`**  
  `total` holds the sum of all the readings, which is used to calculate the average.

- **`int average = 0;`**  
  This variable stores the calculated average value.

### `setup()` Function

```cpp
void setup() {
  Serial.begin(115200);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}
```

- **`Serial.begin(115200);`**  
  Initializes the serial communication at a baud rate of 115200, allowing us to monitor the output in the Serial Monitor.

- **Initialization Loop:**  
  The `for` loop initializes the `readings` array to zero, ensuring that we start with a clean slate before taking any sensor readings.

### `loop()` Function

```cpp
void loop() {
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(A1);
  Serial.print(readings[readIndex]);
  Serial.print(",");
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  average = total / numReadings;
  Serial.println(average);
  delay(15);
}
```

- **Subtract Old Reading:**  
  The old reading at `readIndex` is subtracted from the total to remove its effect on the average.

- **New Reading:**  
  A new analog reading is taken from pin `A1` and stored in the `readings` array at the current `readIndex`.

- **Print Reading:**  
  The new reading is printed to the Serial Monitor.

- **Update Total:**  
  The new reading is added to the total, updating the sum for the average calculation.

- **Increment Index:**  
  `readIndex` is incremented to move to the next position in the array. If `readIndex` exceeds the array size, it wraps around to zero.

- **Calculate Average:**  
  The average is calculated by dividing the `total` by `numReadings`. This smoothed value is printed to the Serial Monitor.

- **Delay:**  
  A short delay of 15 milliseconds is added to control the speed of the loop.

## Advantages of the Moving Average Filter

1. **Noise Reduction:**  
   The filter reduces random noise by averaging multiple readings, resulting in a more stable output.

2. **Simplicity:**  
   It's easy to implement and understand, making it a great choice for beginners and quick projects.

3. **Real-Time Smoothing:**  
   Provides real-time smoothing with minimal computational overhead, which is ideal for embedded systems like Arduino.

4. **Improved Accuracy:**  
   The filter enhances the accuracy of sensor readings, which is crucial for applications like environmental monitoring, robotics, and more.

## Demonstration

To see the code in action:

1. Connect a sensor to analog pin `A1` on your Arduino.
2. Upload the code to your Arduino.
3. Open the Serial Monitor in the Arduino IDE.
4. Observe the raw sensor readings and the smoothed average values.

## Further Exploration

You can experiment with the code by changing the value of `numReadings` to see how it affects the filter's smoothness. A higher number of readings will result in a smoother output but may also introduce a slight lag in the response.



Feel free to contribute by suggesting improvements or by modifying the code for different applications.


**Author:**  
Er. Anoushka Tripathi

**Contact:**  
[LinkedIn](https://www.linkedin.com/in/anoushkastripathi/)




