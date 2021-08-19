#pragma once
#include "FiniteStateMachine.h"
class FiniteStateMachine;
class State
{
public:
	FiniteStateMachine* m_FiniteStateMachine;
	State(FiniteStateMachine* finiteStateMachine);
	~State();
	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual void unlock() = 0;
	virtual void open() = 0;
	virtual void close() = 0;
	virtual void lock() = 0;
};

