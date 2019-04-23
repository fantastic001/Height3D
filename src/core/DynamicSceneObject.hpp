
#ifndef HEIGHT3D_DYNAMIC_SCENE_OBJECT_HPP
#define HEIGHT3D_DYNAMIC_SCENE_OBJECT_HPP

#include "SceneObject.hpp"
#include "Vector.hpp"

/*!
This class provides interface to dynamic objects. Objects of this class can be added to Scene and when drawing, object's 
getObject(...) method is called to get SceneObject needed to draw.

This class is abstract class so you have to subclass it and implement getObject(...) method. 
*/
class DynamicSceneObject 
{


public:
	virtual SceneObject* getObject(Vector camera_position) = 0;
};

#endif // HEIGHT3D_DYNAMIC_SCENE_OBJECT_HPP
