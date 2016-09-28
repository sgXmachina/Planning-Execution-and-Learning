// A state space planner for the lunar lockout world
#include <iostream>
#include "state.h"

int main(int argc,char** argv)
{
	std::cout<<"Got the header";
	std::vector<lunar_lockout::spaceship> spaceships;
	lunar_lockout::board_state initial(spaceships);
}