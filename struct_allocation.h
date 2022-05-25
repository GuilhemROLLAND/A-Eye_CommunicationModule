/**
 * @file struct_allocation.h
 * @author Thomas du Boisrouvray (thomas.duboisrouvray@elsys-design.com)
 * @brief This file defines the structures used in CommunicationModule and the imports 
 * @version 0.1
 * @date 2022-05-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "circular_buffer.h"

#ifndef _STRUCTALLOCATION_H
#define _STRUCTALLOCATION_H

/**
 * @brief Contains all the commands related flags 
 * 
 * @param start start/stop flag
 * @param weight_update flag 
 * @param change_mode flag
 */
typedef struct cmd
{
    bool start;
    bool weights_update;
    bool change_mode;
} cmd;

/**
 * @brief Contains the informations needed for a weights update (not implemented)
 * 
 * @param arch Architecture of the CNN in the corresponding format 
 * @param filename Name of the weight file
 */
typedef struct weight_upd
{
    char *arch;
    char *filename;
} weight_upd;

/**
 * @brief Contains informations concerning mode and capture flag
 * 
 * @param mode Specify the current mode
 * @param capture flag to execute a manual capture
 */
typedef struct chg_mode
{
    char mode;
    bool capture;
} chg_mode;

/**
 * @brief Contains the circular buffer handle and the new data flag
 * 
 * @param cbuf pointer to the circular buffer (not implemented)
 * @param new_data_f flag for new string data
 */
typedef struct buf_f
{
    cbuf_handle_t cbuf;
    bool new_data_f;
} buf_f;

/**
 * @brief Contains parameters concerning image transmissions
 * 
 * @param img_f flag when new boat image by IA
 * @param capture_f flage when the manual captured image is ready
 * @param addr starting addr of the image
 * @param length length of the image
 */
typedef struct img
{
    bool img_f;
    bool capture_f;
    char *addr;
    int length;
} img;

/**
 * @brief Main structures with all the informations for communication 
 * 
 * @param cmd_struct command structure
 * @param chg_mode_struct mode structure
 * @param weight_struct weight update structure
 * @param buf_f_struct circular buffer struct
 * @param img_s image structure
 * @param ack String ack updated when receiving a TC
 * @param fifo ID of the FIFO for communication between AI and Communication
 * 
 */
typedef struct mainStruct 
{
    cmd *cmd_struct;
    chg_mode *chg_mode_struct;
    weight_upd *weight_struct;
    buf_f *buf_f_struct;
    img *img_s;
    char *ack;
    int fifo;
} mainStruct;

#endif