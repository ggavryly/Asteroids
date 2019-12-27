#pragma once


class Player
{
public:
	Player();
	
	Player(Player const &);
	
	~Player();

public:
	float	player_dir[2];
};

