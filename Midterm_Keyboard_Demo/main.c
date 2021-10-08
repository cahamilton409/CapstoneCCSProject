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

/////////////////////////
#include "KeyPress.h"
/////////////////////////

/*********** Application specific globals **********************/
volatile uint8_t button1Pressed = FALSE;
volatile uint8_t button2Pressed = FALSE;
volatile uint8_t keySendComplete = TRUE;
uint8_t numSpanishCharacters;
uint8_t numFrenchCharacters;

/*  
 * ======== main ========
 */
void main (void)
{
    uint8_t i;
    WDT_A_hold(WDT_A_BASE); // Stop watchdog timer
    
    // INITIALIZATIONS INCLUDED WITH H8 KEYBOARD EXAMPLE.
    PMM_setVCore(PMM_CORE_LEVEL_3); // Minumum Vcore setting required for the USB API is PMM_CORE_LEVEL_2 .
    USBHAL_initPorts();             // Config GPIOS for low-power (output low)
    USBHAL_initClocks(25000000);     // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz
    USBHAL_initButtons();           // Init the two buttons
    Keyboard_init();                // Init keyboard report
    USB_setup(TRUE, TRUE);          // Init USB & events; if a host is present, connect

    __enable_interrupt();  // Enable global interrupts

    while (1)
    {
        // VERIFY THAT THE USB DEVICE IS PROPERLY CONNECTED.
        switch(USB_getConnectionState())
        {
            // WWHEN THE USB DEVICE IS PROPERLY CONNECTED, HANDLE INPUTS
            case ST_ENUM_ACTIVE:

                /************* HID keyboard portion ************************/
                if (button1Pressed) {
                    for (i=0; i<NUM_SPANISH_CHARACTERS; i++) {
                        SpecialKeyPress(SpanishCharacters[i]);
                    }
                }
                button1Pressed = FALSE;

                if (button2Pressed) {
                    for (i=0; i<NUM_FRENCH_CHARACTERS; i++) {
                        SpecialKeyPress(FrenchCharacters[i]);
                    }
                }
                button2Pressed = FALSE;
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
