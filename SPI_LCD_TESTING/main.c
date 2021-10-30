#include "SPI_LCD.h"
#include "Display.h"

//extern uint8_t ACTIVE[3] = {0x00, 0x00, 0x00};
//extern uint8_t CLKEXT[3] = {0x44, 0x00, 0x00};

int main(void) {
    SPI_Init();

    Display_Init();

    return 0;
}
