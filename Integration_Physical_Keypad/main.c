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

#include <audio.h>
#include <display.h>
#include <flash_memory.h>
#include <key_press.h>
#include <keypad.h>
#include <status_fsm.h>
#include <string.h>
#include <hal.h>

#include "driverlib.h"

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/usb.h"                  // USB-specific functions
#include "USB_API/USB_HID_API/UsbHid.h"
#include "USB_app/keyboard.h"


button_t key;
status_fsm_t status_fsm;


void main (void)
{
    WDT_A_hold(WDT_A_BASE); // Stop watchdog timer

    clock_init(25000000);     // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz

    flash_memory_init();
    display_init();
    audio_init();
    status_fsm_init(&status_fsm);
    key_press_init();

    // ------------- Physical Keyboard --------------------------------
    keypad_init();
    // ------------- Physical Keyboard --------------------------------

    Keyboard_init();                // Init keyboard report
    USB_setup(TRUE, TRUE);          // Init USB & events; if a host is present, connect

    __enable_interrupt();  // Enable global interrupts

    while (1)
    {
        // ------------- Physical Keyboard --------------------------------
        key = switch_press_scan();
        g_key_press_info.key_press_detected = TRUE;
        if ((key == spanish_tab) || (key == french_tab)) {g_key_press_info.action = change_page;}
        else {g_key_press_info.action = send_key;}
        g_key_press_info.pressed_key = key;
        // ------------- Physical Keyboard --------------------------------


        // VERIFY THAT THE USB DEVICE IS PROPERLY CONNECTED.
        switch(USB_getConnectionState())
        {
            // WWHEN THE USB DEVICE IS PROPERLY CONNECTED, HANDLE INPUTS
            case ST_ENUM_ACTIVE:
                // IF THE DEVICE IS IDLE AND A KEY PRESS IS DETECTED, HANDLE IT ACCORDINGLY.
                if (g_key_press_info.key_press_detected && (status_fsm.current_state == idle)) {
                    // CHANGE THE PAGE IF THE USER SELECTED ANOTHER TAB.
                    if (g_key_press_info.action == change_page) {
                        status_fsm.current_state = change_page;
                        play_sound(change_page);
                        change_current_language(g_key_press_info.pressed_key);
                        update_display();
                        status_fsm.current_state = idle;
                    }

                    // TYPE A KEY IF THE USER PRESSED A KEY.
                    else if (g_key_press_info.action == send_key) {
                        status_fsm.current_state = send_key;
                        play_sound(send_key);
                        uint8_t SelectedCharacter = get_key_from_button(g_key_press_info.pressed_key);
                        special_key_press(SelectedCharacter);
                        status_fsm.current_state = idle;
                    }

                    // REARRANGE A KEY IF A USER HELD DOWN A KEY.
                    else if (g_key_press_info.action == move_key) {
                        status_fsm.current_state = move_key;
                        play_sound(move_key);
                        MoveKeyToFront(g_key_press_info.pressed_key);
                        update_display();
                        status_fsm.current_state = move_key;
                    }
                }
                g_key_press_info.key_press_detected = FALSE;
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

