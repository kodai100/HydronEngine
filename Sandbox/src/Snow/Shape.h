#pragma once

#include <vector>
#include <math.h>
#include "Vector2f.h"

class Shape {
public:
	std::vector<Vector2f> vertices;
	Vector2f vel;
	
	Shape();
	Shape(Vector2f vel);
	Shape(const Shape& orig);
	virtual ~Shape();
	
	//Add vertex to back of vertex list
	void addPoint(float x, float y);

	//Does this shape contain this point
	bool contains(float x, float y);

	//Compute area of shape
	float area();

	//Estimate volume, if this 2D object were actually 3D
	float volume();

	//Bounding box for shape
	void bounds(float bounds[4]);

	static Shape* generateSnowball(Vector2f origin, float radius, Vector2f vel);
	
	void draw();
};
