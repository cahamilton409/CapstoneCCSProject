#ifndef Display_h
#define Display_h

#define DEN_HIGH (0x01 |= 34)
#define DEN_LOW  (0x00 &= 34)
#define CSX_HIGH (0x01 |= 4)
#define CSX_LOW  (0x00 &= 4)

//class LCD_Display {
//    public:
//            void Write_Data();
//            void Display_Init();
//};

void display_init(void);

void update_display(void);

void write_data();

#endif /*Display_h*/
