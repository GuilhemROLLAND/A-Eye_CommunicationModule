#include "interpreteur.h"

#ifndef _DECODAGETC_H
#define _DECODAGETC_H

    /**
     * @brief decode the incoming msg with the code operations described in design.
     *        Param update is done by updating the corresponding structures
     * 
     * @param msg the incoming msg received from server
     */
    void decodeTC(mainStruct *main_s, char *msg);

#endif