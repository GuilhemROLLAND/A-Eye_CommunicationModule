#include "interpreteur.h"
#include "encodageTM.h"

void interpreteur(mainStruct *main_s, char *bufferMsg)
{
    STRINGLENGTH *string;
    
    if ((string = malloc(sizeof(STRINGLENGTH))) == NULL);
        printf("erreur allocation mémoire \n");
    if (main_s->cmd_struct->change_mode == true)
    {
        switch (main_s->chg_mode_struct->mode)
        {
        case 0:
            // TO DO : déclencher le process d'IA
            /* processIA(); */
            bufferMsg = "Process IA running";
            string->length = strlen(bufferMsg);
            string->string = bufferMsg;
            bufferMsg = stringEncodedTM(string, main_s->chg_mode_struct->mode);
            circular_buf_put(main_s->buf_f_struct->cbuf, bufferMsg);
            main_s->buf_f_struct->new_data_f = true;
            break;
        case 1:
            if (main_s->chg_mode_struct->capture == true)
            {
                // TO DO :
                // déclencher une capture manuelle
                bufferMsg = "Capture";
                string->length = strlen(bufferMsg);
                string->string = bufferMsg;
                bufferMsg  = stringEncodedTM(string, main_s->chg_mode_struct->mode);
                circular_buf_put(main_s->buf_f_struct->cbuf, bufferMsg);
                main_s->buf_f_struct->new_data_f == true;
            }
            bufferMsg = "Mode capture manuelle";
            string->length = strlen(bufferMsg);
            string->string = bufferMsg;
            bufferMsg = stringEncodedTM(string, main_s->chg_mode_struct->mode);
            circular_buf_put(main_s->buf_f_struct->cbuf, bufferMsg);
            main_s->buf_f_struct->new_data_f = true;
            break;
        case 2:
            // TO DO :
            // mode vidéo, bonus
            bufferMsg = "Mode video";
            string->length = strlen(bufferMsg);
            string->string = bufferMsg;
            bufferMsg = stringEncodedTM(string, main_s->chg_mode_struct->mode);
            circular_buf_put(main_s->buf_f_struct->cbuf, bufferMsg);
            main_s->buf_f_struct->new_data_f = true;
            break;
        default:
            break;
        }
    }
    if (main_s->cmd_struct->start == true)
    {
        // TO DO :
        // Sequence d'init
        bufferMsg = "Starting ...";
        string->length = strlen(bufferMsg);
        string->string = bufferMsg;
        bufferMsg = stringEncodedTM(string, 3);
        circular_buf_put(main_s->buf_f_struct->cbuf, bufferMsg);
        main_s->buf_f_struct->new_data_f = true;
    }
    else
    {
        // TO DO : stop le système
        bufferMsg = "Closing ...";
        string->length = strlen(bufferMsg);
        string->string = bufferMsg;
        bufferMsg = stringEncodedTM(string, 3);
        circular_buf_put(main_s->buf_f_struct->cbuf, bufferMsg);
        main_s->buf_f_struct->new_data_f = true;
    }
    if (main_s->cmd_struct->weights_update == true)
    {
        // TO DO :
        // charger arch et weights dans IA en c
        // bonus
        bufferMsg = "Chargement des poids";
        string->length = strlen(bufferMsg);
        string->string = bufferMsg;
        bufferMsg = stringEncodedTM(string, 4);
        circular_buf_put(main_s->buf_f_struct->cbuf, bufferMsg);
        main_s->buf_f_struct->new_data_f = true;
    }
}
