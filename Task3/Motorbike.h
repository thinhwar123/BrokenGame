#pragma once
#include "DynamicObject.h"
class Motorbike : public DynamicObject {
public:
	Motorbike(int id, std::string name, Position position);
	void move() override;
};
