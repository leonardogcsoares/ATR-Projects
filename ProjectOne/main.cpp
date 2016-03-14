#include <iostream>
#include <stdio.h>

using namespace std;

int NUM_ROWS;
int NUM_COLS;

void printMaze(char **maze, int rows, int cols) {

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}

void printMazeToFile(char **maze, int rows, int cols) {

    FILE *fp = fopen("mazeResolved.txt", "w");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(fp,"%c", maze[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}


char goNextStep(char **maze, int currentRow, int currentCol) {

    if (currentRow < 0 || currentRow > NUM_ROWS ||
            currentCol < 0 || currentCol > NUM_COLS)
        return ' ';

    else if (maze[currentRow][currentCol] == 's') {
        return 's';
    }

    else if (maze[currentRow][currentCol] == 'x' ||
            maze[currentRow][currentCol] == 'e') {

        maze[currentRow][currentCol] = '-';


        if (goNextStep(maze, currentRow-1, currentCol) == 's')
            return 's';
        else if (goNextStep(maze, currentRow, currentCol-1) == 's'){
            return 's';
        }
        else if (goNextStep(maze, currentRow, currentCol+1) == 's') {
            return 's';
        }
        else if (goNextStep(maze, currentRow+1, currentCol) == 's') {
            return 's';
        }
        else
            return ' ';

//        goNextStep(maze, currentRow-1, currentCol);
//        goNextStep(maze, currentRow, currentCol-1);
//        goNextStep(maze, currentRow, currentCol+1);
//        goNextStep(maze, currentRow+1, currentCol);
    }

    else if (maze[currentRow][currentCol] == '#')
        return  ' ';


};

int main() {

    FILE *fp = fopen("maze1.txt", "r");

    char someChar;

    fscanf(fp, "%d %d", &NUM_ROWS, &NUM_COLS);

    // Represents the first Enter Character
    fscanf(fp, "%c", &someChar);

    char **maze = new char*[NUM_ROWS];
    for (int i = 0; i < NUM_ROWS; ++i) {
        maze[i] = new char[NUM_COLS];
    }

    for (int i = 0; i < NUM_ROWS; i++) {
        // We use numCols + 1 while reading due to the \n characters at the end of the lines
        for (int j = 0; j < NUM_COLS + 1; j++) {
            char value = '1';
            fscanf(fp, "%c", &value);
            if (value != '\n') {
                maze[i][j] = value;
            }
        }
    }


    // The maze starts at Row=4 and Col=0, character "e"
    goNextStep(maze, 4, 0);
    printMazeToFile(maze, NUM_ROWS, NUM_COLS);


    // Dealloc maze pointer and closes the file.
    for (int i = 0; i < NUM_ROWS; ++i)
        delete [] maze[i];
    delete [] maze;
    fclose(fp);

    return 0;
}