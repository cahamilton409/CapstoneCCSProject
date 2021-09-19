/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

#include "driverlib.h"

//******************************************************************************
//!
//!   Empty Project that includes driverlib
//!
//******************************************************************************
void main (void)
{
    WDT_A_hold(WDT_A_BASE); // Stop watchdog timer

   Clock_Init();

   Display_Init();
   Touchscreen_Init();
   Sound_Init();
   Language_FSM_Init();
   Key_Press_FSM_Init();

   USB_setup(TRUE, TRUE); // Init USB & events; if a host is present, connect

   __enable_interrupt();  // Enable global interrupts

    while(1) {

        switch(USB_getConnectionState())
        {
            // This case is executed while your device is enumerated on the USB host
            case ST_ENUM_ACTIVE:
                if (key_press_detected && (Key_Press_FSM.current_state == IDLE)) {
                    if (key_press_type == CHANGE_PAGE) {
                        Key_Press_FSM.Change_State(CHANGE_PAGE);
                        Play_Sound(CHANGE_PAGE);
                        Language_FSM.Change_State(key_press.language);
                        Update_Display();
                        Key_Press_FSM.Change_State(IDLE)
                    }

                    else if (key_press_type == SEND_KEY) {
                        Key_Press_FSM.Change_State(SEND_KEY);
                        Play_Sound(SEND_KEY);
                        Send_Key_Press(key_press);
                        while (Key_Press_Transmission_Active) {}
                        Key_Press_FSM.Change_State(IDLE);
                    }

                    else if (key_press_type == MOVE_KEY) {
                        Key_Press_FSM.Change_State(MOVE_KEY);
                        Play_Sound(MOVE_KEY);
                        Move_Key_To_Front(key_press);
                        Update_Display();
                        Key_Press_FSM.Change_State(MOVE_KEY);
                    }
                }
                break;

            // If the USB device is not properly connected, don't handle key presses.
            case ST_PHYS_DISCONNECTED:
            case ST_ENUM_SUSPENDED:
            case ST_PHYS_CONNECTED_NOENUM_SUSP:
                __bis_SR_register(LPM3_bits + GIE);
                _NOP();
                break;
            case ST_ENUM_IN_PROGRESS:
            default:;
        }
    }  //while(1)
} //main()
