#pragma once
#include "Game.h"
#include "Map.h"
#include "Components.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Collision.h"
#include "HookNPlayer.h"
#include "Fishes.h"
#include <time.h>
#include "HookNFishes.h"



SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Map* map;
Manager manager;
//Manager* manager;
bool hookIsActive = false;
bool fishCatched = false;
bool playerStay = true;

std::vector<ColliderComponent*> Game::colliders; 
Entity& player(manager.addEntity());
//Entity& garbage(manager.addEntity());

Entity& hookEntity(manager.addEntity());
Entity& fishingLine(manager.addEntity());

Entity& leftWall(manager.addEntity());
Entity& rightWall(manager.addEntity());

//Entity& leftWallPlayer(manager.addEntity());
//Entity& rightWallPlayer(manager.addEntity());
Fishes fish;
const char* mapFile = "assets/tileset8x6.png";

Entity& textRecordGame(manager.addEntity());

std::vector<Entity*>& tiles(manager.getGroup(groupMap));

std::vector<Entity*>& fishes(manager.getGroup(groupFishes));

std::vector<Entity*>& garbages(manager.getGroup(groupGarbage));

//std::vector<Entity*>& buttons(manager.getGroup(groupButtons));



extern Death* death;
extern Game* game;

void GameToDeath() {
    death->Run();
    game->Stop();
    manager.destroy();
    //manager.Refresh();
    //game->Init();
}

void (*gameToDeath)() = GameToDeath;

Game::Game() {}

Game::~Game() {}
void Game::Init() {

    map = new Map();

    Map::LoadMap("assets/tilemap8x6.txt", 8, 6);
    game->Record = 0;
    

    player.addComponent<TransformComponent>(3);
    player.addComponent<SpriteComponent>("assets/player.png", true, "idle", 4, 4, 2000);
    //player.getComponent<SpriteComponent>().AnimationsAdd("idle", 0, 5, 2000);
    player.getComponent<SpriteComponent>().AnimationsAdd("walk", 5, 7, 100);
    player.getComponent<SpriteComponent>().AnimationsAdd("catch", 2, 7, 100);
    player.addComponent<KeyboardController<Game>>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupLabels::groupPlayers);
    player.name = "player";

    hookEntity.addComponent<TransformComponent>(100.0f, 100.0f, 32, 32, 1);
    hookEntity.addComponent<SpriteComponent>("assets/MrHook.png", 15, 0, 32, 32);
    hookEntity.getComponent<SpriteComponent>().SetTex("assets/string.png");
    hookEntity.addComponent<HookKeyboardController>();
    hookEntity.addComponent<ColliderComponent>("hook");
    hookEntity.addGroup(groupHooks);
    hookEntity.name = "hook";

    

    leftWall.addComponent<TransformComponent>(-300.0f, 0.0f, 1200, 1, 1);
    leftWall.addComponent<ColliderComponent>("wall");
    leftWall.getComponent<ColliderComponent>().Init();
    leftWall.name = "leftWall";

    rightWall.addComponent<TransformComponent>(1500.0f, 0.0f, 1200, 1, 1);
    rightWall.addComponent<ColliderComponent>("wall");
    rightWall.getComponent<ColliderComponent>().Init();
    rightWall.name = "rightWall";


    fish.SpawnFishes();
    fish.FishScene(fishes);
    fish.SpawnGarbage();
    fish.FishScene(garbages);


   



}

void Game::Init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Initialised" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window){
            std::cout << "Window created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer){
            SDL_SetRenderDrawColor(renderer,255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }
        //IsRunning = true;

    }
    /*else{
        IsRunning = false;
    }*/

   
    //menu->HandleEvents();
    




}
void Game::AddTail(int sourceX, int sourceY, int xpos, int ypos) {
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(sourceX, sourceY, xpos, ypos, mapFile);
    tile.addGroup(groupMap);
}

void Game::HandleEnvents() {
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            IsRunning = false;
            break;

        default:
            break;
        }
    
    
}
void Game::GameReload() {

}
void Game::Clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaned successfully" << std::endl;
}
size_t fishNum = 0;
void Game::Update() {
    
   
    manager.Update();
    
    if (player.getComponent<TransformComponent>().position.x < 0) {
        player.getComponent<TransformComponent>().position.x = 0;
    }
    if (player.getComponent<TransformComponent>().position.x > 1024 - 196) {
        player.getComponent<TransformComponent>().position.x = 1024 - 196;
    }
    
    fish.FishVectorRefresh(fishes, colliders);
    fish.GarbageVectorRefresh(garbages, colliders);
    
    for (auto& f : fishes) {
        HnFUpdate(hookEntity, *f, player, fishNum);
        fishNum++;
    }
    fishNum = 0;
    
        

    hkUpdate(player, hookEntity);
    //hkUpdate(player, fishingLine);
   
    //manager.Refresh();
    HnGUpdate(hookEntity, garbages);
  
    
}  

void Game::Render() {
    SDL_RenderClear(renderer);
    for (std::vector<Entity*>::iterator i = tiles.begin(); i != tiles.end(); ++i) {
        //Entity*& t = *i;
       (*i)->Draw();
    }
    //for (std::vector<Entity*>::iterator i = players.begin(); i != players.end(); ++i) {
    //    //Entity*& t = *i;
    //    (*i)->Draw();
    //}
    
    player.Draw();
    hookEntity.Draw();
    //garbage.Draw();
    
    for (std::vector<Entity*>::iterator i = garbages.begin(); i != garbages.end(); ++i) {
        //Entity*& t = *i;
        (*i)->Draw();
    }

    for (std::vector<Entity*>::iterator i = fishes.begin(); i != fishes.end(); ++i) {
        //Entity*& t = *i;
        (*i)->Draw();
    }

    
    //fishingLine.Draw();
    
    /*for (auto& f : fish.fishesVec) {
        f->Draw();
    }*/

   

    SDL_RenderPresent(renderer);
};