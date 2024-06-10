#include <stdint.h>
#include <cstdio>
#include "main.h"

#define DEBUG

int main(void) {
 
  habilitarClockDoSistema();
  ConfiguracaoDasIO();




    while (1) {
        // Iniciar conversão ADC
        ADC1_CR |= ADC_CR_ADSTART;
        while (!(ADC1_ISR & ADC_ISR_EOC)); // Esperar fim da conversão
        int potValue = ADC1_DR; // Ler valor do ADC

        // Processar valor 
        if ((potValue > 2) && (potValue < 1000)) {
            potValue = 0;
        } else {
            potValue = 1023;
        }

        // Mapear valor para pulso
        int pulse = (potValue * (2000 - 1000) / 1023) + 1000;

        // Gerar pulso PWM para o servo
        GPIOB_BSRR = (1 << 5); 
        delayMicroseconds(pulse);
        GPIOB_BSRR = (1 << (5 + 16));
        delay(20 - (pulse / 1000));

#ifdef DEBUG

        // Imprimir valor do potenciômetro via UART
        char buffer[50];
        std::sprintf(buffer, "Valor do potenciômetro: %d\r\n", potValue);
        for (char* ptr = buffer; *ptr != '\0'; ptr++) {
            while (!(USART2_ISR & USART_ISR_TXE)); // Esperar buffer vazio
            USART2_TDR = *ptr;
        }
#endif // DEBUG
    }
}

void delayMicroseconds(uint32_t us) {
    uint32_t count = (16 * us); // Assumindo clock de 16 MHz
    while(count--) {
        __asm__ volatile ("nop");
    }
}

void delay(uint32_t ms) {
    while (ms--) {
        delayMicroseconds(1000);
    }
}

// Habilitar clocks
void habilitarClockDoSistema(void)
{
     
    RCC_AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_ADCEN;
    RCC_APB1ENR1 |= RCC_APB1ENR1_USART2EN;
}

void ConfiguracaoDasIO(void)
{
      // Configurar PA0 como entrada analógica (potenciômetro)
    GPIOA_MODER |= (3 << (0 * 2)); // PA0 em modo analógico

    // Configurar PB5 como saída (servo)
    GPIOB_MODER &= ~(3 << (5 * 2));
    GPIOB_MODER |= (1 << (5 * 2)); // PB5 em modo saída

    // Configurar ADC1
    ADC1_CR &= ~ADC_CR_ADEN;
    ADC1_SQR1 &= ~(15 << 0); // Limpar bits L (número de conversões)
    ADC1_SQR1 |= (0 << 6);    // Canal 0 na primeira conversão
    ADC1_CR |= ADC_CR_ADEN;   // Habilitar ADC
    while (!(ADC1_ISR & ADC_ISR_ADRDY)); // Esperar até que o ADC esteja pronto

    // Configurar USART2 para 9600 baud rate
    USART2_BRR = 16000000 / 9600; // Assumindo clock de 16 MHz
    USART2_CR1 = USART_CR1_UE | USART_CR1_TE; // Habilitar USART e transmissor
}