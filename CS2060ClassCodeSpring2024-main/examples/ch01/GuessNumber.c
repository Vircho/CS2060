// Randomly generate numbers between a min and max for user to guess.


//Import C functions to allow more options, such as <stdbool.h> (define booleans), <stdio.h> (allow reading/writing to files),
//<stdlib.h> (variety of functions), and <time.h> (time-based functions)
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Defines the minimum and maximum allowed number to guess as 1 and 1000 respectively
#define MIN 1
#define MAX 1000

//Defines the later functions guessGame and isCorrect so that the system will know they exist when called in other functions.
void guessGame(void); 
bool isCorrect(int guess, int answer); 

int main(void) {
    //Sets a random seed for the system to randomize a number in the future.
    srand(time(0)); 

   //Calls guessGame to start the game
   guessGame();
} // end main



//guessGame - runs the number guessing game 
void guessGame(void) {
    
    //Initializes ints response and guess to 0
   int response = 0;
   int guess = 0;

   //Prints "Hello Deb" for GitHub practice 
   puts("Hello Deb");

   do {

      //Sets what number the player has to guess in int answer by randomizing the number, adding 1, and making sure it's below MAX with
      //the remainder between the random number and MAX 
      int answer = 1 + rand() % MAX;

      //Starts the game by telling the player the range of numbers they can guess
      printf("I have a number between %d and %d.\n", MIN, MAX);

      //Prompts the player to guess the number
      puts("Can you guess my number?\n" 
           "Please type your first guess.");

      //Prints a ? where the player should type their answer
      printf("%s", "? ");
      

      //Takes in the number the player guesses and stores it in int guess
      scanf("%d", &guess);

      //Calls isCorrect, putting in guess and answer to see if the player's guess is correct. If it's not, the while loop runs, making
      //the player guess again
      while (!isCorrect(guess, answer)) {
         scanf("%d", &guess);
      }


      puts("\nExcellent! You guessed the number!\n"
         "Would you like to play again?");
      printf("%s", "Please type (1=yes, 2=no)? ");
      scanf("%d", & response);
      puts("");

   } while (response == 1);
} // end function guessGame

//isCorrect - returns true or false if the player's guess is correct or not 
bool isCorrect(int guess, int answer) {

    //Initiallizes the boolean correct to be false
    bool correct = false;

   //Sets correct to true if the player's guess is equal to the correct answer 
   if (guess == answer) {
      correct = true;
   }

   //Tells the player if their guess was too high or too low by seeing if guess is greater than or less than answer 
   if (guess < answer) {
      printf( "%s", "Too low. Try again.\n? " );
   }
   else {
      printf( "%s", "Too high. Try again.\n? " );
   }

   return correct;
} // end function isCorrect



/**************************************************************************
 * (C) Copyright 1992-2012 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
