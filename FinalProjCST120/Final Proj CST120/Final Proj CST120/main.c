/*
 * Final Project CST120.c
 *
 * Created: 6/3/2023 6:19:12 PM
 * Author : Zaelfenn Sandow
 *
 *
 *	The purpose of this project is to be a sort of Simon-esque game. There will be 
 *	a randomly generated pattern created by the computer, which the player will have
 *	to follow. The player will use a combination of a button and a potentiometer to 
 *	select their buttons. If the pattern they select is successful, then they will 
 *	get a new pattern. If the patten they choose is wrong, a piezzo buzzer will sound,
 *	and they will have to restart.
 *
 *
 */ 

#include <util/delay.h> //used for delay
#include <avr/io.h>
#include <avr/interrupt.h> //global interrupts
 //#include <stdlib.h> //used for random number generation
 
//the colors RED, YELLOW, BLUE, GREEN are the colors of the LEDS, and each value corresponds to the position on the board
#define RED 8 //1 shifted over 3 times
#define YELLOW 4 //1 shifted over 2 times
#define BLUE 2 //1 shifted over 1 times
#define GREEN 1 //1 shifted over 0 times


#define COUNT_VAL 3 //used for button debounce

int debouncedSw = 0; //a flag for when the button is debounced
int swChanged = 0; //a flag for if the button was pressed

int numColor = 1; //the number of colors that will be displayed

int playTone = 0; //flag to play the note of failure
int duration = 200;//time to play the note
int toneDone = 0; //flag for when the tone should stop



int main(void)
{
	DDRD = (1 << DDD2) | (1 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD7); //set all these bits for output, allowing LEDs(ports 2,3,4,5) to shine and the buzzer to buzz
	//these will be the computer lights
	
	DDRB =  (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3); //set all these bits for output, allowing LEDs(ports 0,1,2,3) to shine
	//these will be the player lights
	
	
	PORTD = (1 << PORTD6); //button pullup resistor on portb0 (digital pin 8)
	
	TCNT0 = 0; //initialize timer 0
	
	TIMSK0 = ((1 << OCIE0A) | (1 << TOIE0)); //enable interrupts on timer compare A and timer overflow
	sei(); //enable global interrupts
	
	OCR0A = 89; //the note to play on the buzzer
	
	TCCR0B = 4; //start timer 4 in normal mode w/ prescaler of 256
	
	ADCSRA = (1 << ADEN) | (7 << ADPS0) | (1 << ADATE); //enable ADC (1 to ADEN), set the prescaler to 128 (7 to ADPS0)
	//and set the ADC to auto trigger enable/free running mode (1 to ADATE)
	
	ADMUX = (0 << MUX0) | (1 << REFS0) | (1 << ADLAR); //connect ADC to analog pin 0 (0 << MUX0), enable AVCC(1 to REFS0), 
	//and left adjust value of the bits in the register (1 to ADLAR)
	
	ADCSRA |= (1 << ADSC); //start the conversions!
	
	
	uint8_t colors[6] = {RED,BLUE,GREEN,YELLOW,RED,GREEN}; //these are the possible colors for the LED to display, with a bias against blue and yellow because 4 is difficult to create
		//patterns that incorporate all 4 LEDs and 6 is a fun number
	uint8_t compPattern[30]; //there will be 30 colors in the computers pattern
	
	for (int i = 0; i < 30; i++){ //set all the computers pattern to 0
		compPattern[i] = 0;
	}
	
	 
	while (1) 
    {
		int done = 0;
		int playerCount = 0; //the number of colors that the player has inputted
		int reset = 0;
		int r = (numColor * numColor * numColor) % 6; //predictable generated pattern yet still a bit complex
		compPattern[numColor - 1] = colors[r]; //set the next color in the pattern 
		
		for (int i = 0; i < numColor; i++){
			PORTD |= (compPattern[i] << PORTD2); //display the corresponding LED with the pattern
			_delay_ms(500); //small delay for each color
			PORTD &= ~(0xF << PORTD2); //clear the LEDs while not messing with the other bits
			_delay_ms(250); //small delay for the clear
		}
		while(!done){ //while not done, which is also set upon a reset
			int colorValue = GREEN; //default value of green (ADCH 0 - 64)
			while(!(ADCSRA & (1 << ADIF))); //wait for the ADC interrupt flag to be set
			ADCSRA |= (1 << ADIF); //unset the interrupt flag
			
			if (ADCH < 64){ //if the value of the ADCH is less than 64 (first quadrant)
				PORTB = (1 << PORTB0); //set the green light off
			} //color value is default green
			else if (ADCH < 128){ //if the value of the ADCH is between 64 and 128 (second quadrant)
				colorValue = BLUE; //set the color value to blue
				PORTB = (1 << PORTB1); //turn on the blue light
			}
			else if (ADCH < 192){ //if the value of the ADCH is between 128 and 192 (third quadrant)
				colorValue = YELLOW; //set the color value to yellow
				PORTB = (1 << PORTB2); //turn on the yellow light
			}
			else{ //if the value of the ADCH is between 192 and 256 (fourth quadrant)
				colorValue = RED; //set the color value to red
				PORTB = (1 << PORTB3); //turn on the red light
			}
	
	
			if (swChanged){ //if the button changed states
				swChanged = 0; //unset the changed flag
				if (debouncedSw == 0){ //if the button is up
					if (colorValue != compPattern[playerCount]){ //if the color value does not match the color value of the computers pattern
						playTone = 1; //set the playTone flag
						TCNT0 = 0; //reset the timer
						while(!toneDone); //play the tone
						reset = 1;
					}
					playerCount++; //increment the player count
				} //end of if (!debouncedSw)
			} //end of if(swChanged)
			
		if (reset){
			for (int i = 0; i < numColor; i++){
				compPattern[i] = 0;
			}
			numColor = 0; //numColor incremented after while loop
			playerCount = 0; //reset the player count
			
		}
		if (numColor == playerCount){ //if they are the same
			done = 1; //set the done flag
		}
		} //end of while(!reset && numColors != playerCount)
		
	numColor++; //increment the number of colors
	
	}//end of while(1)
} //end of main








/*
	The interrupt service routine for when the timer overflows will be used for a button debounce.
	It is passed the Timer0 overflow vector, and returns nothing. This process is initiated anytime
	the timer overflows.
*/
ISR(TIMER0_OVF_vect){	
	static uint8_t currSw; //state of the switch
	static uint8_t count = COUNT_VAL; //counting overflows for a debounce
	
	
	currSw = !!(PIND & (1 << PIND6)); //value of the buttons pin
	
	if (currSw == debouncedSw){ //if the state of the switch has not changed
		count = COUNT_VAL; //reset the count
	}
	else {
		count--; //otherwise, decrement the count
	}
	
	if (count == 0) { //if the count hits 0
		debouncedSw = currSw; //debounced switch shares the value of the current switch
		swChanged = 1; //set the changed flag
		count = COUNT_VAL; //reset the count
	}
}


/*
	The interrupt service routine for timer 0 will play a note, and returns nothing.
*/
ISR(TIMER0_COMPA_vect){
	if(playTone){ //if the tone is to be played
		PIND = (1 << PIND7); //toggle the pin of the piezzo buzzer
	}

	duration--; //subtract one from the duration
	if (duration <= 0){ //if it is done
		toneDone = 1; //flag the toneDone
		duration = 200; //reset duration
		playTone = 0; //mark the 
	}
}