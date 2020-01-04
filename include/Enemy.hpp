#pragma once
#include "SpaceObject.hpp"
#include "Vector.hpp"
#include "Framework.hpp"

class Enemy : public SpaceObject
{
public:
	Enemy(Vector const &player_pos, Sprite *my_sprite, bool is_big);
	
	Enemy(Vector const &big_asteroid_pos, Sprite *my_sprite, Vector const &big_asteroid_dir);
	
	Enemy(Enemy const &) = default;
	
	~Enemy();
	
	void	movement(ObjectMove);

public:
	bool	is_big;
};

