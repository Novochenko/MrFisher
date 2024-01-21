#pragma once
#include "ECS.h"
#include "SDL.h"


class TileComponent : public Component {
public:

	SDL_Texture* texture;
	SDL_Rect sourceRect, destinationRect;
	 
	TileComponent() = default;
	
	~TileComponent() {
		SDL_DestroyTexture(texture);
	}

	TileComponent(int sourceX, int sourceY, int xpos, int ypos, const char *filename) {
		texture = TextureManager::LoadTexture(filename);
		
		sourceRect.x = sourceX;
		sourceRect.y = sourceY;
		sourceRect.w = sourceRect.h = 32;

		destinationRect.x = xpos;
		destinationRect.y = ypos;
		destinationRect.h = destinationRect.w = 128;
	
	}

	void Draw() override {
		TextureManager::Draw(texture, sourceRect, destinationRect, SDL_FLIP_NONE);
	}

	
};
