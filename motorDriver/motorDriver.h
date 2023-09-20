#include <stdint.h>
#include "../incFiles/stm32f103x6.h"
#include "motorDriver/motorDriver.h"
#include "serialUart/serialUart.h"

void iniciarModulo(void);
void avanzar(uint8_t vel);
void retroceder(uint8_t vel);
void girarDerecha(void);
void girarIzquierda(void);
