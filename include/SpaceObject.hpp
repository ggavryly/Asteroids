#pragma once
#include "main.hpp"
#include "Vector.hpp"

enum ObjectMove
{
	RIGHT,
	LEFT,
	DOWN,
	UP,
	NOTHING
};

class SpaceObject
{
public:
	SpaceObject() = default;
	
	SpaceObject(SpaceObject const &) = default;
	
	virtual ~SpaceObject(){}

public:
	virtual void	movement(ObjectMove) = 0;
	virtual bool	collision(SpaceObject const *obj) const
	{
		return	(obj_min_scope.x <= obj->pos.x <= obj_max_scope.x) &&
				(obj_min_scope.y <= obj->pos.x <= obj_max_scope.y);
	}
	virtual void	takeDamage() = 0;

public:
	Vector		pos;
	Vector		dir;
	float		velocity = 0.0f;
	bool		move = false;
	Vector		obj_min_scope;
	Vector		obj_max_scope;
};

