#include<SDL.h>
class GameTexture
{
public:
	GameTexture(SDL_Renderer* renderer);
	~GameTexture();

	bool load(const char* path, int spriteStepPx);
	void free();
	void render(int x, int y, SDL_Rect* clip, double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int getWidth();
	int getHeight();

private:
	SDL_Texture* mTexture;
	SDL_Renderer* mRenderer;
	int mWidth;
	int mHeight;
	int mSpriteStepPx;
	SDL_Rect mSpriteClips[12];

	void initSpriteClips();
	
};