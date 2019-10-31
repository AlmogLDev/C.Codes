

#include <stdio.h>


#define ASCII_VALUE 48

#include <stdio.h>

/*
 The program calculates the last digit of your ID number.
 you have 2 option:
 1) calculate the last digit. ('C')
 2) check if your last digit is legal or not. ('V')
 */

int main() {
    
    char Check = 0, DigitC = 0;
    int Digit = 0, Sum = 0, CalculateDigit = 0, CheckDigit = 0;
    
    printf("Please enter the letter C for calculating CheckDigit and the letter V for validating an ID by its CheckDigit:\n");
    
    if (scanf(" %c", &Check)<1) {
        printf("\nERROR");
        return 1;
    }
    
    if (Check == 'C') {
        
        printf("\nCalculating CheckDigit, please enter 8 digits:\n");
        
        if (scanf(" %c", &DigitC)<1) {// The program gets the first digit.
            printf("\nERROR");
            return 1;
        }
        if (DigitC<'0' || DigitC > '9') { // Checks if the user enter legal digit from 0 to 9.
            printf("\nERROR");
            return 1;
        }
        Digit = DigitC-ASCII_VALUE; //Calculates the digit (0-9) with ASCII Table.
        Sum = Digit;
        
        for (int i=0; i<7; i++) { //performs operations on each digit.
            
            if (scanf(" %c", &DigitC)<1) { // The program gets a digit.
                printf("\nERROR");
                return 1;
            }
            if (DigitC<'0' || DigitC > '9') {// Checks if the user enter legal digit from 0 to 9.
                printf("\nERROR");
                return 1;
            }
            Digit = DigitC-ASCII_VALUE;
            
            CalculateDigit = Digit;
            if (i%2 == 0) {//Performs actions on every second digit.
                CalculateDigit *= 2;
                if (CalculateDigit>9) {
                    Sum += CalculateDigit%10 + CalculateDigit/10;
                }else{
                    Sum += CalculateDigit;//Calculates the sum of all digits.
                }
            }else{
                Sum += CalculateDigit;
            }
            
        }
        
        if (Sum%10 == 0) {//Calculate the last digit.
            CheckDigit = 0;
        }else{
            CheckDigit = 10 - Sum%10;
        }
        printf("\nCheckDigit = %d", CheckDigit);
        
        
        
        
    }else if (Check == 'V'){
        printf("\nValidating ID, please enter 9 digits ID:\n");
        
        for (int i=0; i<8; i++) {
            if (scanf(" %c", &DigitC)<1) {
                printf("\nERROR");
                return 1;
            }
            if (DigitC<'0' || DigitC > '9') {
                printf("\nERROR");
                return 1;
            }
            Digit = DigitC - ASCII_VALUE;
            
            CalculateDigit = Digit;
            if (i%2 != 0) {
                CalculateDigit *= 2;
                if (CalculateDigit>9) {
                    Sum += CalculateDigit%10 + CalculateDigit/10;
                }else{
                    Sum += CalculateDigit;
                }
            }else{
                Sum += CalculateDigit;
            }
            
        }
        
        if (scanf(" %c", &DigitC)<1) {
            printf("\nERROR");
            return 1;
        }
        if (DigitC<'0' || DigitC > '9') {
            printf("\nERROR");
            return 1;
        }
        Digit = DigitC - ASCII_VALUE;
        CheckDigit = Digit;
        printf("\nYou have entered CheckDigit = %d\n", CheckDigit);
        
        if (Sum%10 == 0) {//Checks if the last digit entered by the user is legal.
            if (CheckDigit == 0) {
                printf("Calculated CheckDigit = %d\n", CheckDigit);
                printf("\nLegal ID :)");
            }else{
                printf("Calculated CheckDigit = %d\n", CheckDigit);
                printf("\nLegal ID :(");
            }
        }else{
            if (CheckDigit == 10 - Sum%10) {
                printf("Calculated CheckDigit = %d\n", 10 - Sum%10);
                printf("\nLegal ID :)");
            }else{
                printf("Calculated CheckDigit = %d\n", 10 - Sum%10);
                printf("\nLegal ID :(");
            }
        }
        
        
        
    }else{//If the user entered wrong letter, the program ends.
        printf("\nERROR");
        return 1;
    }
    
    
    
    return 0;
}
