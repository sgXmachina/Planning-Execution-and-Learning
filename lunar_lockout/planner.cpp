// A state space planner for the lunar lockout world
#include <iostream>
#include <queue>
#include <stack>
#include <memory>
#include "state.h"

bool equal(const std::shared_ptr<lunar_lockout::board_state>& state1, const std::shared_ptr<lunar_lockout::board_state>& state2)
{
	bool equal =true;

	for( size_t x=0;x<lunar_lockout::grid_x;++x)
	{
		for( size_t y=0;y<lunar_lockout::grid_y;++y)
		{
			if(state1->get_xy(x,y)!=state2->get_xy(x,y))
			{
				equal=false;
			}
		}
	}
	return equal;

}

int main(int argc,char** argv)
{
	std::cout<<"Starting the game....\n";
	std::vector<lunar_lockout::spaceship> spaceships;

	lunar_lockout::spaceship red_ship={lunar_lockout::spaceship_type::red,2,0};
	lunar_lockout::spaceship green_ship={lunar_lockout::spaceship_type::green,2,2};
	lunar_lockout::spaceship yellow_ship={lunar_lockout::spaceship_type::yellow,3,4};
	lunar_lockout::spaceship orange_ship={lunar_lockout::spaceship_type::orange,4,0};
	lunar_lockout::spaceship purple_ship={lunar_lockout::spaceship_type::purple,1,3};

	spaceships.push_back(red_ship);
	spaceships.push_back(green_ship);
	spaceships.push_back(yellow_ship);
	spaceships.push_back(purple_ship);
	spaceships.push_back(orange_ship);

	
	std::vector<lunar_lockout::spaceship_type> possible_ships;
	possible_ships.push_back(lunar_lockout::spaceship_type::red);
	possible_ships.push_back(lunar_lockout::spaceship_type::green);
	possible_ships.push_back(lunar_lockout::spaceship_type::yellow);
	possible_ships.push_back(lunar_lockout::spaceship_type::purple);
	possible_ships.push_back(lunar_lockout::spaceship_type::orange);

	std::shared_ptr<lunar_lockout::board_state> final_state;

	bool goal_reached=false;

	std::stack<std::shared_ptr<lunar_lockout::board_state>> states;
	std::vector<std::shared_ptr<lunar_lockout::board_state>> visited_states;

	std::shared_ptr<lunar_lockout::board_state> initial_state_ptr(new lunar_lockout::board_state(spaceships));
	states.push(initial_state_ptr);

	// std::vector<lunar_lockout::board_state> states_stack;space
	
	std::vector<lunar_lockout::direction> possible_directions;
	possible_directions.push_back(lunar_lockout::direction::up);
	possible_directions.push_back(lunar_lockout::direction::down);
	possible_directions.push_back(lunar_lockout::direction::left);
	possible_directions.push_back(lunar_lockout::direction::right);
	
	// std::cout.setstate(std::ios_base::failbit);

	std::cout<<"=======Initial Grid======== ";
	initial_state_ptr->print_grid();

	//Search the state space iteratively using a Breadth First Search till the goal is reached
	while (!goal_reached && !states.empty())
	{	
		//Get the next element in line and pop it from the list;

		std::cout<<"\n++++++++++++++++Changed my current pointer++++++++++++\n";
		std::shared_ptr<lunar_lockout::board_state> current_state_ptr = states.top();
		visited_states.push_back(current_state_ptr);
		states.pop();
		std::cout<<"\n$$$$$$$$$States Remaining: "<<states.size();
		
		// current_state.print_grid();

		if (current_state_ptr->get_valid() && !final_state)
		{
			for (const auto& ship:possible_ships)
			{
				std::cout<<"\n=========PARENT======\n";
				current_state_ptr->print_grid();
				std::cout<<"========\n";
				if(!final_state)
				{
					for(const auto& move:possible_directions)
					{	
						std::cout<<"Ship:                 "<<ship<<" "<<"Dir:                "<<move<<std::endl;
				//Create a new state after manipulating the grid
						std::shared_ptr<lunar_lockout::board_state> new_state_ptr(new lunar_lockout::board_state(current_state_ptr->spaceships_));
						
					



						std::cout<<"\n========CHILD========\n";
					// new_state_ptr->print_grid();
						new_state_ptr->set_parent(current_state_ptr);
						new_state_ptr->manipulate_ship(ship,move);

						for (auto& state:visited_states)
						{
							if(equal(state,new_state_ptr))
							{
								new_state_ptr->set_valid(false);
								std::cout<<"......REPEATED GRID......\nSize of Visited = "<<visited_states.size()<<std::endl;
								new_state_ptr->print_grid();

								break;
							}
						}

				// std::shared_ptr<lunar_lockout::board_state> new_state(std::make_shared<lunar_lockout::board_state>(current_state->manipulate_ship(ship,move)));

				//Check if this is the goal state
						if (new_state_ptr->check_goal_reached())
						{	
					// final_state = std::make_shared<lunar_lockout::board_state>(new_state);
							final_state =new_state_ptr;
							break;
						}

				//Only add this state to the queue if it is valid
						if(new_state_ptr->get_valid())
						{
							states.push(new_state_ptr);

						}

					}
				}

			}
		}
		

		
	}

	std::cout<<"\n\nGot here\n";
	if(final_state)
	{
		std::cout<<"Solution is found";
	}

	else
	{
		std::cout<<"Can't find the solution";
	}
}