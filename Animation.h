#pragma once
struct Animation {
	int index;
	int speed;
	int frames;

	Animation() {}
	Animation(int i, int f, int s) {
		speed = s;
		frames = f;
		index = i;
	}
};