#include<stdio.h>
#include"GameTexture.h"


GameTexture::GameTexture(SDL_Renderer* renderer) : mRenderer(renderer) {
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
	mSpriteStepPx = 50;
}

GameTexture::~GameTexture(){
	free();
}

bool GameTexture::load(const char* path, int spriteStepPx){
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
		else {
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
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

int GameTexture::getHeight() {
	return mHeight;
}

int GameTexture::getWidth() {
	return mWidth;
}

void GameTexture::free(){
	if (mTexture != nullptr) {
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}
