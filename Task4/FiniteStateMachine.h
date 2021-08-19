#pragma once
#include "State.h"
class State;
class FiniteStateMachine
{
private:
	State* m_currentState;
public:
	FiniteStateMachine();
	~FiniteStateMachine();

	void initialize(State* startState);
	void changeState(State* newState);
	void input();

};

