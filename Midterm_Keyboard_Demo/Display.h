#ifndef Display_h
#define Display_h

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

class LCD_Display {
    public:
            void Display_Init();
            void Vertex_Select_Coordinate(int16_t X, int16_t Y);
            void Vertex_Select_Pixel(int8_t X, int8_t Y, int8_t handle, int8_t cell);
            void Begin(int8_t prim);
            void Set_Line_Width(int16_t width);
            void Send_Character_at_Vertex(int16_t X, int16_t Y, int16_t font, char s);
            void Create_Button_Center_Length_Thickness_Character(int16_t X, int16_t Y, int16_t length, int16_t thickness, char character);
            void Create_Grid_Given_Points(int16_t[] X_coords, int16_t[] Y_coords, int16_t length, char[] characters);
};
