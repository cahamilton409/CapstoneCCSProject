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
/*
 * ======== hal.c ========
 *
 */
#include "msp430.h"

#include "driverlib.h"

#include "USB_API/USB_Common/device.h"
#include "USB_config/descriptors.h"

#include "hal.h"
#include "KeyPress.h"

#define GPIO_ALL	GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3| \
					GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7

extern volatile uint8_t button1Pressed;
extern volatile uint8_t button2Pressed;

/*
 * This function drives all the I/O's as output-low, to avoid floating inputs
 * (which cause extra power to be consumed).  This setting is compatible with  
 * TI FET target boards, the F5529 Launchpad, and F5529 Experimenters Board;  
 * but may not be compatible with custom hardware, which may have components  
 * attached to the I/Os that could be affected by these settings.  So if using
 * other boards, this function may need to be modified.
 */
void USBHAL_initPorts(void)
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_ALL);

    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_ALL);

    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_ALL);

    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_ALL);

    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_ALL);

    GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_ALL);

    GPIO_setOutputLowOnPin(GPIO_PORT_P7, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_ALL);

    GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_ALL);

    GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_PJ, GPIO_ALL);
}

/* Configures the system clocks:
* MCLK = SMCLK = DCO/FLL = mclkFreq (expected to be expressed in Hz)
* ACLK = FLLref = REFO=32kHz
*
* XT2 is not configured here.  Instead, the USB API automatically starts XT2
* when beginning USB communication, and optionally disables it during USB
* suspend.  It's left running after the USB host is disconnected, at which
* point you're free to disable it.  You need to configure the XT2 frequency
* in the Descriptor Tool (currently set to 4MHz in this example).
* See the Programmer's Guide for more information.
*/
void USBHAL_initClocks(uint32_t mclkFreq)
{
	UCS_initClockSignal(
	   UCS_FLLREF,
	   UCS_REFOCLK_SELECT,
	   UCS_CLOCK_DIVIDER_1);

	UCS_initClockSignal(
	   UCS_ACLK,
	   UCS_REFOCLK_SELECT,
	   UCS_CLOCK_DIVIDER_1);

    UCS_initFLLSettle(
        mclkFreq/1000,
        mclkFreq/32768);
}

void USBHAL_initButtons(void)
{
	GPIO_setOutputHighOnPin(BUTTON1_PORT, BUTTON1_PIN);
	GPIO_setAsInputPinWithPullUpResistor(BUTTON1_PORT, BUTTON1_PIN);
	GPIO_clearInterrupt(BUTTON1_PORT, BUTTON1_PIN);
	GPIO_enableInterrupt(BUTTON1_PORT, BUTTON1_PIN);


	GPIO_setOutputHighOnPin(BUTTON2_PORT, BUTTON2_PIN);
	GPIO_setAsInputPinWithPullUpResistor(BUTTON2_PORT, BUTTON2_PIN);
	GPIO_clearInterrupt(BUTTON2_PORT, BUTTON2_PIN);
    GPIO_enableInterrupt(BUTTON2_PORT, BUTTON2_PIN);

}

/*
 * ======== Port1_ISR ========
 */
#if defined(__TI_COMPILER_VERSION__) || (__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt void Button1_ISR (void)
#elif defined(__GNUC__) && (__MSP430__)
void __attribute__ ((interrupt(PORT1_VECTOR))) Button1_ISR (void)
#else
#error Compiler not found!
#endif
{
    uint16_t i;

    if (GPIO_getInterruptStatus (BUTTON1_PORT, BUTTON1_PIN)){
        for (i = 0x23FF; i > 0; i--){ //Cheap debounce.
        }
        KeyPressInfo.KeyPressDetected = TRUE;
        KeyPressInfo.Action = ChangePage;
        if (CurrentLanguage == Spanish) KeyPressInfo.PressedKey = FrenchTab;
        else KeyPressInfo.PressedKey = SpanishTab;
        GPIO_clearInterrupt(BUTTON1_PORT, BUTTON1_PIN);
    }
}

/*
 * ======== Port2_ISR ========
 */
#if defined(__TI_COMPILER_VERSION__) || (__IAR_SYSTEMS_ICC__)
#pragma vector=PORT2_VECTOR
__interrupt void Button2_ISR (void)
#elif defined(__GNUC__) && (__MSP430__)
void __attribute__ ((interrupt(PORT2_VECTOR))) Button2_ISR (void)
#else
#error Compiler not found!
#endif
{
    uint16_t i;

    if (GPIO_getInterruptStatus (BUTTON2_PORT, BUTTON2_PIN)){
        for (i = 0x23FF; i > 0; i--){ //Cheap debounce.
        }
        KeyPressInfo.KeyPressDetected = TRUE;
        KeyPressInfo.Action = SendKey;
        KeyPressInfo.PressedKey = Key1;
        GPIO_clearInterrupt(BUTTON2_PORT, BUTTON2_PIN);
    }
}

/*
 * ======== UNMI_ISR ========
 */
#if defined(__TI_COMPILER_VERSION__) || (__IAR_SYSTEMS_ICC__)
#pragma vector = UNMI_VECTOR
__interrupt void UNMI_ISR (void)
#elif defined(__GNUC__) && (__MSP430__)
void __attribute__ ((interrupt(UNMI_VECTOR))) UNMI_ISR (void)
#else
#error Compiler not found!
#endif
{
    switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG))
    {
        case SYSUNIV_NONE:
            __no_operation();
            break;
        case SYSUNIV_NMIIFG:
            __no_operation();
            break;
        case SYSUNIV_OFIFG:
             UCS_clearFaultFlag(UCS_XT2OFFG);
            UCS_clearFaultFlag(UCS_DCOFFG);
            SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);
            break;
        case SYSUNIV_ACCVIFG:
            __no_operation();
            break;
        case SYSUNIV_BUSIFG:
            // If the CPU accesses USB memory while the USB module is
            // suspended, a "bus error" can occur.  This generates an NMI.  If
            // USB is automatically disconnecting in your software, set a
            // breakpoint here and see if execution hits it.  See the
            // Programmer's Guide for more information.
            SYSBERRIV = 0; //clear bus error flag
            USB_disable(); //Disable
    }
}



//Released_Version_5_20_06_02
