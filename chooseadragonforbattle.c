/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/

#define YES 1
#define NO 0
#define END 0
#define FIRST_LETTER 1

/*-------------------------------------------------------------------------
  The program choose the appropriate dragon from 3 dragons, and print his name.
 if none of them fit the conditions, the program will print that too.
 -------------------------------------------------------------------------*/

int print_enter_enemy_name();
int print_dragonA_sent();
int print_dragonB_sent();
int print_dragonC_sent();
int print_no_dragon_sent();

char getLetter();
int checkS(char Letter);
void getEnemyName();
void selectDragon(int Counter, int Sum, int Mono, int CheckS);
int checkDragonA(int Counter, int Sum);
int checkDragonB(char PreviousLetter, char Letter, int Mono, int Counter);
int checkDragonC(int Counter, int CheckS);

//gets a letter from the user.
char getLetter(){
    char Letter = 0;
    print_enter_enemy_name();
    scanf("%c", &Letter);
    return Letter;
}

//gets the enemy name and print the appropriate dragon
void getEnemyName(){
    char Letter = 0, PreviousLetter = 0;
    int Sum = 0, Counter = 0, Mono=YES, CheckS = NO;
    
    Letter = getLetter();
    PreviousLetter = Letter;
    //get letters until the user enter '!'
    while (Letter != '!') {
        //checks if one of the letters is 's'
        if (checkS(Letter) && CheckS==NO) {
            CheckS = YES;
        }
        //checks if the name is mono up.
        Mono = checkDragonB(PreviousLetter, Letter, Mono, Counter);
        //save the value of the previous letter for comparison.
        PreviousLetter = Letter;
        // Calculates the sum of the ascii value of the letters
        Sum += Letter;
        Counter++;//Count the letters
        scanf("%c", &Letter);// Gets letter
    }
    selectDragon(Counter, Sum, Mono, CheckS);
}

// Checks if dragonA fits the conditions.
int checkDragonA(int Counter, int Sum){
    if (Sum%5 != 0 || Counter>4) {
        return YES;
    }
    return NO;
}

// Checks if dragonB fits the conditions.
int checkDragonB(char PreviousLetter, char Letter, int Mono, int Counter){
    if (Counter>0 && Mono == YES && PreviousLetter<Letter) {
        return YES;
    }else{
        if (!Counter) {
            return YES;
        }
    }
    return NO;
}

//Checks if at least one of the letters is 's'
int checkS(char Letter){
    if (Letter == 's') {
        return YES;
    }
    return NO;
}

// Checks if dragonC fits the conditions.
int checkDragonC(int Counter, int CheckS){
    if (!CheckS && (Counter<6)){
        return YES;
    }
    return NO;
}
                                                                           
//Selects the best dragon according to requirements and print the result.
void selectDragon(int Counter, int Sum, int Mono, int CheckS){
    int DragonB=NO;
    
    //Name with one letter isnt mono.
    if (Counter>FIRST_LETTER) {
        DragonB = Mono;
    }
    
    if (checkDragonC(Counter, CheckS)) {
        print_dragonC_sent();
        return;
    }
    if (DragonB) {
        print_dragonB_sent();
        return;
    }
    if (checkDragonA(Counter, Sum)) {
        print_dragonA_sent();
        return;
    }
    print_no_dragon_sent();
    return;
    
}




int main()
{
    
    getEnemyName();
    
    return END;
}

int print_enter_enemy_name(){
    return printf("Please enter enemy name:\n");
}

int print_dragonA_sent(){
   return printf("\nKhalisi sent dragonA into the battle!!!\n");
}

int print_dragonB_sent(){
   return printf("\nKhalisi sent dragonB into the battle!!!\n");
}

int print_dragonC_sent(){
    return printf("\nKhalisi sent dragonC into the battle!!!\n");
}

int print_no_dragon_sent(){
    return printf("\nNO Dragon has been sent into the battle!!!\n");
}
