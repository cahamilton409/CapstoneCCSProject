/* --COPYRIGHT--,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
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

#include <string.h>

#include "driverlib.h"

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/usb.h"                  // USB-specific functions
#include "USB_API/USB_HID_API/UsbHid.h"
#include "USB_app/keyboard.h"

#include "hal.h"
#include "Audio.h"
#include "Display.h"
#include "FlashMem.h"
#include "FSM.h"
#include "KeyPress.h"
#include "KeyPad.h"

void SendCurrentCharacterSet(void);
Button key;

void main (void)
{
    WDT_A_hold(WDT_A_BASE); // Stop watchdog timer

    PMM_setVCore(PMM_CORE_LEVEL_3); // Minumum Vcore setting required for the USB API is PMM_CORE_LEVEL_2 .
    USBHAL_initPorts();             // Config GPIOS for low-power (output low)
    USBHAL_initClocks(25000000);     // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz

    Flash_Memory_Init();
    Display_Init();
    Audio_Init();
    FSMType Key_Press_FSM;
    Key_Press_FSM_Init(&Key_Press_FSM);
    KeyPressInit();

    // ------------- Physical Keyboard --------------------------------
    InitKeypad();
    // ------------- Physical Keyboard --------------------------------

    Keyboard_init();                // Init keyboard report
    USB_setup(TRUE, TRUE);          // Init USB & events; if a host is present, connect

    __enable_interrupt();  // Enable global interrupts

    // Use LEDs for tracking the current language
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN7);
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN7);



    while (1)
    {
        // ------------- Physical Keyboard --------------------------------
        key = switch_press_scan();
        KeyPressInfo.KeyPressDetected = TRUE;
        if ((key == SpanishTab) || (key == FrenchTab)) KeyPressInfo.Action = ChangePage;
        else KeyPressInfo.Action = SendKey;
        KeyPressInfo.PressedKey = key;
        // ------------- Physical Keyboard --------------------------------


        // VERIFY THAT THE USB DEVICE IS PROPERLY CONNECTED.
        switch(USB_getConnectionState())
        {
            // WWHEN THE USB DEVICE IS PROPERLY CONNECTED, HANDLE INPUTS
            case ST_ENUM_ACTIVE:
                // IF THE DEVICE IS IDLE AND A KEY PRESS IS DETECTED, HANDLE IT ACCORDINGLY.
                if (KeyPressInfo.KeyPressDetected && (Key_Press_FSM.CurrentState == Idle)) {
                    // CHANGE THE PAGE IF THE USER SELECTED ANOTHER TAB.
                    if (KeyPressInfo.Action == ChangePage) {
                        Key_Press_FSM.CurrentState = ChangePage;
                        Play_Sound(ChangePage);
                        ChangeCurrentLanguage(KeyPressInfo.PressedKey);
                        Update_Display();
                        Key_Press_FSM.CurrentState = Idle;
                    }

                    // TYPE A KEY IF THE USER PRESSED A KEY.
                    else if (KeyPressInfo.Action == SendKey) {
                        Key_Press_FSM.CurrentState = SendKey;
                        Play_Sound(SendKey);
                        uint8_t SelectedCharacter = GetKeyFromButton(KeyPressInfo.PressedKey);
                        SpecialKeyPress(SelectedCharacter);
                        Key_Press_FSM.CurrentState = Idle;
                    }

                    // REARRANGE A KEY IF A USER HELD DOWN A KEY.
                    else if (KeyPressInfo.Action == MoveKey) {
                        Key_Press_FSM.CurrentState = MoveKey;
                        Play_Sound(MoveKey);
                        MoveKeyToFront(KeyPressInfo.PressedKey);
                        Update_Display();
                        Key_Press_FSM.CurrentState = MoveKey;
                    }
                }
                KeyPressInfo.KeyPressDetected = FALSE;
                if (CurrentLanguage == Spanish) {
                    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
                    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN7);
                }
                else {
                    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
                    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN7);
                }
                break;

            // WHEN THE USB DEVICE IS NOT PROPERLY CONNECTED, DON'T HANDLE INPUTS.
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

void SendCurrentCharacterSet(void) {
    uint8_t i;
    if (CurrentLanguage == Spanish) {
        for (i=0; i<NUM_SPANISH_CHARACTERS; i++) {
            SpecialKeyPress(SpanishCharacters[i]);
        }
    }

    if (CurrentLanguage == French) {
        for (i=0; i<NUM_FRENCH_CHARACTERS; i++) {
            SpecialKeyPress(FrenchCharacters[i]);
        }
    }
}

