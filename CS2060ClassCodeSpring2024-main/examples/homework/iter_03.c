//Project iteration 03 - UCCS RIDE SHARE
/*
* Name: Joshua White
* Class: CS2060 T/R 1:40-2:55
* OS: Windows 11
* Due: 4/24/24 11:59 PM
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
//rideshare - represents one rideshare
typedef struct rideshare {

	double base;
	double minuteCost;
	double mileCost;
	double flatRate;
	char name[STRING_LENGTH];

} Rideshare;

//totals - represents totals values in riderMode
struct totals {
	
	int surveys;
	int riders;
	double miles;
	int minutes;
	double profit;

};

//rider - represents one rider
typedef struct rider {

	double miles;
	int minutes;
	double charge;
	char takingRide;
	char isRating;

} Rider;

//

//Function prototypes
//Owner Mode Functions
void ownerMode(struct rideshare* values);
bool getAdminLogin();
bool verifyAdminLogin(const char* adminID, const char* adminPass, const char* enteredID, const char* enteredPass);

//Setup Mode Functions
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
void printAverageData(double average[], size_t size);
char yesOrNo();

//Array of strings holding the survey categories
const char* surveyCategories[SURVEY_CATEGORIES] = { "Safety", "Cleanliness", "Comfort" };

// function main
/*
* -> Calls the most important functions and holds certain variables such as arrays and the main structure.
* returns: nothing
* parameters: none
*/
int main(void) {

}





void ownerMode(struct rideshare* values) {

}





void setupMode(struct rideshare* values) {

}





void riderMode(struct rideshare* values, int surveys[][SURVEY_CATEGORIES], double averages[]) {

}
