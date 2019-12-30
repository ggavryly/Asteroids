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
	bool	collision(SpaceObject const *obj) const
	{
		if (this->pos.x < obj->pos.x + obj->width &&
			this->pos.x + this->width > obj->pos.x &&
			this->pos.y < obj->pos.y + obj->height &&
			this->pos.y + this->height > obj->pos.y)
			return true;
		return false;
	}
	virtual void	takeDamage() = 0;

public:
	Vector		pos;
	Vector		dir;
	float		velocity = 0.0f;
	float		angle = 0.0;
	float		angle_velocity = 0.0f;
	bool		move = false;
	int 		width;
	int 		height;
};

