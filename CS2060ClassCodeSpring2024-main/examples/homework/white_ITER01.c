//Project iteration 01 - UCCS RIDE SHARE
//description goes here

#include <stdio.h>
#include <stdbool.h>

#define MIN_MILES 1
#define MAX_MILES 100

//Tell C that these functions exist
double getUserMiles();

// function main
int main (void) {

	//Initialize Variables
	double userMiles = 0; //How many miles the user inputs to ride

	// Part 1: Get miles input from user
	puts("Welcome to the UCCS Ride Share!");
	puts("How many miles will your ride be today?");
	userMiles = getUserMiles();

}

// function getUserMiles
double getUserMiles() {

	// Initialize Variables
	bool dataIsGood = false;
	double userInput = 0;

	do {

		printf("Input miles: (%d - %d)", MIN_MILES, MAX_MILES);
		int scanfReturn = scanf("%lf", &userInput);
		while ((getchar()) != '\n');

		if (scanfReturn == 1) {

			if (userInput > MAX_MILES || userInput < MIN_MILES) {
				puts("Bad");
			}
			else {
				puts("Good");
				dataIsGood = true;
			}
		}
		else {
			puts("Bad");
		}

	} while (!dataIsGood);
}

// function estimateMinutes
double estimateMinutes() {

}

// function calculateCharge
double calculateCharge() {

}

// function endProgram
void endProgram() {

}