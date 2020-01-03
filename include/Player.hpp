#pragma once
#include "main.hpp"
#include "SpaceObject.hpp"
#include "Framework.hpp"
#include "Vector.hpp"
#include "Bullet.hpp"

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
	Bullet* shoot(Vector const & mouse_pos, Sprite *bullet_sprite);
	void	movement(ObjectMove);
	void	computeMouseDir(Vector const & mouse_pos);

public:
	Vector					_last_dir;
	Vector					_mouse_dir;
	float					_mouse_angle;
};

void getComputerCoord(Vector &lhs, double angle);

