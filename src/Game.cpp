#include "Game.hpp"
/*
 * structure declarations
 */

class Sprite {
public:
	Sprite():w(0), h(0), tex(nullptr) {}
	
	int w, h;
	SDL_Texture* tex;
};

FRAMEWORK_API double radianToAngle(double radian)
{
	return 180 / M_PI * radian;
}

FRAMEWORK_API double angleToRadian(double angle)
{
	return M_PI / 180 * angle;
}

FRAMEWORK_API Sprite* createSprite(const char* path)
{
	SDL_assert(g_framework_initialized);
	SDL_assert(g_renderer);
	
	SDL_Texture* texture = IMG_LoadTexture(g_renderer, path);
	if (!texture) {
		fprintf(stderr, "Couldn't load %s: %s\n", path, SDL_GetError());
		return nullptr;
	}
	
	
	Sprite* s = new Sprite();
	if (!s)
	{
		fprintf(stderr, "Not enough memory\n");
		SDL_Quit();
		exit(1);
	}
	
	SDL_QueryTexture(texture, NULL, NULL, &s->w, &s->h);
	
	s->tex = texture;
	
	return s;
}

FRAMEWORK_API void destroySprite(Sprite* s)
{
//	SDL_assert(g_framework_initialized);
//	SDL_assert(s);
	
	if (s->tex)
	{
		SDL_DestroyTexture(s->tex);
	}
	
	delete s;
}

FRAMEWORK_API void getSpriteSize(Sprite* s, int& w, int &h)
{
//	SDL_assert(s);
	w = s->w;
	h = s->h;
}

FRAMEWORK_API void drawSprite(Sprite* sprite, int x, int y)
{
	SDL_assert(g_framework_initialized);
	SDL_assert(g_renderer);
	SDL_assert(sprite);
	
	SDL_Rect r;
	r.w = sprite->w;
	r.h = sprite->h;
	r.x = x;
	r.y = y;
	SDL_RenderCopy(g_renderer, sprite->tex, NULL, &r);
}
FRAMEWORK_API void	wrapCoordinate(int &x, int &y)
{
	int sx, sy;
	getScreenSize(sx, sy);
	
	x = (x > sx) ? (0) : (x);
	y = (y > sy) ? (0) : (y);
	
	x = (x < 0) ? (sx) : (x);
	y = (y < 0) ? (sx) : (y);
}

FRAMEWORK_API void	wrapCoordinatef(float &x, float &y)
{
	int sx, sy;
	getScreenSize(sx, sy);
	
	x = (x > sx) ? (0) : (x);
	y = (y > sy) ? (0) : (y);
	
	x = (x < 0) ? (sx) : (x);
	y = (y < 0) ? (sx) : (y);
}
FRAMEWORK_API void drawSpriteAngle(Sprite *sprite,int x, int y, double angle)
{
	SDL_assert(g_framework_initialized);
	SDL_assert(g_renderer);
	SDL_assert(sprite);
	
	SDL_Rect renderQuad = {x, y, sprite->w, sprite->h};
	SDL_RenderCopyEx(g_renderer, sprite->tex, nullptr, &renderQuad, angle, nullptr, SDL_FLIP_NONE);
}

FRAMEWORK_API void getScreenSize(int& w, int &h)
{
//	SDL_assert(g_framework_initialized);
//	SDL_assert(g_renderer);
	
	SDL_Rect viewport;
	SDL_RenderGetViewport(g_renderer, &viewport);
	w = viewport.w;
	h = viewport.h;
}

FRAMEWORK_API unsigned int getTickCount()
{
	return SDL_GetTicks();
}



/* Draw a Gimpish background pattern to show transparency in the image */
static void draw_background(SDL_Renderer *renderer, int w, int h)
{
}


FRAMEWORK_API void drawTestBackground()
{
	SDL_assert(g_framework_initialized);
	SDL_assert(g_renderer);
	
	SDL_Rect viewport;
	SDL_RenderGetViewport(g_renderer, &viewport);
	return draw_background(g_renderer, viewport.w, viewport.h);
}

FRAMEWORK_API void showCursor(bool bShow)
{
	SDL_ShowCursor(bShow?1:0);
}

bool GKeyState[(int)FRKey::COUNT] = {};

FRAMEWORK_API int run(Framework* framework)
{
	SDL_Window *window;
	Uint32 flags;
	int done;
	bool event_check = false;
	SDL_Event event;
	
	for (int i = 0; i < (int)FRKey::COUNT; ++i)
	{
		GKeyState[i] = false;
	}
	
	Framework* GFramework = framework;
	
	bool fullscreen;
	GFramework->PreInit(g_width, g_height, fullscreen);
	
	SDL_ShowCursor(SDL_ENABLE);
	flags = SDL_WINDOW_HIDDEN;
	if (fullscreen) {
		SDL_ShowCursor(SDL_ENABLE);
		flags |= SDL_WINDOW_FULLSCREEN;
	}
	
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "SDL_Init(SDL_INIT_VIDEO) failed: %s\n", SDL_GetError());
		return(2);
	}
	
	if (SDL_CreateWindowAndRenderer(0, 0, flags, &window, &g_renderer) < 0) {
		fprintf(stderr, "SDL_CreateWindowAndRenderer() failed: %s\n", SDL_GetError());
		return(2);
	}
	
	{
		/* Show the window */
		SDL_SetWindowTitle(window, GFramework->GetTitle());
		SDL_SetWindowSize(window, g_width, g_height);
		SDL_ShowWindow(window);
		
		g_framework_initialized = true;
		
		if (!GFramework->Init())
		{
			fprintf(stderr, "Framework::Init failed\n");
			SDL_Quit();
			exit(1);
		}
		
		done = 0;
		while ( ! done )
		{
			while ( SDL_PollEvent(&event) ) {
				switch (event.type) {
					case SDL_KEYUP:
						switch (event.key.keysym.sym)
						{
							case SDLK_RIGHT:
							case SDLK_LEFT:
							case SDLK_DOWN:
							case SDLK_UP:
							{
								int key_index = (event.key.keysym.sym - SDLK_RIGHT);
								GFramework->onKeyReleased((FRKey)key_index);
								GKeyState[key_index] = false;
								break;
							}
							case SDLK_ESCAPE:
								done = 1;
								break;
							default:
								break;
						}
						break;
					case SDL_KEYDOWN:
						switch (event.key.keysym.sym)
						{
							case SDLK_RIGHT:
							case SDLK_LEFT:
							case SDLK_DOWN:
							case SDLK_UP:
							{
								int key_index = (event.key.keysym.sym - SDLK_RIGHT);
								GKeyState[key_index] = true;
							}
								break;
							default:
								break;
							
						}
						break;
					case SDL_MOUSEBUTTONDOWN:
						if (event.button.button <= SDL_BUTTON_RIGHT) {
							GFramework->onMouseButtonClick((FRMouseButton)(event.button.button - SDL_BUTTON_LEFT), false);
						}
						break;
					case SDL_MOUSEBUTTONUP:
						if (event.button.button <= SDL_BUTTON_RIGHT) {
							GFramework->onMouseButtonClick((FRMouseButton)(event.button.button - SDL_BUTTON_LEFT), true);
						}
						break;
					case SDL_MOUSEMOTION:
						GFramework->onMouseMove(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
						break;
					case SDL_QUIT:
						done = 1;
						break;
					default:
						break;
				}
			}
			GFramework->onKeyPressed(FRKey::COUNT);
			
			SDL_RenderClear(g_renderer);
			
			SDL_Rect viewport;
			SDL_RenderGetViewport(g_renderer, &viewport);
			
			/* Draw a gray background */
			SDL_SetRenderDrawColor(g_renderer, 0xA0, 0xA0, 0xA0, 0xFF);
			SDL_RenderClear(g_renderer);
			
			done |= GFramework->Tick() ? 1 : 0;
			SDL_RenderPresent(g_renderer);
			SDL_Delay(1);
		}
	}
	
	GFramework->Close();
	
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(window);
	
	g_framework_initialized = false;
	
	/* We're done! */
	SDL_Quit();
	return(0);
}

Game::Game()
{}

Game::~Game()
{
	Close();
}

void Game::drawEvents()
{

	if (events.size() > 0)
	{
		for (auto elem = events.begin(); elem < events.end(); elem++)
		{
			if (elem->animation.getCurrentFrame() != -1)
				elem->animation.animate(elem->pos.x - ex_w / 2 , elem->pos.y - ex_h / 2, explosion);
			else if (elem->animation.getCurrentFrame() == -1)
				elem = events.erase(elem);
		}
	}
}

Vector Game::interpolateCoords(Vector const &xy0, Vector const &xy1)
{
	Vector tmp;
	tmp.x = (xy0.x + xy1.x) / 2;
	tmp.y = (xy0.y + xy1.y) / 2;
	return tmp;
}

void Game::PreInit(int& width, int& height, bool& fullscreen)
{
	width = 1000;
	height = 1000;
	fullscreen = false;
}
bool Game::Init()
{
	
	int sx, sy;
	getScreenSize(sx, sy);
	
	showCursor(false);
	
	ava_ = createSprite("../data/spaceship.png");
	enemy_ = createSprite("../data/small_asteroid.png");
	reticle_ = createSprite("../data/circle.tga");
	bullet_ = createSprite("../data/bullet.png");
	for (int j = 1; j < 14 + 1; j++)
		explosion.push_back(createSprite(("../data/explosion-" + std::to_string(j) + ".png").c_str()));
	
	if (!reticle_ || !ava_ || ! enemy_ || !reticle_ || !bullet_)
		return false;
	
	getSpriteSize(ava_, as_w, as_h);
	getSpriteSize(enemy_, es_w, es_h);
	getSpriteSize(reticle_, rs_w, rs_h);
	getSpriteSize(bullet_, bs_w, bs_h);
	getSpriteSize(explosion[0] ,ex_w, ex_h);
	
	
	player_ = new Player(ava_);
	for (int i = 0; i < sNumEnemies; i++)
		enemies.push_back(new Enemy(player_->pos, enemy_));
	
	ava_pos_x = sx / 2;
	ava_pos_y = sy / 2;
	
	r_x = ava_pos_x;
	r_y = ava_pos_y;
	
	b_x = b_y = 0;
	is_bullet_active = false;
	b_dir_x = b_dir_y = 1;
	
	return true;
}

void Game::Close()
{
	destroySprite(ava_);
	destroySprite(enemy_);
	destroySprite(reticle_);
	for (auto &elem : explosion)
		destroySprite(elem);
}

void Game::unitsCollision()
{
	for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
	{
//		if (player_->collision(*enemy))
//		{
//			(*enemy)->takeDamage();
//			player_->takeDamage();
//			Game::Close();
//			exit(1);
//		}
		for (auto elem = enemies.begin(); elem != enemies.end(); elem++)
		{
			if (elem != enemy && (*enemy)->collision(*elem))
			{
				(*elem)->takeDamage();
				(*enemy)->takeDamage();
				events.push_back(EventExplosion(interpolateCoords((*elem)->getPos(), (*enemy)->getPos()), explosion.size()));
				elem = enemies.erase(elem);
				enemy = enemies.erase(enemy);
				break;
			}
		}
	}
}

bool Game::Tick() {
	
	drawTestBackground();
	
	unitsCollision();
	drawSpriteAngle(ava_, player_->pos.x - as_w / 2,  player_->pos.y - as_h / 2, player_->angle);
	
	bool should_exit = false;
	for (auto & elem : enemies)
	{
		if (enemies.size() > 0)
		{
			drawSpriteAngle(enemy_, elem->pos.x - es_w / 2, elem->pos.y - es_h / 2, elem->angle += elem->angle_velocity);
			elem->angle = (elem->angle > 360.0f) ? (0.0f) : (elem->angle);
			should_exit = false;
			elem->pos.x += elem->dir.x * elem->velocity;
			elem->pos.y += elem->dir.y * elem->velocity;
			wrapCoordinatef(elem->pos.x, elem->pos.y);
		}
	}
	
	drawSprite(reticle_, r_x - rs_w / 2, r_y - rs_h / 2);
	if (is_bullet_active)
	{
		const float speed = 1.5f;
		
		b_x = b_x + b_dir_x * speed;
		b_y = b_y + b_dir_y * speed;
		
		int sx, sy;
		getScreenSize(sx, sy);
		
		if (b_x < 0 || b_x > sx)
			is_bullet_active = false;
		
		if (b_y < 0 || b_y > sy)
			is_bullet_active = false;
	}
	if (is_bullet_active)
	{
		drawSprite(bullet_, (int)b_x - bs_w / 2, (int)b_y - bs_h / 2);
	}
	
	if (enemies.size() != sNumEnemies)
	{
		for(int i = 0, delta = sNumEnemies - enemies.size(); i < delta; i++)
			enemies.push_back(new Enemy(player_->pos, enemy_));
	}
	drawEvents();
	
	return should_exit;
}

void Game::onMouseMove(int x, int y, int xrelative, int yrelative)
{
	last_mouse_x = x;
	last_mouse_y = y;
	r_x = x;
	r_y = y;
}

void Game::onMouseButtonClick(FRMouseButton button, bool isReleased)
{
	
	float rx = (float)r_x;
	float ry = (float)r_y;
	if (button == FRMouseButton::LEFT && !isReleased)
	{
		for (int i = 0; i < sNumEnemies; ++i)
		{
			if (!alive_[i])
				continue;
			
			float x = (float)e_x[i];
			float y = (float)e_y[i];
			
			float dist_sq = (rx - x)*(rx - x) + (ry - y)*(ry - y);
			
			if (dist_sq < 10 * 10)
			{
				alive_[i] = false;
				continue;
			}
		}
	}
	
	if (button == FRMouseButton::RIGHT && !isReleased)
	{
		b_x = (float)ava_pos_x;
		b_y = (float)ava_pos_y;
		b_dir_x = (float)(rx - b_x);
		b_dir_y = (float)(ry - b_y);
		
		// normalize
		float len = sqrtf(b_dir_x*b_dir_x + b_dir_y*b_dir_y);
		b_dir_x = b_dir_x / len;
		b_dir_y = b_dir_y / len;
		
		is_bullet_active = true;
	}
	
}
void Game::onKeyPressed(FRKey k) {
	
	onKey(k);
}
void Game::onKeyReleased(FRKey k) {
	
	onKey(k);
}

void Game::onKey(FRKey k)
{
	bool ev_check = false;
	for (int i = 0; i < 4; i++)
	{
		if (GKeyState[i])
		{
			player_->movement(ObjectMove(i));
			ev_check = true;
		}
	}
	player_->movement(NOTHING);
}
const char* Game::GetTitle()
{
	return "asteroids";
}
