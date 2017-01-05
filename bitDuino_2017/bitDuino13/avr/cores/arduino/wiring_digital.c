/*
  wiring_digital.c - digital input and output functions
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

#define ARDUINO_MAIN
#include "wiring_private.h"
// #include "pins_arduino.h"

#if defined(__AVR_ATtiny10__)
void pinMode(uint8_t pin, uint8_t mode)
{
	if (pin > 3) return;

	if (pin < 4) DIDR0 &= ~(1 << pin);	// Digital Input Disable Register 0

	if (mode == INPUT) { 
		uint8_t oldSREG = SREG;
                cli();
		DDRB &= ~(1<<pin);
		PUEB &= ~(1<<pin);		// Pull-up Enable Control Register
		SREG = oldSREG;
	} else if (mode == INPUT_PULLUP) {
		uint8_t oldSREG = SREG;
                cli();
		DDRB &= ~(1<<pin);
		PUEB |= (1<<pin);		// Pull-up Enable Control Register
		SREG = oldSREG;
	} else {
		uint8_t oldSREG = SREG;
                cli();
		PUEB &= ~(1<<pin);		// Pull-up Enable Control Register
		DDRB |= (1<<pin);
		SREG = oldSREG;
	}
}

#else

void pinMode(uint8_t pin, uint8_t mode)
{
	if (pin > 4) return;

	if (mode == INPUT) { 
		uint8_t oldSREG = SREG;
                cli();
		DDRB &= ~(1<<pin);
		PORTB &= ~(1<<pin); 
		SREG = oldSREG;
	} else if (mode == INPUT_PULLUP) {
		uint8_t oldSREG = SREG;
                cli();
		DDRB &= ~(1<<pin);
		PORTB |= (1<<pin);
		SREG = oldSREG;
	} else {
		uint8_t oldSREG = SREG;
                cli();
		DDRB |= (1<<pin);
		SREG = oldSREG;
	}
}
#endif


void digitalWrite(uint8_t pin, uint8_t val)
{
	if (pin == 0) cbi(TCCR0A, COM0A1); //turnOffPWM(TIMER0A);
	if (pin == 1) cbi(TCCR0A, COM0B1); //turnOffPWM(TIMER0B);

	uint8_t oldSREG = SREG;
	cli();

	if (val == LOW) {
		PORTB &= ~(1<<pin);
	} else {
		PORTB |= (1<<pin);
	}

	SREG = oldSREG;
}

int digitalRead(uint8_t pin)
{
#if defined(__AVR_ATtiny10__)
	if (pin < 4) DIDR0 &= ~(1 << pin);	// Digital Input Disable Register 0
#endif

	if (pin == 0) cbi(TCCR0A, COM0A1); //turnOffPWM(TIMER0A);
	if (pin == 1) cbi(TCCR0B, COM0A1); //turnOffPWM(TIMER0B);

	if (PINB & (1<<pin)) return HIGH;
	return LOW;
}
