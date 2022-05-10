#include <string.h>
#include <stdbool.h>
#include "circular_buffer.h"

#ifndef _STRUCTALLOCATION_H
#define _STRUCTALLOCATION_H

typedef struct cmd
{
    bool start;
    bool weights_update;
    bool change_mode;
} cmd;

typedef struct weight_upd
{
    char *arch;
    char *filename;
} weight_upd;

typedef struct chg_mode
{
    char mode;
    bool capture;
} chg_mode;

typedef struct buf_f
{
    cbuf_handle_t cbuf;
    bool new_data_f;
} buf_f;

typedef struct img
{
    bool img_f;
    int *addr;
    int length;
} img;

typedef struct mainStruct 
{
    cmd *cmd_struct;
    chg_mode *chg_mode_struct;
    weight_upd *weight_struct;
    buf_f *buf_f_struct;
    img *img_s;
} mainStruct;



/**
 * @brief allocate memory for global structures
 * 
 */
//void struct_alloc();
#endif