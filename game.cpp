#include <mygba.h>
#include<cstdlib>
#include<time.h>
#include "game.h"


void game::rotate(int r_dir){
	locked=true;
	to_rotate=true;
	rotate_dir=r_dir;
}

// create a shit for the snake to eat;
void game::createShit()
{
    _game_map->set_int_map( rand()%M_SIZE , rand()%M_SIZE, rand()%M_SIZE,5 );
}


// create a barrier on the map;
void game::createBarrier()
{

    _game_map->set_int_map( rand()%M_SIZE , rand()%M_SIZE, rand()%M_SIZE,4 );
    //_game_map->set_int_map( 2 ,10 , 3,4 );
}

// create an apple on the map;
void game::createApple()
{
		
		NextApple_x = rand()%M_SIZE;
		NextApple_y = rand()%M_SIZE;
		int tmp;	
			tmp = rand()%6;						
			
	    NextApple_z = tmp;										
		
		//update the apple to int_map;
		_game_map->set_int_map(NextApple_z,NextApple_x,NextApple_y,1);
}


void game::checkApple(int pos_z, int pos_x, int pos_y)
{
	 if(_game_map->get_int_map(pos_z,pos_x,pos_y) == 1)
	 {
		
		appleWalk();		
		createApple();			// create another apple on the map;		
	 }
	 else if(_game_map->get_int_map(pos_z,pos_x,pos_y) == 5)
	 {
	    shitWalk();
	    createShit();
    }
	 else
	    snakeWalk();
}

// extend the snake, that is, snakeSizeNow++;

void game::appleWalk()
{
	snake* tmp = new snake(Next_head_z, Next_head_x, Next_head_y);
	updateAppleWalk(Next_head_z,Next_head_x,Next_head_y,tmp);
}

// be similar with the snakeWalk, but do not delete the tail,and size++;
void game::updateAppleWalk(int z, int x, int y, snake* tmpS)
{
	tmpS->setChild( _game_map->getSnakeHead() );
	_game_map->set_int_map(z,x,y,2);
	_game_map->getSnakeHead()->setParent(tmpS); 
	_game_map->set_int_map(_game_map->getSnakeHead()->getZ(),
	                      _game_map->getSnakeHead()->getX(),
					      _game_map->getSnakeHead()->getY(),3);
	_game_map->setSnakeHead(tmpS);
	_game_map->setSnakeSize(1);		// size++;
}

void game::unlock(){
	locked=false;
}
void game::lock(){
	locked=true;
}


void game::key(){
	if(F_CTRLINPUT_UP_PRESSED )
	   _Dir_flag = 1;
	else if(F_CTRLINPUT_DOWN_PRESSED)
       _Dir_flag = 2;
    else if(F_CTRLINPUT_LEFT_PRESSED)
       _Dir_flag = 3;      
	else if(F_CTRLINPUT_RIGHT_PRESSED)
	   _Dir_flag = 4;
}

void game::int_handler(){


	count++;		
	bool bomb_flag = false;
	
	if(count == 15){
		if(!locked){
			update_pos(_game_map->getSnakeHead()->getZ(),
					   _game_map->getSnakeHead()->getX(),
					   _game_map->getSnakeHead()->getY());		
			
			bomb_flag = bomb(Next_head_z, Next_head_x, Next_head_y);
			
			
			if( !bomb_flag )
			{
			    checkApple(Next_head_z, Next_head_x, Next_head_y);
			     _Dir_flag = 0;
			if(to_rotate){
				display->refresh(this->_game_map,this,rotate_dir);
				to_rotate=false;
			}else{
				display->refresh(this->_game_map);
			}
			}
		}
		count = 0;
	}
	//ham_SyncMixer();
	//ham_UpdateMixer();
    //if(!mysample->playing){
    //ham_PlaySample(mysample);
    //}
}

void game::shitWalk()
{
    snake* tmp = new snake(Next_head_z , Next_head_x, Next_head_y );
    updateShit(Next_head_z, Next_head_x, Next_head_y,tmp);
    
}

void game::updateShit(int z, int x , int y, snake* tmpS)
{
     tmpS->setChild( _game_map->getSnakeHead() );
	// set the block of the snakeHead to "2"
	_game_map->set_int_map(z,x,y,2);
	_game_map->getSnakeHead()->setParent(tmpS) ;
	_game_map->set_int_map(_game_map->getSnakeHead()->getZ(),
	                      _game_map->getSnakeHead()->getX(),
					      _game_map->getSnakeHead()->getY(),3);
	_game_map->setSnakeHead(tmpS);
	
	//reset the block that the tail is standing to "0";
	for(int i=0 ; i < 2; i++)
	{
	   _game_map->set_int_map(_game_map->getSnakeTail()->getZ(),
			              	   _game_map->getSnakeTail()->getX(),
					       	   _game_map->getSnakeTail()->getY(),0);
						
	   _game_map->setSnakeTail(_game_map->getSnakeTail()->getParent());
	   delete(_game_map->getSnakeTail()->getChild());
	   
	}
	_game_map->setSnakeSize(-1);
	
}


// create _game_map;
game::game(display_controller * display){
    _game_map = new map();
	_side_now = 0 ; 
	_upside = 2;
	_leftside = 4;
	_rightside = 1;
	_downside = 3;
	_backside = 5;
	_Dir_flag = 0;
	locked=false;
	for(int i=0;i<6;i++)
	   _index[i]=0;   
	this->display = display;
	display->refresh(this->_game_map);
	
	createApple();
	srand(rand());
	for(int i = 0 ; i <20; i++ )
	{
	    createBarrier();
	  createShit();
    }

    
}



// check game over or not;
bool game::bomb(int pos_z,int pos_x,int pos_y){
	if(_game_map->get_int_map(pos_z,pos_x,pos_y) > 1 && _game_map->get_int_map(pos_z,pos_x,pos_y)!=5 || _game_map->getSnakeSizeNow()==2)
		return true;	//bomb!!
	return false;		//safe
}
// return 0 if is not at boundary;
// return the direction of the boundary encountered;
// up=1; down=2; left=3; right=4;
int game::checkBoundary(int pos_z,int pos_x,int pos_y){
	if(pos_y == -1)					//check upside;
		return 1;
	else if(pos_y == M_SIZE) 		//check downside;
		return 2;
	else if(pos_x == -1)				//check leftside;
		return 3;
	else if(pos_x == M_SIZE)		//check rightside;
		return 4;
	else							//is not at boundary;
		return 0;
}
// return the direction that user input;
int game::changeDir(int current_Dir){
    
    // transpose the direction user inputed ( _Dir_flag ) to the cordinate of the _up_left = (0,0);
    int transpose[4] = {1,4,2,3};
    int index_trans[5] = {0,0,2,3,1};
    
    if( _Dir_flag != 0)
    {
        if(_index[_side_now] == 1)       
           _Dir_flag = transpose[ ( index_trans[_Dir_flag] +3 ) % 4];
    
        else if(_index[_side_now] == 2 )                
           _Dir_flag = transpose[(index_trans[_Dir_flag] + 2) % 4];
    
        else if(_index[_side_now] == 3)       
           _Dir_flag = transpose[(index_trans[_Dir_flag]+1 ) % 4 ];
    }
    
	if(_Dir_flag ==1 && current_Dir != 2)
		return 1;			// up;
	else if( _Dir_flag == 2 && current_Dir != 1)
		return 2;			// down;
	else if( _Dir_flag == 3 && current_Dir != 4)
		return 3;			// left;
	else if( _Dir_flag == 4 && current_Dir != 3)
		return 4;			// right;
	return current_Dir;
}

// update the next SnakeHead's position;
void game::update_pos(int z,int x, int y){
	_game_map->setSnakeHead_Dir( changeDir(_game_map->getSnakeHead_Dir() ) );
	int flag;
	    
	int tmpDir = _game_map->getSnakeHead_Dir();    // had been transepose to the cordinate of upleft = (0,0);
	
	if(tmpDir==1&&checkBoundary(z,x,y-1)==1)	flag=1;
	else if(tmpDir==2&&checkBoundary(z,x,y+1)==2) flag=2;
	else if(tmpDir==3&&checkBoundary(z,x-1,y)==3) flag=3;
	else if(tmpDir==4&&checkBoundary(z,x+1,y)==4) flag=4;
	else flag=0;
	static int transpose[4] = {1,4,2,3};
	static int index_trans[5] = {0,0,2,3,1};
	static int rotate_dir[4] = {0,2,3,1};
	static int project[4]={0,3,2,1};
	int display_flag=0;
	
    
    if(flag != 0)
    {
       //transpose  back to the cordinate of the display sight;     
       
       display_flag = transpose[ (index_trans[flag] + _index[_side_now] ) % 4 ];
    //   
                
       
       // update _side_now, leftside....       
       setNewSide(display_flag); 
       _game_map->set_upside(project[_index[_side_now]]);    
       rotate(rotate_dir[display_flag-1]);
       
       int tmpflag = display_flag;
       
       // _side_now had been updated to the "NextSide" ;
       if(_index[_side_now] == 1)
          tmpflag = transpose[ ( index_trans[display_flag ]+3) % 4 ];
       else if(_index[_side_now] == 2)
          tmpflag = transpose[ (index_trans[display_flag]+2) % 4 ];
       else if(_index[_side_now] == 3)
          tmpflag = transpose[ (index_trans[display_flag]+1) % 4 ];   
          
       if(tmpflag == 1)        // entered from the buttom;
       {
          Next_head_y = M_SIZE-1;
          if(flag == 1)
               Next_head_x = x;       
          else if( flag == 2)
               Next_head_x = (M_SIZE-1) - x ;                       
          else if(flag == 3)
               Next_head_x = (M_SIZE-1) - y;
          else if( flag == 4)
               Next_head_x =  y;     
       
       }    
       else if(tmpflag == 2 )  // entered from the top;
       {
          if(flag == 1)
             Next_head_x = (M_SIZE - 1) -x;
          else if( flag == 2)
               Next_head_x = x;       
                  
          else if(flag == 3)
               Next_head_x = y;
          else if( flag == 4)     
               Next_head_x = ( M_SIZE-1) - y ;
                 
          Next_head_y = 0;  
       }
       else if(tmpflag == 3 )  // entered from the rightside;
       {
          Next_head_x = M_SIZE - 1;  
          
          if(flag == 1 )
               Next_head_y = (M_SIZE -1) - x ;
          else if(flag == 2 )     
               Next_head_y = x;
          else if(flag == 3)
               Next_head_y = y;
          else if( flag == 4)     
               Next_head_y = (M_SIZE - 1) - y;
       }
       else if(tmpflag == 4 )  // entered from the leftside;
       {
          Next_head_x = 0;  
          
          if(flag == 1 )
               Next_head_y = x;
          else if(flag == 2 )     
               Next_head_y = (M_SIZE -1) - x;
          else if(flag == 3)
               Next_head_y = (M_SIZE-1) - y;
          else if( flag == 4)     
               Next_head_y = y;
       }             
       
         _game_map->setSnakeHead_Dir(tmpflag);   
    }
	else{//4��  need not to rotate,just change the Next_head
		if(tmpDir ==1){
			Next_head_y=y-1;
			Next_head_x=x;
		}
		else if(tmpDir ==2){
			Next_head_y=y+1;
			Next_head_x=x;
		}
		else if(tmpDir ==3){
			Next_head_x=x-1;
			Next_head_y=y;
		}
		else if(tmpDir ==4){
			Next_head_x=x+1;
			Next_head_y=y;
		}
		
	}
	
	
	Next_head_z=_side_now;
}

void game::setNewSide(int a){
//	rotate(_upside);
	//_game_map->set_upside(_upside);
//	ham_VBAText("upside:%d\n",_side_now);
	if(a==1){
        //update the _index[];
        _index[_rightside] +=3 ;
        _index[_rightside] %= 4;
        
        _index[_leftside] +=1;
        _index[_leftside] %=4;
        
        
        // update the _side_now, left_side.....     
        _backside = _downside;
		_downside=_side_now;
		_side_now=_upside;
		_upside=5-_downside;
	}
	else if(a==2){
         // update the _index[];
         _index[_leftside] += 3;
         _index[_leftside] %= 4;
         
         _index[_rightside] += 1;
         _index[_rightside] %= 4;
         
         // update the _side_now,left_side...
         _backside = _upside;
		_upside=_side_now;
		_side_now=_downside;
		_downside=5-_upside;
	}
	else if(a==3){
         //update the _index[];
         _index[_upside] += 3;
         _index[_upside] %= 4;
         
         _index[_downside] += 1;
         _index[_downside] %= 4;
         
         _index[_rightside] += 2;
         _index[_rightside] %= 4;
         
         _index[_backside] += 2;
         _index[_backside] %= 4;
         
         //update the _side_now, left_side...
        _backside = _rightside;
		_rightside=_side_now;
		_side_now=_leftside; 
		_leftside=5-_rightside;
	}
	else if(a==4){
        //update the index[];
        
        _index[_upside] +=1 ;
        _index[_upside] %=4;
        
        _index[_downside] += 3;
        _index[_downside] %= 4;
        
        _index[_leftside] += 2;
        _index[_leftside] %= 4;
        
        _index[_backside] += 2;
        _index[_backside] %= 4;
         
         
        // update the _side_now, leftside...
        _backside = _leftside;
		_leftside=_side_now;
		_side_now=_rightside;
		_rightside=5-_leftside;
	}
	
}


// control the move of the snake;
// create a new SnakeHead, delete the Snaketail and update them;
void game::snakeWalk(){
	
		snake* tmp=new snake(Next_head_z,Next_head_x,Next_head_y);
		updateSnake(Next_head_z,Next_head_x,Next_head_y,tmp);
}
// update the snake's Head and Tail, and also update the map ;
void game::updateSnake(int z, int x, int y, snake* tmpS){
	tmpS->setChild( _game_map->getSnakeHead() );
	// set the block of the snakeHead to "2"
	_game_map->set_int_map(z,x,y,2);
	_game_map->getSnakeHead()->setParent(tmpS) ;
	_game_map->set_int_map(_game_map->getSnakeHead()->getZ(),
	                      _game_map->getSnakeHead()->getX(),
					      _game_map->getSnakeHead()->getY(),3);
	_game_map->setSnakeHead(tmpS);
	
	//reset the block that the tail is standing to "0";
	_game_map->set_int_map(_game_map->getSnakeTail()->getZ(),
						   _game_map->getSnakeTail()->getX(),
						   _game_map->getSnakeTail()->getY(),0);
						   
	_game_map->setSnakeTail(_game_map->getSnakeTail()->getParent());
	delete(_game_map->getSnakeTail()->getChild());
}
void game:: coordinate(int nowside,int nextside,int x,int y){}

        
