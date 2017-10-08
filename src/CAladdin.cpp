#include "CAladdin.h"

CAladdin::CAladdin()
{
	//_ActionCurrent = nullptr;

	_Action[STATE::STAND] = new CAladdinStand();
	_Action[STATE::WALK] = new CAladdinWalk();

	// set sate first Aladdin is stand
	//_ActionCurrent = _Action[STATE::STAND];
}

CAladdin::~CAladdin()
{
	//delete _ActionCurrent;
	//delete[] _Action;
}

void CAladdin::Init()
{
	_Action[STATE::STAND]->Init();
	_Action[STATE::WALK]->Init();
}

void CAladdin::Release()
{
	_Action[STATE::STAND]->Release();
	_Action[STATE::WALK]->Release();
}

//void CAladdin::SetActionCurrent(CAladdinAction* Action)
//{
//	_ActionCurrent = Action;
//}

void CAladdin::Activities(STATE state, DIRECTION direction)
{
	// process action is set
	_Action[state]->Activities(state, direction);
}
