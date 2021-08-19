#pragma once
#include "State.h"
class ClosedState : public State
{
public:
	ClosedState(FiniteStateMachine* finiteStateMachine);
	void enter() override;
	void exit() override;
	void unlock() override;
	void open() override;
	void close() override;
	void lock() override;
};

