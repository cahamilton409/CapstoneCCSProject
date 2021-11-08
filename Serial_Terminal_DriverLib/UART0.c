// UART0.c
// Runs on MSP432
// Busy-wait device driver for the UART UCA0.
// Daniel Valvano
// September 23, 2017
// Modified by EE345L students Charlie Gough && Matt Hawk
// Modified by EE345M students Agustinus Darmawan && Mingjie Qiu

/* This example accompanies the books
   "Embedded Systems: Introduction to the MSP432 Microcontroller",
       ISBN: 978-1512185676, Jonathan Valvano, copyright (c) 2017
   "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
       ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2017
   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
       ISBN: 978-1466468863, , Jonathan Valvano, copyright (c) 2017
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/

Simplified BSD License (FreeBSD License)
Copyright (c) 2017, Jonathan Valvano, All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of the FreeBSD Project.
*/

// UCA0RXD (VCP receive) connected to P1.2
// UCA0TXD (VCP transmit) connected to P1.3

#include <stdint.h>
#include <stdio.h>
#include "UART0.h"
#include <msp430.h>

//------------UART0_Init------------
// Initialize the UART for 115,200 baud rate (assuming 12 MHz SMCLK clock),
// 8 bit word length, no parity bits, one stop bit
// Input: none
// Output: none
void UART0_Init(void){
    P4SEL = BIT4 + BIT5;                        // P3.4,5 = USCI_A0 TXD/RXD
    P5SEL |= BIT4+BIT5;                         // Select XT1
    // Configure USCI_A0 for UART mode
    UCA1CTLW0 = UCSWRST;                      // Put eUSCI in reset

    UCA1CTLW0 |= UCSSEL__SMCLK;               // CLK = SMCLK
    // Baud Rate calculation
    // 25000000/(16*115200) = 13.6805
    // Fractional portion = 0.6805
    // Use Table 24-5 in Family User Guide
    UCA1BR0 = 13;                               // 25000000/16/9600
    UCA1BR1 = 0x00;
    UCA1MCTL |= UCOS16 | UCBRF_11 | UCBRS_0;

    UCA1CTLW0 &= ~UCSWRST;                    // Initialize eUSCI
    UCA1IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
}

//------------UART0_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART0_OutChar(char letter){
    while (!(UCA1IFG & UCTXIFG));
    UCA1TXBUF = letter;
}

//------------UART0_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART0_OutString(char *pt){
  while(*pt){
    UART0_OutChar(*pt);
    pt++;
  }
}

//-----------------------UART0_OutUDec-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Variable format 1-10 digits with no space before or after
void UART0_OutUDec(uint32_t n){
// This function uses recursion to convert decimal number
//   of unspecified length as an ASCII string
  if(n >= 10){
    UART0_OutUDec(n/10);
    n = n%10;
  }
  UART0_OutChar(n+'0'); /* n is between 0 and 9 */
}
uint32_t Messageindexb;
char Messageb[8];
void static fillmessageb(uint32_t n){
// This function uses recursion to convert decimal number
//   of unspecified length as an ASCII string
  if(n >= 10){
    fillmessageb(n/10);
    n = n%10;
  }
  Messageb[Messageindexb] = (n+'0'); /* n is between 0 and 9 */
  if(Messageindexb<7)Messageindexb++;
}
void static fillmessage4b(uint32_t n){
  if(n>=1000){  // 1000 to 9999
    Messageindexb = 0;
  } else if(n>=100){  // 100 to 999
    Messageb[0] = ' ';
    Messageindexb = 1;
  }else if(n>=10){ //
    Messageb[0] = ' '; /* n is between 10 and 99 */
    Messageb[1] = ' ';
    Messageindexb = 2;
  }else{
    Messageb[0] = ' '; /* n is between 0 and 9 */
    Messageb[1] = ' ';
    Messageb[2] = ' ';
    Messageindexb = 3;
  }
  fillmessageb(n);
}
void static fillmessage5b(uint32_t n){
  if(n>99999)n=99999;
  if(n>=10000){  // 10000 to 99999
    Messageindexb = 0;
  } else if(n>=1000){  // 1000 to 9999
    Messageb[0] = ' ';
    Messageindexb = 1;
  }else if(n>=100){  // 100 to 999
    Messageb[0] = ' ';
    Messageb[1] = ' ';
    Messageindexb = 2;
  }else if(n>=10){ //
    Messageb[0] = ' '; /* n is between 10 and 99 */
    Messageb[1] = ' ';
    Messageb[2] = ' ';
    Messageindexb = 3;
  }else{
    Messageb[0] = ' '; /* n is between 0 and 9 */
    Messageb[1] = ' ';
    Messageb[2] = ' ';
    Messageb[3] = ' ';
    Messageindexb = 4;
  }
  fillmessageb(n);
}
//-----------------------UART0_OutUDec4-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Fixed format 4 digits with no space before or after
void UART0_OutUDec4(uint32_t n){
  if(n>9999){
    UART0_OutString("****");
  }else{
    Messageindexb = 0;
    fillmessage4b(n);
    Messageb[Messageindexb] = 0; // terminate
    UART0_OutString(Messageb);
  }
}
//-----------------------UART0_OutUDec5-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Fixed format 5 digits with no space before or after
void UART0_OutUDec5(uint32_t n){
  if(n>99999){
    UART0_OutString("*****");
  }else{
    Messageindexb = 0;
    fillmessage5b(n);
    Messageb[Messageindexb] = 0; // terminate
    UART0_OutString(Messageb);
  }
}
//-----------------------UART0_OutUFix1-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// fixed format <digit>.<digit> with no space before or after
void UART0_OutUFix1(uint32_t n){
  UART0_OutUDec(n/10);
  UART0_OutChar('.');
  UART0_OutUDec(n%10);
}
//-----------------------UART0_OutUFix2-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// fixed format <digit>.<digit><digit> with no space before or after
void UART0_OutUFix2(uint32_t n){
  UART0_OutUDec(n/100);
  UART0_OutChar('.');
  n = n%100;
  UART0_OutUDec(n/10);
  UART0_OutUDec(n%10);
}

//--------------------------UART0_OutUHex----------------------------
// Output a 32-bit number in unsigned hexadecimal format
// Input: 32-bit number to be transferred
// Output: none
// Variable format 1 to 8 digits with no space before or after
void UART0_OutUHex(uint32_t number){
// This function uses recursion to convert the number of
//   unspecified length as an ASCII string
  if(number >= 0x10){
    UART0_OutUHex(number/0x10);
    UART0_OutUHex(number%0x10);
  }
  else{
    if(number < 0xA){
      UART0_OutChar(number+'0');
     }
    else{
      UART0_OutChar((number-0x0A)+'A');
    }
  }
}
//--------------------------UART0_OutUHex2----------------------------
// Output a 32-bit number in unsigned hexadecimal format
// Input: 32-bit number to be transferred
// Output: none
// Fixed format 2 digits with no space before or after
void outnibble(uint32_t n){
    if(n < 0xA){
   UART0_OutChar(n+'0');
  }
  else{
    UART0_OutChar((n-0x0A)+'A');
  }
}
void UART0_OutUHex2(uint32_t number){
  outnibble(number/0x10); // ms digit
  outnibble(number%0x10); // ls digit
}
