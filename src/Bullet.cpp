#include "Bullet.hpp"

Bullet::Bullet(Vector &bullet_dir, Vector &bullet_pos ,Sprite *bullet_sprite, float angle)
{
	dir = bullet_dir;
	pos = bullet_pos;
	velocity = 5;
	this->bullet_sprite = bullet_sprite;
	int sp_w, sp_h;
	getSpriteSize(bullet_sprite, sp_w, sp_h);
	width = sp_w;
	height = sp_h;
	this->angle = angle;
}

void Bullet::movement(ObjectMove)
{
	pos.x += dir.x * velocity;
	pos.y += dir.y * velocity;
	int sx, sy;
	getScreenSize(sx, sy);
	
	pos.x = (pos.x > sx) ? (0) : (pos.x);
	pos.y = (pos.y > sy) ? (0) : (pos.y);
	
	pos.x = (pos.x < 0) ? (sx) : (pos.x);
	pos.y = (pos.y < 0) ? (sy) : (pos.y);
}

Bullet::~Bullet()
{}


