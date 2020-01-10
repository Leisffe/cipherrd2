#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "encodedcharacter.h"
#include "eclist.h"

int nextSystem(int previousNumber)
{
    return (previousNumber % 8) + 2;
}

void exit_on_error(char * error_msg, EcList * ecList)
{
    if(error_msg)
    {
        printf("error: %s", error_msg);
        list_free(ecList);
        exit(1);
    }
}

void readWholeFile(const char * fname, char ** buffer, size_t* size)
{
	FILE* f = fopen(fname, "r");
	fseek(f, 0, SEEK_END);

    size_t fsize = (size_t)ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

    *buffer = malloc(fsize + 1);
    fread(*buffer, 1, fsize, f);
    fclose(f);

    (*buffer)[fsize] = 0;
    *size = fsize;
}

bool skip(int c)
{
    return c == '\r' || c == '\n' || c == EOF; // EOF probably unnecessary
}

void encode(const char * inputFile, const char * outputFile)
{
    char * data;
    size_t dataLen;
    readWholeFile(inputFile, &data, &dataLen);

    int previousNumber = 0;
    EcList ecList;
    list_init(&ecList);
    char * error_msg = NULL;
    for(size_t i = 0; i < dataLen; ++i)
    {
        if(skip(data[i]))
            continue;

        int system = nextSystem(previousNumber);
        previousNumber = data[i];
        EncodedCharacter ec = encodeCharacter(data[i], system, &error_msg);
        exit_on_error(error_msg, &ecList);
        list_append(&ecList, ec);
    }

    list_writeToFile(ecList, outputFile);
    list_free(&ecList);
}

char * decode(const char * data)
{
    return "react.js";
}

int main()
{
    printf("encoding...\n");
    encode("C:\\Users\\timot\\source\\repos\\CipherRD\\input.txt", "C:\\Users\\timot\\source\\repos\\CipherRD\\output.txt");
    printf("done!\n");

    return 0;
}
