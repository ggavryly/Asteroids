#pragma once
#include "main.hpp"
#include "SDL2/SDL.h"
#include "../SDL2_image.framework/Headers/SDL_image.h"
#include "InitOptions.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

static SDL_Renderer *g_renderer;
static int g_width = 800;
static int g_height = 600;
static int g_framework_initialized = false;
static double g_angle = 0.0;
static bool move = false;

class Game : public Framework
{
public:
	Game();
	Game(Game const &);
	~Game();
	
	void PreInit(int& width, int& height, bool& fullscreen) override;
	bool Init() override;
	void Close() override;
	bool Tick() override;
	void onMouseMove(int x, int y, int xrelative, int yrelative) override;
	void onMouseButtonClick(FRMouseButton button, bool isReleased) override;
	void unitsCollision(void);
	void onKeyPressed(FRKey k) override;
	void onKeyReleased(FRKey k) override;
	void onKey(FRKey k);
	const char* GetTitle() override;

public:
	InitOptions	*init_;
private:
	Player	*player_;
	std::list<SpaceObject *>	enemies;
	Sprite* ava_;
	Sprite* enemy_;
	Sprite* reticle_;
	Sprite* bullet_;
	int as_w, as_h;
	int es_w, es_h;
	int rs_w, rs_h;
	int bs_w, bs_h;
	
	int r_x;
	int r_y;
	
	int ava_pos_x;
	int ava_pos_y;
	
	float b_x, b_y;
	float b_dir_x, b_dir_y;
	bool is_bullet_active;
	
	static const int sNumEnemies = 10;
	int e_x[sNumEnemies];
	int e_y[sNumEnemies];
	bool alive_[sNumEnemies];
	
	int last_mouse_x = 500;
	int last_mouse_y = 0;
};

