#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <cstdio>

// Definições de registradores para STM32L433
#define RCC_BASE        0x40021000
#define GPIOA_BASE      0x48000000
#define GPIOB_BASE      0x48000400
#define ADC1_BASE       0x50040000
#define USART2_BASE     0x40004400

#define RCC_AHB2ENR     (*(volatile unsigned int *)(RCC_BASE + 0x4C))
#define RCC_APB1ENR1    (*(volatile unsigned int *)(RCC_BASE + 0x58))
#define GPIOA_MODER     (*(volatile unsigned int *)(GPIOA_BASE + 0x00))
#define GPIOA_PUPDR     (*(volatile unsigned int *)(GPIOA_BASE + 0x0C))
#define GPIOA_IDR       (*(volatile unsigned int *)(GPIOA_BASE + 0x10))
#define GPIOB_MODER     (*(volatile unsigned int *)(GPIOB_BASE + 0x00))
#define GPIOB_BSRR      (*(volatile unsigned int *)(GPIOB_BASE + 0x18))
#define ADC1_ISR        (*(volatile unsigned int *)(ADC1_BASE + 0x00))
#define ADC1_CR         (*(volatile unsigned int *)(ADC1_BASE + 0x08))
#define ADC1_SQR1       (*(volatile unsigned int *)(ADC1_BASE + 0x30))
#define ADC1_DR         (*(volatile unsigned int *)(ADC1_BASE + 0x40))
#define USART2_CR1      (*(volatile unsigned int *)(USART2_BASE + 0x00))
#define USART2_BRR      (*(volatile unsigned int *)(USART2_BASE + 0x0C))
#define USART2_ISR      (*(volatile unsigned int *)(USART2_BASE + 0x1C))
#define USART2_TDR      (*(volatile unsigned int *)(USART2_BASE + 0x28))

// Definições de bits
#define RCC_AHB2ENR_GPIOAEN   (1 << 0)
#define RCC_AHB2ENR_GPIOBEN   (1 << 1)
#define RCC_AHB2ENR_ADCEN     (1 << 13)
#define RCC_APB1ENR1_USART2EN (1 << 17)
#define ADC_ISR_ADRDY         (1 << 0)
#define ADC_ISR_EOC           (1 << 2)
#define ADC_CR_ADEN           (1 << 0)
#define ADC_CR_ADSTART        (1 << 2)
#define USART_CR1_UE          (1 << 0)
#define USART_CR1_TE          (1 << 3)
#define USART_ISR_TXE         (1 << 7)

// Funções
void delayMicroseconds(uint32_t us);
void delay(uint32_t ms);
void habilitarClockDoSistema(void);
void ConfiguracaoDasIO(void);

#endif // !MAIN_H