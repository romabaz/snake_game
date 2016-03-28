#include<stdio.h>
#include"GameTexture.h"


GameTexture::GameTexture(SDL_Renderer* renderer){
	mTexture = NULL;
	mRenderer = renderer;
	mWidth = 0;
	mHeight = 0;
}

GameTexture::~GameTexture(){
	free();
}

bool GameTexture::load(char* path){
	free();
	SDL_Texture* loadedTexture = NULL;
	SDL_Surface* loadedSurface = SDL_LoadBMP(path);
	if (loadedSurface == NULL){
		printf("\n[ERROR][GameTexture::load] Unable to load image %s! SDL_Error: %s\n", path, SDL_GetError());
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
		loadedTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
		if (loadedTexture == NULL){
			printf("\n[ERROR][GameTexture::load] Unable to create texture from %s! SDL_Error: %s\n", path, SDL_GetError());
		}
		else {
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = loadedTexture;
	return loadedTexture != NULL;
}

void GameTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_RendererFlip flip){
	SDL_Rect targetRect = { x, y, mWidth, mHeight };
	if (clip != NULL){
		targetRect.w = clip->w;
		targetRect.h = clip->h;
	}
	SDL_RenderCopyEx(mRenderer, mTexture, clip, &targetRect, angle, NULL, flip);
}

int GameTexture::getHeight() {
	return mHeight;
}

int GameTexture::getWidth() {
	return mWidth;
}

void GameTexture::free(){
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
