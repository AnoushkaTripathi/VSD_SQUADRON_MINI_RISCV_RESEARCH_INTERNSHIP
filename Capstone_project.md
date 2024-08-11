


# Low-Pass Filter Implementation on CH32V00x Microcontroller

This code demonstrates how to implement a low-pass filter using a CH32V00x microcontroller. It reads data from an Analog-to-Digital Converter (ADC), applies the filter, and sends the results via UART for communication.

## Components

1. **LowPass Class**
2. **USART Configuration**
3. **Timer Configuration**
4. **ADC Handling**
5. **Main Functionality**

### 1. LowPass Class

#### Purpose

The `LowPass` class implements a first-order low-pass filter using fixed-point arithmetic.

#### Constructor

```cpp
LowPass(uint16_t f0, uint16_t fs) {
    float omega0 = 2.0f * 3.14159265f * f0 / fs;
    float alpha = omega0 / (omega0 + 1);
    a1 = static_cast<int16_t>(-(1.0f - alpha) * 10000);
    b0 = static_cast<int16_t>(alpha * 10000);
    b1 = b0;
}
```

- **`f0`**: Cutoff frequency.
- **`fs`**: Sampling frequency.
- **Coefficients Calculation**: Computes the filter coefficients `a1`, `b0`, and `b1` based on the cutoff and sampling frequencies. These coefficients are scaled for fixed-point arithmetic.

#### Method `filt`

```cpp
int16_t filt(int16_t xn) {
    int16_t yn = a1 * y1 + b0 * xn + b1 * x1;
    x1 = xn;
    y1 = yn;
    return yn;
}
```

- **Inputs and Outputs**:
  - `xn`: Current input sample.
  - `yn`: Filtered output.
- **Function**: Applies the filter to the input sample and returns the filtered result.

### 2. USART Configuration

#### Function `USARTx_CFG`

```cpp
void USARTx_CFG(void) {
    // GPIO and USART initialization
}
```

- **Purpose**: Configures the USART1 peripheral for serial communication.
- **Steps**:
  - Initializes GPIO pins for USART TX and RX.
  - Sets USART parameters like baud rate, word length, stop bits, and mode.
  - Enables interrupts and sets priority for USART communication.

### 3. Timer Configuration

#### Function `Timer2_Init`

```cpp
void Timer2_Init() {
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    // Timer configuration
}
```

- **Purpose**: Configures Timer2 for microsecond timing.
- **Steps**:
  - Initializes Timer2 with a prescaler to achieve a 1 MHz frequency, providing 1 µs resolution.

### 4. ADC Handling

#### `setup` Function

```cpp
void setup() {
    USARTx_CFG();   // Setup UART for communication
    Timer2_Init();  // Initialize Timer 2 for microseconds timing

    // Configure ADC
    ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE); // Assuming you're setting up the ADC
}
```

- **Purpose**: Initializes UART and Timer2. Configures ADC to generate interrupts when conversion is complete.

#### `loop` Function

```cpp
void loop() {
    ADC_SoftwareStartInjectedConvCmd(ADC1, ENABLE); // Start ADC conversion

    while (!adcFlag) {} // Wait for ADC conversion to complete

    uint16_t analogValue = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);

    // Convert ADC reading to corresponding input signal (adjust based on your circuit)
    int16_t xn = (int16_t)(((analogValue * 325) / 1023 - 2503) * 1000 / 185);

    // Compute the filtered signal
    int16_t yn = lp.filt(xn);

    // Output the results
    char buffer[50];
    itoa(xn, buffer, 10);
    strcat(buffer, ", ");
    itoa(yn, buffer + strlen(buffer), 10);
    strcat(buffer, "\r\n");
    UartBufferSend((uint8_t*)buffer, strlen(buffer));

    Delay_Ms(200); // Replace with a suitable delay function
}
```

- **Purpose**: Performs ADC conversions, applies the low-pass filter to the data, and sends the results via UART.
- **Steps**:
  - Starts ADC conversion.
  - Waits for conversion to complete.
  - Reads and converts ADC value to an integer.
  - Applies the filter to the converted value.
  - Formats and sends the filtered data via UART.
  - Adds a delay to regulate the loop execution rate.

### 5. Utility Functions

#### `UartBufferSend`

```cpp
void UartBufferSend(uint8_t* buffer, uint16_t length) {
    for(uint16_t i = 0; i < length; i++) {
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData(USART1, buffer[i]);
    }
}
```

- **Purpose**: Sends data through UART.
- **Function**: Transmits each byte of data, waiting for the transmit buffer to be empty before sending the next byte.

#### `GetMicrosecondsFromTimer`

```cpp
uint32_t GetMicrosecondsFromTimer() {
    return TIM_GetCounter(TIM2) * (1.0 / (SystemCoreClock / 1000000));
}
```

- **Purpose**: Returns the current time in microseconds based on Timer2.
- **Function**: Retrieves the timer counter value and converts it to microseconds.



