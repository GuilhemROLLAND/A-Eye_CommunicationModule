#include "interpreteur.h"
#include "encodageTM.h"
int main ()
{
    char *img; 
    if ((img = malloc(921661*sizeof(char))) == NULL)
    {
        printf("erreur allocation memoire");
        return -1;
    }
    img = capture();
    img = imgEncodedTM(img, 921656);
    printf("end of main");
}