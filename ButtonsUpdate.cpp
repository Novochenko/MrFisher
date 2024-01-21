#include "ButtonsUpdate.h"


//extern Manager manager;

extern void (*pauseToMenu)();
extern void (*resumePause)();

extern void (*deathToMenu)();
extern void (*deathToGame)();

extern void (*recordsClean)();
extern void (*recordsPrint)();
extern void (*recordsToMenu)();

extern MouseController<Menu> mouse;
extern MouseController<Pause> mousePause;
extern MouseController<Death> mouseDeath;
extern MouseController<Record> mouseRecord;


void Buttons::ButtonsUpdate(std::vector<Entity*> buttons) {
	bool m_IsRelleased = true;
	Vector2D* mPos = mouse.GetMousePosition();
	SDL_Rect mShape;
	SDL_Point point = { (int)mPos->x,(int)mPos->y };
	delete mPos;
	mouse.GetLKM();
	for (auto& b : buttons) {
		mShape.x = static_cast<int>(b->getComponent<TransformComponent>().position.x);
		mShape.y = static_cast<int>(b->getComponent<TransformComponent>().position.y);
		mShape.w = b->getComponent<TransformComponent>().width * b->getComponent<TransformComponent>().scale;
		mShape.h = b->getComponent<TransformComponent>().height * b->getComponent<TransformComponent>().scale;
		//std::cout << "meow" << std::endl;

		
		if (SDL_PointInRect(&point, &mShape)){

			if (mouse.GetLKM() && m_IsRelleased) {
				mouse.SetLKM();
				//buttonsBitSet[i] = true;
				std::cout << "meow" << std::endl;
				b->getComponent<SpriteComponent>().xIndex = 2;
				//b->getComponent<Buttons>().GetCallback();
				b->getComponent<Buttons>().m_callback();
				m_IsRelleased = false;
				
			}
			else {
				if (!mouse.GetLKM()) {
					m_IsRelleased = true;
					//b->getComponent<SpriteComponent>().sourceRect.x += 64;
					b->getComponent<SpriteComponent>().xIndex = 1;
				}

			}
		}
		else {
			b->getComponent<SpriteComponent>().xIndex = 0;
		}	
	}
}
void Buttons::PauseButtonsUpdate(std::vector<Entity*> buttons) {
	bool m_IsRelleased = true;
	Vector2D* mPos = mousePause.GetMousePosition();
	SDL_Rect mShape;
	SDL_Point point = { (int)mPos->x,(int)mPos->y };
	delete mPos;
	mousePause.GetLKM();
	for (auto& b : buttons) {
		mShape.x = static_cast<int>(b->getComponent<TransformComponent>().position.x);
		mShape.y = static_cast<int>(b->getComponent<TransformComponent>().position.y);
		mShape.w = b->getComponent<TransformComponent>().width * b->getComponent<TransformComponent>().scale;
		mShape.h = b->getComponent<TransformComponent>().height * b->getComponent<TransformComponent>().scale;
		//std::cout << "meow" << std::endl;


		if (SDL_PointInRect(&point, &mShape)) {

			if (mousePause.GetLKM() /*&& m_IsRelleased*/) {
				mousePause.SetLKM();
				//buttonsBitSet[i] = true;
				std::cout << "meow" << std::endl;
				b->getComponent<SpriteComponent>().xIndex = 2;
				//b->getComponent<Buttons>().GetCallback();
				b->getComponent<Buttons>().m_callback();
				m_IsRelleased = false;

			}
			else {
				if (!mousePause.GetLKM()) {
					m_IsRelleased = true;
					//b->getComponent<SpriteComponent>().sourceRect.x += 64;
					b->getComponent<SpriteComponent>().xIndex = 1;
				}

			}
		}
		else {
			b->getComponent<SpriteComponent>().xIndex = 0;
		}
	}
}
void Buttons::DeathButtonsUpdate(std::vector<Entity*> buttons) {
	bool m_IsRelleased = true;
	Vector2D* mPos = mouseDeath.GetMousePosition();
	SDL_Rect mShape;
	SDL_Point point = { (int)mPos->x,(int)mPos->y };
	delete mPos;
	mouseDeath.GetLKM();
	for (auto& b : buttons) {
		mShape.x = static_cast<int>(b->getComponent<TransformComponent>().position.x);
		mShape.y = static_cast<int>(b->getComponent<TransformComponent>().position.y);
		mShape.w = b->getComponent<TransformComponent>().width * b->getComponent<TransformComponent>().scale;
		mShape.h = b->getComponent<TransformComponent>().height * b->getComponent<TransformComponent>().scale;
		//std::cout << "meow" << std::endl;


		if (SDL_PointInRect(&point, &mShape)) {

			if (mouseDeath.GetLKM() /*&& m_IsRelleased*/) {
				mouseDeath.SetLKM();
				//buttonsBitSet[i] = true;
				std::cout << "meow" << std::endl;
				b->getComponent<SpriteComponent>().xIndex = 2;
				//b->getComponent<Buttons>().GetCallback();
				b->getComponent<Buttons>().m_callback();
				m_IsRelleased = false;

			}
			else {
				if (!mouseDeath.GetLKM()) {
					m_IsRelleased = true;
					//b->getComponent<SpriteComponent>().sourceRect.x += 64;
					b->getComponent<SpriteComponent>().xIndex = 1;
				}

			}
		}
		else {
			b->getComponent<SpriteComponent>().xIndex = 0;
		}
	}
}
void Buttons::RecordButtonsUpdate(std::vector<Entity*> buttons) {
	bool m_IsRelleased = true;
	Vector2D* mPos = mouseRecord.GetMousePosition();
	SDL_Rect mShape;
	SDL_Point point = { (int)mPos->x,(int)mPos->y };
	delete mPos;
	mouseRecord.GetLKM();
	for (auto& b : buttons) {
		mShape.x = static_cast<int>(b->getComponent<TransformComponent>().position.x);
		mShape.y = static_cast<int>(b->getComponent<TransformComponent>().position.y);
		mShape.w = b->getComponent<TransformComponent>().width * b->getComponent<TransformComponent>().scale;
		mShape.h = b->getComponent<TransformComponent>().height * b->getComponent<TransformComponent>().scale;
		//std::cout << "meow" << std::endl;


		if (SDL_PointInRect(&point, &mShape)) {

			if (mouseRecord.GetLKM() /*&& m_IsRelleased*/) {
				mouseRecord.SetLKM();
				//buttonsBitSet[i] = true;
				std::cout << "meow" << std::endl;
				b->getComponent<SpriteComponent>().xIndex = 2;
				//b->getComponent<Buttons>().GetCallback();
				b->getComponent<Buttons>().m_callback();
				m_IsRelleased = false;

			}
			else {
				if (!mouseRecord.GetLKM()) {
					m_IsRelleased = true;
					//b->getComponent<SpriteComponent>().sourceRect.x += 64;
					b->getComponent<SpriteComponent>().xIndex = 1;
				}

			}
		}
		else {
			b->getComponent<SpriteComponent>().xIndex = 0;
		}
	}
}

Buttons::Buttons(void (*mcallback)()) {
	m_callback = mcallback;
}
void Buttons::SpawnDeathButtons() {
	Entity& deathButtonResume(managerDeath.addEntity());
	Entity& deathButtonQuit(managerDeath.addEntity());
	deathButtonResume.addComponent<TransformComponent>(100.0f, 100.0f, 64, 64, 3);
	deathButtonResume.addComponent<SpriteComponent>("assets/garbageV2.png", 0, 0, 64, 64);

	deathButtonResume.addComponent<Buttons>().m_callback = deathToGame;
	deathButtonResume.addGroup(groupDeathButtons);


	deathButtonQuit.addComponent<TransformComponent>(100.0f, 330.0f, 64, 64, 3);
	deathButtonQuit.addComponent<SpriteComponent>("assets/garbageV2.png", 0, 0, 64, 64);
	deathButtonQuit.getComponent<SpriteComponent>().animIndex = 2;
	deathButtonQuit.addComponent<Buttons>().m_callback = deathToMenu;
	deathButtonQuit.addGroup(groupDeathButtons);
}
void Buttons::SpawnRecordsButtons() {
	Entity& recordButtonQuit(managerRecord.addEntity());
	Entity& recordButtonPrint(managerRecord.addEntity());
	Entity& recordButtonClear(managerRecord.addEntity());

	recordButtonPrint.addComponent<TransformComponent>(100.0f, 100.0f, 64, 64, 3);
	recordButtonPrint.addComponent<SpriteComponent>("assets/garbageV2.png", 0, 0, 64, 64);

	recordButtonPrint.addComponent<Buttons>().m_callback = recordsPrint;
	recordButtonPrint.addGroup(groupRecordsButtons);

	recordButtonClear.addComponent<TransformComponent>(100.0f, 250.0f, 64, 64, 3);
	recordButtonClear.addComponent<SpriteComponent>("assets/garbageV2.png", 0, 0, 64, 64);
	recordButtonClear.getComponent<SpriteComponent>().animIndex = 1;
	recordButtonClear.addComponent<Buttons>().m_callback = recordsClean;
	recordButtonClear.addGroup(groupRecordsButtons);


	recordButtonQuit.addComponent<TransformComponent>(100.0f, 400.0f, 64, 64, 3);
	recordButtonQuit.addComponent<SpriteComponent>("assets/garbageV2.png", 0, 0, 64, 64);
	recordButtonQuit.getComponent<SpriteComponent>().animIndex = 2;
	recordButtonQuit.addComponent<Buttons>().m_callback = recordsToMenu;
	recordButtonQuit.addGroup(groupRecordsButtons);
}
void Buttons::SpawnPauseButtons() {
	Entity& pauseButtonResume(managerPause.addEntity());
	Entity& pauseButtonQuit(managerPause.addEntity());
	pauseButtonResume.addComponent<TransformComponent>(100.0f, 100.0f, 64, 64, 3);
	pauseButtonResume.addComponent<SpriteComponent>("assets/garbageV2.png", 0, 0, 64, 64);

	pauseButtonResume.addComponent<Buttons>().m_callback = resumePause;
	pauseButtonResume.addGroup(groupPauseButtons);


	pauseButtonQuit.addComponent<TransformComponent>(100.0f, 330.0f, 64, 64, 3);
	pauseButtonQuit.addComponent<SpriteComponent>("assets/garbageV2.png", 0, 0, 64, 64);
	pauseButtonQuit.getComponent<SpriteComponent>().animIndex = 2;
	pauseButtonQuit.addComponent<Buttons>().m_callback = pauseToMenu;
	pauseButtonQuit.addGroup(groupPauseButtons);
}
void Buttons::SpawnButtons(void (*call)(), void (*callQuit)(), void (*nameWrite)(), void (*callRecords)() ) {
	Entity& startButton(managerMenu.addEntity());
	Entity& RecordsButton(managerMenu.addEntity());
	Entity& NameButton(managerMenu.addEntity());
	Entity& ExitButton(managerMenu.addEntity());


		startButton.addComponent<TransformComponent>(100.0f, 50.0f, 64, 64, 3);
		startButton.addComponent<SpriteComponent>("assets/garbageV2.png", 0, 0, 64, 64, 64, 64);
		startButton.addComponent<Buttons>().m_callback = call;
		startButton.getComponent<Buttons>().nameOfCallback = "start";
		startButton.addGroup(groupButtons);

		NameButton.addComponent<TransformComponent>(100.0f, 160.0f, 64, 64, 3);
		NameButton.addComponent<SpriteComponent>("assets/player.png", 0, 0, 64, 0, 0, 64);
		NameButton.getComponent<SpriteComponent>().AnimationsAdd("walk", 0, 8, 250);
		NameButton.addGroup(groupButtons);
		NameButton.addComponent<Buttons>().m_callback = nameWrite;
		NameButton.getComponent<Buttons>().nameOfCallback = "name";

		RecordsButton.addComponent<TransformComponent>(100.0f, 330.0f, 64, 64, 3);
		RecordsButton.addComponent<SpriteComponent>("assets/garbageV2.png", 0, 1, 64, 0, 0, 64);
		RecordsButton.addGroup(groupButtons);
		RecordsButton.addComponent<Buttons>().m_callback = callRecords;
		RecordsButton.getComponent<Buttons>().nameOfCallback = "records";

		ExitButton.addComponent<TransformComponent>(100.0f, 470.0f, 64, 64, 3);
		ExitButton.addComponent<SpriteComponent>("assets/garbageV2.png", 0, 2, 64, 0, 0, 64);
		ExitButton.addComponent<Buttons>().m_callback = callQuit;
		ExitButton.getComponent<Buttons>().nameOfCallback = "exit";
		ExitButton.addGroup(groupButtons);
}
