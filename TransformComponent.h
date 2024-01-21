#pragma once
#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component {
public:
	Vector2D position;
	Vector2D velocity;

	int speed = 3;
	int height = 64;
	int width = 64;
	int scale = 1;
	float startPosY;
	float startPosX;

	TransformComponent() {
		position.Zero();
	}
	TransformComponent(int scale) {
		position.Zero();
		this->scale = scale;
	}
	TransformComponent(float x, float y) {
		/*position.x = x;
		position.y = y;*/
		position.Zero();
	}


	TransformComponent(float x, float y, int h, int w) {
		position.x = x;
		position.y = y;
		width = w;
		height = h;

	}

	TransformComponent(float x, float y, int h, int w, int scale) {
		position.x = x;
		position.y = y;
		width = w;
		height = h;
		this->scale = scale;
		
	}

	void Init() override {
		velocity.Zero();
	}

	void Update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	} 

};
