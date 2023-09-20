#include <stdint.h>
#include "incFiles/stm32f103x6.h"
#include "motorDriver/motorDriver.h"
#include "serialUart/serialUart.h"

int main(void) {
    char caracter;

    while (1) {
        if (existeCaracter()) {  // Verifica si existe un carácter
            caracter = leerCaracter();  // Lee el carácter

            switch (caracter) {  // Ejecuta una acción dependiendo del carácter
                case 'a':
                    avanzar(1);
                    break;
                case 'w':
                    avanzar(2);
                    break;
                case 'b':
                    retroceder(1);
                    break;
                case 's':
                    retroceder(2);
                    break;
                case 'q':
                    girarDerecha();
                    break;
                case 'e':
                    girarIzquierda();
                    break;
                default:
                    // No hace nada si el carácter no es 'a', 'w', 'b', 's', 'q' o 'e'
                    break;
            }
        }
    }

    return 0;
}