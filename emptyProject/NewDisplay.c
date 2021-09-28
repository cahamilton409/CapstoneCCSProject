#include "driverlib.h"

void Display_Init() {
    SPI_Init();
    //init commands - active
    SPI_SEND(REG_HCYCLE |= 0x22400);
    SPI_SEND(REG_HOFFSET |= 0x2B00);
    SPI_SEND(REG_HYSNC0 |= 0x00);
    SPI_SEND(REG_HSYNC1 |= 0x29);
    SPI_SEND(REG_VCYCLE |= 0x12400);
    SPI_SEND(REG_VOFFSET |= 0xC00);
    SPI_SEND(REG_VSYNC0 |= 0x00);
    SPI_SEND(REG_VSYNC1 |= 0xA00);
    SPI_SEND(REG_SWIZZLE |= 0x00);
    SPI_SEND(REG_PCLK_POL |= 0x100);
    SPI_SEND(REG_SCPREAD |= 0x100);
    SPI_SEND(REG_HSIZE |= 0x1E000);
    SPI_SEND(REG_VSIZE |= 0x11000);

    SPI_SEND(RAM_DL |= 0x02111000);
    SPI_SEND((RAM_DL + 4) |= 0x26111000);
    SPI_SEND((RAM_DL + 8) |= 0x00000000);
    SPI_SEND(REG_DLSWAP |= 0x10);

    gpio_dir = SPI_READ(REG_GPIO_DIR);
    gpio = SPI_READ(REG_GPIO)
    SPI_SEND(REG_GPIO_DIR |= (0x80 | gpio_dir));
    SPI_SEND(REG_GPIO |= (0x080 | gpio));
    SPI_SEND(REG_PCLK |= 0x500)
}
