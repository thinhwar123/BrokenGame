#include "OpenedState.h"
#include "ClosedState.h"
#include <iostream>

OpenedState::OpenedState(FiniteStateMachine* finiteStateMachine): State(finiteStateMachine)
{
}

void OpenedState::enter()
{
	std::cout << "Enter Opened State" << std::endl;
}

void OpenedState::exit()
{
	std::cout << "Exit Opened State" << std::endl;
}

void OpenedState::unlock()
{
	std::cout << "The Door Is Unlocked" << std::endl;
}

void OpenedState::open()
{
	std::cout << "The Door Is Opened" << std::endl;
}

void OpenedState::close()
{
	m_FiniteStateMachine->changeState(new ClosedState(m_FiniteStateMachine));
}

void OpenedState::lock()
{
	std::cout << "The Door Is Opened" << std::endl;
}
