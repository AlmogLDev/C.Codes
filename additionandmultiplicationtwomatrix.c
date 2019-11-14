/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
#define ERROR 1
#define END 0
#define N 25

/*-------------------------------------------------------------------------
  this program gets 2 matrix and the user choose from 2 actions:
 1) matrix1+matrix2
 2) matrix1*matrix2
 -------------------------------------------------------------------------*/
                                                                           
void print_enter_matrix_size();
void print_enter_first_matrix();
void print_enter_second_matrix();
void print_invalid_input();
void print_enter_required_operation();
void print_number(int number);
void print_enter();


int getRowLength();
void matrixSum(int matrixOne[N][N], int rowLength, int matrixTwo[N][N]);
int getMatrix(int Size, int matrix[N][N]);
int chooseAction(int matrixOne[N][N], int rowLength, int matrixtwo[N][N]);
void matrixMulti(int matrixOne[N][N], int rowLength, int matrixTwo[N][N]);


//multiple matrix1 and matrix2
void matrixMulti(int matrixOne[N][N], int rowLength, int matrixTwo[N][N]){
    int Sum = 0;
    
    for (int i=0; i<rowLength; i++) {
        for (int k=0; k<rowLength; k++) {
            for (int j=0; j<rowLength; j++) {
                Sum += matrixOne[i][j]*matrixTwo[j][k];
            }
            print_number(Sum);
            Sum = 0;
        }
        print_enter();
        Sum = 0;
    }
}
//the user choose one option: addition or multiplication
int chooseAction(int matrixOne[N][N], int rowLength, int matrixtwo[N][N]){
    char Action = 0;
    print_enter_required_operation();
    scanf(" %c", &Action);
    if (Action == '+') {
        matrixSum(matrixOne, rowLength, matrixtwo);
        return END;
    }
    if (Action == '*') {
        matrixMulti(matrixOne, rowLength, matrixtwo);
        return END;
    }
    return ERROR;
}

//add matrix1 to matrix2
void matrixSum(int matrixOne[N][N], int rowLength, int matrixTwo[N][N]){
    
    for (int i=0; i<rowLength; i++) {
        for (int j=0; j<rowLength; j++) {
            print_number(matrixOne[i][j]+matrixTwo[i][j]);
        }
        print_enter();
    }
    
    
    
    return;
}
//gets matrix from the user
int getMatrix(int Size, int matrix[N][N]){
    
    for (int i=0; i<Size; i++) {
        for (int j=0; j<Size; j++) {
            if (scanf("%d", &matrix[i][j])<1) {
                print_invalid_input();
                return ERROR;
            }
        }
    }
    return END;
}
//get the matrix size from the user
int getRowLength(){
    int Size = 0;
    
    print_enter_matrix_size();
    scanf("%d", &Size);

    return Size;
}

//the main function, gets 2 matrix and פerforms user selected actions
int main()
{
    int Size = 0;
    int matrixOne[N][N] = {{0}};
    int matrixTwo[N][N] = {{0}};
    
    Size = getRowLength();
    
    print_enter_first_matrix();
    if (getMatrix(Size, matrixOne)) {
        return ERROR;
    }
    print_enter_second_matrix();
    if (getMatrix(Size, matrixTwo)) {
        return ERROR;
    }
    if (chooseAction(matrixOne, Size, matrixTwo) == ERROR) {
        print_invalid_input();
        return ERROR;
    }
    
    return END;
}

void print_enter_matrix_size(){
    printf("Please enter the matrix size:\n");
}

void print_enter_first_matrix(){
    printf("Please enter the first matrix:\n");
}

void print_enter_second_matrix(){
    printf("Please enter the second matrix:\n");
}

void print_invalid_input(){
    printf("Invalid input.");
}

void print_enter_required_operation(){
    printf("Please enter the required operation:\n");
}

void print_number(int number){
    printf("%d ", number);
}

void print_enter(){
    printf("\n");
}
