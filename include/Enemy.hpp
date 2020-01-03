#pragma once
#include "SpaceObject.hpp"
#include "Vector.hpp"
#include "Framework.hpp"

class Enemy : public SpaceObject
{
public:
	Enemy(Vector &player_pos, Sprite *my_sprite, bool is_big);
	
	Enemy(Enemy const &) = default;
	
	~Enemy();
	
	void	movement(ObjectMove);

public:
	Sprite	*enemy_sprite;
	bool	is_big;
};

