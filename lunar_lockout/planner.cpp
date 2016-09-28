// A state space planner for the lunar lockout world
#include <iostream>
#include <queue>
#include "state.h"


int main(int argc,char** argv)
{
	std::cout<<"Got the header";
	std::vector<lunar_lockout::spaceship> spaceships;
	lunar_lockout::board_state initial(spaceships);

	bool goal_reached=false;

	std::queue<lunar_lockout::board_state> states;
	states.push(initial);

	std::vector<lunar_lockout::board_state> states_stack;
	
	std::vector<lunar_lockout::spaceship_type> possible_ships;
	possible_ships.push_back(lunar_lockout::spaceship_type::red);
	std::vector<lunar_lockout::direction> possible_directions;
	while (!goal_reached)
	{
		lunar_lockout::board_state& current_state = states.front();

		for (auto ship:possible_ships)
		{

			for(auto move:possible_directions)

		}

	}
}