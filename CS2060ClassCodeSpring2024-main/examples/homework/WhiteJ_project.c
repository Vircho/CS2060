//Project iteration 02 - UCCS RIDE SHARE
/*
* Name: Joshua White
* Class: CS2060 T/R 1:40-2:55
* OS: Windows 11
* Due: 4/4/24 11:59 PM
*
* Description: Emulates a rideshare app where an admin can log in to change values, a rider can take a ride, get information about the ride, and rate the ride.
* Contains functions to do all these tasks securely.
*/

//Import libraries
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//Define Constants
//Maximum length of a string
#define  STRING_LENGTH 80

//Two dimensional array storage amounts for rows and columns of survey data
#define SURVEY_RIDER_ROWS 5
#define SURVEY_CATEGORIES 3

// login and sentinel values
#define CORRECT_ID "id1"
#define CORRECT_PASSCODE "ABCD"
#define LOGIN_MAX_ATTEMPTS 4
#define SENTINAL_NEG1 -1

// Minimums and maximums
#define CALC_MIN 0.1
#define CALC_MAX 50
#define MIN_MILES 1
#define MAX_MILES 100
#define MIN_MINUTES_CALC 1.2
#define MAX_MINUTES_CALC 1.5
#define MINIMUM_RATE 20.00
#define MIN_SURVEY 1
#define MAX_SURVEY 5

//Structures
//Holds values that the admin can update
struct rideshare {

	//Values that admin inputs
	double base;
	double minuteCost;
	double mileCost;
	double flatRate;
	char orgName[STRING_LENGTH];

	//Surveys for the rideshare
	char survey[SURVEY_RIDER_ROWS][SURVEY_CATEGORIES];
	char averages[SURVEY_CATEGORIES];

	//Totals for the rideshare
	int totalRiders;
	double totalMiles;
	double totalProfit;

	//Pointer to the next rideshare
	struct rideshare* nextRideshare;
};

//Function prototypes
//Owner Mode Functions
bool ownerMode(struct rideshare* values);
bool getAdminLogin();
bool verifyAdminLogin(const char* adminID, const char* adminPass, const char* enteredID, const char* enteredPass);
void printAverageData(double average[], size_t size);

//SetupMode Functions
void setupMode(struct rideshare* values);

//Rider Mode Functions
void riderMode(struct rideshare* values, int surveys[][SURVEY_CATEGORIES], double averages[]);
void printSurveyResults(int survey[][SURVEY_CATEGORIES], int takenSurveys);
int estimateMinutes(double miles);
double calculateFare(struct rideshare values, int minutes, int miles);
void getRatings(int survey[][SURVEY_CATEGORIES], const char* categories[], int takenSurveys);
void calculateCategoryAverages(double average[], int surveyTakers, int survey[][SURVEY_CATEGORIES]);
void printCategories(const char* categories[], size_t totalCategories);

//Other functons
void removeNewline(char* str1, size_t strSize);
void clearBuffer();
double getValidDouble(double min, double max, bool sentinalRelevant);
bool scanDouble(const char* buffer, double* output);
void endProgramWithoutSummary();
char askYesOrNo();

//Linked-list functions
struct rideshare* addNodeToEnd(struct rideshare* head);
void printLL(const struct rideshare* head);

//Array of strings holding the survey categories
const char* surveyCategories[SURVEY_CATEGORIES] = { "Safety", "Cleanliness", "Comfort" };

// function main
/*
* -> Calls the most important functions and holds certain variables such as arrays and the main structure.
* returns: nothing
* parameters: none
*/
int main(void) {

	//Hold the head structure
	struct rideshare *head = malloc(sizeof(struct rideshare));
	head->nextRideshare = NULL;

	//Hold other variables
	bool ownerLoggedIn = false;

	//Start in ownerMode()
	ownerLoggedIn = ownerMode(head);
	if (ownerLoggedIn) {

		//Once Owner is finished, move to rider mode
		riderMode(head, head->survey, head->averages);
	}
	else {
		endProgramWithoutSummary();
	}

}

// function ownerMode
/*
* -> Runs through the beginning of the program by having the admin log in to change the data
* returns: nothing
* parameters: (values: the main structure holding the organization data)
*/
bool ownerMode(struct rideshare* values) {

	//Initialize variables
	bool loginSuccess = false;
	bool addingMoreRideshares = true;
	char addingAnother = 'm';

	//Start by getting the admin's verification
	loginSuccess = getAdminLogin();

	//Check the status of the login attempt and bring admin to change values
	if (loginSuccess) {

		//Setup the first rideshare
		setupMode(values);

		do {

			//Ask admin to add another rideshare
			puts("Would you like to add another rideshare?");
			addingAnother = askYesOrNo();

			//Check if they are adding another rideshare
			if (addingAnother == 'y') {

				//If adding another rideshare, create a new rideshare to put values in
				struct rideshare* newRideshare = addNodeToEnd(values);

				//Change the values of this rideshare
				setupMode(newRideshare);

			}
			else if (addingAnother == 'n') {
				addingMoreRideshares = false;
			}

		} while (addingMoreRideshares);

		//Once all rideshares have been added, print all the rideshares
		printLL(values);

	}
	//Let main know that the owner logged in
	return loginSuccess;
}

// function getAdminLogin
/*
* -> Asks admin to enter their id and password. After both are entered, it calls verifyAdmin to see if they're right.
* If they're not right, it asks again until the admin either uses up their attempts or inputs the right id and password.
* returns: boolean for if the admin successfully logged in or not.
* parameters: none
*/
bool getAdminLogin() {

	//Initialize variables
	//Local function variables
	int attempts = LOGIN_MAX_ATTEMPTS;
	bool loginSuccess = false;

	//Entered ID/Pass
	char adminID[STRING_LENGTH] = { "" };
	char adminPass[STRING_LENGTH] = { "" };

	//Real ID/Pass
	char realID[STRING_LENGTH] = CORRECT_ID;
	char realPass[STRING_LENGTH] = CORRECT_PASSCODE;

	//Start loop
	do {

		//Start admin login
		puts("Admin Login");

		//Get ID
		puts("Enter your admin ID");
		fgets(adminID, STRING_LENGTH, stdin);

		//Get Pass
		puts("Enter your admin Password");
		fgets(adminPass, STRING_LENGTH, stdin);

		//Remove newlines from adminPass & adminID
		removeNewline(adminID, STRING_LENGTH);
		removeNewline(adminPass, STRING_LENGTH);

		//Check ID and pass
		loginSuccess = verifyAdminLogin(realID, realPass, adminID, adminPass);

		//Decrement attempts and print the failure
		if (loginSuccess == false) {

			attempts--;
			if (attempts != 0) {
				puts("Incorrect ID or Passcode. Please enter again");
				printf("You have %d attmepts left.\n", attempts);
			}

		}

	} while (loginSuccess == false && attempts > 0);

	return loginSuccess;
}

// function verifyAdminLogin
/*
* -> compares two sets of two strings to their partner to see if they are the same as their partner.
* returns: boolean value on whether both set's strings are equal to their partner.
* parameters: (adminID: The correct ID) (adminPass: The correct password) (enteredID: the ID to compare to adminID)
* (enteredPass: the password to compare to adminPass)
*/
bool verifyAdminLogin(const char* adminID, const char* adminPass, const char* enteredID, const char* enteredPass) {

	//Initialize
	bool inputsAreCorrect = false;
	int strcmpReturnID = 0;
	int strcmpReturnPass = 0;

	//Compare the IDs and passwords
	strcmpReturnID = strcmp(adminID, enteredID);
	strcmpReturnPass = strcmp(adminPass, enteredPass);

	//Check the return values of strcmp to see if they were both the same
	if (strcmpReturnID == 0 && strcmpReturnPass == 0) {
		inputsAreCorrect = true;
	}

	return inputsAreCorrect;
}

// function setupMode
/*
* -> Asks the admin to enter data to change all variables in the main structure
* returns: nothing
* parameters: (values: structure holding the data to update)
*/
void setupMode(struct rideshare* values) {

	//Change values one-by-one
	puts("Enter Base Fare");
	values->base = getValidDouble(CALC_MIN, CALC_MAX, false);
	printf("You have entered %.2lf\n", values->base);

	puts("Enter the Cost Per Minute");
	values->minuteCost = getValidDouble(CALC_MIN, CALC_MAX, false);
	printf("You have entered %.2lf\n", values->minuteCost);

	puts("Enter the Cost Per Mile");
	values->mileCost = getValidDouble(CALC_MIN, CALC_MAX, false);
	printf("You have entered %.2lf\n", values->mileCost);

	puts("Enter the Flat Rate");
	values->flatRate = getValidDouble(CALC_MIN, CALC_MAX, false);
	printf("You have entered %.2f\n", values->flatRate);

	puts("Enter the Organization Name");
	fgets(values->orgName, STRING_LENGTH, stdin);
	removeNewline(values->orgName, STRING_LENGTH);
	printf("You have entered %s\n", values->orgName);
}

// function endProgram
/*
* -> Gives a summary of the totals data since program started
* returns: nothing
* parameters: (users: total of users that took a ride) (totalMiles: total of miles ridden across all users)
* (totalMinutes: total of all minutes ridden) (totalProfit: total amount of charges from users)
* (averages, array holding the average in each category for the survey)
*/
void endProgram(int users, double totalMiles, int totalMinutes, double totalProfit, double averages[]) {

	if (users == 0) {
		puts("No riders since last activation");
	}
	else {
		puts("Summary of program since last activation:");
		printf("Users \t Miles ridden \t Minutes ridden \t Fares collected \n");
		printf("%d \t %.1f \t %d \t $%.2f \n", users, totalMiles, totalMinutes, totalProfit);

		puts("");
		puts("Total ratings averages");
		printAverageData(averages, SURVEY_CATEGORIES);
	}

}





// function riderMode
/*
* -> Runs through one ride from a user, where they choose to have a ride, find out the data from that ride, and choose to take a survey
* returns: nothing
* parameters: (values: the structure holding the data that is used to calculate charge) (surveys: the 2d array holding all surveys from users)
* (averages: 1d array holding the average ratings of each category)
*/
void riderMode(struct rideshare* values, int surveys[][SURVEY_CATEGORIES], double averages[]) {

	//Initialize Variables
	//Totals
	int surveysTaken = 0;
	int ridersSinceActivation = 0;
	double totalMiles = 0;
	int totalMinutes = 0;
	double totalProfit = 0;

	//Others
	bool adminLoginSuccess = false;

	//Start the rideshare
	do {

		//Initialize user-specific variables
		double riderMiles = 0;
		int riderMinutes = 0;
		double riderCharge = 0;
		char isUserTakingRide = 'm';
		char isUserRating = 'm';

		printf("Welcome to %s! You may take a ride between %d and %d miles.\n", values->orgName, MIN_MILES, MAX_MILES);

		//Print surveys
		printSurveyResults(surveys, surveysTaken);

		//Ask user for ride
		puts("Would you like to take a ride with us today?");
		isUserTakingRide = askYesOrNo();

		//Proceed with ride if user said yes to a ride
		if (isUserTakingRide == 'y' || isUserTakingRide == 'Y') {

			//Get amount of miles user will ride
			puts("How many miles will you take?");
			printf("Remember that we can only give rides between %d and %d miles currently.", MIN_MILES, MAX_MILES);
			riderMiles = getValidDouble(MIN_MILES, MAX_MILES, true);

			//If user inputted sentinal value, have admin log in
			if (riderMiles == SENTINAL_NEG1) {

				adminLoginSuccess = getAdminLogin();

				//If admin successfully logged in, end the program
				if (adminLoginSuccess) {
					endProgram(ridersSinceActivation, totalMiles, totalMinutes, totalProfit, averages);
				}

			}//end of checking for sentinal

			//else statement ensures that sentinal input does not count as a ride if the owner couldn't log in
			else {
				//Estimate amount of minutes user's ride will take
				riderMinutes = estimateMinutes(riderMiles);
				printf("Your ride of %.2lf miles is estimated to take %d minutes.\n", riderMiles, riderMinutes);

				//Calculate how much the ride will cost
				riderCharge = calculateFare(*values, riderMinutes, riderMiles);
				printf("Your ride will cost $%.2lf\n", riderCharge);
				puts("...");

				//Ask user to rate their experience.
				puts("Thank you for riding with us! Would you like to rate your experience today?");
				isUserRating = askYesOrNo();
			}

			//Check for if user wants to rate their experience
			if (isUserRating == 'Y' || isUserRating == 'y') {

				//If user chooses to rate, bring them to getRatings()
				getRatings(surveys, surveyCategories, surveysTaken);

				//Once they have rated their experience, upsate relevant variables
				surveysTaken++;

				//Once they have rated their experience, update the averages between all users
				calculateCategoryAverages(averages, surveysTaken, surveys);
			}
			else if (isUserRating == 'N' || isUserRating == 'n') {

				puts("Thanks for riding with us, hope you have a great rest of your day!");

			}//end of checking for rating

			//Collect data from this ride
			//The reason they are done here is to avoid updating riders if user answered N
			ridersSinceActivation++;
			totalMiles += riderMiles;
			totalMinutes += riderMinutes;
			totalProfit += riderCharge;

		}//end of checking for ride

	} while (!adminLoginSuccess);
}

// function printSurveyResults
/*
* -> prints a 2d survey array row by row in a table
* returns: nothing
* parameters: (surveys: the 2d array to print) (takenSurveys: amount of filled rows)
*/
void printSurveyResults(int survey[][SURVEY_CATEGORIES], int takenSurveys) {

	//Initialize
	int surveyBeingPrinted = 0;

	//Categories to loop through
	int thisCategory1 = 0;
	int thisCategory2 = 0;
	int thisCategory3 = 0;

	//Print first line
	puts("-LIST OF SURVEYS TAKEN-");

	//Check for no surveys taken
	if (takenSurveys == 0) {
		puts("(No surveys have been taken yet, take a ride and be the first!)");
	}
	else {
		while (surveyBeingPrinted < takenSurveys) {

			//Take the 3 columns in the current row being looped through and store them
			thisCategory1 = survey[surveyBeingPrinted][0];
			thisCategory2 = survey[surveyBeingPrinted][1];
			thisCategory3 = survey[surveyBeingPrinted][2];

			//Print the columns in a table
			printf("Survey %d:\t%d\t%d\t%d", surveyBeingPrinted + 1, thisCategory1, thisCategory2, thisCategory3);
			puts("");

			surveyBeingPrinted++;
		}
	}

}

// function estimateMinutes
/*
* -> Estimates amount of minutes a ride will take by randomizing a number between two other numbers that are decided by amount of miles
* returns: int representing how many minutes the ride will take
* parameters: (miles: amount of miles to allow the function to calculate minutes)
*/
int estimateMinutes(double miles) {

	// Get the minimum minutes and maximum minutes
	double minMinutes = (MIN_MINUTES_CALC * miles);
	double maxMinutes = (MAX_MINUTES_CALC * miles);

	//Cast min & max to ints
	int min = minMinutes;
	int max = maxMinutes;

	// Randomize the minutes between min & max
	srand(time(0));
	int randomMinutes = min + rand() % (max - min + 1);

	return randomMinutes;
}

// function calculateFare
/*
* -> Calculates cost of the ride based on a specific equation
* returns: A double representing the cost of the ride
* parameters: (values: the structure holding values that are part of the equation) (minutes: amount of minutes the ride will be)
* (miles: amount of miles the ride will be)
*/
double calculateFare(struct rideshare values, int minutes, int miles) {

	double fare = values.base + (values.minuteCost * minutes) + (values.mileCost * miles);

	if (fare < MINIMUM_RATE) {
		fare = MINIMUM_RATE;
	}

	return fare;

}

// function getRatings
/*
* -> Asks user to input 3 ratings for different categories and places them into a specific row into the 2d array
* returns: nothing
* parameters: (survey: the 2d array to update) (categories: an array holding the categories that will be printed in the prompt)
* (takenSurveys: amount of surveys taken to know which row to update)
*/
void getRatings(int survey[][SURVEY_CATEGORIES], const char* categories[], int takenSurveys) {

	//Prompts for the user to input a score and lets them know what they can input
	puts("Thank you for using the UCCS RideShare!");
	puts("We would like to know how your experience with us was.");
	printf("Please enter a score for these categories from %d to %d", MIN_SURVEY, MAX_SURVEY);
	puts(""); //newline
	printCategories(categories, SURVEY_CATEGORIES);

	//For loop goes through the columns of the survey[][] array to get the necessary scores one-by-one.
	for (size_t place = 0; place < SURVEY_CATEGORIES; place++) {

		//Asks the user to input for the category in the place currently having an input entered for
		printf("How did you feel about the %s? \n", categories[place]);

		//Initialize
		double userScoreAsDouble = 0;
		int userScore = 0;

		//Take in the user score as a double. This will allow decimals, but the decimals will be removed.
		userScoreAsDouble = getValidDouble(MIN_SURVEY, MAX_SURVEY, false);

		//Turn the user score into an int, this will cut off any decimal places
		userScore = userScoreAsDouble;

		// Once valid data is obtained, put the data into the 2d array at current collumn in the for-loop and row current user as defined in parameters
		survey[takenSurveys][place] = userScore;

	}
}

// function calculateCategoryAverages
/*
* -> Calculates the average of each column in a 2d array
* returns: nothing
* parameters: (average: the 1d array to place averages into) (surveyTakers: amount of filled rows in the 2d array)
* (survey: 2d array to read)
*/
void calculateCategoryAverages(double average[], int surveyTakers, int survey[][SURVEY_CATEGORIES]) {

	for (size_t categories = 0; categories < SURVEY_CATEGORIES; categories++) {

		double categoryAverage = 0;

		for (size_t score = 0; score < surveyTakers; score++) {

			categoryAverage += survey[score][categories];

		}

		categoryAverage = (double)(categoryAverage / surveyTakers);
		average[categories] = categoryAverage;

	}
}

// function printCategories
/*
* -> prints a 1d array of strings
* returns: nothing
* parameters: (categories: array to print) (totalCategories: size of array)
*/
void printCategories(const char* categories[], size_t totalCategories) {

	//loop to display each category horizontally
	printf("%s", "Rating Categories:\t");
	for (size_t surveyCategory = 0; surveyCategory < totalCategories; ++surveyCategory) {
		printf("\t%zu.%s\t", surveyCategory + 1, categories[surveyCategory]);
	}
	puts(""); // start new line of output
}





// function removeNewline
/*
* -> removes the newline from the end of a string after it is filled from fgets()
* returns: nothing
* parameters: (str1: string to search in for a newline) (strSize: size of string)
*/
void removeNewline(char* str1, size_t strSize) {

	for (int place = 0; place <= strSize; place++) {

		if (str1[place] == '\n') {
			str1[place] = '\0';
		}
	}
}

// function clearBuffer
/*
* -> removes extra unwanted characters from the buffer
* returns: nothing
* parameters: none
*/
void clearBuffer() {
	while ((getchar()) != '\n');
}

// function getValidDouble
/*
* -> Takes in a string, calls scanDouble to convert the string to a double, and checks the double to see if it is valid
* returns: a double value that the user inputted
* parameters: (min: the minimum valid value) (max: the maximum valid value)
* (sentinalRelevant: whether to expect the sentinal value could be potentially inputted)
*/
double getValidDouble(double min, double max, bool sentinalRelevant) {

	// Initialize Variables
	bool dataIsGood = false;
	char userInput[STRING_LENGTH] = { "" };
	double doubleValue = 0;
	bool inputtedDataIsDouble = false;

	do {

		//Set a place for user to type
		printf("%s", "-");

		//Get the user input
		fgets(userInput, STRING_LENGTH, stdin);
		removeNewline(userInput, STRING_LENGTH);

		// Convert user input to double
		inputtedDataIsDouble = scanDouble(userInput, &doubleValue);

		//Once converted to double, check to see if it is in a valid range
		if (inputtedDataIsDouble == true) {

			//Checks double data for validity, if the sentinal is *not* relevant and double is not within min/max, data is invalid 
			if ((doubleValue > max || doubleValue < min) && !sentinalRelevant) {
				puts("Inputted Data Is Invalid");
			}

			//Otherwise, if the owner inputted the sentinal value while the sentinal was relevant, the data is valid
			else if (doubleValue == SENTINAL_NEG1 && sentinalRelevant) {
				dataIsGood = true;
			}

			//Otherwise, the data is valid
			else {
				dataIsGood = true;
			}
		}
		else {
			puts("Inputted Data Is Invalid");
		}

	} while (!dataIsGood);

	return doubleValue;
}

// function scanDouble
/*
* -> Attempts to convert a string to a double
* returns: boolean representing whether it successfully converted the string
* parameters: (buffer: the string to convert) (output: the double value to update if string is successfully converted)
*/
bool scanDouble(const char* buffer, double* output) {

	//Initialize
	char* end; //When strtod will stop
	double testNum = 0; //The number to put strtod's output into
	bool isValid = false; //Whether buffer is a double or not

	//Attempt to convert inputted string to double
	testNum = strtod(buffer, &end);

	//Test the output of strtod
	if (buffer == end) {
		isValid = false;
	}
	else if (*end != '\0') {
		isValid = false;
	}
	else {
		isValid = true;
	}

	if (isValid) {
		*output = testNum;
	}

	return isValid;
}

// function printAverageDara
/*
* -> Prints a 1d array of the average scores
* returns: nothing
* parameters: (average: 1d array to print) (size: size of the 1d array)
*/
void printAverageData(double average[], size_t size) {

	for (size_t place = 0; place < size; place++) {
		printf("%.1f\t", average[place]);
	}

}

// endProgramWithoutSummary
/*
* -> Ends the program without any summary
* returns: nothing
* parameters: none
*/
void endProgramWithoutSummary() {
	puts("Ending Program...");
}

// function askYesOrNo
/*
* -> Asks the user for a yes or no answer, and loops until they do
* returns: a char representing the users answer y or n
* parameters: none
*/
char askYesOrNo() {

	//Initialize
	char userAnswer = 'm';
	bool validAnswer = false;

	//Take in their answer
	do {

		puts("To answer, put in a Y for yes or a N for no. Words that start with Y or N also work.");
		userAnswer = getchar();
		clearBuffer();
		printf("You have answered %c\n", userAnswer);

		//Check that their answer is valid
		if (userAnswer == 'y' || userAnswer == 'Y') {
			puts("You have said yes. Thank you for your answer!");
			validAnswer = true;
		}
		else if (userAnswer == 'n' || userAnswer == 'N') {
			puts("You have said no. We understand. Have a great rest of your day!");
			validAnswer = true;
		}
		else {
			puts("Sorry, you did not answer a yes or no.");
			puts("Enter Y or N for Yes or No. Words that start with Y or N will also work.");
		}

	} while (!validAnswer);

	//Update to function as of 4/23/24: automatically tolowers the answer so that the function only returns lowercase y or n
	userAnswer = tolower(userAnswer);

	return userAnswer;
}





// function addNodeToEnd
/*
* -> Adds a node to the end of a linked list, does not sort the linked list
* returns: The address of the new node
* parameters: (head: pointer to the head of the linked list)
*/
struct rideshare* addNodeToEnd(struct rideshare* head) {

	struct rideshare* newRideshare = malloc(sizeof(struct rideshare));
	newRideshare->nextRideshare = NULL;


	//Make a rideshare pointer to represent parts of the linked list
	struct rideshare* thisRsPtr = head;

	//Find a place in the linked list to put the rideshare
	while (thisRsPtr->nextRideshare != NULL) {

		//Move through the linked list until thisRsPtr->nextRsPtr is null, when it's null, it's found the last rideshare 
		thisRsPtr = thisRsPtr->nextRideshare;

	}

	//Set the new rideshare
	thisRsPtr->nextRideshare = newRideshare;

	//Return the pointer to the end of the linked list
	return newRideshare;

}

// function printLL
/*
* -> Prints a linked list
* returns: nothing
* parameters: (head: pointer to the head of the linked list)
*/
void printLL(const struct rideshare* head) {

	//Make a pointer to parts of the linked list
	struct rideshare* thisRsPtr = head;

	//Start the tables
	puts("----------------------");
	puts("All Entered Rideshares");
	puts("----------------------");

	//Go until the end of the linked list
	while (thisRsPtr != NULL) {

		printf("%s\n", thisRsPtr->orgName);
		printf("baseFare = %.1f\n", thisRsPtr->base);
		printf("costPerMinute = $%.2f\n", thisRsPtr->minuteCost);
		printf("costPerMile = $%.2f\n", thisRsPtr->mileCost);
		printf("minFlatRate = $%.2f\n", thisRsPtr->flatRate);
		printf("\n");

		thisRsPtr = thisRsPtr->nextRideshare;
	}

}