#include "Car.h"
#include "Motorbike.h"
#include "Tree.h"
#include "House.h"
#include "BaseObject.h"
#include <iostream>
#include <list>
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;
int main() {
	{
		list<shared_ptr<BaseObject>> objects;
		shared_ptr<BaseObject> object1 = make_shared<Car>(1, "Car", Position(0, 0));
		objects.push_back(object1);

		shared_ptr<BaseObject> object2 = make_shared<Motorbike>(2, "Motorbike", Position(0, 0));
		objects.push_back(object2);

		shared_ptr<BaseObject> object3 = make_shared<House>(3, "House", Position(0, 0));
		objects.push_back(object3);

		shared_ptr<BaseObject> object4 = make_shared<Tree>(1, "Tree", Position(0, 0));
		objects.push_back(object4);

		cout << "List Object: " << endl;
		for (auto obj : objects) {
			cout << "Object ID: " << obj->getid() << "; Object Name: " << obj->getName() << endl;
			obj->printPosition();
			cout << endl;
		}
		cout << "Move Object: " << endl;
		for (auto obj : objects) {
			obj->move();
			cout << endl;
		}
		cout << "List Object After Move: " << endl;
		for (auto obj : objects) {
			cout << "Object ID: " << obj->getid() << "; Object Name: " << obj->getName() << endl;
			obj->printPosition();
			cout << endl;
		}
	}

	_CrtDumpMemoryLeaks();
	return 0;
}