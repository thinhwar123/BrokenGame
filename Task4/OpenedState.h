#pragma once
#include "State.h"
class OpenedState : public State
{
public:
	OpenedState(FiniteStateMachine* finiteStateMachine);
	void enter() override;
	void exit() override;
	void unlock() override;
	void open() override;
	void close() override;
	void lock() override;
};

