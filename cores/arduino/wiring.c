/*
  wiring.c - Partial implementation of the Wiring API for the ATmega8.
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

  $Id$
*/

#include "wiring_private.h"

void delay(unsigned int ms)
{
	volatile unsigned int n;
#if defined(__AVR_ATtiny13__)
	for(n=0;n<ms;n++) delayMicroseconds(960);
#else
	for(n=0;n<ms;n++) delayMicroseconds(966);
#endif
}


/* Delay for the given number of microseconds.  Assumes a 8 or 16 MHz clock. */
void delayMicroseconds(unsigned int us)
{

	// calling avrlib's delay_us() function with low values (e.g. 1 or
	// 2 microseconds) gives delays longer than desired.
	//delay_us(us);
	// for the 8 MHz internal clock on the ATmega168

	// for a one- or two-microsecond delay, simply return.  the overhead of
	// the function calls takes more than two microseconds.  can't just
	// subtract two, since us is unsigned; we'd overflow.
	if (--us == 0)
		return;
	if (--us == 0)
		return;

	// the following loop takes half of a microsecond (4 cycles)
	// per iteration, so execute it twice for each microsecond of
	// delay requested.
	us <<= 1;
#if defined(__AVR_ATtiny13__)
	us += (us >> 3);
	us += (us >> 4); // near to 9.2
#endif
    
	// partially compensate for the time taken by the preceeding commands.
	// we can't subtract any more than this or we'd overflow w/ small delays.
	us--;

	// busy wait
#if defined(__AVR_ATtiny10__)

	volatile uint8_t ush;

	ush = (uint8_t)(0x00ff & (us>>8));

	__asm__ volatile (
		"     tst  %0"    "\n\t"
		"     brne lp1"   "\n\t"
		"lp2: dec  %1"    "\n\t"
		"lp1: dec  %0"    "\n\t"
		"     tst  %0"    "\n\t"
		"     brne lp1"   "\n\t"
		"     tst  %1"    "\n\t"
		"     brne lp2"
		:: "r" (us), "r" (ush)
	);

#else
	__asm__ volatile (
		"1: sbiw %0,1" "\n\t"
		"brne 1b"
		: "=w" (us)
		: "0" (us)
	);
#endif
}

void init()
{
#if defined(__AVR_ATtiny10__)
	//set clock internal 8MHz
//	CCP = 0xd8;
//	CLKMSR = 0x00;
	CCP = 0xd8;
	CLKPSR = 0x00;
#endif 

	sei();


}