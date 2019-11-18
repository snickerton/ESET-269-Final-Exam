/* 
* Lab Partner Names:
* Lab #:
*/

/*Include files */
#include "MSP.h"
#include <stdio.h>
#include <stdlib.h>
#include "functionsDef.h"

/*Function Declarations*/
void OutputInit(void); 


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
