#include "ClosedState.h"
#include "OpenedState.h"
#include "LockedState.h"
#include <iostream>


ClosedState::ClosedState(FiniteStateMachine* finiteStateMachine): State(finiteStateMachine)
{
}

void ClosedState::enter()
{
	std::cout << "Enter Close State" << std::endl;
}

void ClosedState::exit()
{
	std::cout << "Exit Close State" << std::endl;
}

void ClosedState::unlock()
{
	std::cout << "The Door Is Unlocked" << std::endl;
}

void ClosedState::open()
{
	m_FiniteStateMachine->changeState(new OpenedState(m_FiniteStateMachine));
}

void ClosedState::close()
{
	std::cout << "The Door Is Closed" << std::endl;
}

void ClosedState::lock()
{
	m_FiniteStateMachine->changeState(new LockedState(m_FiniteStateMachine));
}
