#include "LockedState.h"
#include "ClosedState.h"
#include <iostream>

LockedState::LockedState(FiniteStateMachine* finiteStateMachine) : State(finiteStateMachine)
{
}

void LockedState::enter()
{
	std::cout << "Enter Locked State" << std::endl;
}

void LockedState::exit()
{
	std::cout << "Exit Locked State" << std::endl;
}

void LockedState::unlock()
{
	m_FiniteStateMachine->changeState(new ClosedState(m_FiniteStateMachine));
}

void LockedState::open()
{
	std::cout << "The Door Is Locked" << std::endl;
}

void LockedState::close()
{
	std::cout << "The Door Is Locked" << std::endl;
}

void LockedState::lock()
{
	std::cout << "The Door Is Locked" << std::endl;
}
