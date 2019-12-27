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
	SDL_assert(g_framework_initialized);
	SDL_assert(s);
	
	if (s->tex)
	{
		SDL_DestroyTexture(s->tex);
	}
	
	delete s;
}

FRAMEWORK_API void getSpriteSize(Sprite* s, int& w, int &h)
{
	SDL_assert(s);
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

FRAMEWORK_API void getScreenSize(int& w, int &h)
{
	SDL_assert(g_framework_initialized);
	SDL_assert(g_renderer);
	
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
	SDL_Color col[2] = {
			{ 0x66, 0x66, 0x66, 0xff },
			{ 0x99, 0x99, 0x99, 0xff },
	};
	int i, x, y;
	SDL_Rect rect;
	
	rect.w = 8;
	rect.h = 8;
	for (y = 0; y < h; y += rect.h) {
		for (x = 0; x < w; x += rect.w) {
			/* use an 8x8 checkerboard pattern */
			i = (((x ^ y) >> 3) & 1);
			SDL_SetRenderDrawColor(renderer, col[i].r, col[i].g, col[i].b, col[i].a);
			
			rect.x = x;
			rect.y = y;
			SDL_RenderFillRect(renderer, &rect);
		}
	}
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
	SDL_Event event;
	
	for (int i = 0; i < (int)FRKey::COUNT; ++i)
	{
		GKeyState[i] = false;
	}
	
	Framework* GFramework = framework;
	
	bool fullscreen;
	GFramework->PreInit(g_width, g_height, fullscreen);
	
	flags = SDL_WINDOW_HIDDEN;
	if (fullscreen) {
		SDL_ShowCursor(0);
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
		while ( ! done ) {
			while ( SDL_PollEvent(&event) ) {
				switch (event.type) {
					case SDL_KEYUP:
						switch (event.key.keysym.sym) {
							case SDLK_RIGHT:
							case SDLK_LEFT:
							case SDLK_DOWN:
							case SDLK_UP:
							{
								int key_index = (event.key.keysym.sym - SDLK_RIGHT);
								if (GKeyState[key_index])
								{
									GFramework->onKeyReleased((FRKey)key_index);
									GKeyState[key_index] = false;
								}
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
						switch (event.key.keysym.sym) {
							case SDLK_RIGHT:
							case SDLK_LEFT:
							case SDLK_DOWN:
							case SDLK_UP:
							{
								int key_index = (event.key.keysym.sym - SDLK_RIGHT);
								if (!GKeyState[key_index])
								{
									GFramework->onKeyPressed((FRKey)key_index);
									GKeyState[key_index] = true;
								}
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

void Game::PreInit(int& width, int& height, bool& fullscreen)
{
	width = 1024;
	height = 768;
	fullscreen = false;
}
bool Game::Init()
{
	
	int sx, sy;
	getScreenSize(sx, sy);
	
	showCursor(false);
	
	ava_ = createSprite("data/spaceship.png");
	enemy_ = createSprite("data/small_asteroid.png");
	reticle_ = createSprite("data/circle.tga");
	bullet_ = createSprite("data/bullet.png");
	
	if (!reticle_ || !ava_ || ! enemy_ || !reticle_ || !bullet_)
		return false;
	
	getSpriteSize(ava_, as_w, as_h);
	getSpriteSize(enemy_, es_w, es_h);
	getSpriteSize(reticle_, rs_w, rs_h);
	getSpriteSize(bullet_, bs_w, bs_h);
	
	for (int i = 0; i < sNumEnemies; i++)
	{
		e_x[i] = rand() % sx;
		e_y[i] = rand() % sy;
		alive_[i] = true;
	}
	
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
}
bool Game::Tick() {
	
	drawTestBackground();
	
	drawSprite(ava_, ava_pos_x - as_w / 2, ava_pos_y - as_h / 2);
	
	bool should_exit = true;
	for (int i = 0; i < sNumEnemies; ++i)
	{
		if (alive_[i])
		{
			int offset_y = (int)(30*sinf(getTickCount()*0.01f + e_x[i]));
			drawSprite(enemy_, e_x[i] - es_w / 2, e_y[i] - es_w / 2 + offset_y);
			should_exit = false;
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
	
	return should_exit;
}

void Game::onMouseMove(int x, int y, int xrelative, int yrelative) {
	
	r_x = x;
	r_y = y;
}

void Game::onMouseButtonClick(FRMouseButton button, bool isReleased) {
	
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
	
	//onKey(k);
}

void Game::onKey(FRKey k)
{
	switch (k)
	{
		case FRKey::LEFT:
			ava_pos_x -= 10;
			break;
		case FRKey::RIGHT:
			ava_pos_x += 10;
			break;
		case FRKey::DOWN:
			ava_pos_y += 10;
			break;
		case FRKey::UP:
			ava_pos_y -= 10;
			break;
	}
	
	ava_pos_x = ava_pos_x < 0 ? 0 : ava_pos_x;
	ava_pos_y = ava_pos_y < 0 ? 0 : ava_pos_y;
	
	int sx, sy;
	getScreenSize(sx, sy);
	
	ava_pos_x = ava_pos_x > sx ? sx : ava_pos_x;
	ava_pos_y = ava_pos_y > sy ? sy : ava_pos_y;
}
const char* Game::GetTitle()
{
	return "asteroids";
}
