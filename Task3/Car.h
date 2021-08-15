#pragma once
#include "DynamicObject.h"
class Car : public DynamicObject {
public:
	Car(int id, std::string name, Position position);
	void move() override;
};