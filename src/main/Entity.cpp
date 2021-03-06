#include "Entity.h"
#include <iostream>
namespace ecs{
Entity::Entity(void)
{
	reset();
}
void Entity::reset()
{
	myCount = 0;
	myHoles = decltype(myHoles)();
	for(auto & m : mask)
		m = 0;
}
unsigned Entity::claim()
{
	unsigned next;
	if(myHoles.empty())
	{
		if(myCount == MAX_ENTITIES)
			next = MAX_ENTITIES - 1;
		else
			next = myCount++;
	}
	else
	{
		next = myHoles.top();
		myHoles.pop();
	}
	image[next] = nullptr;
	target[next] = 0;
	think_function[next] = [](unsigned self){std::cerr << "missing think function\n";};
	life[next].deathAction = [](unsigned self){std::cerr << "missing death function\n";};
	timer[next].action = [](unsigned self){std::cerr << "missing timer function\n";};
	return next;
}
void Entity::remove(unsigned i)
{
	mask[i] = 0;
	myHoles.push(i);
}
unsigned Entity::count(void) const
{
	return myCount;
}
unsigned Entity::capacity(void) const
{
	return MAX_ENTITIES;
}
}
