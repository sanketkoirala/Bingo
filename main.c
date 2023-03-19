
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define ROWS 5
#define COLS 5

void fillArray(int bingo[ROWS][COLS]);
void printArray(int bingo[ROWS][COLS]);
int newRandomNumber(int allPicked[], int *num);
int isNumberInBingo(int bingo[ROWS][COLS], int *num, int *containsNumber, char *userResponse);
void askUser(int *containsNumber, char *userResponse);
int checkRowsEqual(int bingo[ROWS][COLS], int *rowsEqual);
int checkColsEqual(int bingo[ROWS][COLS], int *colsEqual);
int checkDiagonalsEqual(int bingo[ROWS][COLS], int *diagonalsEqual);

int main()
{
    int bingo[ROWS][COLS];
    srand(time(0));
    fillArray(bingo);
    int allPicked[75] = {};

    int newNumberVal;
    int containsNumberVal;
    char userResponseVal;

    int rowEqualVal;
    int colsEqualVal;
    int diagonalsEqualVal;

    //stores bool value if the rows/cols/diagonals are filled
    int *rowsEqual = &rowEqualVal;
    int *colsEqual = &colsEqualVal;
    int *diagonalsEqual = &diagonalsEqualVal;


    int *newNumber = &newNumberVal;
    int *containsNumber = &containsNumberVal;
    char *userResponse = &userResponseVal;


    do
    {

        printArray(bingo);
        newRandomNumber(allPicked, newNumber);
        isNumberInBingo(bingo, newNumber, containsNumber, userResponse);
        askUser(containsNumber, userResponse);
        isNumberInBingo(bingo, newNumber, containsNumber, userResponse);

        checkRowsEqual(bingo, rowsEqual);
        checkColsEqual(bingo, colsEqual);
        checkDiagonalsEqual(bingo, diagonalsEqual);

        if(*rowsEqual==1)
        {
            printf("\n\n");
            printArray(bingo);
            printf("You filled out a row - BINGO!!!");
        }

        if(*colsEqual==1)
        {
            printf("\n\n");
            printArray(bingo);
            printf("You filled out a column - BINGO!!!");
        }

        if(*diagonalsEqual==1)
        {
            printf("\n\n");
            printArray(bingo);
            printf("You filled out a diagonal - BINGO!!!");
        }
    }
    while ((!(*rowsEqual) && !(*colsEqual)) && (!(*diagonalsEqual)));
    return 0;
}

void fillArray(int bingo[ROWS][COLS])
{
    int allNumbers[ROWS*COLS] = {0}; // initialize all elements to 0
    int index = 0;

    // Assign unique random numbers to the bingo array
    for (int j = 0; j < COLS; j++)
    {
        for (int i = 0; i < ROWS; i++)
        {
            int num = (rand() % 15) + (15 * j) + 1;
            int found = 0;
            for (int k = 0; k < index && !found; k++)
            {
                found = (allNumbers[k] == num);
            }
            if (found)
            {
                // Number already exists, generate a new one
                i--; // repeat for the same position
            }
            else
            {
                // Number is unique, assign it to the bingo array
                bingo[i][j] = num;
                allNumbers[index++] = num;
            }
        }
    }
    //set the center of the array to 0 as per requirement
    bingo[2][2] = 0;
}


void printArray(int bingo[ROWS][COLS])
{
    printf("     B\t      I\t       N\t     G\t     O\n");
    for (int k=0; k<46; k++)
    {
        //prints the border of bingo box
        printf("-");
    }
    printf("\n");

    for(int i = 0; i < ROWS; i++)
    {
        for (int j =0; j< COLS; j++)
        {
            //properly align the numbers
            if (bingo[i][j]>0 && bingo[i][j]<10)
            {
                printf("|    %d   ",bingo[i][j]);
            }
            else if (bingo[i][j]==0)
            {
                //set checked number (0 to X)
                printf("|    X   ");
            }
            else {
                printf("|   %d   ",bingo[i][j]);
            }

        }
        printf("|\n");
        for (int k=0; k<46; k++)
        {
            printf("-");
        }
        printf("\n");
    }
}



int newRandomNumber (int allPicked[], int *num) {
    *num = rand() % 75 + 1;
    int found = 0;
    for (int i = 0; i < 75 && !found; i++)
    {
        if (allPicked[i] == *num)
        {
            int newNum = rand() % 75 + 1;
            *num = newNum;
            i = -1;
            found = 1;
        }
    }


    if (1<=*num && *num<=15)
    {
        printf("\nThe next number is B%d", *num );
    }

    else if (16<=*num && *num<=30)
    {
        printf("\nThe next number is I%d", *num );
    }

    else if (31<=*num && *num<=45)
    {
        printf("\nThe next number is N%d", *num );
    }

    else if (46<=*num && *num<=60)
    {
        printf("\nThe next number is G%d", *num );
    }
    else
    {
        printf("\nThe next number is O%d", *num );
    }
    printf("\n");
    return *num;
}

int isNumberInBingo(int bingo[ROWS][COLS], int *num, int *containsNumber, char *userResponse)
{
    *containsNumber = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if ((bingo[i][j] == *num) && (*userResponse == 'Y' || *userResponse == 'y'))
            {
                bingo[i][j] = 0;
                *containsNumber = 1;
            }
        }
    }
    return *containsNumber;
}

void askUser(int *containsNumber, char *userResponse)
{
    int isCheating = 0; // flag to indicate if user is trying to cheat
    printf("Do you have it? (Y/N) ");
    scanf(" %c", userResponse);
    if ((*userResponse == 'Y' || *userResponse == 'y') && *containsNumber == 0)
    {
        printf("Are you trying to cheat?\n");
    }
}

int checkRowsEqual(int bingo[ROWS][COLS], int *rowsEqual)
{
    int foundEqualRow = 0;
    for (int i = 0; i < ROWS && !foundEqualRow; i++)
    {
        *rowsEqual = 1;
        for (int j = 0; j < COLS && *rowsEqual; j++)
        {
            if (bingo[i][j] != bingo[i][0])
            {
                *rowsEqual = 0;
            }
        }
        foundEqualRow = *rowsEqual;
    }
    return *rowsEqual;
}

int checkColsEqual(int bingo[ROWS][COLS], int *colsEqual)
{
    int foundEqualCol = 0;
    for (int i = 0; i < COLS && !foundEqualCol; i++)
    {
        *colsEqual = 1;
        for (int j = 0; j < ROWS && *colsEqual; j++)
        {
            if (bingo[j][i] != bingo[0][i])
            {
                *colsEqual = 0;
            }
        }
        foundEqualCol = *colsEqual;
    }
    return *colsEqual;
}

int checkDiagonalsEqual(int bingo[ROWS][COLS], int *diagonalsEqual)
{
    int diagLtoRFlag = 1;
    int diagRtoLFlag = 1;

    // Check diagonal from top-left to bottom-right
    for (int i = 0; i < ROWS && diagLtoRFlag; i++)
    {
        if (bingo[i][i] != bingo[0][0])
        {
            diagLtoRFlag = 0;
        }
    }

    // Check diagonal from top-right to bottom-left
    for (int i = 0; i < ROWS && diagRtoLFlag; i++)
    {
        if (bingo[i][4-i] != bingo[0][4])
        {
            diagRtoLFlag = 0;
        }
    }
    // Return true if either diagonal is equal
    *diagonalsEqual =  diagLtoRFlag || diagRtoLFlag ;
    return *diagonalsEqual;
}

