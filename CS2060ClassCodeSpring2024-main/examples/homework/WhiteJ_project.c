//Project iteration 02 - UCCS RIDE SHARE
/*Joshua White - CS2060-002 - Professor Harding
*
* Name: Joshua White
* Class: CS2060 T/R 1:40-2:55
* OS: Windows 11
* Due: 4/4/24 11:59 PM
*
* Summary goes here
*/

//Import libraries
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Function Prototypes
void ownerMode();
void riderMode();
bool getAdminLogin();
bool verifyAdminLogin();
void removeNewline(char str1[], size_t strSize);

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

//Array of strings holding the survey categories
const char* surveyCategories[SURVEY_CATEGORIES] = { "Safety", "Cleanliness", "Comfort" };

// function main
/*
* Summary
* -> 
* returns: 
* parameters:
*/
int main(void) {

	//Start in ownerMode
	ownerMode();
}

// function ownerMode
/*
* Summary
* ->
* returns:
* parameters:
*/
void ownerMode() {

	//Variables
	bool loginSuccess = false;

	//Have admin login to the system
	loginSuccess = getAdminLogin();

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

bool verifyAdminLogin(const char adminID[], const char adminPass[], const char enteredID[], const char enteredPass[]) {

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

// function riderMode
/*
* Summary
* ->
* returns:
* parameters:
*/
void riderMode() {

}

void removeNewline(char str1[], size_t strSize) {

	for (int place = 0; place <= strSize; place++) {

		if (str1[place] == '\n') {
			str1[place] = '\0';
		}
	}
}