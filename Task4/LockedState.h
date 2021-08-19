#pragma once
#include "State.h"
class LockedState : public State
{
public:
	LockedState(FiniteStateMachine* finiteStateMachine);
	void enter() override;
	void exit() override;
	void unlock() override;
	void open() override;
	void close() override;
	void lock() override;
};

