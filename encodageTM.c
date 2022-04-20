#include "encodageTM.h"

STRINGLENGTH *ackTxtFileReading(char *filePath)
{
    char buffer[50];
    STRINGLENGTH *str;
    FILE *inputFile = fopen(filePath, "r");
    if (inputFile == NULL)
        printf("impossible d'ouvrir le fichier\n");
    int i = 0;
    while (!feof(inputFile))
    {
        buffer[i] = fgetc(inputFile);
        i++;
    }

    str->length = i;
    str->string = &buffer[0];
    return str;
}

void codeOpConcat(STRINGLENGTH *inputString, char codeOp)
{
    char *dest;
    dest = malloc(9 * sizeof(char));
    if (dest == NULL)
        printf("erreur allocation mémoire \n");
    inputString->string[0] = codeOp;
    inputString->string[1] = 0;
    inputString->string[2] = 0;
    inputString->string[3] = 0;
    inputString->string[4] = inputString->length;
    
    return;
}

char *stringEncodedTM(STRINGLENGTH *inputString, unsigned char typeOfAck)
{
    char codeOp;
    inputString->string = malloc(inputString->length * sizeof(char));
    if (inputString->string == NULL)
        printf("erreur allocation mémoire \n");
    switch (typeOfAck)
    {
    case 0: // chg_mode_ack
        codeOp = 0x10;
        codeOpConcat(inputString, codeOp);
        break;
    case 1: // takePct ack
        codeOp = 0x20;
        codeOpConcat(inputString, codeOp);
        break;
    case 2: // startStopFlag
        codeOp = 0x30;
        codeOpConcat(inputString, codeOp);
        break;
    case 3: // loadWeights
        codeOp = 0x40;
        codeOpConcat(inputString, codeOp);
        break;
    case 4: // arbitrary string
        codeOp = 0x60;
        codeOpConcat(inputString, codeOp);
        break;
    }
    return inputString->string;
}

char *imgEncodedTM(int *addr, int length)
{
    // length = 1228938;
    char *imgTM = malloc((length * sizeof(unsigned char)) + 6 * sizeof(char));
    if (imgTM == NULL)
    {
        printf("erreur allocation mémoire \n");
        return NULL;
    }
    imgTM[0] = (char)0x50;
    imgTM[1] = (length >> 24) & 0xFF;
    imgTM[2] = (length >> 16) & 0xFF;
    imgTM[3] = (length >> 8) & 0xFF;
    imgTM[4] = length & 0xFF;
    imageInTM(&imgTM[5], "pict.bmp");
    return imgTM;
}

int imageInTM(char *buffer, char *fileName)
{
    // char buffer[2000000] = {0};
    FILE *file = fopen(fileName, "r");
    int len = 0;
    len += fread(buffer + len, 1, 2000000, file);
    return len;
}
