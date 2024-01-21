#include "Fishes.h"
#include "Components.h"
#include "Collision.h"

std::bitset<maxFishes> fishesBitSet;

int Fishes::RandFish() {
	int r;
	do {
		r = rand() % 6;
	} while (r % 2 != 0);
	return r;
}
void Fishes::SpawnFishes() {
	for (size_t i = 0; i < maxFishes; i++) {
		int r = Fishes::RandFish();
		Entity& fish(manager.addEntity());
		fish.addComponent<TransformComponent>(2);
		fish.addComponent<SpriteComponent>("assets/fish_pack.png", true, "swim", r, 8, 100);
		fish.getComponent<SpriteComponent>().AnimationsAdd("catch", r + 1, 6, 100);
		//fish.getComponent<SpriteComponent>().AnimationsAdd("catch", r + 1, 6, 100);
		fish.addComponent<ColliderComponent>("fish");
		fishesBitSet[i] = 0;
		switch (r / 2)
		{
		case 0:
			fish.name = "fishPurple";
			break;

		case 1:
			fish.name = "fishGreen";
			break;

		case 2:
			fish.name = "carrotOctopus";
			break;
		}
		fish.addGroup(groupLabels::groupFishes);

	}
	
}
void Fishes::SpawnGarbage() {
	for (size_t i = 0; i < maxFishes / 2; i++) {
		Entity& garbage(manager.addEntity());
		garbage.addComponent<TransformComponent>(0.0f, 0.0f, 32, 32, 3);
		garbage.addComponent<SpriteComponent>("assets/garbage.png", true, "idle", 0, 6, 300);
		garbage.getComponent<SpriteComponent>().AnimationsAdd("idle", 0, 6, 200);

		garbage.addComponent<ColliderComponent>("garbage");
		garbage.addGroup(groupLabels::groupGarbage);
		garbage.name = "garbage";

	}
}
void Fishes::FishTransform(Entity& fish) {
	fish.getComponent<TransformComponent>().velocity.x = 1;
	fish.getComponent<TransformComponent>().velocity.y = 1;
}

std::vector<Entity*> leftFishes;
std::vector<Entity*> rightFishes;

void Fishes::FishRefresh(Entity* f) {
	//srand(time(NULL));
	f->getComponent<TransformComponent>().position.y = 160.0f + rand() % 300;
	f->getComponent<TransformComponent>().speed = 1 + rand() % 4;
	f->getComponent<TransformComponent>().position.x = f->getComponent<TransformComponent>().startPosX + rand() % 50;
	f->getComponent<ColliderComponent>().isActive = true;
	f->getComponent<SpriteComponent>().Play("swim");
			

}
void Fishes::GarbageRefresh(Entity* f) {
	f->getComponent<TransformComponent>().position.y = 160.0f + rand() % 300;
	f->getComponent<TransformComponent>().speed = 1 + rand() % 4;
	f->getComponent<TransformComponent>().position.x = f->getComponent<TransformComponent>().startPosX + rand() % 50;
	f->getComponent<SpriteComponent>().Play("idle");
}

void Fishes::GarbageVectorRefresh(std::vector<Entity*> garbages, std::vector<ColliderComponent*> colliders) {
	for (auto cols : Game::colliders) {

		if (cols->tag == "wall") {
			for (auto f : garbages) {
				if (Collision::AABB(f->getComponent<ColliderComponent>(), *cols)) {
					/*f->getComponent<TransformComponent>().position.y = 160.0f + rand() % 400;
					f->getComponent<TransformComponent>().speed = 1 + rand() % 4;
					f->getComponent<TransformComponent>().position.x = f->getComponent<TransformComponent>().startPosX + rand() % 128;*/
					Fishes::GarbageRefresh(f);
				}
			}
		}
	}
}

void Fishes::FishVectorRefresh(std::vector<Entity*> fishes, std::vector<ColliderComponent*> colliders) {
	for (auto cols : Game::colliders) {

		if (cols->tag == "wall") {
			for (auto f : fishes) {
				if (Collision::AABB(f->getComponent<ColliderComponent>(), *cols)) {
					/*f->getComponent<TransformComponent>().position.y = 160.0f + rand() % 400;
					f->getComponent<TransformComponent>().speed = 1 + rand() % 4;
					f->getComponent<TransformComponent>().position.x = f->getComponent<TransformComponent>().startPosX + rand() % 128;*/
					Fishes::FishRefresh(f);
				}
			}
		}
	}
}

void Fishes::FishScene(std::vector<Entity*> fish) {
	size_t each = maxFishes / 2;
	srand(time(NULL));
	//int side;
	for (auto f : fish) {
		if (rand() % 2 == 0) {
			f->getComponent<TransformComponent>().position.x = -200.0f + rand() % 64;
			f->getComponent<TransformComponent>().position.y = 160.0f + rand() % 400;
			f->getComponent<TransformComponent>().startPosY = f->getComponent<TransformComponent>().position.y;
			f->getComponent<TransformComponent>().startPosX = f->getComponent<TransformComponent>().position.x;
			f->getComponent<TransformComponent>().velocity.x = 1;
			f->getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_HORIZONTAL;
			f->getComponent<TransformComponent>().speed = 1 + rand() & 3;
			f->addComponent<ColliderComponent>("fish");
		}
		else {
			f->getComponent<TransformComponent>().position.x = 1050.0f + rand() % 64;
			f->getComponent<TransformComponent>().position.y = 160.0f + rand() % 400;
			f->getComponent<TransformComponent>().startPosY = f->getComponent<TransformComponent>().position.y;
			f->getComponent<TransformComponent>().startPosX = f->getComponent<TransformComponent>().position.x;
			f->getComponent<TransformComponent>().velocity.x = -1;
			f->getComponent<TransformComponent>().speed = 1 + rand() & 3;
			f->addComponent<ColliderComponent>("fish");
		}
	}

}