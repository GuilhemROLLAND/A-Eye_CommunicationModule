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

char *stringEncodedTM(STRINGLENGTH *inputString, unsigned char typeOfAck)
{
    char *string;
    char *temp;
    char *dest;
    string = malloc(inputString->length * sizeof(char));
    if (string == NULL)
        printf("erreur allocation mémoire \n");
    temp = malloc(4 * sizeof(char));
    if (temp == NULL)
        printf("erreur allocation mémoire \n");
    dest = malloc((strlen(temp) + strlen(string)) * sizeof(char));
    if (dest == NULL)
        printf("erreur allocation mémoire \n");
    switch (typeOfAck)
    {
    case 0: // chg_mode_ack
        temp = "0x10";
        strcpy(dest, temp);
        strcat(dest, " ");
        strcat(dest, inputString->string);
        break;
    case 1: // takePct ack
        temp = "0x20";
        strcpy(dest, temp);
        strcat(dest, " ");
        strcat(dest, inputString->string);
        break;
    case 2: // startStopFlag
        temp = "0x30";
        strcpy(dest, temp);
        strcat(dest, " ");
        strcat(dest, inputString->string);
        break;
    case 3: // loadWeights
        temp = "0x40";
        strcpy(dest, temp);
        strcat(dest, " ");
        strcat(dest, inputString->string);
        break;
    case 4: // arbitrary string
        temp = "0x60";
        strcpy(dest, temp);
        strcat(dest, " ");
        strcat(dest, inputString->string);
        break;
    }
    return dest;
}

char *imgEncodedTM(int *addr, int length)
{
    char *imgTM;
    if (imgTM = malloc((length * sizeof(unsigned char)) + 4 * sizeof(char)) == NULL)
        printf("erreur allocation mémoire \n");
    imgTM[0] = 0x5;
    imgTM[1] = (length >> 24) & 0xFF;
    imgTM[2] = (length >> 16) & 0xFF;
    imgTM[3] = (length >> 8)  & 0xFF;
    imgTM[4] = length & 0xFF ;
    imgTM[5] = addr;
    return imgTM;
}

int imageInTM(char *buffer, char *file)
{
    // char buffer_img[2000000] = {0};
    FILE *file = fopen(file, "r");
    int len = 0;
    *buffer = (char)0x50;
    len++;
    uint32_t sizeBMP = 1228938;
    buffer[1] = (sizeBMP >> 24) & 0xFF;
    buffer[2] = (sizeBMP >> 16) & 0xFF;
    buffer[3] = (sizeBMP >> 8) & 0xFF;
    buffer[4] = sizeBMP & 0xFF;
    len += 4;
    len += fread(buffer + len, 1, 2000000 - len, file);
    return len;
}
