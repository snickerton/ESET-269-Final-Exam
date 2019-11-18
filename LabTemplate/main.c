/* 
* Lab Partner Names:
* Lab #:
*/

/*Include files */
#include "MSP.h"
#include <stdio.h>
#include <stdlib.h>

/*Function Declarations*/
void OutputInit(void); 

void PinEnable(int P4Pin)
{
    P1 -> SEL0 &= ~0x13;
    P1 -> SEL1 &= ~0x13;
    P2 -> SEL0 &= ~0x07;
    P2 -> SEL1 &= ~0x07;
    P4 -> SEL0 &= ~P4Pin;
    P4 -> SEL1 &= ~P4Pin;
    
    P1 -> DIR |= 0x01;    // RED LED is an output
    P1 -> DIR &= ~0x12;        // S1 and S2 are inputs
    P2 -> DIR |= 0x07;    // RGB LED is an output
    P4 -> DIR &= ~P4Pin;    // Temperature Sensor is an input
    
    P1 -> REN |= 0x12;   // Enable internal resistors on pins 1 and 4
    P1 -> OUT |= 0x12;    // Use Pull Up Resistor Configuration
}



void print(char* word){ // Tony Z.
			int i = 0;
			//print word
			while(word[i] != 0){
				EUSCI_A0 ->TXBUF = word[i];
				while((EUSCI_A0 -> IFG & 2)==0){
					//wait for buffer ready
				}
				i++;
			}
			//add enter at the end
			/*
				while((EUSCI_A0 -> IFG & 2)==0){
					//wait for buffer ready
				}
				
				EUSCI_A0 ->TXBUF = '\n';
				
				while((EUSCI_A0 -> IFG & 2)==0){
					//wait for buffer ready
				}
				EUSCI_A0 ->TXBUF = '\r';
				
				while((EUSCI_A0 -> IFG & 2)==0){
					//wait for buffer ready
				}*/
}
char* input(){ // Tony Z.
			char input[255];
			int i = 0;
			//loop through and receive each character unless entere
			while(1){
				if((EUSCI_A0 -> IFG & 1)!=0){
					input[i] = EUSCI_A0->RXBUF;
					EUSCI_A0 ->TXBUF = input[i];
						if(input[i] == '\r'){
							input[i] = '\0';
							
							//print out a newline if the user hits enter
							
							while((EUSCI_A0 -> IFG & 2)==0){
								//wait for buffer ready
							}
												
							EUSCI_A0 ->TXBUF = '\n';
							while((EUSCI_A0 -> IFG & 2)==0){
								//wait for buffer ready
							}
							EUSCI_A0 ->TXBUF = '\r';
							while((EUSCI_A0 -> IFG & 2)==0){
								//wait for buffer ready
							}
							break;
						}
						else{
							i++;
						}
				}
			}
			//return the character array address to pointer variable
			return input;
}

void RGBControl(){
	print("RGB Control function here\n\r");
}
void DigitalInput(){ //Tony Z.
			//check for all possible combinations of switch on or off
			if((P1 -> IN & 0x02) == 0x02 && (P1 -> IN & 0x10) == 0x10){
				print("No Buttons pressed. \n\r");
			}
			else if((P1 -> IN & 0x02) != 0x02 && (P1 -> IN & 0x10) == 0x10){
				print("Button 1 pressed.\n\r");
			}			
			else if((P1 -> IN & 0x02) == 0x02 && (P1 -> IN & 0x10) != 0x10){
				print("Button 2 pressed.\n\r");
			}
			else{
				print("Both Button pressed.\n\r");
			}
			print("\n\r");
}
void TemperatureReading(){
		print("Temperature Reading function here\n\r");
}

int main(void)
	{
    /*Setup Launchpad for Printf & Scanf*/
		EUSCI_A0 -> BRW = 115200;
		PinEnable(0);
		
		OutputInit(); 		
		
		/* Place application code here */
		//print("transmitUART1\n\r");
		//char* receive = input();	
		
		while(1){ //Tony Z.
			print("MSP432 Menu\n\r\n\r");
			print("1. RGB Control\n\r2. Digital Input\n\r3. Temperature Reading\n\r");
			print("\n\r	 *Backspaces will not work due to the nature of EUSCI*\n\r\n\r");
			//convert input choice from char array to integer
			int menuChoice = atoi(input());
			switch(menuChoice){
				case 1:
					RGBControl();
					break;
				case 2:
					DigitalInput();
					break;
				case 3:
					TemperatureReading();
					break;
				default:
					print("Not a valid menu choice\n\r\n\r");
			}
				
		}
		
		/*Go in waiting state. Will modify in later labs*/
		while(1);
  }
