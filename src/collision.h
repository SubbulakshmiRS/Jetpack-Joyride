#include <iostream> 

struct Point 
{ 
	int x; 
	int y; 
}; 

int orientation(Point p, Point q, Point r) ;
bool doIntersect(Point p1, Point q1, Point p2, Point q2);
bool onSegment(Point p, Point q, Point r) ;