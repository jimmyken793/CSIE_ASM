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
game *GAME=NULL;
int main(void){
	ham_Init();
	GAME_display=new display_controller;
	GAME=new game(GAME_display);
	ham_StartIntHandler(INT_TYPE_VBL,( void *)&callback);
	//ham_StartIntHandler(INT_TYPE_KEY,( void *)&callback);
	while(true){}
	return 0;
}
void callback(){
	GAME->int_handler();
	GAME_display->int_handler();
}
