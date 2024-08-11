#include "ch32v00x.h" // Include the appropriate CH32V library headers

volatile bool adcFlag = false;

class LowPass {
  private:
    int16_t a1, b0, b1;
    int16_t x1 = 0, y1 = 0;

  public:
   LowPass(uint16_t f0, uint16_t fs) {
        // Calculate coefficients (fixed-point)
        float omega0 = 2.0f * 3.14159265f * f0 / fs;
        float alpha = omega0 / (omega0 + 1);
        a1 = static_cast<int16_t>(-(1.0f - alpha) * 10000);
        b0 = static_cast<int16_t>(alpha * 10000);
        b1 = b0;
    }


    int16_t filt(int16_t xn) {
        int16_t yn = a1 * y1 + b0 * xn + b1 * x1;
        x1 = xn;
        y1 = yn;
        return yn;
    }
};

// Filter instance with fixed sample frequency
LowPass lp(3, 1000);

void USARTx_CFG(); // Declare the UART configuration function
void Timer2_Init(); // Declare the Timer2 initialization function

void setup() {
    USARTx_CFG();   // Setup UART for communication
    Timer2_Init();  // Initialize Timer 2 for microseconds timing

    // Configure ADC
    ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE); // Assuming you're setting up the ADC
}

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

// UART Configuration Function
void USARTx_CFG(void) {
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef  NVIC_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    /* USART1 TX-->D.5   RX-->D.6 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1, ENABLE);
}

void UartBufferSend(uint8_t* buffer, uint16_t length) {
    for(uint16_t i = 0; i < length; i++) {
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData(USART1, buffer[i]);
    }
}

// Implement this function to return the time in microseconds
uint32_t GetMicrosecondsFromTimer() {
    // Assuming TIM2 is used for timing purposes
    return TIM_GetCounter(TIM2) * (1.0 / (SystemCoreClock / 1000000)); // Assuming TIM2 is set up correctly
}

void Timer2_Init() {
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // Timer configuration
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
    TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / 1000000) - 1; // 1 MHz timer frequency (1 µs resolution)
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_Cmd(TIM2, ENABLE);
}
