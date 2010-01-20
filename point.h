#ifndef POINT_H
#define POINT_H

class point{
	private:
		double x,y,z;
	public:
		double getX();
		double getY();
		double getZ();
		void setX(double x);
		void setY(double y);
		void setZ(double z);
		point(double x=0,double y=0,double z=0);
		void reflectXY();
		void reflectX(double ax);
		void reflectY(double ay);
		void reverseX();
		void reverseY();
		void reverseXY();
};

#endif
