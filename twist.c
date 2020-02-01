#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main (int argc, char *argv[])
{
    // creating flag string variables for strcmp
    char inputFile[] = "-i";
    char outputFile[] = "-o";
    char blockNum[] = "-b";

    char *buffer = (char*)calloc(10001, sizeof(char));
    char comparisonStringIn[] = "stdin";
    char comparisonStringOut[] = "stdout";
    //fd in & out
    int fileDescIn;
    int fileDescOut;

    int numBytes;
    int numBlocks;


    // initialize default

    char* i = malloc(sizeof(char) * 1001);
    if (!i)
    {
        write(STDERR_FILENO, "Could not create Input File...exiting\n", 39);
        exit(1);
    }
    i = "stdin";

    char* o = malloc(sizeof(char) * 1001);
    if (!o)
    {
        write(STDERR_FILENO, "Could not create Output File...exiting\n", 40);
        exit(1);
    }
    o = "stdout";

    int b = 10;

    // replacing arguments with flags found in argv array

    for(int j = 0; j < argc; j++)
    {
        if(strcmp(inputFile, argv[j]) == 0)
        {
            i = (argv[j+1]);
        }
        else if(strcmp(outputFile, argv[j]) == 0)
        {
            o = argv[j+1];
        }
        else if(strcmp(blockNum, argv[j]) == 0)
        {
            b = atoi(argv[j+1]);
        }
    }

    // error checking block size
    if(b > 999)
    {
        write(STDERR_FILENO, "Block size is too large...exiting\n", 35);
        exit(1);
    }

    // file has been entered by user
    if((strcmp(comparisonStringIn, i)) != 0)
    {
        fileDescIn = open("i", O_RDONLY);

        if (fileDescIn < 0)
        {
            write(STDERR_FILENO, "Could not open input file...exiting\n", 37);
            exit(1);
        }
    }


    // if user requests no file entry or does not specify
    if((strcmp(comparisonStringIn, i)) == 0)
    {
        fileDescIn = 0;     //STDIN
    }

    // file has been entered by user
    if((strcmp(comparisonStringOut, o)) != 0)
    {
        fileDescOut = open("o", O_WRONLY);

        if (fileDescOut < 0)
        {
            write(STDERR_FILENO, "Could not open output file...exiting\n", 38);
            exit(1);
        }
    }

    // if user requests no file entry or does not specify
    if((strcmp(comparisonStringOut, o)) == 0)
    {
        fileDescOut = 1;        //STDOUT
    }

    // encouragement
    if (fileDescIn != 0)
    {
        write(1, "Success! Reading file...\n", 24);
    }

    // user provides string of characters to reverse
    if(fileDescIn == 0)
    {
        write(1, "Please enter a string of letters. Press ENTER when finished\n", 61);
    }

    while((numBytes = read(fileDescIn, buffer, 10000)) > 0)

        close(fileDescIn);
        buffer[strlen(buffer) - 2] = '\0';

    char userInput[strlen(buffer) + 1];

    for (int j = 0; j <= strlen(buffer); j++)
    {
        userInput[j] = buffer[j];
    }

    char* tempCharArray = (char*)calloc((strlen(userInput) + 1), sizeof(char));
    int lastElement = b - 1;

    if(strlen(userInput) < b){
        lastElement = strlen(userInput) - 1;
    }

    for (int j = 0; j <= strlen(userInput); j++)
    {
        if(j % b == 0)
        {
            for(int k = j; k < (j + b); k++)
            {
                tempCharArray[lastElement--] = userInput[k];
            }
            write(fileDescOut, tempCharArray, strlen(tempCharArray));
        }
    }
}
