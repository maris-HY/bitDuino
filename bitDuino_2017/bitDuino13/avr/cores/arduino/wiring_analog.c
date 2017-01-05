/*
  wiring_analog.c - analog input and output
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  Modified 28 September 2010 by Mark Sproul

  $Id: wiring.c 248 2007-02-03 15:36:30Z mellis $
*/

#include "wiring_private.h"
#include "pins_arduino.h"


void analogReference(uint8_t mode)
{
	// can't actually set the register here because the default setting
	// will connect AVCC and the AREF pin, which would cause a short if
	// there's something connected to AREF.
	ADMUX = (mode << 6) ;
}

int analogRead(uint8_t pin)
{
#if defined(__AVR_ATtiny10__)
#else
	uint8_t low, high;
#endif	
	if(bit_is_clear(ADCSRA, ADEN)){
		// set a2d prescale factor to 128
		// 16 MHz / 128 = 125 KHz, inside the desired 50-200 KHz range.
		// XXX: this will not work properly for other clock speeds, and
		// this code should use F_CPU to determine the prescale factor.

		// enable a2d conversions

		ADCSRA |= 0x87; // ADEN , ACPS2,ADPS1,SDPS0
		ADMUX = 0;
	}
	  
	// set the analog reference (high two bits of ADMUX) and select the
	// channel (low 4 bits).  this also sets ADLAR (left-adjust result)
	// to 0 (the default).

	ADMUX = ((ADMUX & 0x40) | (pin & 0x03));
#if defined(__AVR_ATtiny10__)
	DIDR0 |= (1 << pin);
#endif
	// without a delay, we seem to read from the wrong channel
	// delay(1);

	// start the conversion
	sbi(ADCSRA, ADSC);

	// ADSC is cleared when the conversion finishes
	while (bit_is_set(ADCSRA, ADSC));

	// we have to read ADCL first; doing so locks both ADCL
	// and ADCH until ADCH is read.  reading ADCL second would
	// cause the results of each conversion to be discarded,
	// as ADCL and ADCH would be locked when it completed.

#if defined(__AVR_ATtiny10__)
	return (ADCL << 2);
#else
	low  = ADCL;
	high = ADCH;

	// combine the two bytes
	return (high << 8) | low;
#endif
}

// Right now, PWM output only works on the pins with
// hardware support.  These are defined in the appropriate
// pins_*.c file.  For the rest of the pins, we default
// to digital output.

void analogWrite(uint8_t pin, int val)
{
	// We need to make sure the PWM output is enabled for those pins
	// that support it, as we turn it off when digitally reading or
	// writing with them.  Also, make sure the pin is in output mode
	// for consistenty with Wiring, which doesn't require a pinMode
	// call for the analog output pins.
	pinMode(pin, OUTPUT);
	if (val == 0)
	{
		digitalWrite(pin, LOW);
	}
	else if (val == 255)
	{
		digitalWrite(pin, HIGH);
	}
	else
	{
		// set timer 0 fast hardware pwm

#if defined(__AVR_ATtiny10__)
		TCCR0A |= 0x01; //set WGM00
//		TCCR0B |= 0x08; //set WGM02
#elif defined(TCCR0A) && defined(WGM01)
		TCCR0A |= 0x03; //set WGM01,WGM00
#endif

		// set timer 0 prescale factor to 64
		TCCR0B = ((TCCR0B & 0xF8) | 0x03); //clear CS02, set CS01,CS00
	
		switch(pin)
		{

			case 0:
				// connect pwm to pin on timer 0, channel A
				sbi(TCCR0A, COM0A1);
				OCR0A = val; // set pwm duty
				break;

			case 1:
				// connect pwm to pin on timer 0, channel B
				sbi(TCCR0A, COM0B1);
				OCR0B = val; // set pwm duty
				break;
			default:
				if (val < 128) {
					digitalWrite(pin, LOW);
				} else {
					digitalWrite(pin, HIGH);
				}
		}
	}
}

