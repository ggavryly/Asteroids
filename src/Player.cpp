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

void Player::computeMouseDir(Vector const & mouse_pos)
{
	Vector pl_mouse_hytotenuse = mouse_pos - pos;
	Vector x_line(abs(mouse_pos.x - pos.x), 0);
	_mouse_dir = pl_mouse_hytotenuse.normalization();
	if (_mouse_dir.x > 0 && _mouse_dir.y < 0)
		_mouse_angle = abs(GRID_90 - radianToAngle(acosf(Vector::abs(pl_mouse_hytotenuse).angleVector(x_line))));
	else if (_mouse_dir.x < 0 && _mouse_dir.y > 0)
		_mouse_angle = -(radianToAngle(acosf(Vector::abs(pl_mouse_hytotenuse).angleVector(x_line))) - GRID_90) + GRID_180;
	else if (_mouse_dir.x < 0 && _mouse_dir.y < 0)
		_mouse_angle = radianToAngle(acosf(Vector::abs(pl_mouse_hytotenuse).angleVector(x_line))) + GRID_270;
	else if (_mouse_dir.x > 0 && _mouse_dir.y > 0)
		_mouse_angle = radianToAngle(acosf(Vector::abs(pl_mouse_hytotenuse).angleVector(x_line))) + GRID_90;
}

Bullet* Player::shoot(Vector const & mouse_pos, Sprite *bullet_sprite)
{
	computeMouseDir(mouse_pos);
	return new Bullet(_mouse_dir, pos, bullet_sprite, _mouse_angle);
}

void Player::movement(ObjectMove m)
{
	switch (m)
	{
		case ObjectMove::UP:
		{
			velocity *= 1.05;
			velocity = (velocity > 2) ? (2) : (velocity);
			_last_dir.x += dir.x / velocity;
			_last_dir.y += dir.y / velocity;
			_last_dir = _last_dir.normalization();
			break;
		}
		case ObjectMove::LEFT:
		{
			angle -= 1;
			angle = (angle < 0.0f) ? (360.0f) : (angle);
			dir = Vector(GRID_90 -  angle);
			getComputerCoord(dir, angle);
			break;
		}
		case ObjectMove::RIGHT:
		{
			angle += 1;
			angle = (angle > 360.0f) ? (0.0f) : (angle);
			dir = Vector(GRID_90 - angle);
			getComputerCoord(dir, angle);
			break;
		}
		case ObjectMove::DOWN:
		{
			velocity *= 0.98;
			velocity = (velocity < 0.001) ? (0.001) : (velocity);
			_last_dir.x += dir.x * velocity;
			_last_dir.y += dir.y * velocity;
			_last_dir = _last_dir.normalization();
			break;
		}
		case ObjectMove::NOTHING:
			pos.x += _last_dir.x * velocity;
			pos.y += _last_dir.y * velocity;
			break;
	}
	int sx, sy;
	getScreenSize(sx, sy);
	
	pos.x = pos.x < 0 ? sx : pos.x;
	pos.y = pos.y < 0 ? sy : pos.y;
	
	
	pos.x = pos.x > sx ? 0 : pos.x;
	pos.y = pos.y > sy ? 0 : pos.y;
}

void getComputerCoord(Vector & lhs, double angle)
{
	if (angle <= GRID_90)
		lhs.y = -lhs.y;
	else if (angle >= GRID_90 && angle <= GRID_180)
		lhs.y = abs(lhs.y);
	else if (angle >= GRID_180 && angle <= GRID_270)
		lhs.y = abs(lhs.y);
	else if (angle >= GRID_270 && angle <= GRID_360)
		lhs.y = -lhs.y;
}