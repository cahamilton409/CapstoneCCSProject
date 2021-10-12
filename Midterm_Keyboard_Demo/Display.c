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

void Vertex_Select_Coordinate(int16_t X, int16_t Y) {
    //1/16th pixel scale coordinate
    int32_t coordinate = 0x10000000;
    coordinate |= (X << 4);
    coordinate |= Y;
    SPI_SEND(coordinate);
}

void Vertex_Select_Pixel(int8_t X, int8_t Y, int8_t handle, int8_t cell) {
    int32_t pixel = 0x20000000;
    pixel |= (X << 7);
    pixel |= (Y << 5);
    pixel |= (handle << 1);
    pixel |= cell;
    SPI_SEND(pixel);
}

void Begin(uint8_t prim) {
    //BITMAPS = 1
    //POINTS = 2
    //LINES = 3
    //LINE_STRIP = 4
    //EDGE_STRIP_R = 5
    //EDGE_STRIP_L = 6
    //EDGE_STRIP_A = 7
    //EDGE_STRIP_B = 8
    //RECTS = 9
    int32_t primitive = 0x1F000000;
    primitive |= prim;
    SPI_SEND(primitive);
}

void Set_Line_Width(int16_t width) {
    uint32_t size = 0x0E000000;
    size |= width;
    SPI_SEND(size);
}

void Send_Text(int16_t X, int16_t y, int16_t font, uint16_t options, const char* s) {

}
