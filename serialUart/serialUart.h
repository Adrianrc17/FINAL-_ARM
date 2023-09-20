#include <stdint.h>
#include "../incFiles/stm32f103x6.h"
#include "motorDriver/motorDriver.h"
#include "serialUart/serialUart.h"

void inicializarUart(void);
void enviarCaracter(uint8_t caracter);
void nuevaLinea(void);
void enviarPalabra(uint8_t cadena[]);




/*
Desarrollar el prototipo de las funciones: 
existeCaracter()
leerCaracter()
*/
int existeCaracter(void);
uint8_t leerCaracter(void);