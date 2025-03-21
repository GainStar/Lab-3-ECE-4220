

/*  Important Note: 

 *      1. Compile this file using the command: gcc Lab3_W1.c -lwiringPi -lpthread -o Lab3_W1
 *      2. Run the program as a SUDO user: sudo ./Lab3_W1
 *  
 */

// http://wiringpi.com/reference/core-functions/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>
#include <stdint.h>
#include <sys/timerfd.h>
#include <time.h>			
#include <semaphore.h>
#include <wiringPi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define RED 2
#define YEL 3
#define GRE 4
#define BLE 5
#define BTN 16

int main(void){


    // Step-1
    // ------
    
    // Set-up of GPIO pins using WiringPi library
    if(wiringPiSetupGpio()!=0)
    {
        printf("WiringPiSetupGpio failed.\n");
        return -1;
    }

    pinMode(RED, OUTPUT);
    pinMode(YEL, OUTPUT);
    pinMode(GRE, OUTPUT);
    pinMode(BLE, OUTPUT);

    pinMode(BTN, INPUT);
    pullUpDnControl(BTN, PUD_DOWN);
    digitalWrite(BLE, LOW); // Turn off blue pedestrian light




    // Step-2
    // ------
	// Run a infinite while loop and turn on/off one light at a time.
    while(1)
    {
        digitalWrite(GRE, HIGH);
        digitalWrite(RED, LOW); 
        digitalWrite(YEL, LOW); 
        delay(2000); // Green light for 5 seconds



        if (digitalRead(BTN) == HIGH) 
        {
            digitalWrite(RED, HIGH);
            // Pedestrian button pressed, turn on pedestrian red light
            digitalWrite(GRE, LOW);
            digitalWrite(YEL, LOW);
            delay(3000);  // Pedestrian signal for 3 seconds
            digitalWrite(RED, LOW);


        }


        // Turn on yellow light for direction 1 (transition)
        digitalWrite(GRE, LOW);
        digitalWrite(YEL, HIGH);
        digitalWrite(BLE, LOW);
        delay(1000); // Yellow light for 1 second

        // Check if pedestrian button was pressed
        if (digitalRead(BTN) == HIGH) 
        {
            digitalWrite(RED, HIGH);
            // Pedestrian button pressed, turn on pedestrian light
            digitalWrite(GRE, LOW);
            digitalWrite(YEL, LOW);
            delay(3000);  // Pedestrian signal for 3 seconds
            digitalWrite(RED, LOW);

        }

    }
    




	return 0;
}
