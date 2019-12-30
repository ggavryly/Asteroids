#pragma once
#include "SpaceObject.hpp"
#include "Vector.hpp"
#include "Framework.hpp"

class Enemy : public SpaceObject
{
public:
	Enemy(Vector &player_pos, Sprite *my_sprite);
	
	Enemy(Enemy const &) = default;
	
	~Enemy();
	
	void	movement(ObjectMove);
	void	takeDamage();

public:
	Sprite	*enemy_sprite;
};

