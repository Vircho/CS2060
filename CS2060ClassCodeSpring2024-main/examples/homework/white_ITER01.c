//Project iteration 01 - UCCS RIDE SHARE
/*Joshua White - CS2060-002 - Professor Harding
* 
* Prompts & takes in input for miles to be driven from the user, then estimates amount of minutes
* that the ride will take by randomizing between a min and max. Then calculate fare of the ride
* and print for the user their ID, the miles to be ridden, the minutes it will take, and the cost
* of the ride. A business summary can be seen by the owner by inputting the sentinal value
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MIN_RAND_MINUTES_FACTOR 1.2
#define MAX_RAND_MINUTES_FACTOR 1.5
#define SENTINAL_VALUE -1

// Define functions before using them
double getValidDouble(int min, int max, int sentinal);
int estimateMinutes(double miles);
double calculateFare(double base, double minuteCost, double mileCost, double minRate, double miles, int minutes);
void printFare(int count, double miles, int minutes, double fare);
void endProgram(int users, double miles, int minutes, double profit);

// function main
/*
* main keeps the needed variables and calls the needed functions within a loop that runs
* until the sentinal value to end the program is entered.
*/
int main (void) {

	// Initialize Variables
	// Min and Max range of inputted miles
	int minMiles = 1;
	int maxMiles = 100;

	// Values to calcualate ride fare
	double baseFare = 1.8;
	double costPerMinute = .25;
	double costPerMile = 1.2;
	double minFlatRate = 20.0;

	// User variables
	double userMiles = 0;
	int userMinutes = 0;
	double userCharge = 0;
	int userID = 1;

	// Totals values
	double totalMiles = 0;
	int totalMinutes = 0;
	double totalFares = 0;

	// Start the main loop until sentinal value is inputted
	do {

		// Part 1: Get miles input from user
		puts("Welcome to the UCCS Ride Share!");
		puts("How many miles will your ride be today?");
		userMiles = getValidDouble(minMiles, maxMiles, SENTINAL_VALUE);
		
		// Call endProgram if sentinal value is inputted, otherwise continue for user.
		if (userMiles == SENTINAL_VALUE) {
			endProgram(userID, totalMiles, totalMinutes, totalFares);
		}
		else {
			// Part 2: Estimate how many minutes their ride will be
			userMinutes = estimateMinutes(userMiles);

			// Part 3: Calculate the fare of the user
			userCharge = calculateFare(baseFare, costPerMinute, costPerMile, minFlatRate, userMiles, userMinutes);

			// Part 4: Print the totals
			printFare(userID, userMiles, userMinutes, userCharge);

			// Part 5: Collect everything from this ride and get things ready for the next user
			totalMiles += userMiles;
			totalMinutes += userMinutes;
			totalFares += userCharge;
			userID++;
		}

	} while (userMiles != SENTINAL_VALUE);
} // end main

// function getValidDouble
/*
*  getValidDouble takes in input from user and checks for if the user inputted a valid double
* (double value from min to max)
* [takes in: min: the minimum value the user can input. max: the maximum value the user can input.
* sentinal: the value that will end the program when inputted]
*/
double getValidDouble(int min, int max, int sentinal) {

	// Initialize Variables
	bool dataIsGood = false;
	double userInput = 0;

	do {

		printf("Input miles: (%d - %d)", min, max);
		int scanfReturn = scanf("%lf", &userInput);
		while ((getchar()) != '\n');

		if (scanfReturn == 1) {

			if ((userInput > max || userInput < min) && userInput != sentinal) {
				puts("Please put in a valid number of miles.");
			}
			else if (userInput == sentinal) {
				dataIsGood = true;
			}
			else {
				dataIsGood = true;
			}
		}
		else {
			puts("Please put in a valid number of miles.");
		}

	} while (!dataIsGood);

	return userInput;
} // end getValidDouble

// function estimateMinutes
/*
* estimateMinutes randomzes an int value from MIN & MAX RAND_MINUTES_FACTOR multiplied
* by taken in miles. 
*/
int estimateMinutes(double miles) {

	// Get the minimum minutes and maximum minutes
	double minMinutes = (MIN_RAND_MINUTES_FACTOR * miles);
	double maxMinutes = (MAX_RAND_MINUTES_FACTOR * miles);

	//Cast min & max to ints
	int min = minMinutes;
	int max = maxMinutes;


	// Randomizeeee
	srand(time(0));
	int randomMinutes = min + rand() % (max - min + 1);

	return randomMinutes;
} // end estimateMinutes

// function calculateFare
/*
* calculateFare calculates returns a fare using the equation base + (minuteCost * minutes) + (mileCost * miles)
* If the calculated fare is less than minRate, then it is set to equal min rate.
*/
double calculateFare(double base, double minuteCost, double mileCost, double minRate, double miles, int minutes) {

	double fare = base + (minuteCost * minutes) + (mileCost * miles);

	if (fare < minRate) {
		fare = minRate;
	}

	return fare;

} // end calculateFare

// function printFare
/*
* printFare prints the fare calculated in the calculateFare function. The table is organized with \t format speccifiers.
*/
void printFare(int count, double miles, int minutes, double fare) {

	puts("Your ride is ready!");
	printf("Rider ID \t Miles \t Minutes \t Cost \n");
	printf("%d \t %.1f \t %d \t $%.2f \n", count, miles, minutes, fare);
} // end printFare

// function endProgram
/*
* endProgram is called when the sentinal value is entered in the getValidDouble function.
* It prints the total values defined in main and passed to this function, in a table
* organized with \t format specifiers.
*/
void endProgram(int users, double miles, int minutes, double profit) {

	puts("Summary of program since last activation:");
	printf("Users \t Miles ridden \t Minutes ridden \t Fares collected \n");
	printf("%d \t %.1f \t %d \t $%.2f \n", users, miles, minutes, profit);

} // end endProgram