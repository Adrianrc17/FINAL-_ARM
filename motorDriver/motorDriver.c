#include "motorDriver.h"
#include "motorDriver/motorDriver.h"
#include "serialUart/serialUart.h"


/*
Implementar el codigo fuente de las fuciones
iniciarModulo(),
avanzar(),
retroceder(),
girarDerecha(),
girarIzquierda()

*/
void iniciarModulo(void) {
    // Habilita la señal de reloj para el puerto GPIOA, GPIOC, UART4 y funciones alternas
    RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;

    // Configura los puertos PA4, PA5, PA6, PA7 y PC13 como salidas digitales y deja sus valores iniciales en LOW (0 Volt)
    GPIOA->CRL &= ~(GPIO_CRL_MODE4 | GPIO_CRL_MODE5 | GPIO_CRL_MODE6 | GPIO_CRL_MODE7);
    GPIOA->ODR &= ~(GPIO_ODR_ODR4 | GPIO_ODR_ODR5 | GPIO_ODR_ODR6 | GPIO_ODR_ODR7);
    GPIOC->CRH &= ~GPIO_CRH_MODE13;
    GPIOC->ODR &= ~GPIO_ODR_ODR13;

    // Configura los puertos PB8 y PB9 como salidas digitales de funciones alternas
    GPIOB->CRH |= (GPIO_CRH_MODE8 | GPIO_CRH_MODE9);
    GPIOB->CRH &= ~(GPIO_CRH_CNF8_0 | GPIO_CRH_CNF9_0);
    GPIOB->CRH |= (GPIO_CRH_CNF8_1 | GPIO_CRH_CNF9_1);

    // Configura el timer de acuerdo a lo revisado en clase
    TIM4->CCMR2 = ((0x68 << 8) | (0x68 << 0));
    TIM4->BDTR |= TIM_BDTR_MOE;
    TIM4->CCER |= (TIM_CCER_CC4E | TIM_CCER_CC3E);
    TIM4->PSC = 7;
    TIM4->ARR = 999;  // Ajusta este valor para generar una onda PWM de 100Hz de frecuencia
    TIM4->CCR4 = 0;
    TIM4->CCR3 = 0;
    TIM4->CR1 |= (TIM_CR1_ARPE | TIM_CR1_CEN);
}

void avanzar(uint8_t vel) {
    GPIOA->ODR |= (GPIO_ODR_ODR5 | GPIO_ODR_ODR6);  // Coloca los puertos PA5 y PA6 en alta
    GPIOA->ODR &= ~(GPIO_ODR_ODR4 | GPIO_ODR_ODR7);  // Coloca los puertos PA4 y PA7 en baja
    TIM4->CCR3 = TIM4->CCR4 = (vel == 1 ? 500 : 1000);  // Configura el ciclo de trabajo de las ondas PWM para PB8 y PB9
    HAL_Delay(1000);  // Espera 1 segundo
    TIM4->CCR3 = TIM4->CCR4 = 0;  // Coloca 0% de ciclo de trabajo en las ondas PWM de PB8 y PB9
}

void retroceder(uint8_t vel) {
    GPIOA->ODR &= ~(GPIO_ODR_ODR5 | GPIO_ODR_ODR6);  // Coloca los puertos PA5 y PA6 en baja
    GPIOA->ODR |= (GPIO_ODR_ODR4 | GPIO_ODR_ODR7);  // Coloca los puertos PA4 y PA7 en alta
    TIM4->CCR3 = TIM4->CCR4 = (vel == 1 ? 500 : 1000);  // Configura el ciclo de trabajo de las ondas PWM para PB8 y PB9
    HAL_Delay(1000);  // Espera 1 segundo
    TIM4->CCR3 = TIM4->CCR4 = 0;  // Coloca 0% de ciclo de trabajo en las ondas PWM de PB8 y PB9
}

void girarDerecha(void) {
    GPIOA->ODR &= ~(GPIO_ODR_ODR5 | GPIO_ODR_ODR7);  // Coloca los puertos PA5 y PA7 en baja
    GPIOA->ODR |= (GPIO_ODR_ODR4 | GPIO_ODR_ODR6);  // Coloca los puertos PA4 y PA6 en alta
    TIM4->CCR3 = TIM4->CCR4 = 500;  // Genera una onda PWM de 50% de ciclo de trabajo
    HAL_Delay(1000);  // Espera 1 segundo
    TIM4->CCR3 = TIM4->CCR4 = 0;  // Coloca 0% de ciclo de trabajo en las ondas PWM de PB8 y PB9
}

void girarIzquierda(void) {
    GPIOA->ODR |= (GPIO_ODR_ODR5 | GPIO_ODR_ODR7);  // Coloca los puertos PA5 y PA7 en alta
    GPIOA->ODR &= ~(GPIO_ODR_ODR4 | GPIO_ODR_ODR6);  // Coloca los puertos PA4 y PA6 en baja
    TIM4->CCR3 = TIM4->CCR4 = 500;  // Genera una onda PWM de 50% de ciclo de trabajo
    HAL_Delay(1000);  // Espera 1 segundo
    TIM4->CCR3 = TIM4->CCR4 = 0;  // Coloca 0% de ciclo de trabajo en las ondas PWM de PB8 y PB9
}