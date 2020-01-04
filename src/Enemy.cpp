#include "Enemy.hpp"

Enemy::Enemy(Vector const & player_pos, Sprite * enemy_sprite, bool is_big)
{
	static int i=1;
	int tmpx, tmpy;
	getScreenSize(tmpx, tmpy);
	srand(time(nullptr));
	dir = Vector((rand() + i) % 360,0,0).normalization();
	i += 2;
	pos.x = abs((rand() * i) % tmpx);
	pos.y = abs((rand() / i) % tmpy);
	velocity = rand() % 1 + 1;
	sprite = enemy_sprite;
	angle_velocity = (rand() + i) % 4 + 1;
	getSpriteSize(enemy_sprite, tmpx, tmpy);
	width = tmpx;
	height = tmpy;
	this->is_big = is_big;
	angle_velocity = (rand() + i) % 4 + 1;
	if (abs(this->pos.x - player_pos.x) < 250)
		this->pos.x -= 200;
	if (abs(this->pos.y - player_pos.y) < 250)
		this->pos.y -= 200;
}

Enemy::Enemy(Vector const &big_asteroid_pos, Sprite *my_sprite, Vector const &big_asteroid_dir)
{
	static int j = 1;
	int tmpx, tmpy;
	srand(time(nullptr));
	angle_velocity = (rand() + j) % 4 + 1;
	sprite = my_sprite;
	getSpriteSize(sprite, tmpx, tmpy);
	width = tmpx;
	height = tmpy;
	velocity = rand() % 1 + 1;
	pos = big_asteroid_pos;
	dir = big_asteroid_dir;
	is_big = false;
	float tmp_angle = radianToAngle(acosf(dir.x));
	tmp_angle = (dir.y > 0) ? (tmp_angle) : (tmp_angle + 180);
	if (j % 2 == 0)
		dir = Vector(tmp_angle + 90, 0,0);
	else
		dir = Vector(tmp_angle - 90,0,0);
	j++;
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
