//Project iteration 01 - UCCS RIDE SHARE
//description goes here

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
int main (void) {

	//Initialize Variables
	//Min and Max range of inputted miles
	int minMiles = 1;
	int maxMiles = 100;

	//Values to calcualate ride fare
	double baseFare = 1.8;
	double costPerMinute = .25;
	double costPerMile = 1.2;
	double minFlatRate = 20.0;

	//User variables
	double userMiles = 0; //How many miles the user inputs to ride
	int userMinutes = 0;
	double userCharge = 0;
	int userID = 1;

	// Totals values
	double totalMiles = 0;
	int totalMinutes = 0;
	double totalFares = 0;

	do {

		// Part 1: Get miles input from user
		puts("Welcome to the UCCS Ride Share!");
		puts("How many miles will your ride be today?");
		userMiles = getValidDouble(minMiles, maxMiles, SENTINAL_VALUE);
		
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
}

// function getUserMiles
double getValidDouble(int min, int max, int sentinal) {

	// Initialize Variables
	bool dataIsGood = false;
	double userInput = 0;

	do {

		printf("Input miles: (%d - %d)", min, max);
		int scanfReturn = scanf("%lf", &userInput);
		while ((getchar()) != '\n');

		if (scanfReturn == 1) {

			if (userInput > max || userInput < min && userInput != sentinal) {
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
}

// function estimateMinutes
int estimateMinutes(double miles) {

	// Get the minimum minutes and maximum minutes
	double minMinutes = (MIN_RAND_MINUTES_FACTOR * miles);
	double maxMinutes = (MAX_RAND_MINUTES_FACTOR * miles);

	//Cast min & max to ints
	int min = minMinutes;
	int max = maxMinutes;


	// Randomizeeee
	srand(time(0));
	int randomMinutes = min + rand() % max;

	return randomMinutes;
}

// function calculateCharge
double calculateFare(double base, double minuteCost, double mileCost, double minRate, double miles, int minutes) {

	double fare = base + (minuteCost * minutes) + (mileCost * miles);

	if (fare < minRate) {
		fare = minRate;
	}

	return fare;

}

// function printFare
void printFare(int count, double miles, int minutes, double fare) {

	puts("Your ride is ready!");
	printf("Rider ID \t Miles \t Minutes \t Cost \n");
	printf("%d \t %.1f \t %d \t $%.2f \n", count, miles, minutes, fare);
}

// function endProgram
void endProgram(int users, double miles, int minutes, double profit) {

	puts("Summary of program since last activation:");
	printf("Users \t Miles ridden \t Minutes ridden \t Fares collected \n");
	printf("%d \t %.1f \t %d \t $%.2f \n", users, miles, minutes, profit);

}