#ifndef POINT_H
#define POINT_H

class point{
	private:
		int x,y;
	public:
		int getX();
		int getY();
		void setX(int x);
		void setY(int y);
		point(int x=0,int y=0);
};

#endif
