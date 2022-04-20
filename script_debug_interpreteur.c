#include "interpreteur.h"
#include "encodageTM.h"
#include "decodageTC.h"

int main()
{
    mainStruct *main_s;
    if ((main_s = malloc(sizeof(mainStruct))) == NULL)
    {
        printf("erreur allocation mémoire\n");
        return -1;
    }
    if ((main_s->img_s = malloc(sizeof(img))) == NULL)
    {
        printf("erreur allocation mémoire\n");
        return -1;
    }
    if ((main_s->cmd_struct = malloc(sizeof(cmd))) == NULL)
    {
        printf("erreur allocation mémoire\n");
        return -1;
    }
    if ((main_s->chg_mode_struct = malloc(sizeof(chg_mode))) == NULL)
    {
        printf("erreur allocation mémoire\n");
        return -1;
    }
    if ((main_s->weight_struct = malloc(sizeof(weight_upd))) == NULL)
    {
        printf("erreur allocation mémoire\n");
        return -1;
    }
    if ((main_s->buf_f_struct = malloc(sizeof(circular_buf_t) + sizeof(bool))) == NULL)
    {
        printf("erreur allocation mémoire\n");
        return -1;
    }
    char *bufferMsg = malloc(100 * sizeof(char));
    char buffer[100];
    main_s->buf_f_struct->cbuf = circular_buf_init(100);
    char *tc;
    int ret;
    tc = "11";
    if (decodeTC(main_s, tc) == 0)
        printf("Not a TC\n");
    interpreteur(main_s);
    bufferMsg = circular_buf_get(main_s->buf_f_struct->cbuf, bufferMsg);
    printf("Code op : %d\n", bufferMsg[0]);
    printf("Length : %d\n", bufferMsg[4]);
    printf("Message : ");
    for (int i=5; i < bufferMsg[4] + 5; i++)
        printf("%c", bufferMsg[i]);
    printf("\n");
    tc = "21";
    if (decodeTC(main_s, tc) == 0)
        printf("Not a TC\n");
    interpreteur(main_s);
    bufferMsg = circular_buf_get(main_s->buf_f_struct->cbuf, bufferMsg);
    printf("Code op : %d\n", bufferMsg[0]);
    printf("Length : %d\n", bufferMsg[4]);
    printf("Message : ");
    for (int i=5; i < bufferMsg[4] + 5; i++)
        printf("%c", bufferMsg[i]);
    printf("\n");
    tc = "21";
    if (decodeTC(main_s, tc) == 0)
        printf("Not a TC\n");
    interpreteur(main_s);
    bufferMsg = circular_buf_get(main_s->buf_f_struct->cbuf, bufferMsg);
    printf("Code op : %d\n", bufferMsg[0]);
    printf("Length : %d\n", bufferMsg[4]);
    printf("Message : ");
    for (int i=5; i < bufferMsg[4] + 5; i++)
        printf("%c", bufferMsg[i]);
    printf("\n");
    tc = "12";
    if (decodeTC(main_s, tc) == 0)
        printf("Not a TC\n");
    interpreteur(main_s);
    bufferMsg = circular_buf_get(main_s->buf_f_struct->cbuf, bufferMsg);
    printf("Code op : %d\n", bufferMsg[0]);
    printf("Length : %d\n", bufferMsg[4]);
    printf("Message : ");
    for (int i=5; i < bufferMsg[4] + 5; i++)
        printf("%c", bufferMsg[i]);
    printf("\n");

}
