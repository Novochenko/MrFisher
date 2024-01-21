#include "Menu.h"
#include "Components.h"
SDL_Event Death::event;
Manager managerDeath;
Entity& backgroundDeath(managerDeath.addEntity());
MouseController<Death> mouseDeath;
extern Buttons* butt;
std::vector<Entity*>& deathButtons(managerDeath.getGroup(groupDeathButtons));
extern Death* death;
extern Game* game;
extern Menu* menu;
extern Pause* pause;
extern Record* record;
Entity& textRetry(managerDeath.addEntity());
Entity& textExitDeath(managerDeath.addEntity());
Entity& textRecord(managerDeath.addEntity());



void DeathToMenu() {
	game->Stop();
	menu->Run();
	death->Stop();
	//game->Init(); // !!!
	record->add(menu->name, game->Record);
	
}
void DeathToGame(){
	game->Init();
	game->Run();
	death->Stop();
}
void (*deathToMenu)() = DeathToMenu;
void (*deathToGame)() = DeathToGame;




void Death::Init(SDL_Renderer* renderer, SDL_Window* window) {
	//game->Init();
	mWindowHeight = 720;
	mWindowWidth = 1024;
	mRenderer = renderer;

	mWindow = window;
	mIsRunning = false;

	backgroundDeath.addComponent<TransformComponent>(0.0f, -1200.0f, 960, 720, 2);
	backgroundDeath.addComponent<SpriteComponent>("assets/menuback1024x720.png", 0, 0, 0, 0);
	butt->SpawnDeathButtons();
	textRetry.addComponent<TextOutput<Death>>(death);
	textExitDeath.addComponent<TextOutput<Death>>(death);
	textRecord.addComponent<TextOutput<Death>>(death);
}
void Death::HandleEvents() {
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		mIsRunning = false;
		//windowClosed = true;
		break;

	default:
		break;
	}
}
void Death::Update() {
	//managerMenu.Refresh();
	managerDeath.Update();
	mouseDeath.Update();
	
	butt->DeathButtonsUpdate(deathButtons);

}

void Death::Render() {

	SDL_RenderClear(Death::mRenderer);

	managerDeath.Draw();
	textRetry.getComponent<TextOutput<Death>>().Write("Retry", 135, 167, 60, 0, 0, 0);
	textExitDeath.getComponent<TextOutput<Death>>().Write("Exit", 150, 400, 60, 0, 0, 0);
	textRecord.getComponent<TextOutput<Death>>().Write(std::to_string(game->Record), mWindowWidth/2, 50, 200, 0, 0, 0);

	
	SDL_RenderPresent(mRenderer);
}
