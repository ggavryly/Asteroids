#include "Animation.hpp"

Animation::Animation(int sprite_count)
{
	current_frame = 0;
	max_frames = sprite_count;
	frame_inc = 1;
	frame_rate = 65;
	old_time = 0;
	oscillate = false;
}

Animation::~Animation()
{}

void Animation::animate(int pos_x, int pos_y, std::vector<Sprite *> & sprites)
{
	drawSprite(sprites[current_frame], pos_x, pos_y);
	onAnimate();
}

void Animation::onAnimate()
{
	if (old_time + frame_rate > SDL_GetTicks())
		return;
	
	old_time = SDL_GetTicks();
	current_frame += frame_inc;
	
	if (oscillate)
	{
		if (frame_inc > 0)
		{
			if(current_frame >= max_frames)
				frame_inc = -frame_inc;
		}
		else
		{
			if (current_frame <= 0)
				frame_inc = -frame_inc;
		}
	}
	else
	{
		if (current_frame >= max_frames)
			current_frame = -1;
	}
}

void Animation::setFrameRate(int Rate)
{
	frame_rate = Rate;
}

void Animation::setCurrentFrame(int Frame)
{
	if (Frame < 0 || Frame >= max_frames)
		return;
	
	current_frame = Frame;
}

int Animation::getCurrentFrame()
{
	return current_frame;
}
