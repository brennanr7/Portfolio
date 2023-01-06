#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>

//Struct
typedef struct ImageStorage
{
    int numRows, numColumns, numMatches, index;
    int *matchingX;
    int *matchingY;
    char** matrix;
    char* name;
}ImageStorage;

void populate(ImageStorage* storage, char* argv[], int argc);
void matches(ImageStorage* storage, char** patternArray, int patRow, int patColumn, int argc, int imageIndex);
int handleMatches(ImageStorage* storage, char** patternArray, int patRow, int patColumn, int argc, int imageIndex, int i, int j);
void printMatches(ImageStorage* storage, char** patternArray, int patRow, int patColumn, int imageIndex);
void printNames(ImageStorage* storage, int imageIndex);
void printNoMatchNames(ImageStorage* storage, int imageIndex);
void freeMemory(ImageStorage* storage, char** patternArray, int patRow, int patColumn, int imageIndex);

int main(int argc, char* argv[])
{
    //variables to store width, height
    int column = 0, row = 0;
    ImageStorage* pictureStorage = (ImageStorage*)calloc(argc - 2, sizeof(ImageStorage));


    //allocate filePath size, open file
    char filePath[strlen(argv[1])];
    strcpy(filePath, argv[1]);

    FILE* fp = fopen(filePath, "r");

    fscanf(fp, "%d", &row);
    fscanf(fp, "%d", &column);

    char** pattern = (char**)calloc(row+1, sizeof(char*));
    for(int i = 0; i < column; i++)
    {
        pattern[i] = (char*)calloc(column+1, sizeof(char*));
    }

    char tempArray[column];
    for(int i = 0; i < row; i++)
    {
        fscanf(fp, "%s", tempArray);
        for(int j = 0; j < column; j++)
        {
            pattern[i][j] = tempArray[j];
        }
    }
    fclose(fp);

    populate(pictureStorage, argv, argc);

    //go through each image in the image struct
    for(int i = 0; i < argc - 2; i++)
    {
        matches(pictureStorage, pattern, row, column, argc, i);
    }
    // for(int i = 0; i < argc - 2; i++)
    // {
    //     printNames(pictureStorage, i);
    // }
    for(int i = 0; i < argc - 2; i++)
    {
        printMatches(pictureStorage, pattern, row, column, i);
        //freeMemory(pictureStorage, pattern, row, column, i);
    }
    for(int i = 0; i < argc - 2; i++)
    {
        //printNoMatchNames(pictureStorage, i);
    }
    for(int i = 0; i < argc - 2; i++)
    {
        freeMemory(pictureStorage, pattern, row, column, i);
    }

    free(pictureStorage);
    free(pattern);
    return 0;
}

/* populate
*   
*   Brief: To populate the image matrix with image files and allocate memory to variables in the struct
*
*   Arg: storage[in] = pointer to the image struct
*   Arg: argv[in] = pointer to the arguments list
*   Arg: argc[in] = number of command line arguments
*
*   Returns: Void
*/
void populate(ImageStorage* storage, char* argv[], int argc)
{

    int imageIndex = 0;
    for(int i = 2; i < argc; i++)
    {
        int  row = 0, column = 0;
        char filePath[strlen(argv[i])];

        strcpy(filePath, argv[i]);

        FILE* fp = fopen(filePath, "r");
        char* base;

        storage[imageIndex].name = (char*)calloc(strlen(basename(argv[i]))+2, sizeof(char));
        storage[imageIndex].matchingX = (int*)calloc(1000, sizeof(int));
        storage[imageIndex].matchingY = (int*)calloc(1000, sizeof(int));
        
        base = basename(argv[i]);
        strcpy(storage[imageIndex].name, base);

        fscanf(fp, "%d", &column);
        fscanf(fp, "%d", &row);

        storage[imageIndex].numColumns = column;
        storage[imageIndex].numRows = row;
        storage[imageIndex].numMatches = 0;


        storage[imageIndex].matrix = (char**)calloc(storage[imageIndex].numRows, sizeof(char*));

        for(int x = 0; x < storage[imageIndex].numRows; x++)
        {
            storage[imageIndex].matrix[x] = (char*)calloc(storage[imageIndex].numColumns+1, sizeof(char));
            fscanf(fp, "%s", storage[imageIndex].matrix[x]);
        }

        storage[imageIndex].index = imageIndex;

        imageIndex++;

        fclose(fp);

    }

}

/* matches
*
*   Brief: The outer loop to iterate through the image matrix
*
*   Arg: storage[in] = pointer to the image struct
*   Arg: patternArray[in] = 2d array of the pattern file
*   Arg: patRow[in] = number of rows in the pattern matrix
*   Arg: patColumn[in] = number of columns in the pattern matrix
*   Arg: argc[in] = the number of command line arguments
*   Arg: imageIndex[in] = the image index corresponding to an image file path
*
*   Returns: void
*/
void matches(ImageStorage* storage, char** patternArray, int patRow, int patColumn, int argc, int imageIndex)
{
    int coordinateIndex = 0;
    // image rows
        for(int x = 0; x < storage[imageIndex].numRows; x++)
        {
            //image columns
            for(int y = 0; y < storage[imageIndex].numColumns; y++)
            {
                if(handleMatches(storage, patternArray, patRow, patColumn, argc, imageIndex, x, y) == 1)
                {
                    storage[imageIndex].matchingX[coordinateIndex] = x;
                    storage[imageIndex].matchingY[coordinateIndex] = y;
                    storage[imageIndex].numMatches++;
                    coordinateIndex++;
                }
            }
        }

}

/* handleMatches
*
*   Brief: The inner loop comparing the image matrix and pattern matrix
*
*   Arg: storage[in] = pointer to the image struct
*   Arg: patternArray[in] = 2d array of the pattern file
*   Arg: patRow[in] = number of rows in the pattern matrix
*   Arg: patColumn[in] = number of columns in the pattern matrix
*   Arg: argc[in] = the number of command line arguments
*   Arg: imageIndex[in] = the image index corresponding to an image file path
*   Arg: i[in] = the index of the first matrix pointer
*   Arg: j[in] = the index of the pointer to the second pointer of the matrix
*
*   Returns: an integer 0, if false, 1 if true
*/
int handleMatches(ImageStorage* storage, char** patternArray, int patRow, int patColumn, int argc, int imageIndex, int i, int j)
{
    for(int x = 0; x < patRow; x++)
    {
        for(int y = 0; y < patColumn; y++)
        {
            //out of bounds
            if(i + x >= storage[imageIndex].numRows || j + y >= storage[imageIndex].numColumns)
            {
                return 0;
            }

            if(storage[imageIndex].matrix[i + x][j + y] != patternArray[x][y])
            {
                return 0;
            }
        }
    }
    return 1;
}

/* printNames
*
*   Brief: printing the names of the image files who matched the pattern matrix
*
*   Arg: storage[in] = pointer to the image struct
*   Arg: imageIndex[in] = the image index corresponding to an image file path
*
*   Returns: void
*/
void printNames(ImageStorage* storage, int imageIndex)
{
    if(storage[imageIndex].numMatches == 0)
    {
        printf("%s\n", storage[imageIndex].name);
        return;
    }

}

void printNoMatchNames(ImageStorage* storage, int imageIndex)
{
    if(storage[imageIndex].numMatches == 0)
    {
        printf("%s\n", storage[imageIndex].name);
        return;
    }
}

/* handleMatches
*
*   Brief: The inner loop comparing the image matrix and pattern matrix
*
*   Arg: storage[in] = pointer to the image struct
*   Arg: patternArray[in] = 2d array of the pattern file
*   Arg: patRow[in] = number of rows in the pattern matrix
*   Arg: patColumn[in] = number of columns in the pattern matrix
*   Arg: imageIndex[in] = the image index corresponding to an image file path
*
*   Returns: void
*/
void printMatches(ImageStorage* storage, char** patternArray, int patRow, int patColumn, int imageIndex)
{
    if(storage[imageIndex].numMatches == 0)
    {
        printf("%s\n", storage[imageIndex].name);
        return;
    }
    else
    {
        printf("%s\n", storage[imageIndex].name);
        printf("\t%d ", storage[imageIndex].numMatches);
        for(int i = 0; i < storage[imageIndex].numMatches; i++)
        {
            printf("%d %d", storage[imageIndex].matchingX[i], storage[imageIndex].matchingY[i]);
            if(storage[imageIndex].numMatches > 1 && i != storage[imageIndex].numMatches - 1)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

/* handleMatches
*
*   Brief: Freeing the allocated memory
*
*   Arg: storage[in] = pointer to the image struct
*   Arg: patternArray[in] = 2d array of the pattern file
*   Arg: patRow[in] = number of rows in the pattern matrix
*   Arg: patColumn[in] = number of columns in the pattern matrix
*   Arg: imageIndex[in] = the image index corresponding to an image file path
*
*   Returns: void
*/
void freeMemory(ImageStorage* storage, char** patternArray, int patRow, int patColumn, int imageIndex)
{
    int size = storage[imageIndex].numRows;
    free(storage[imageIndex].matchingX);
    free(storage[imageIndex].matchingY);
    free(storage[imageIndex].name);
    for(int i = 0; i < size; i++)
    {
        free(storage[imageIndex].matrix[i]);
    }
    free(storage[imageIndex].matrix);
}