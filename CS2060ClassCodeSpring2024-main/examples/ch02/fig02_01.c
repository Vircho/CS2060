// fig02_01.c
// A first program in C.
#include <stdio.h>

double calculateArea(double length, double width);

// function main begins program execution 
int main(void) {

	//Variables
	int length = 0;
	int width = 0;
	int area = 0;
	double avgOfWidthLength = 0;

   //Wlecome the user in
   printf("Welcome to C!\n");
   puts("Enter the length");
   
   //Take in length from the user's keyboard
   //scanfReturn = 
   scanf("%d", &length);
   //while (!scanfReturn <= 0) {
	  // puts("Please enter a valid number (>0)");
	   //scanfReturn = scanf("%d", &length);
   //}

   //Prompt the user to input width, scan in width from keyboard, & store the input in variable width
   puts("Now enter the width");
   //scanfReturn = 
   scanf("%d", &width);
   //while (scanfReturn <= 0) {
	  // puts("Please enter a valid number (>0)");
	   //scanfReturn = scanf("%d", &width);
   //}

  
   //Calculate area by multiplying length & width
   area = (length * width);

   //Print out all information, including the inputted length, inputted width, and calculated area
   printf("The length is: %d\n", length);
	printf("The width is: %d\n", width);
   printf("And so, the area is: %d\n", area);

   //Find the average of the width and length
   avgOfWidthLength = ((double)length + (double)width) / 2;
   printf("The average of the width & length is: %.1f\n", avgOfWidthLength);

   //Find the average length & width in a function
   area = calculateArea(length, width);
   printf("The area as returned from function calculateArea in main is: %d\n", area);

   return 0;
} // end function main 

// function calculateArea calculates area from passed length & width
double calculateArea(double length, double width) {

	double area = (length * width);
	printf("The area as calculated in function calculateArea is: %.1f\n", area);
	return area;

} // end function calculateArea



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
