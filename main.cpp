/*********************************************************************************
 * Includes
 ********************************************************************************/
#include "main.h"
#include "display.h"
#include "game.h"
/*********************************************************************************
 * Program entry point
 ********************************************************************************/
display_controller* GAME_display=NULL;
int main(void){
	ham_Init();
	display_controller display;
	GAME_display=&display;
	ham_StartIntHandler(INT_TYPE_VBL,( void *)&callback);
	while(true){}
	return 0;
}
void callback(){
	GAME_display->int_handler();
}
