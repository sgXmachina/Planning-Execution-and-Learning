// A state space planner for the lunar lockout world
#include <iostream>
#include <queue>
#include <memory>
#include "state.h"


int main(int argc,char** argv)
{
	std::cout<<"Got the header";
	std::vector<lunar_lockout::spaceship> spaceships;

	lunar_lockout::board_state initial_state(spaceships);
	std::shared_ptr<lunar_lockout::board_state> final_state;

	bool goal_reached=false;

	std::queue<lunar_lockout::board_state> states;
	states.push(initial_state);

	std::vector<lunar_lockout::board_state> states_stack;
	
	std::vector<lunar_lockout::spaceship_type> possible_ships;
	possible_ships.push_back(lunar_lockout::spaceship_type::red);
	std::vector<lunar_lockout::direction> possible_directions;

	//Search the state space iteratively using a Breadth First Search till the goal is reached
	while (!goal_reached && !states.empty())
	{	
		//Get the next element in line and pop it from the list;
		lunar_lockout::board_state& current_state = states.front();
		states.pop();

		for (auto ship:possible_ships)
		{

			for(auto move:possible_directions)
			{	
				//Create a new state after manipulating the grid
				lunar_lockout::board_state new_state = current_state.manipulate_ship(ship,move);

				//Check if this is the goal state
				if (new_state.check_goal_reached())
				{	
					final_state = std::make_shared<lunar_lockout::board_state>(new_state);
					break;
				}

				//Only add this state to the queue if it is valid
				if(new_state.get_valid())
				{
					states.push(new_state);
				}

			}

		}
	}

	if(final_state)
	{
		std::cout<<"Solution is found";
	}

	else
	{
		std::cout<<"Can't find the solution";
	}
}