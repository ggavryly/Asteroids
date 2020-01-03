#pragma once
#include "main.hpp"
#include "Vector.hpp"
#include "Framework.hpp"

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
	
	const Vector &getPos() const
	{
		return pos;
	}
	
	const Vector &getDir() const
	{
		return dir;
	}
	
	float getVelocity() const
	{
		return velocity;
	}
	
	float getAngle() const
	{
		return angle;
	}
	
	float getAngleVelocity() const
	{
		return angle_velocity;
	}
	
	bool isMove() const
	{
		return move;
	}
	
	int getWidth() const
	{
		return width;
	}
	
	int getHeight() const
	{
		return height;
	}
	
	virtual ~SpaceObject(){}

public:
	virtual void	movement(ObjectMove) = 0;
	bool	collision(SpaceObject const  &obj) const
	{
		if (pos.x < obj.pos.x + obj.width &&
			pos.x + width > obj.pos.x &&
			pos.y < obj.pos.y + obj.height &&
			pos.y + height > obj.pos.y)
			return true;
		return false;
	}

public:
	Sprite		*sprite;
	Vector		pos;
	Vector		dir;
	float		velocity = 0.0f;
	float		angle = 0.0;
	float		angle_velocity = 0.0f;
	bool		move = false;
	int 		width;
	int 		height;
};

