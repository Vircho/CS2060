//Import libraries
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

//Structures
struct organizationValues {
	double base;
	double minuteCost;
	double mileCost;
	double flatRate;
	char orgName[STRING_LENGTH];
};

//Function prototypes
//Owner Mode Functions
void ownerMode(struct organizationValues* values);
bool getAdminLogin();
bool verifyAdminLogin(const char* adminID, const char* adminPass, const char* enteredID, const char* enteredPass);
void changeValues(struct organizationValues* values);

//Rider Mode Functions
void riderMode(struct organizationValues* values, int surveys[][SURVEY_CATEGORIES], double averages[]);
void printSurveyResults(int survey[][SURVEY_CATEGORIES], int takenSurveys);
char askYesOrNo();
int estimateMinutes(double miles);
double calculateFare(struct organizationValues values, int minutes, int miles);

//Other functons
void removeNewline(char* str1, size_t strSize);
void clearBuffer();
double getValidDouble(double min, double max, bool sentinalRelevant);
bool scanDouble(const char* buffer, double* output);

//Array of strings holding the survey categories
const char* surveyCategories[SURVEY_CATEGORIES] = { "Safety", "Cleanliness", "Comfort" };

int main(void) {

	//Hold the structure
	struct organizationValues values = {1.8, 0.25, 1.2, 20, "UCCS Rideshare"};
	struct organizationValues* valuesPointer = &values;

	//Hold Ratings Arrays
	int rideshareSurvey[SURVEY_RIDER_ROWS][SURVEY_CATEGORIES];
	double categoryAverages[SURVEY_CATEGORIES];

	//Start in ownerMode()
	ownerMode(valuesPointer);

	//Once Owner is finished, move to rider mode
	riderMode(valuesPointer, rideshareSurvey, categoryAverages);
}

void ownerMode(struct organizationValues* values) {

	//Initialize variables
	bool loginSuccess = false;

	//Start by getting the admin's verification
	loginSuccess = getAdminLogin();

	//Check the status of the login attempt and bring admin to change values
	if (loginSuccess) {
		changeValues(values);
	}
}

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
			puts("Incorrect ID or Passcode. Please enter again");
			printf("You have %d attmepts left.\n", attempts);
		}

	} while (loginSuccess == false && attempts > 0);

	return loginSuccess;
}

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

void changeValues(struct organizationValues* values) {

	//Change values one-by-one
	puts("Enter Base Fare");
	values->base = getValidDouble(CALC_MIN, CALC_MAX, false);
	printf("You have entered %.2lf\n", values->base);

	puts("Enter the Cost Per Minute");
	values->minuteCost = getValidDouble(CALC_MIN, CALC_MAX, false);
	printf("You have entered %.2lf\n", values->flatRate);

	puts("Enter the Cost Per Mile");
	values->mileCost = getValidDouble(CALC_MIN, CALC_MAX, false);
	printf("You have entered %.2lf\n", values->mileCost);

	puts("Enter the Flat Rate");
	values->flatRate = getValidDouble(CALC_MIN, CALC_MAX, false);
	printf("You have entered %.2f\n", values->flatRate);

	puts("Enter the Flat Rate");
	fgets(values->orgName, STRING_LENGTH, stdin);
	printf("You have entered %s\n", values->orgName);
}





void riderMode(struct organizationValues* values, int surveys[][SURVEY_CATEGORIES], double averages[]) {

	//Initialize Variables
	//Totals
	int surveysTaken = 0;
	int ridersSinceActivation = 0;
	int totalMiles = 0;
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
			riderMiles = getValidDouble(MIN_MILES, MAX_MILES, true);

			//If user inputted sentinal value, have admin log in
			if (riderMiles == SENTINAL_NEG1) {

				adminLoginSuccess = getAdminLogin();

				//If admin successfully logged in, end the program
				if (adminLoginSuccess) {
					//Do later
				}

			}//end of checking for sentinal
			
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

		}//end of checking for yes or no

	} while (!adminLoginSuccess);
}

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
	
	return userAnswer;
}

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

double calculateFare(struct organizationValues values, int minutes, int miles) {

	double fare = values.base + (values.minuteCost * minutes) + (values.mileCost * miles);

	if (fare < MINIMUM_RATE) {
		fare = MINIMUM_RATE;
	}

	return fare;

}





void removeNewline(char* str1, size_t strSize) {

	for (int place = 0; place <= strSize; place++) {

		if (str1[place] == '\n') {
			str1[place] = '\0';
		}
	}
}

void clearBuffer() {
	while ((getchar()) != '\n');
}

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

			if (doubleValue > max || doubleValue < min) {
				puts("Inputted Data Is Invalid");
			}
			else if (doubleValue == SENTINAL_NEG1 && sentinalRelevant) {
				dataIsGood = true;
			}
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