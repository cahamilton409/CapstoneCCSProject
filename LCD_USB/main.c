#include <audio.h>
#include <display.h>
#include <flash_memory.h>
#include <key_press.h>
#include <string.h>
#include <hal.h>

#include "driverlib.h"

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/usb.h"
#include "USB_API/USB_HID_API/UsbHid.h"
#include "USB_app/keyboard.h"

void main (void)
{
    // Stop the watchdog timer.
    WDT_A_hold(WDT_A_BASE);

    // Initialize the device.
    clock_init(8000000);
    key_press_init();
    flash_memory_init();
    display_init();
    audio_init();
    Keyboard_init();
    USB_setup(TRUE, TRUE);
    __enable_interrupt();

    while (1)
    {
        // Wait for touchscreen input from the user.
        wait_for_touch();
        play_sound();

        // Wait for the input to finish.
        wait_for_release();
        stop_sound();

        // If the USB connection is active, handle the input.
        uint8_t connection_status = USB_getConnectionState();
        if (connection_status == ST_ENUM_ACTIVE)
        {
            action_t current_action = g_key_press_info.action;
            // If the user selected a language tab, change the language accordingly.
            if (current_action == change_page)
            {
                change_current_language(g_key_press_info.pressed_key);
            }

            // If the user pressed a key, type the corresponding character.
            else if (current_action == send_key)
            {
                uint8_t selected_character = get_key_from_button(g_key_press_info.pressed_key);
                special_key_press(selected_character);
            }

            // If the user held down a key, move the selected key to the front and
            // store the new language mappings.
            else if (current_action == move_key)
            {
                move_key_to_front(g_key_press_info.pressed_key);
                save_mappings();
            }
        }
    }
}

