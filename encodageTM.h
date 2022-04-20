#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "circular_buffer.h"

#ifndef _ENCODAGETM_H
#define _ENCODAGETM_H

    //STRUCTURES


    #ifndef H_TELEMESURE
    #define H_TELEMESURE

    typedef struct
    {
        int length;
        char* addrContent; 
        char codeOp;
    } TELEMESURE;
    #endif

    #ifndef H_CHANGEMODEACK
    #define H_CHANGEMODEACK

    typedef enum 
    {
        startStopFlag,
        takePctFlag,
        loadWeigthsFlag,
        stringFlag,
        numberofAck
    } CHANGEMODEACK;
    #endif

    #ifndef H_TYPEOFTM
    #define H_TYPEOFTM

    typedef struct 
    {
        bool imgFlag;
        CHANGEMODEACK ackFlag; 
    } TYPEOFTM;
    #endif

    #ifndef H_STRINGLENGTH
    #define H_STRINGLENGTH

    typedef struct
    {
        char length;
        char* string; 
    } STRINGLENGTH;
    #endif

    // FUNCTIONS


    /**
     * @brief read a txt file containing the ack and outputs the ack in string format
     * 
     * @param filePath txt file containing the ack
     * @return char* ack in a string format
     */
    STRINGLENGTH* ackTxtFileReading(char* filePath);

    /**
     * @brief convert a string into a telemesure
     * 
     * @param inputString input string with the length
     * @param typeOfAck ack type
     * @return TELEMESURE* struct containing the starting addr of the data, codeOp and length
     */
    char* stringEncodedTM(STRINGLENGTH* inputString, unsigned char typeOfAck);

    /**
     * @brief convert an img into a telemesure
     * 
     * @param addr starting address of the img
     * @param length length of the img
     * @return TELEMESURE* struct containing the starting addr of the data, codeOp and length
     */
    char* imgEncodedTM(int length);

    /**
     * @brief get data from file and return the data in a char buffer
     * 
     * @param buffer out buffer
     * @param file filename 
     * @return int 
     */
    int imageInTM(char* buffer, char* file);

    /**
     * @brief convert a manual captured img to a TM
     * 
     * @param length length of the img
     * @return char* char* ptr to the TM
     */
    char *captureManuelle(int length);

    /**
     * @brief add corresponding codeop to the msg 
     * 
     * @param inputString the input message
     * @param codeOp corresponding codeOp
     * @param tm output string containing tm
     * @return char* tm : the tm
     */
    char* codeOpConcat(STRINGLENGTH *inputString, char codeOp, char *tm);

#endif