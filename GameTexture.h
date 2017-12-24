#include<SDL.h>
#include<map>
#include"GameObject.h"
class GameTexture
{
public:
	GameTexture(SDL_Renderer* renderer);
	~GameTexture();

	bool load(const char* path);
	void free();
	void render(GameObjectType type, SDL_Point target, double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	SDL_Texture* mTexture = nullptr;
	SDL_Renderer* mRenderer;
	int mSpriteStepPx = 50;

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