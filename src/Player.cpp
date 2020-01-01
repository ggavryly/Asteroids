#include "Player.hpp"
Player::Player(Sprite *player_sprite)
{
	int tmp_x,tmp_y;
	getScreenSize(tmp_x, tmp_y);
	pos.x = tmp_x / 2; pos.y = tmp_y / 2;
	dir.x = 0; dir.y = -1;
	getSpriteSize(player_sprite, tmp_x, tmp_y);
	width = tmp_x;
	height = tmp_y;
	velocity = 0.5;
	angle = 0;
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
			_last_dir.x += dir.x;
			_last_dir.y += dir.y;
			_last_dir = _last_dir.normalization();
			pos.x += _last_dir.x;
			pos.y += _last_dir.y;
			break;
		}
		case ObjectMove::LEFT:
		{
			angle -= 3;
			angle = (angle < 0.0f) ? (360.0f) : (angle);
			dir = Vector(GRID_90 -  angle);
			getComputerCoord(dir, angle);
			std::cout << "angle =" << GRID_90 - angle << " | " << dir << std::endl;
			break;
		}
		case ObjectMove::RIGHT:
		{
			angle += 3;
			angle = (angle > 360.0f) ? (0.0f) : (angle);
			dir = Vector(GRID_90 - angle);
			getComputerCoord(dir, angle);
			std::cout << "angle =" << GRID_90 - angle << " | " << dir << std::endl;
			break;
		}
		case ObjectMove::DOWN:
		{
			velocity *= 0.9;
			velocity = (velocity < 0.5) ? (0.5) : (velocity);
			_last_dir.x += dir.x;
			_last_dir.y += dir.y;
			_last_dir = _last_dir.normalization();
			pos.x -= _last_dir.x;
			pos.y -= _last_dir.y;
			break;
		}
		case ObjectMove::NOTHING:
//			pos.x += _last_dir.x * velocity;
//			pos.y += _last_dir.y * velocity;
			break;
	}
//	std::cout << _last_dir << std::endl;
	
	int sx, sy;
	getScreenSize(sx, sy);
	
	pos.x = pos.x < 0 ? sx : pos.x;
	pos.y = pos.y < 0 ? sy : pos.y;
	
	
	pos.x = pos.x > sx ? 0 : pos.x;
	pos.y = pos.y > sy ? 0 : pos.y;
}

void Player::takeDamage()
{

}

void getComputerCoord(Vector & lhs, double angle)
{
	std::cout << "BEFORE COMPUTER COORDS { x =" << lhs.x << "  | y =" << lhs.y << " }" << std::endl;
	if (angle <= GRID_90)
		lhs.y = -lhs.y;
	else if (angle >= GRID_90 && angle <= GRID_180)
		lhs.y = abs(lhs.y);
	else if (angle >= GRID_180 && angle <= GRID_270)
		lhs.y = abs(lhs.y);
	else if (angle >= GRID_270 && angle <= GRID_360)
		lhs.y = -lhs.y;
	std::cout << "AFTER COMPUTER COORDS { x =" << lhs.x << "  | y =" << lhs.y << " }" << std::endl;
}