

#include <stdio.h>

#define ASCII_VALUE 48


 /*
  The program decode a word from a number wich entered by the user.
  The "rules" are:
  1) if the ascii value of the small letter is even, so the program prints the big letter.
  2) if the ascii value of the small letter is odd, so the program prints the big letter.
  3) Each letter in the original word is encoded by the high value of the small letter corresponding to it in the reverse order. for example : 79 => a (a=97).
  */


int main() {
    
    char EncodedWordLetter = 0;
    int Sum = 0;
    
    printf("Enter an encoded word and I'll do my best:\n");
    if (scanf("%c", &EncodedWordLetter) == EOF) { // Checks that the input is not EOF.
        printf("\nThere is nothing there :(");
        return 1;
    }
    Sum = ((int)EncodedWordLetter - ASCII_VALUE); // Calculates the Sum of the digits before the decode.
    
    if (scanf("%c", &EncodedWordLetter) == EOF) {
        printf("\nThere is nothing there :(");
        return 1;
    }
    Sum += ((int)EncodedWordLetter - ASCII_VALUE)*10;
    
    if ((Sum>='a' && Sum<='z') && (Sum-'a')%2!=0) {// Checks if the sum is odd or even.
        printf("The decoded word is: %c", (Sum-'a')+'A');
    }else if ((Sum>='a' && Sum<='z') && (Sum-'a')%2==0){
        printf("The decoded word is: %c", Sum);
    }else if (scanf("%c", &EncodedWordLetter) == EOF){
            printf("\nThere is nothing there :(");
            return 1;
    }else{
        Sum += ((int)EncodedWordLetter - ASCII_VALUE)*100;
        if ((Sum>='a' && Sum<='z') && (Sum-'a')%2!=0) {
            printf("The decoded word is: %c", (Sum-'a')+'A');
        }else if ((Sum>='a' && Sum<='z') && (Sum-'a')%2==0){
            printf("The decoded word is: %c", Sum);
        }else{
            printf("\nThere is nothing there :(");// If the user entered wrong input the program ends.
            return 1;
        }
    }
    Sum = 0;
    
    while (scanf("%c", &EncodedWordLetter) != EOF) {// Gets input from user untill EOF or wrong input.
        Sum += ((int)EncodedWordLetter - ASCII_VALUE);
        if (scanf("%c", &EncodedWordLetter) == EOF) {
            break;
        }
        Sum += ((int)EncodedWordLetter - ASCII_VALUE)*10;
        if ((Sum>='a' && Sum<='z') && (Sum-'a')%2!=0) {
            printf("%c", (Sum-'a')+'A');
        }else if ((Sum>='a' && Sum<='z') && (Sum-'a')%2==0){
            printf("%c", Sum);
        }else{
            if (scanf("%c", &EncodedWordLetter) == EOF) {
                break;
            }
            Sum += ((int)EncodedWordLetter - ASCII_VALUE)*100;
            if ((Sum>='a' && Sum<='z') && (Sum-'a')%2!=0) {
                printf("%c", (Sum-'a')+'A');
            }else if ((Sum>='a' && Sum<='z') && (Sum-'a')%2==0){
                printf("%c", Sum);
            }else{
                break;
            }
            
        }
        Sum = 0;
    }
    
    printf("\nDone and even had time for coffee :)");
    
    
    
    return 0;
}
