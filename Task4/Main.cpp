#include "FiniteStateMachine.h"
#include "ClosedState.h"
#include "OpenedState.h"
#include "LockedState.h"
#include <iostream>

int main() {
	{
		FiniteStateMachine* finiteStateMachine = new FiniteStateMachine();
		finiteStateMachine->initialize(new ClosedState(finiteStateMachine));
		finiteStateMachine->input();

		delete(finiteStateMachine);
	}
	_CrtDumpMemoryLeaks();
	return 0;
}