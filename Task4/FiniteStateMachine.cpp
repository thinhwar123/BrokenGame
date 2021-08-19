#include "FiniteStateMachine.h"
#include <iostream>
FiniteStateMachine::FiniteStateMachine()
{
	m_currentState = nullptr;
}

FiniteStateMachine::~FiniteStateMachine()
{
	delete(m_currentState);
}

void FiniteStateMachine::initialize(State* startState)
{
	m_currentState = startState;
	m_currentState->enter();
}

void FiniteStateMachine::changeState(State* newState)
{
	m_currentState->exit();
	delete(m_currentState);
	m_currentState = newState;
	m_currentState->enter();
}

void FiniteStateMachine::input()
{
	int n = -1;
	std::cout << "0. Exit" << std::endl;
	std::cout << "1. Unlock" << std::endl;
	std::cout << "2. Open" << std::endl;
	std::cout << "3. Close" << std::endl;
	std::cout << "4. Lock" << std::endl;
	while (n != 0)
	{
		std::cin >> n;
		switch (n)
		{
		case 1:
			m_currentState->unlock(); 
			break;
		case 2:
			m_currentState->open();
			break;
		case 3:
			m_currentState->close();
			break;
		case 4:
			m_currentState->lock();
			break;
		default:
			break;
		}
	}
}
