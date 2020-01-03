#pragma once
#include "SpaceObject.hpp"
#include "Vector.hpp"
#include "Framework.hpp"
#include "main.hpp"

class Bullet : public SpaceObject
{
public:
	Bullet(Vector &bullet_dir, Vector &bullet_pos , Sprite *bullet_sprite, float angle);
	
	Bullet(Bullet const &) = default;
	
	~Bullet();
	
	void movement(ObjectMove);

public:
	Sprite	*bullet_sprite;
};

