#pragma once
#include "Game.h"
//#include "ECS.h"
#include "Components.h"
constexpr std::size_t maxFishes = 10;
extern Manager manager;
class Fishes
{

	//Manager manager;

public:
	void SpawnFishes();
	void FishTransform(Entity& fish);
	void FishScene(std::vector<Entity*> fish);
	int RandFish();
	void FishRefresh(Entity* fish);
	void FishVectorRefresh(std::vector<Entity*> fishes, std::vector<ColliderComponent*> colliders);
	void SpawnGarbage();
	void GarbageRefresh(Entity* f);
	void GarbageVectorRefresh(std::vector<Entity*> garbages, std::vector<ColliderComponent*> colliders);
};

 