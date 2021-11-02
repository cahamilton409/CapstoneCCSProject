#include <Display.h>

void Write_Data() {
    TURN_ON_DEN;
    //stay here til interrupts reach 800
    //switch VSD and HSD to select pixels
    //at this point all pixels should be written
    TURN_OFF_DEN;
}

void Display_Init() {
    SET_DEN_AS_AN_OUTPUT;
    SET_VSD_AS_AN_OUTPUT;
    SET_HSD_AS_AN_OUTPUT;
    SET_STBYB_AS_AN_OUTPUT;
    SET_PIXEL_AS_AN_OUTPUT;
    TURN_ON_STBYB;
}

void Display_Exit() {
    TURN_OFF_STBYB;
}
