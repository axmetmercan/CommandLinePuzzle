#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define StringSize 255

typedef struct
{
char *word; //word and corresponding hint
char *clue;
int x; //Starting x and y positions
int y;
char direction[StringSize]; //H for horizontal, V for vertical
int f; //solved or not
} Word_t;
Word_t* loadTextFile( FILE* myFile, int nrWords );
void displayBoard(int rows, int cols, char** myBoard);
int isBoardFilled(int rows, int cols, char** myBoard);
char** createArray(int rows, int cols);
int findIndex(int arr[], int size, int val);
void playGame(char** myBoard, int word_numbers, Word_t *words, int x, int y, int countToFinish);
char** updateBoard(char** myBoard, Word_t *words, int solve);

int main(){
    // we define some necessary variables
    char scanFileName[StringSize];
    char line[StringSize];
    char s[StringSize] = " ";
    char** board;
    Word_t* array;
    int number_of_rows, number_of_colums, number_of_words;
    char file_name;
    printf("Please Enter the File Name First: ");
    // ıt takes the name of the file from the user.
    scanf("%s",scanFileName);
    //strcpy(scanFileName, "puzzle2010Long.txt");
    // File pointer to the File
    FILE *myFile = fopen(scanFileName, "r");
    //Reads the first line
    fgets(line,255,myFile);
    number_of_rows = atoi((int)strtok(line,s));
    number_of_colums = atoi((int)strtok(NULL,s));
    number_of_words = atoi((int)strtok(NULL,s));
    int word_numbers = number_of_words;

    // Dynamic Array of Word_t type
    Word_t* Array =  malloc(number_of_words * sizeof(Word_t)) ;
    // Assign the Array
    Array = loadTextFile(myFile, number_of_words);
    // For calling the create array function
    board = createArray(number_of_rows,number_of_colums);
    // initially update the board with words and # symbols.
    updateBoard(board,Array, number_of_words);
    // it starts the game
    playGame( board, word_numbers, Array, number_of_colums, number_of_rows, number_of_words);
    return 0;
}

Word_t* loadTextFile( FILE* myFile, int nrWords ){

    // Holds the values of  textfile for a temp time to return to original Array.
    Word_t* tempArray = (Word_t*)malloc(( sizeof(Word_t)*nrWords) );
    char direction_of[2];
    char word1[StringSize];
    char clue1[StringSize];
    int len;
    char line[StringSize];
    //printf("%d", nrWords);
    // in a while loop we reads the important places in file and we assign them to their struct types.
    int i =0;
    while(fgets(line, StringSize,myFile)!= NULL){
        strcpy(direction_of,strtok(line," ") ) ;
        strcpy(tempArray[i].direction, direction_of);
        tempArray[i].y =atoi( strtok(NULL," "));
        tempArray[i].x = atoi(strtok(NULL," "));
        tempArray[i].f = 0;
        strcpy(word1 ,strtok(NULL, " "));
        len = strlen(word1);
        tempArray[i].word = (char *)malloc (len+1);
        strcpy(tempArray[i].word,word1);
        strcpy(clue1 ,strtok(NULL, "\0"));
        len = strlen(clue1);
        tempArray[i].clue = (char *)malloc (len+1);
        strcpy(tempArray[i].clue,clue1);
    i++;

  }
    // it returns the struct named tempArray
    return tempArray;
}

// Dynamicaly we are creating 2d array with calloc to hold the all values of struct type
char** createArray(int rows, int cols){
    int i = 0, j =0, count = 0;

    char **arr = (char**) calloc(rows, sizeof(char*));

    for ( i = 0; i < rows; i++ ){
        arr[i] = (char*) calloc(cols, sizeof(char));
    }
    // initially adds all values assinged to '#' in 2d array
    for (i =0; i < rows; i++)
        for (j =0; j< cols; j++){
            arr[i][j] = '#';
                     }
    return arr;

}

//ıt displays the table of arrays as in the documentation file
void displayBoard(int rows, int cols, char** myBoard){
    //in a for loop it prints the col numbers.
    int i=1, j=0;
    printf("\t");
    for (i;i<=cols; i++){
        printf("%2d  ", i );
    }
    printf("\n");
    printf("\t");
    // just make it same as the doc.
    for (i=1;i<=cols; i++){
        printf("%4s","-- ");
    }
    printf("\n");
    // ıt prints the values in the array in a loop and their row numbers respectively with a seperate symbol |
    for (i=1; i <= rows; i++){
        printf("%d\t|", i);
        for (j=1; j<=cols; j++){
            printf("%c   ", myBoard[i-1][j-1]);
        }
        printf("\n");
    }
    printf(" \t -_-_-_-_-_-_-_-_-_-_-_\n");

}
// this function checks all the values in 2d array with nested loop whether is there an empty character in board
int isBoardFilled(int rows, int cols, char** myBoard){

    int i,j;
    for (i=0; i<rows; i++)
        for(j=0; j<cols; j++){
            if (myBoard[i][j] == '_')
                return 0;
        }
    return 1;
}
// ı could not use that function but i realised that after finishing game. I just implement it as wished in doc. file.
int findIndex(int arr[], int size, int val){
    int i;
    for (i=0;i<size;i++)
        if (val == arr[i])
            return 1;
}

//updates the board with the word characters respectively to the txt file
char** updateBoard(char** myBoard, Word_t *words, int solve){

    int k ;
    char b = '#';
    char a = '_';
    int i,j;
    // in a loop of question numbers
    for (i=0; i< solve; i++){
    //checks each words direction and f value than it replaces it with the wished character.
        // vertical direction and solved
        if ( strcmp(words[i].direction, "V") ==0 &&words[i].f == 1){
                for (j=0; j< strlen(words[i].word); j++){
                     if (myBoard[words[i].y+j-1][words[i].x-1] != b)
                        myBoard[words[i].y+j-1][words[i].x-1] = words[i].word[j];
                }
        }
        // h direction and solved
        else if (words[i].f == 1){
            for (j=0; j< strlen(words[i].word); j++){
                 if (myBoard[words[i].y-1][words[i].x+j-1] != b)
                        myBoard[words[i].y-1][words[i].x+j-1] = words[i].word[j];
            }

        }
        // vertical direction and unsolved
        if ( strcmp(words[i].direction, "V") ==0 && words[i].f == 0){

            for (j=0; j< strlen(words[i].word); j++){
                    if (myBoard[words[i].y+j-1][words[i].x-1]  == b || myBoard[words[i].y+j-1][words[i].x-1]  == a  )
                        myBoard[words[i].y+j-1][words[i].x-1] = a;
            }
        }

        // horizontal direction and unsolved
        else if ( words[i].f == 0){
            for (j=0; j< strlen(words[i].word); j++){
                   if (myBoard[words[i].y-1][words[i].x+j-1] == b || myBoard[words[i].y-1][words[i].x+j-1] == a)
                        myBoard[words[i].y-1][words[i].x+j-1] = a;
            }
        }
    }

}

void playGame(char** myBoard, int word_numbers, Word_t *words, int x, int y, int countToFinish){
    printf("*** CENG2010 Midterm Puzzle Game ***\n");
    displayBoard(y,x,myBoard);
    int questNo;
    int solved_before[word_numbers];
    int a;
    for (a =0; a<word_numbers;a++)
        solved_before[a] = -5;

    int i,elem, flag;
    while (countToFinish != 0 && isBoardFilled(y, x, myBoard) == 0 && questNo != -1){
        printf("\nAsk For Hint:\n");
        printf("# \tDirection \trow \tcol\n");
        printf("-------------------------------------\n");

        // in a nested loop it checks the question number if it is in the solved question list or not
        // if it is solved, it wont print it again.
        for (i = 1 ; i <= word_numbers; i++){
            for (elem =0; elem<word_numbers;elem++){
                if (solved_before[elem] == i-1){
                   
                    i++;
                    }
            }
            // it prints the value of questions and their coordinates.
            if (strcmp(words[i-1].direction, "V")==0 && i<word_numbers+1)
                printf("%d \tVertical \t%d \t %d\n", i, words[i-1].y, words[i-1].x);
            else if(i<word_numbers+1){
                printf("%d \tHorizontal \t%d \t %d\n", i, words[i-1].y, words[i-1].x);
            }
        }
        printf("Enter -1 to exit \nWhich word to solve next?: ");
        scanf("%d", &questNo);
        if (questNo == -1){
            printf("\nProgram Closing");
            break;
        }
        flag = 0;
        for (i = 0; i<word_numbers; i++){
             if (solved_before[i] == questNo-1){
                flag = 1;
             }
        }
        // checks the user input if the question solved or invalid input
        if (questNo < -1 || questNo > word_numbers ||flag == 1){
            printf("\nWrong input type or it is a solved question please enter a number between -1 and %d which is unsolved.\nEnter -1 to exit.",word_numbers);
            //scanf("%d: ", &questNo);
            displayBoard(y,x,myBoard);
            countToFinish++;
        }
        // prints tbe user clue and waits for iput for solution
        else if (flag != 1){
            printf("Current Hint: %s", words[questNo-1].clue);
            char sol[StringSize];
            printf("Enter Your Solution: ");
            scanf("%s", &sol);
            // compares the input with the answer of question and if it same it just updates the board
            if (strcmp(sol, words[questNo-1].word)==0){
                words[questNo-1].f = 1;
                solved_before[questNo-1] = questNo-1;
                printf("\nCorrect!");
            }
            // if the answer is wrong prints
            else{
                printf("\nWRONG ANSWER PLEASE TRY AGAIN");
                countToFinish++;
            }
            printf("\nCurrent Puzzle: \n");
            // updates the board.
            updateBoard(myBoard,words, word_numbers);

            displayBoard(y,x,myBoard);
            // for each movement it checks whether the board is fulled or not.
            if ( isBoardFilled(y,x, myBoard) == 1){
                updateBoard(myBoard,words, word_numbers);
                printf("Congratulations, you beat the puzzle... \n");
            }
        }
        //if user enters different input it just increment by 1 the counter to finish game.
        else
            countToFinish++;

        countToFinish--;
    }
}
