#include <iostream>
#include <memory>
#include "UniquePtr.h"

struct Entity {
	Entity(int x) : x(x) {}
	int x;
};

int main() {

	UniquePtr<Entity> entity2(new Entity(10));
	std::cout << entity2->x << std::endl;

	UniquePtr<Entity> entity3(new Entity(15));
	entity3.Swap(entity2);
	std::cout << entity3->x << std::endl;
	std::cout << entity2->x << std::endl;

	return 0;
}