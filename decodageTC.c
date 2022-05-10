#include <stdio.h> 
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "interpreteur.h"

void decodeTC(mainStruct *main_s, char *msg) 
{   
    // Test the first byte of the msg,
    // for TC, values can be 1, 2, 3, 4
    switch(msg[0])
    {
        // mode change, second byte will specify the mode 
        case '1' :
            main_s->cmd_struct->change_mode = true;
            // read and update the corresponding mode
            switch(msg[1])
            {
                case '0' :
                    main_s->chg_mode_struct->mode = 0;
                    break;
                case '1' :
                    main_s->chg_mode_struct->mode = 1;
                    break;
                case '2' :
                    main_s->chg_mode_struct->mode = 2;
                    break;
            }
            break;
        // take picture mode
        case '2' :
            // take picture only if we are in takePct mode and second byte is valid 
            if (main_s->chg_mode_struct->mode == 1 && msg[1] == '1') 
            {
                main_s->chg_mode_struct->capture = true;
            }
            else 
                main_s->chg_mode_struct->capture = false;
            break;
        // start/stop
        case '3' :
            // check second byte to know if its start or stop
            if (msg[1] == '1')
                main_s->cmd_struct->start = true;
            else 
                main_s->cmd_struct->start = false;
            break;
        // update param AI, optional, TO DO
        case '4' :
            if (msg[1] == '1')
            {
                main_s->cmd_struct->weights_update = true;
                //TO DO : Configure the weight update operation
            }
            else 
                main_s->cmd_struct->weights_update = false;
            break;
        default :
            break;
    }
}
