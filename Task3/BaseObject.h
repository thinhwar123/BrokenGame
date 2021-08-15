#pragma once
#include <string>
#include "Position.h"
class BaseObject {
private:
	int m_ID;
	std::string m_Name;
protected:
	Position m_Position;
public:
	BaseObject();
	BaseObject(int id, std::string name, Position position);
	~BaseObject();
	virtual std::string getName();
	virtual int getid();
	virtual void move();
	virtual void printPosition();
};