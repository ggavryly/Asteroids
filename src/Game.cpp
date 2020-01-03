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
	Uint32	old_time = 0;
	Uint32	fps = 12;
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
			if (old_time + fps > SDL_GetTicks())
				continue;
			else
			{
				old_time = SDL_GetTicks();
				GFramework->onKeyPressed(FRKey::COUNT);
				
				SDL_RenderClear(g_renderer);
				
				SDL_Rect viewport;
				SDL_RenderGetViewport(g_renderer, &viewport);
				
				/* Draw a gray background */
				SDL_SetRenderDrawColor(g_renderer, 0xA0, 0xA0, 0xA0, 0xFF);
				SDL_RenderClear(g_renderer);
				
				done |= GFramework->Tick() ? 1 : 0;
				SDL_RenderPresent(g_renderer);
			}
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
	big_enemy_ = createSprite("../data/big_asteroid.png");
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
		enemies.push_back(new Enemy(player_->pos, (i % 2 == 0) ? enemy_ : big_enemy_, i % 2 == 0));
	
	ava_pos_x = sx / 2;
	ava_pos_y = sy / 2;
	
	r_x = ava_pos_x;
	r_y = ava_pos_y;
	
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
	for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++) // collsion's compute
	{
//		if (player_->collision(*enemy)) // player and enemy's collsion
//		{
//			(*enemy)->takeDamage();
//			player_->takeDamage();
//			Game::Close();
//			exit(1);
//		}
		for (auto bullet = bullets.begin(); bullet < bullets.end(); bullet++) // bullets and enemy's collsion
		{
			if (enemy != enemies.end() && (*bullet)->collision(*enemy))
			{
				events.push_back(EventExplosion(interpolateCoords((*bullet)->getPos(), (*enemy)->getPos()), explosion.size()));
				bullet = bullets.erase(bullet);
//				if (dynamic_cast<Enemy *>(*enemy)->is_big)
//					splitAsteroid();
				enemy = enemies.erase(enemy);
			}
		}
		for (auto elem = enemies.begin(); elem != enemies.end(); elem++) // enemy's with enemy's collsion
		{
			if (elem != enemy && enemy != enemies.end() && (*enemy)->collision(*elem))
			{
				events.push_back(EventExplosion(interpolateCoords((*elem)->getPos(), (*enemy)->getPos()), explosion.size()));
//				if (dynamic_cast<Enemy *>(*enemy)->is_big)
//					splitAsteroid();
//				if (dynamic_cast<Enemy *>(*elem)->is_big)
//					splitAsteroid();
				elem = enemies.erase(elem);
				enemy = enemies.erase(enemy);
				continue;
			}
		}
	}
}

void Game::splitAsteroid(Vector const & pos)
{
	enemies.push_back(new Enemy(player_->pos, enemy_, false));
	enemies.push_back(new Enemy(player_->pos, enemy_, false));
}

bool Game::Tick() {
	
	drawTestBackground();
	
	unitsCollision();
	drawSpriteAngle(player_->sprite, player_->pos.x - as_w / 2,  player_->pos.y - as_h / 2, player_->angle);
	
	for (auto & elem : enemies) // enemy's rendering
	{
		if (enemies.size() > 0)
		{
			drawSpriteAngle(elem->sprite, elem->pos.x - es_w / 2, elem->pos.y - es_h / 2, elem->angle += elem->angle_velocity);
			elem->movement(ObjectMove::NOTHING);
		}
	}
	
	for (auto & elem : bullets) // bullet's rendering
	{
		if (enemies.size() > 0)
		{
			drawSpriteAngle(elem->sprite , elem->pos.x - es_w / 2, elem->pos.y - es_h / 2, elem->angle);
			elem->movement(ObjectMove::NOTHING);
		}
	}
	
	drawSprite(reticle_, r_x - rs_w / 2, r_y - rs_h / 2);
	
	if (enemies.size() != sNumEnemies)
	{
		srand(time(nullptr));
		for(int i = 0, delta = sNumEnemies - enemies.size(); i < delta; i++)
			enemies.push_back(new Enemy(player_->pos, (rand() % 2 == 0) ? (enemy_) : (big_enemy_), rand() % 2));
	}
	drawEvents();
	return false;
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
	
	if (button == FRMouseButton::LEFT && isReleased)
	{
		if (bullets.size() == sNumAmmo)
			bullets.erase(bullets.begin());
		bullets.push_back(player_->shoot(Vector(last_mouse_x, last_mouse_y), bullet_));
	}
	if (button == FRMouseButton::RIGHT && isReleased)
	{}
	
}
void Game::onKeyPressed(FRKey k) {
	
	onKey(k);
}
void Game::onKeyReleased(FRKey k) {
	
	onKey(k);
}

void Game::onKey(FRKey k)
{
	for (int i = 0; i < 4; i++)
	{
		if (GKeyState[i])
			player_->movement(ObjectMove(i));
	}
	player_->movement(NOTHING);
}
const char* Game::GetTitle()
{
	return "asteroids";
}
