#include "Collision.h"
#include "ColliderComponent.h"

SDL_Rect* result;
bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {
	if (rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y) {
		return true;
		}
	return false;

}

/*bool Colision::AABB(const SDL_Rect* rectA, const SDL_Rect* rectB) {
	if (SDL_IntersectRect(rectA, rectB, result) == SDL_TRUE) {
		return true;
	}
	return false;
}*/
bool Collision::AABB(const ColliderComponent& colA, ColliderComponent& colB) {
	if (AABB(colA.collider, colB.collider)) {
		std::cout << colA.tag << " Hit! " << colB.tag << std::endl;
		return true;
	}
	return false;
}