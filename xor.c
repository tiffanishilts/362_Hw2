#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main (int argc, char *argv[])
{
    char inputComparator[] = "-i";
    char outputComparator[] = "-o";

    char comparisonStringIn[] = "stdin";
    char comparisonStringOut[] = "stdout";

    //fd in & out
    int fileDescIn;
    int fileDescOut;

    int numBytes;

    char *buffer = (char*)calloc(10001, sizeof(char));

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

    char* mask = (char*)calloc(11, sizeof(char));

    for(int j = 1; j < argc; j++)
    {
        if((strcmp(inputComparator, argv[j]) != 0) && (strcmp(outputComparator, argv[j]) != 0) && (strcmp(inputComparator, argv[(j - 1)]) != 0) && (strcmp(outputComparator, argv[(j - 1)]) != 0))
        {
            strcpy(mask, argv[j]);
        }
    }
    printf("%s\n", mask);

    for(int j = 0; j < argc; j++)
    {
        if(strcmp(inputComparator, argv[j]) == 0)
        {
            i = argv[j+1];
        }
        else if(strcmp(outputComparator, argv[j]) == 0)
        {
            o = argv[j+1];
        }
    }

    // file has been entered by user
    if((strcmp(comparisonStringIn, i)) != 0)
    {
        fileDescIn = open(i, O_RDONLY);

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
        fileDescOut = open(o, O_WRONLY);

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
        write(1, "Please enter a string of letters. Press ENTER when finished.\n", 62);
    }
    // read input and store in buffer
    while((numBytes = read(fileDescIn, buffer, 10000)) > 0)
        close(fileDescIn);

    // append null terminator
    buffer[strlen(buffer) - 2] = '\0';

    char* xorMask = (char*)calloc(10001, sizeof(char));
    char* results = (char*)calloc(10001, sizeof(char));

    strcpy(xorMask, mask);

    int bufferIndex = 0;
    int maskIndex = strlen(mask);
    int iterations = strlen(buffer) - strlen(mask);
    if(strlen(mask) < strlen(buffer))
    {
        for(int j = 0; j < iterations; j++)
        {
            xorMask[maskIndex++] = xorMask[j];
        }
    }

    for(int j = 0; j < strlen(buffer); j++)
    {
        results[j] = buffer[j]^xorMask[j];
    }

    char** printArray = malloc(strlen(results) * sizeof(char*));
    for(int j = 0; j < strlen(results); j++)
    {
        printArray[j] = calloc(2, sizeof(char));
        printArray[j][0] = results[j];
    }

    char tempPrintArray[strlen(buffer) + 1];
    for(int j = 0; j < strlen(buffer); j++)
    {
        strcpy(tempPrintArray, printArray[j]);
        write(fileDescOut, tempPrintArray, strlen(tempPrintArray));
    }
}
