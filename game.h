class map{
	public:
		map(int M_SIZE)
		{
			map = new map[6][M_SIZE][M_SIZE];	//create the map;	
			
			// initialize the default snake of snakeSizeNow = 3;
			// the default start side is " 0 " ;
			// use linked list to implement the whole snake;
			
			snake tmp = new snake();
			snakeSizeNow = 0;
			snakeSizeNow++;
			SnakeHead = tmp(0,5,10);
			SnakeHead -> child = SnakeHead;
			SnakeHead -> parent = SnakeHead;
			SnakeTail = SnakeHead;
			
			for(int i=1;i<=2;i++)
			{
				tmp = new snake(SnakeTail.z, (SnakeTail.x)-i, SnakeTail.y);
				tmp -> parent = SnakeTail;
				SnakeTail -> child = tmp;
				SnakeTail = tmp;
				snakeSizeNow++;	
			}			
			
		}
		
		~map(){}
		
		snake* getSnakeHead(){return SnakeHead;}
		snake* getSnakeTail(){return SnakeTail;}
		int getSnakeHead_Dir(){return SnakeHead_Dir;}
		int getSnakeSizeNow(){return snakeSizeNow;}
		
		void setSnakeHead(snake* Head){SnakeHead = Head;}
		void setSnakeTail(snake* Tail){SnakeTail = Tail;}
		
    private:
		int NextApple_x;	//record the next apple's position;
		int NextApple_y;
		int NextApple_Z;

		snake* SnakeHead;
		snake* SnakeTail;		
		
		int SnakeHead_Dir;	// record the direction of the snake's head now;
							// up = 1; down = 2; left = 3; right = 4 ;
		
		block map[6][M_SIZE][M_SIZE];//elements that construct the whole map;
		//        z    x        y
		
		int snakeSizeNow;
};

class snake
{
	public:
		snake(int z, int x, int y)
		{
			snake_x = x;
			snake_y = y;
			snake_z = z;	
		}
		~snake(){}
		
	private:
		
		int snake_x;
		int snake_y;
		int snake_z;		
		snake* child;
		snake* parent;
};

class block{
	
	int sprite_type;	// blank = 0; apple = 1; snakehead = 2; snakebody = 3;
	                    // barrier = 4;						  
	
};



class game{
	public:
    	void unlock();
    	void int_handler();		// timer;
    
    
    private:
		map _game_map;
		int _side_now;	// the index of the current side;
		int _upside;		// the index of the upside;
		int _downside;   // the index of the downside;
		int _leftside;	// the index of the leftside;
		int _rightside;	// the index of the rightside;
		int _M_SIZE;
			
	// check game over or not;			
	bool bomb(int pos_Z,int pos_x,int pos_y)		
	{
		if(_game_map.map[pos_z][pos_x][pos_y].sprite_type > 1 )
			return false;				
	}	
	
	
	// return 0 if is not at boundary;
	// return the direction of the boundary encountered;
	// up = 1; down = 2; left = 3; right = 4;
	int checkBoundary(int pos_z,int pos_x,int pos_y) 		
	{
		if(pos_y < 0)					//check upside;
			return 1;

		else if(pos_y > _M_SIZE) 		//check downside;
			return 2;

		else if(pos_x < 0)				//check leftside;
			return 3;

		else if(pos_x > _M_SIZE)		//check rightside;
			return 4;

		else							//is not at boundary;
		    return 0;
	}
	
	// return the direction that user input;
	int changeDir(int current_Dir)		
	{
		if(F_CTRLINPUT_UP_PRESSED && current_Dir != 2)
		   return 1;			// up;
		
		else if(F_CTRLINPUT_DOWN_PRESSED && current_Dir != 1)
		   return 2;			// down;
		
		else if(F_CTRLINPUT_LEFT_PRESSED && current_Dir != 4)
		   return 3;			// left;
		   
		else if(F_CTRLINPUT_RIGHT_PRESSED && current_Dir != 3)
		   return 4;			// right;
		   
		return current_Dir;   
	}
	
	// control the move of the snake;
	// create a new SnakeHead, delete the Snaketail and update them;
	void snakeWalk()
	{
		_game_map.SnakeHead_Dir = changeDir(_game_map.SnakeHead_Dir);
		if(
		snake tmp = snake(
	}
};
