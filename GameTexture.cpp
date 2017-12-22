#include<stdio.h>
#include"GameTexture.h"


GameTexture::GameTexture(SDL_Renderer* renderer){
	mTexture = nullptr;
	mRenderer = renderer;
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
	if (loadedTexture != nullptr) {
		mSpriteStepPx = spriteStepPx;
		initSpriteClips();
		return true;
	}
	else {
		return false;
	}
}

void GameTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_RendererFlip flip){
	SDL_Rect targetRect = { x, y, mWidth, mHeight };
	if (clip != nullptr){
		targetRect.w = clip->w;
		targetRect.h = clip->h;
	}
	SDL_RenderCopyEx(mRenderer, mTexture, clip, &targetRect, angle, nullptr, flip);
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

void GameTexture::initSpriteClips() {
	//Snake's head
	mSpriteClips[0].x = 0;
	mSpriteClips[0].y = 0;
	mSpriteClips[0].w = mSpriteStepPx;
	mSpriteClips[0].h = mSpriteStepPx;

	//Snake's body chain outer
	mSpriteClips[1].x = 50;
	mSpriteClips[1].y = 0;
	mSpriteClips[1].w = mSpriteStepPx;
	mSpriteClips[1].h = mSpriteStepPx;

	//Snake's body chain outer
	mSpriteClips[2].x = 100;
	mSpriteClips[2].y = 0;
	mSpriteClips[2].w = mSpriteStepPx;
	mSpriteClips[2].h = mSpriteStepPx;

	//Snake's body chain outer
	mSpriteClips[3].x = 150;
	mSpriteClips[3].y = 0;
	mSpriteClips[3].w = mSpriteStepPx;
	mSpriteClips[3].h = mSpriteStepPx;

	//Snake's body chain outer
	mSpriteClips[4].x = 200;
	mSpriteClips[4].y = 0;
	mSpriteClips[4].w = mSpriteStepPx;
	mSpriteClips[4].h = mSpriteStepPx;

	//Food: leave
	mSpriteClips[5].x = 250;
	mSpriteClips[5].y = 0;
	mSpriteClips[5].w = mSpriteStepPx;
	mSpriteClips[5].h = mSpriteStepPx;

	//Food: apple
	mSpriteClips[6].x = 300;
	mSpriteClips[6].y = 0;
	mSpriteClips[6].w = mSpriteStepPx;
	mSpriteClips[6].h = mSpriteStepPx;

	//Food: potato
	mSpriteClips[7].x = 350;
	mSpriteClips[7].y = 0;
	mSpriteClips[7].w = mSpriteStepPx;
	mSpriteClips[7].h = mSpriteStepPx;

	//Food: carrot
	mSpriteClips[8].x = 400;
	mSpriteClips[8].y = 0;
	mSpriteClips[8].w = mSpriteStepPx;
	mSpriteClips[8].h = mSpriteStepPx;
}
