// fig03_06.c
// Analysis of examination results.
#include <stdio.h>
#include <stdbool.h>

/* Temporary Comment
* Modify the program so that on any input, if the value entered is other than 1 or 2, 
* keep looping until the user enters a correct value. This means if a non numeric value 
*is entered the program should handle that situation.
*/

// function main begins program execution 
int main(void) {
   // initialize variables in definitions 
   int passes = 0; 
   int failures = 0; 
   int student = 1;  

   // process 10 students using counter-controlled loop 
   while (student <= 10) {
      // prompt user for input and obtain value from user 
      printf("%s", "Enter result (1=pass,2=fail): ");
      int result = 0; // one exam result 
      bool dataIsGood = false; // represents if the user inputted a 1/2, or invalid data

      do {
          int scanfReturnValue = scanf("%d", &result); // scanfReturnValue sees if the user input causes an error or not (1 = success) (0 = error)
          while ((getchar()) != '\n'); // clears the buffer so that the system doesn't take in enter

          if (scanfReturnValue == 1) {

              if (result <= 0 || result >= 3) { // if the scanf didn't return an error, check if it's a valid integer (1 or 2)
                  puts("Enter a valid integer: 1 = pass, 2 = fail");
              }
              else {
                  dataIsGood = true;
              }
          }
          else {
              puts("Enter a valid integer: 1 = pass, 2 = fail");
          }

      } while (!dataIsGood);

      // if result 1, increment passes 
      if (result == 1) {     
         passes = passes + 1;
      } // end if 
      else { // otherwise, increment failures 
         failures = failures + 1;
      } // end else 

      student = student + 1; // increment student counter  
   } // end while 

   // termination phase; display number of passes and failures 
   printf("Passed %d\n", passes);
   printf("Failed %d\n", failures);

   // if more than eight students passed, print "Bonus to instructor!"
   if (passes > 8) {
      puts("Bonus to instructor!");
   } // end if 
} // end function main 


/**************************************************************************
 * (C) Copyright 1992-2021 by Deitel & Associates, Inc. and               *
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
 *************************************************************************/

