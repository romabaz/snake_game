#include<stdio.h>
#include"GameTexture.h"


GameTexture::GameTexture(SDL_Renderer* renderer) : mRenderer(renderer) {
}

GameTexture::~GameTexture(){
	free();
}

bool GameTexture::load(const char* path){
	free();
	SDL_Texture* loadedTexture = nullptr;
	SDL_Surface* loadedSurface = SDL_LoadBMP(path);
	if (loadedSurface == nullptr){
		printf("\n[ERROR][GameTexture::load] Unable to load image %s! SDL_Error: %s\n", path, SDL_GetError());
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
		loadedTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
		if (loadedTexture == nullptr){
			printf("\n[ERROR][GameTexture::load] Unable to create texture from %s! SDL_Error: %s\n", path, SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = loadedTexture;
	return loadedTexture != nullptr;
}

void GameTexture::render(GameObjectType type, SDL_Point target, double angle, SDL_RendererFlip flip) {
	SDL_Rect sourceRect = { sprites[type].x, sprites[type].y, mSpriteStepPx, mSpriteStepPx };
	SDL_Rect targetRect = { target.x, target.y, mSpriteStepPx, mSpriteStepPx };
	SDL_RenderCopyEx(mRenderer, mTexture, &sourceRect, &targetRect, angle, nullptr, flip);
}

//checkme: avoiding overhead for sequencial render() call -> duplicated all SDL_RenderCopyEx calls here. Check whether this increases fps
//possible simplification: renderVector() invokes render() for each different direction. 
void GameTexture::renderVector(const std::vector<DrawConstruct>& drawConstruct) {
	SDL_Rect sourceRect;
	SDL_Rect targetRect;
	for (DrawConstruct dc : drawConstruct) {
		sourceRect = { sprites[dc.type].x, sprites[dc.type].y, mSpriteStepPx, mSpriteStepPx };
		targetRect = { dc.x, dc.y, mSpriteStepPx, mSpriteStepPx };
		switch (dc.dir) {
		case LEFT:
			SDL_RenderCopyEx(mRenderer, mTexture, &sourceRect, &targetRect, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
			break;
		case RIGHT:
			SDL_RenderCopyEx(mRenderer, mTexture, &sourceRect, &targetRect, 0.0, nullptr, SDL_FLIP_NONE);
			break;
		case UP:
			SDL_RenderCopyEx(mRenderer, mTexture, &sourceRect, &targetRect, -90.0, nullptr, SDL_FLIP_NONE);
			break;
		case DOWN:
			SDL_RenderCopyEx(mRenderer, mTexture, &sourceRect, &targetRect, 90.0, nullptr, SDL_FLIP_NONE);
			break;
		}
	}
}

void GameTexture::free(){
	if (mTexture != nullptr) {
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
	}
}
