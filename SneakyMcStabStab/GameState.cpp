#include "GameState.h"
#include "Game.h"

void GameState::transition(GameState * from, GameState * to)
{
	from->exit();
	to->entry();
	mOwner->setCurrentState(to);
}
