#pragma once
#include "main.hpp"
#include "SpaceObject.hpp"
#include "Framework.hpp"
#include "Vector.hpp"

#define GRID_0	0
#define GRID_90 90
#define GRID_180 180
#define GRID_270 270
#define GRID_360 360

class Player : public SpaceObject
{
public:
	Player();
	Player(Sprite *player);
	
	Player(Player const &);
	
	~Player();

public:
	void	shoot();
	void	movement(ObjectMove);
	void	takeDamage();

public:
	Sprite*					_player;
	Vector					_last_dir;
	Vector					_mouse_dir;
};

void getComputerCoord(Vector &lhs, double angle);

