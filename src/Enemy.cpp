#include "Enemy.hpp"

Enemy::Enemy(Vector & player_pos, Sprite * enemy_sprite, bool is_big)
{
	static int i=1;
	int tmpx, tmpy;
	srand(time(nullptr));
	velocity = rand() % 1 + 1;
	angle_velocity = (rand() + i) % 4 + 1;
	getScreenSize(tmpx, tmpy);
	sprite = enemy_sprite;
	getSpriteSize(enemy_sprite, tmpx, tmpy);
	width = tmpx;
	height = tmpy;
	if (!is_big)
	{
		dir = Vector(rand() / i++, rand() * i++).normalization();
		pos.x = abs((rand() * i) % tmpx);
		pos.y = abs((rand() / i) % tmpy);
		if (abs(this->pos.x - player_pos.x) < 250)
			this->pos.x -= 200;
		if (abs(this->pos.y - player_pos.y) < 250)
			this->pos.y -= 200;
		this->is_big = is_big;
	}
	else
	{
	
	}
}

Enemy::~Enemy()
{}


void Enemy::movement(ObjectMove)
{
	angle = (angle > 360.0f) ? (0.0f) : (angle);
	pos.x += dir.x * velocity;
	pos.y += dir.y * velocity;
	int sx, sy;
	getScreenSize(sx, sy);
	
	pos.x = (pos.x > sx) ? (0) : (pos.x);
	pos.y = (pos.y > sy) ? (0) : (pos.y);
	
	pos.x = (pos.x < 0) ? (sx) : (pos.x);
	pos.y = (pos.y < 0) ? (sy) : (pos.y);
}
