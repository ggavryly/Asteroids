#pragma once
#include "SDL.h"
#include "main.hpp"
#include "Framework.hpp"
class Animation
{
public:
	
	Animation(int sprite_count);
	
	Animation(Animation const &) = default;
	
	~Animation();
	
public:
	
	void onAnimate();
	void animate(int pos_x, int pos_y, std::vector<std::unique_ptr<Sprite>> const &);
	void setFrameRate(int Rate);
	void setCurrentFrame(int Frame);
	int getCurrentFrame();

private:
	int     				frame_rate;
	long    				old_time;
	int    					max_frames;
	bool    				oscillate;
	int   					current_frame;
	int    					frame_inc;
};

