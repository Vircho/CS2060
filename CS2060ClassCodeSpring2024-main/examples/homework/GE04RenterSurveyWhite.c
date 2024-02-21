//Guided Exploration 4 Renter Survey
/*
* Name: Joshua White
* Class: CS2060 T/R 1:40-2:55
* OS: Windows 11
* Due: 2/26/24
*
* Description: 
*/

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#define SURVEY_ROWS 7
#define SURVEY_COLUMNS 3
#define SURVEY_CATEGORIES 3

#define MIN_SURVEY_VALUE 1
#define MAX_SURVEY_VALUE 5

//Function prototypes
void printCategories(const char* categories[], size_t totalCategories);
void getRatings(int survey[SURVEY_ROWS][SURVEY_COLUMNS], size_t rows, size_t columns, const char* categories[], int user);
void printSurveyResults();
void calculateCategoryAverages();
void printCategoryData();

void clearBuffer();

int main(void) {

	//Create arrays
	int rideshareSurvey[SURVEY_ROWS][SURVEY_COLUMNS];
	int categoryAverages[SURVEY_CATEGORIES];
	const char* surveyCategories[SURVEY_CATEGORIES] = { "Safety", "Cleanliness", "Comfort" };

    //Initialize other variables
    int surveyTaker = 1;
    
    while (surveyTaker <= SURVEY_ROWS) {

        //Get ratings from the user
        getRatings(rideshareSurvey, SURVEY_ROWS, SURVEY_COLUMNS, surveyCategories, surveyTaker);

    }
}

void printCategories(const char* categories[], size_t totalCategories)
{
    //loop to display each category horizontally
    printf("%s", "Rating Categories:\t");
    for (size_t surveyCategory = 0; surveyCategory < totalCategories; ++surveyCategory)
    {
        printf("\t%zu.%s\t", surveyCategory + 1, categories[surveyCategory]);
    }
    puts(""); // start new line of output
}

void getRatings(int survey[SURVEY_ROWS][SURVEY_COLUMNS], size_t rows, size_t columns, const char* categories[], int user) {

    //Prompts for the user to input a score and lets them know what they can input
    puts("Thank you for using the UCCS RideShare!");
    puts("We would like to know how your experience with us was.");
    printf("Please enter a score for these categories from %d to %d", MIN_SURVEY_VALUE, MAX_SURVEY_VALUE);
    puts(""); //newline
    printCategories(categories, SURVEY_CATEGORIES);

    // for loop goes through the columns of the survey[][] array to get the necessary scores one-by-one.
    for (size_t place = 0; place < SURVEY_CATEGORIES; place++) {

        // asks the user to input for the category in the place currently having an input entered for
        printf("How did you feel about the %s? \n", categories[place]);

        // initialize boolean for valid data, and variable for user input
        bool dataIsGood = false;
        int userScore = 0;

        do {

            // scanfReturnValue returns whether scanf() returned successfully or not, with 1 being successful and 0 being not
            // clearBuffer clears the buffer of the newline character inputted after an insuccessful input
            int scanfReturnValue = scanf("%d", &userScore);
            clearBuffer();

            if (scanfReturnValue == 1) {

                // checks if userScore is within the allowed range
                if (userScore >= MIN_SURVEY_VALUE && userScore <= MAX_SURVEY_VALUE) {
                    dataIsGood = true;
                }
                else {
                    printf("You did not input a valid score. Vald scores are whole numbers between %d and %d", MIN_SURVEY_VALUE, MAX_SURVEY_VALUE);
                }
            }
            else {
                printf("You did not input a valid score. Vald scores are whole numbers between %d and %d", MIN_SURVEY_VALUE, MAX_SURVEY_VALUE);
            }
        } while (!dataIsGood);

        // Once valid data is obtained, put the data into the 2d array at current collumn in the for-loop and row current user as defined in parameters
        survey[user][place] = userScore;
    }
}

void printSurveyResults() {

}

void calculateCategoryAverages() {

}

void printCategoryData() {

}

void clearBuffer() {
    while ((getchar()) != '\n');
}