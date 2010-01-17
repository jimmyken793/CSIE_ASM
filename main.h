#ifndef MAIN_H
#define MAIN_H

// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include <mygba.h>
//#include "display.h"
//#include "game.h"

/*********************************************************************************
 * MULTIBOOT is interesting.
 * If you write this on the top of your main file,
 * the GBA ROM you build will automatically be capable of running both
 * from FLA carts and, in addition directly over the MBV2 cable.
 * If you do not need this, simply comment it out.
 ********************************************************************************/
MULTIBOOT

/*********************************************************************************
 * Globals
 ********************************************************************************/
bool g_NewFrame=true;

/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc(void);


#endif /* MAIN_H */

/* END OF FILE */
