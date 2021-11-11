#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

//
//DISPLAY.H DEFINES
//
//Below the registers on the LCD are defined.
#define REG_HCYCLE      0x2C
#define REG_HOFFSET     0x30
#define REG_HSYNC0      0x38
#define REG_HSYNC1      0x3C
#define REG_VCYCLE      0x40
#define REG_VOFFSET     0x44
#define REG_VSYNC0      0x4C
#define REG_VSYNC1      0x50
#define REG_SWIZZLE     0x64
#define REG_PCLK_POL    0x6C
#define REG_CSPREAD     0x68
#define REG_HSIZE       0x34
#define REG_VSIZE       0x48
#define REG_DLSWAP      0x54
#define REG_GPIO_DIR    0x90
#define REG_GPIO        0x94
#define REG_PCLK        0x70
#define RAM_DL          0x100
#define REG_GPIO        0x90
#define REG_GPIO_DIR    0x98

//Below are the different params of begin() commands for the LCD.
#define BITMAPS         1
#define POINTS          2
#define LINES           3
#define LINE_STRIP      4
#define EDGE_STRIP_R    5
#define EDGE_STRIP_L    6
#define EDGE_STRIP_A    7
#define EDGE_STRIP_B    8
#define RECTS           9
