#include "Player.hpp"
Player::Player(Sprite *player_sprite)
{
	int tmp_x,tmp_y;
	getScreenSize(tmp_x, tmp_y);
	pos.x = tmp_x / 2; pos.y = tmp_y / 2;
	dir.x = 0; dir.y = 1;
	getSpriteSize(player_sprite, tmp_x, tmp_y);
	obj_min_scope.x = -(tmp_x / 2);
	obj_min_scope.y = -(tmp_y / 2);
	obj_max_scope.x = tmp_x / 2;
	obj_max_scope.y = tmp_y / 2;
	velocity = 0.5;
	_player = player_sprite;
}

Player::Player(Player const &)
{}

Player::~Player()
{}

void Player::shoot()
{

}

void Player::movement(ObjectMove m)
{
	switch (m)
	{
		case ObjectMove::UP:
		{
			velocity *= 1.1;
			velocity = (velocity > 2) ? (2) : (velocity);
			pos.x += dir.x * (velocity * 5);
			pos.y += dir.y * (velocity * 5);
			std::cout << velocity << std::endl;
			_last_dir = dir;
			break;
		}
		case ObjectMove::DOWN:
		{
			velocity *= 0.9;
			velocity = (velocity < 0.01) ? (0.01) : (velocity);
			pos.x -= dir.x * (velocity * 5);
			pos.y -= dir.y * (velocity * 5);
			_last_dir = dir;
			break;
		}
		case ObjectMove::NOTHING:
			pos.x += _last_dir.x * velocity;
			pos.y += _last_dir.y * velocity;
			break;
	}
	
	pos.x = pos.x < 0 ? 0 : pos.x;
	pos.y = pos.y < 0 ? 0 : pos.y;
	
	int sx, sy;
	getScreenSize(sx, sy);
	
	pos.x = pos.x > sx ? sx : pos.x;
	pos.y = pos.y > sy ? sy : pos.y;
//	std::cout << "pos_x = " << pos.x << std::endl;
//	std::cout << "pos_y = " << pos.y << std::endl << std::endl;
//	std::cout << "dir_x = " << dir.x << std::endl;
//	std::cout << "dir_y = " << dir.y << std::endl << std::endl;
}

float Player::directionChoose(Vector const & last_mouse_state)
{
	
	Vector hypotenuse = last_mouse_state - pos;
	Vector x_line(abs(last_mouse_state.x - pos.x), 0);
	Vector y_line(0, abs(last_mouse_state.y - pos.y));
	dir.x = hypotenuse.normalization().x;
	dir.y = hypotenuse.normalization().y;
	if (hypotenuse.x > 0 && hypotenuse.y < 0)
		return -(radianToAngle(acosf(Vector::abs(hypotenuse).angleVector(x_line))) - GRID_90);
	else if (hypotenuse.x < 0 && hypotenuse.y < 0)
		return radianToAngle(acosf(Vector::abs(hypotenuse).angleVector(x_line))) + GRID_270;
	else if (hypotenuse.x < 0 && hypotenuse.y > 0)
		return -(radianToAngle(acosf(Vector::abs(hypotenuse).angleVector(x_line))) - GRID_90) + GRID_180;
	else if (hypotenuse.x > 0 && hypotenuse.y > 0)
		return radianToAngle(acosf(Vector::abs(hypotenuse).angleVector(x_line))) + GRID_90;
	_last_dir = dir;
}

void Player::takeDamage()
{

}