#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>
#include "Game.h"

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	
	
public:
	bool animated = false;
	int frames = 0;
	int speed = 100;
	SDL_Rect sourceRect, destinationRect;
	int animIndex = 0;
	int xIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(const char* filename, int sourceX, int sourceY, int destinationX, int destinationY) {
		sourceRect.h = sourceRect.w = 32;
		xIndex = sourceX;
		/*sourceRect.x = sourceX * sourceRect.w;
		sourceRect.y = sourceY * sourceRect.h;*/
		destinationRect.x = destinationX;
		destinationRect.y = destinationY;
		SetTex(filename);
		

	}
	SpriteComponent(const char* filename, int sourceX, int sourceY, int destinationX, int destinationY, int w, int h) {
		//sourceRect.h = sourceRect.w = 32;
		sourceRect.w = w;
		sourceRect.h = h;
		xIndex = sourceX;
		animIndex = sourceY;
		/*sourceRect.x = sourceX * sourceRect.w;
		sourceRect.y = sourceY * sourceRect.h;*/
		destinationRect.x = destinationX;
		destinationRect.y = destinationY;
		SetTex(filename);


	}
	std::pair<const char*, Animation>* AnimationsAdd(const char* name, int index, int frames, int speed) {
		Animation *tmp = new Animation(index, frames, speed);
		tmp->frames = frames;
		tmp->index = index;
		tmp->speed = speed;
		std::pair<const char*, Animation> *p =  new std::pair<const char*, Animation>(name, *tmp);
		animations.emplace(*p);
		return p;
	}
	SpriteComponent(const char* filename, bool isAnimated, const char* anim, int index, int frame, int speed) {
		animated = isAnimated;
		/*Animation idle = Animation(0, 5, 2000);
		Animation walk = Animation(1, 6, 100);
		animations.emplace("idle", idle);
		animations.emplace("walk", walk);*/
		AnimationsAdd(anim, index, frame, speed);

		Play(anim);

		SetTex(filename);
	}
	
	
	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}
	void SetTex(const char* filename) {
		if (texture) {
			SDL_DestroyTexture(texture);
		}
		texture = TextureManager::LoadTexture(filename);
	}

	void Init() override {

		transform = &entity->getComponent<TransformComponent>();

		//sourceRect.x = sourceRect.y = 0;
		sourceRect.w = transform->height;
		sourceRect.h = transform->width;
		destinationRect.w = destinationRect.h = 64;
	}


	void Update() override {

		if (animated) {
			sourceRect.x = sourceRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
			//sourceRect.y = sourceRect.w;
		}
		else {
			sourceRect.x = xIndex * sourceRect.w;
		}
		sourceRect.y = animIndex * sourceRect.h;


		destinationRect.x = static_cast<int>(transform->position.x);
		destinationRect.y = static_cast<int>(transform->position.y);
		destinationRect.w = transform->width * transform->scale;
		destinationRect.h = transform->height * transform->scale;
	}

	void Draw() override {
		TextureManager::Draw(texture, sourceRect, destinationRect, spriteFlip);
	} 

	void Play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};