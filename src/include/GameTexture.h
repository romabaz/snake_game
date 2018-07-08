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
	void renderVector(const std::vector<DrawConstruct>& drawConstruct);

private:
	SDL_Texture* mTexture = nullptr;
	SDL_Renderer* mRenderer;
	int mSpriteStepPx = 50;

	std::map<GameObjectType, SDL_Point> sprites = {
		{ SNAKEY_HEAD, {0, 0} },
		{ SNAKEY_QUANTUM1, { mSpriteStepPx, 0} },
		{ SNAKEY_QUANTUM2, { 2 * mSpriteStepPx, 0 } },
		{ SNAKEY_QUANTUM3, { 3 * mSpriteStepPx, 0 } },
		{ SNAKEY_QUANTUM4, { 4 * mSpriteStepPx, 0 } },
		{ FOOD_LEAF, { 5 * mSpriteStepPx, 0 } },
		{ FOOD_APPLE, { 6 * mSpriteStepPx, 0 } },
		{ FOOD_POTATO, { 7 * mSpriteStepPx, 0 } },
		{ FOOD_CARROT, { 8 * mSpriteStepPx, 0 } }
	};
};