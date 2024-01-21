#pragma once
#include <vector>
#include "ECS.h"
//#include "SDL.h"
//#include "MouseController.h"
#include "Components.h"
//#include "Menu.h"
#include "Game.h"

extern Manager managerMenu;
extern Manager manager;
extern Manager managerPause;
extern Manager managerDeath;
extern Manager managerRecord;


class Buttons : public Component {
private:
	void (*m_callback)();
	bool m_IsRelleased = true;
	const char* nameOfCallback;
public:
	
	const char* buttonFunc;
	Buttons() = default;
	inline void* GetCallback() { 
		std::cout << nameOfCallback << std::endl;
		return m_callback; }
	void ButtonsUpdate(std::vector<Entity*> buttons);
	Buttons(void (*m_callback)());
	void PauseButtonsUpdate(std::vector<Entity*> buttons);
	void DeathButtonsUpdate(std::vector<Entity*> buttons);
	void SpawnButtons(void (*call)(), void (*callQuit)(), void (*nameWrite)(), void (*callRecords)());
	void SpawnPauseButtons();
	void SpawnDeathButtons();
	void SpawnRecordsButtons();
	void RecordButtonsUpdate(std::vector<Entity*> buttons);
};

