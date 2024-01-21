#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "KeyboardController.h"
#include "ColliderComponent.h"
#include "TileComponent.h"
#include "HookKeyboardController.h"
#include "MouseController.h"

#include "ButtonsUpdate.h"
#include "TextOutput.h"





enum groupLabels : std::size_t {
    groupMap,
    groupEnemies,
    groupColliders,
    groupPlayers,
    groupFishes,
    groupHooks,
    groupGarbage,
    groupButtons,
    groupPauseButtons,
    groupDeathButtons,
    groupMenuText,
    groupPauseText,
    groupDeathText,
    groupGameText,
    groupRecordsButtons
};

enum buttonsLabels : std::size_t {
    startB, nameB, recordsB, exitB
};


enum ButtonState { NORMAL = 0, HOVER = 1, PRESSED = 2 };


