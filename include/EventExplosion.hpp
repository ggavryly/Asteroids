#pragma once
#include "main.hpp"
#include "Vector.hpp"
#include "Animation.hpp"

class EventExplosion
{
public:
	EventExplosion(Vector const & pos, int sprite_count);
	
	EventExplosion(EventExplosion const &) = default;
	~EventExplosion();

public:
	Vector		pos;
	Animation	animation;
	int			frame = 0;
};

