/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/

#define DEP_NUM 10
#define OPTION1 1
#define OPTION2 2
#define OPTION3 3
#define OPTION4 4
#define EMPTY 0
#define DIGITS_NUM 3
#define END 0
#define DOUBLE_DIGIT 99

/*-------------------------------------------------------------------------
 The program organizes the army in 10 departments.
 The program gets a3 digit personal number of each soldier
 and prints data by request (1-4).
 -------------------------------------------------------------------------*/

void print_warriors_details();
void print_army_size(int size);
void print_biggest_platoon_and_size(int index, int size);
void print_active_platoons_and_avg(int size, double avg);
void print_show_army();
void print_number(int num);
void print_enter();
void print_star();
void print_space();


void armyOrganization();
int getWarriorsNum();
int calculateDepartment(int WarriorNumber);
void calculatesArmySize(int departments[], int DepartmentsAmount);
void calculatesLargestDepartment(int departments[], int DepartmentsAmount);
void nonEmptyDepartments(int departments[], int DepartmentsAmount);
void printDepartments(int departments[], int DepartmentsAmount);
double departmentAvgSize(int departments[], int DepartmentsAmount,
                         int nonEmptyDepNum);
void chooseOption(int WarriorNumber, int departments[],
                  int DepartmentAmount);



void chooseOption(int WarriorNumber, int departments[],
                  int DepartmentAmount){
    if (WarriorNumber == OPTION1) {
        calculatesArmySize(departments, DepartmentAmount);
        return;
    }
    if (WarriorNumber == OPTION2) {
        calculatesLargestDepartment(departments, DepartmentAmount);
        return;
    }
    if (WarriorNumber == OPTION3) {
        nonEmptyDepartments(departments, DepartmentAmount);
        return;
    }
    if (WarriorNumber == OPTION4) {
        printDepartments(departments, DepartmentAmount);
        return;
    }
    return;
}

//organizes the army and prints by request.
void armyOrganization(){
    int departments[DEP_NUM] = {0};//the departments
    int WarriorNumber = 0;// the number of each soldier
    
    print_warriors_details();
    WarriorNumber = getWarriorsNum(departments, DEP_NUM);
    
    //get numbers until gets num between 1-4.
    while(WarriorNumber > DOUBLE_DIGIT){
        
        departments[calculateDepartment(WarriorNumber)]++;
        WarriorNumber = getWarriorsNum(departments, DEP_NUM);
    }
    //checks what the user chose and prints the data.
    
    chooseOption(WarriorNumber, departments, DEP_NUM);
                                                        
    return;
}

//prints the soldiers of each department
void printDepartments(int departments[], int DepartmentsAmount){
    int MaxSoldiers = 0;
    
    print_show_army();
    
    for (int i=0; i<DepartmentsAmount; i++) {
        printf("%d", i);
        if (departments[i] >= MaxSoldiers) {
            MaxSoldiers = departments[i];
        }
    }
    printf("\n");
    
    for (int i=0; i<MaxSoldiers; i++) {
        for (int j=0; j<DepartmentsAmount; j++) {
            if (i<departments[j]) {
                print_star();
            }else{
                print_space();
            }
        }
        print_enter();
    }
    
    
    return;
}

/*prints the number of the non empty departments
 and prints the avg size of them*/
void nonEmptyDepartments(int departments[], int DepartmentsAmount){
    int Counter = 0;
    
    for (int i=0; i<DepartmentsAmount; i++) {
        if (departments[i] != EMPTY) {
            Counter++;
        }
    }
    
    print_active_platoons_and_avg(Counter, departmentAvgSize(departments, DepartmentsAmount, Counter));
    
}

//calculates the non empty departmnets avg size.
double departmentAvgSize(int departments[], int DepartmentsAmount,
                         int nonEmptyDepNum){
    double Sum = 0;
    
    for (int i=0; i<DepartmentsAmount; i++) {
        if (departments[i]!=EMPTY) {
            Sum += departments[i];
        }
    }
    
    return Sum/nonEmptyDepNum;
}

//calculates the largest department.
void calculatesLargestDepartment(int departments[], int DepartmentsAmount){
    int MaxDepartment = 0, MaxSoldiers = 0;
    
    for (int i=0; i<DepartmentsAmount; i++) {
        if (departments[i] >= MaxSoldiers) {
            MaxDepartment = i;
            MaxSoldiers = departments[i];
        }
    }
    print_biggest_platoon_and_size(MaxDepartment, MaxSoldiers);
    return;
}

//calculates the number of the soldiers in the army.
void calculatesArmySize(int departments[], int DepartmentsAmount){
    int Sum = 0;
    
    for (int i=0; i<DepartmentsAmount; i++) {
        Sum += departments[i];
    }
    print_army_size(Sum);
    return;
}

//calculate the department of each soldier by the sum of the digits.
int calculateDepartment(int WarriorNumber){
    int Sum = 0;
    
    for (int i=0; i<DIGITS_NUM; i++) {
        Sum += WarriorNumber%10;
        WarriorNumber /= 10;
    }
    
    return Sum%10;
}
//gets the warrior personal number.
int getWarriorsNum(){
    int WarriorNumber = 0;
    
    scanf("%d", &WarriorNumber);
    
    return WarriorNumber;
}

int main()
{
    armyOrganization();
    return END;
}

void print_warriors_details(){
    printf("Enter warriors id and demand at the end:\n\n");
}

void print_army_size(int size){
    printf("The army size is: %d\n", size);
}

void print_biggest_platoon_and_size(int index, int size){
    printf("The biggest platoon index is: %d and its size is: %d\n", index, size);
}

void print_active_platoons_and_avg(int size, double avg){
    printf("There are %d active platoons \n\nThe avg size of a platoon is: %.2f\n", size, avg);
}

void print_show_army(){
    printf("Show army!\n\n");
}

void print_number(int num){
    printf("%d", num);
}

void print_enter(){
    printf("\n");
}

void print_star(){
    printf("*");
}

void print_space(){
    printf(" ");
}
