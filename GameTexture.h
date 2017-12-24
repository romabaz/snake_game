#include<SDL.h>
#include<map>
#include"GameWorld.h"
class GameTexture
{
public:
	GameTexture(SDL_Renderer* renderer);
	~GameTexture();

	bool load(const char* path, int spriteStepPx);
	void free();
	void render(GameObjectType type, SDL_Point target, double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int getWidth();
	int getHeight();

private:
	SDL_Texture* mTexture;
	SDL_Renderer* mRenderer;
	int mWidth;
	int mHeight;
	int mSpriteStepPx;
	SDL_Rect mSpriteClips[12];

	std::map<GameObjectType, SDL_Point> sprites = {
		{ SNAKEY_HEAD, {0, 0} },
		{ SNAKEY_QUANTUM1, {50, 0} },
		{ SNAKEY_QUANTUM2, { 100, 0 } },
		{ SNAKEY_QUANTUM3, { 150, 0 } },
		{ SNAKEY_QUANTUM4, { 200, 0 } },
		{ FOOD_LEAF, { 250, 0 } },
		{ FOOD_APPLE, { 250, 0 } },
		{ FOOD_POTATO, { 250, 0 } },
		{ FOOD_CARROT, { 250, 0 } }
	};
};