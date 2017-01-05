/* Tone.cpp

  A Tone Generator Library

  Written by Brett Hagman

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

Version Modified By Date     Comments
------- ----------- -------- --------
0001    B Hagman    09/08/02 Initial coding
0002    B Hagman    09/08/18 Multiple pins
0003    B Hagman    09/08/18 Moved initialization from constructor to begin()
0004    B Hagman    09/09/26 Fixed problems with ATmega8
0005    B Hagman    09/11/23 Scanned prescalars for best fit on 8 bit timers
                    09/11/25 Changed pin toggle method to XOR
                    09/11/25 Fixed timer0 from being excluded
0006    D Mellis    09/12/29 Replaced objects with functions
0007    M Sproul    10/08/29 Changed #ifdefs from cpu to register
0008    S Kanemoto  12/06/22 Fixed for Leonardo by @maris_HY
*************************************************/

#include <avr/interrupt.h>
#include "Arduino.h"

// timerx_toggle_count:
//  > 0 - duration specified
//  = 0 - stopped
//  < 0 - infinitely (until stop() method called, or new play() called)

volatile uint8_t timer0_pin_mask;
 
// frequency (in hertz) and duration (in milliseconds).

#if defined(__AVR_ATtiny10__)

void toneCycle(uint8_t _pin, unsigned int cycle)
{
  unsigned int toggle_count = 0;

  // Set the pinMode as OUTPUT
  pinMode(_pin, OUTPUT);

  if(cycle == 0){
     noTone(_pin);
     return;
  }
  cycle -=1;
  timer0_pin_mask = (1<<_pin);
  TCCR0A = 0;
  TCCR0B = (1<<WGM02) | (1<<CS00); // CTC mode , prescalar x1;

  // Set the OCR for the given timer,
  // set the toggle count,
  // then turn on the interrupts
  OCR0A = cycle;

  bitSet(TIMSK0, OCIE0A);
}

#else
//#endif

void tone(uint8_t _pin, unsigned int frequency)
{
  uint8_t prescalarbits = 0b001;
  unsigned int toggle_count = 0;
  uint32_t ocr = 0;

  // Set the pinMode as OUTPUT
  pinMode(_pin, OUTPUT);

  if(frequency == 0){
     noTone(_pin);
     return;
  }
  TCCR0A = (1 << WGM01);   // CTC mode
  timer0_pin_mask = (1<<_pin);

  // if we are using an 8 bit timer, scan through prescalars to find the best fit
  ocr = ((F_CPU / frequency)>>1);
  prescalarbits = 1;  // ck/1: same for both timers
  while((ocr > 256) && (prescalarbits < 5)){
    if(prescalarbits < 3) {
    	ocr >>= 3;
    } else {
    	ocr >>= 2;
    }
    prescalarbits++;    
  }

  ocr -= 1;

  TCCR0B = prescalarbits;

  // Set the OCR for the given timer,
  // set the toggle count,
  // then turn on the interrupts
  OCR0A = (uint8_t)ocr;
  bitSet(TIMSK0, OCIE0A);
}

#endif

// XXX: this function only works properly for timer 2 (the only one we use
// currently).  for the others, it should end the tone, but won't restore
// proper PWM functionality for the timer.
/*
void disableTimer()
{
        TIMSK0 = 0;
}
*/

void noTone(uint8_t _pin)
{
  bitClear(TIMSK0, OCIE0A); // disableTimer();
  bitClear(PORTB, _pin);  //  digitalWrite(_pin, 0);
}

ISR(TIM0_COMPA_vect)
{
  // toggle the pin
  PORTB ^= timer0_pin_mask;
}


