#pragma once

#include <stdlib.h>
#include "Shape.h"
#include "Vector2f.h"

using namespace std;

class Scene {
public:
	vector<Shape*> snow_shapes;

	Scene();
	Scene(const Scene&);
	virtual ~Scene();
	
	static Scene* snowman();
	static Scene* snowballSmash();
	static Scene* highspeedSnowballSmash();
};
