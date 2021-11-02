#ifndef Display_h
#define Display_h

#define DEN_PORT                P3
#define DEN_PIN                 6
#define DEN_BIT                 (0x01 << DEN_PIN)
#define SET_DEN_AS_AN_OUTPUT    DEN_PORT->DIR |= DEN_BIT
#define TURN_ON_DEN             DEN_PORT->OUT |= DEN_BIT
#define TURN_OFF_DEN            DEN_PORT->OUT &= ~DEN_BIT

#define VSD_PORT                P7
#define VSD_PIN                 0
#define VSD_BIT                 (0x01 << VSD_PIN)
#define SET_VSD_AS_AN_OUTPUT    VSD_PORT->DIR |= VSD_BIT
#define TURN_ON_VSD             VSD_PORT->OUT |= VSD_BIT
#define TURN_OFF_VSD            VSD_PORT->OUT &= ~VSD_BIT

#define HSD_PORT                P3
#define HSD_PIN                 2
#define HSD_BIT                 (0x01 << HSD_PIN)
#define SET_HSD_AS_AN_OUTPUT    HSD_PORT->DIR |= HSD_BIT
#define TURN_ON_HSD             HSD_PORT->OUT |= HSD_BIT
#define TURN_OFF_HSD            HSD_PORT->OUT &= ~HSD_BIT

#define STBYB_PORT                P6
#define STBYB_PIN                 6
#define STBYB_BIT                 (0x01 << STBYB_PIN)
#define SET_STBYB_AS_AN_OUTPUT    STBYB_PORT->DIR |= STBYB_BIT
#define TURN_ON_STBYB             STBYB_PORT->OUT |= STBYB_BIT
#define TURN_OFF_STBYB            STBYB_PORT->OUT &= ~STBYB_BIT

#define PIXEL_PORT              P6
#define PIXEL_PIN               4
#define PIXEL_BIT               (0x01 << PIXEL_PIN)
#define SET_PIXEL_AS_AN_OUTPUT  PIXEL_PORT->DIR |= PIXEL_BIT
#define TURN_ON_PIXEL           PIXEL_PORT->OUT |= PIXEL_BIT
#define TURN_OFF_PIXEL          PIXEL_PORT->OUT &= ~PIXEL_BIT

class LCD_Display {
    public:
            void Write_Data();
            void Display_Init();
            void Display_Exit();
};
