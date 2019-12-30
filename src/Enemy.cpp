#include "Enemy.hpp"

Enemy::Enemy(Vector & player_pos, Sprite * my_sprite)
{
	static int i=1;
	int tmpx, tmpy;
	getScreenSize(tmpx, tmpy);
	srand(time(nullptr));
	dir = Vector(rand() /  i++, rand() * i++).normalization();
	pos.x = abs((rand() * i) % tmpx);
	pos.y = abs((rand() / i) % tmpy);
	velocity = rand() % 1 + 1;
	enemy_sprite = my_sprite;
	getSpriteSize(enemy_sprite, tmpx, tmpy);
	width = tmpx;
	height = tmpy;
	angle_velocity = (rand() + i) % 4 + 1;
	if (abs(this->pos.x - player_pos.x) < 100)
		this->pos.x += 200;
	if (abs(this->pos.y - player_pos.y) < 100)
		this->pos.y += 200;
}

Enemy::~Enemy()
{}

void Enemy::movement(ObjectMove)
{

}

void Enemy::takeDamage()
{

}