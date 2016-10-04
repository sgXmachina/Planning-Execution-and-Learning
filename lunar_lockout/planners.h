///// Initialization of the planners of the lunar lockout game
///// Author: Shivam Gautam
///// 		  MRSD, CMU

#include <iostream>
#include <queue>
#include <stack>
#include <memory>
#include "state_ship.h"
#include "state_cell.h"

bool equal_ship_states(const std::shared_ptr<lunar_lockout_ship::board_ship_state>& state1, const std::shared_ptr<lunar_lockout_ship::board_ship_state>& state2)
{
	bool equal =true;

	for( size_t x=0;x<lunar_lockout_ship::grid_x;++x)
	{
		for( size_t y=0;y<lunar_lockout_ship::grid_y;++y)
		{
			if(state1->get_xy(x,y)!=state2->get_xy(x,y))
			{
				equal=false;
			}
		}
	}
	return equal;
};

bool equal_cell_states(const std::shared_ptr<lunar_lockout_cell::board_cell_state>& state1, const std::shared_ptr<lunar_lockout_cell::board_cell_state>& state2)
{
	bool equal =true;

	for( size_t x=0;x<lunar_lockout_cell::grid_x;++x)
	{
		for( size_t y=0;y<lunar_lockout_cell::grid_y;++y)
		{
			if(state1->get_xy(x,y)!=state2->get_xy(x,y))
			{
				equal=false;
			}
		}
	}
	return equal;
};

void copy_grid(const unsigned int original_grid[][lunar_lockout_cell::grid_y],lunar_lockout_cell::grid_type &target_grid)
{
	for( size_t x=0;x<lunar_lockout_cell::grid_x;++x)
	{
		for( size_t y=0;y<lunar_lockout_cell::grid_y;++y)
		{
			target_grid[x][y]=original_grid[y][x];
		}
	}
}

void init_spaceship_statespace(std::vector<lunar_lockout_ship::spaceship>& spaceships,
	std::vector<lunar_lockout_ship::spaceship_type>& possible_ships,
	std::vector<lunar_lockout_ship::direction>& possible_directions
	)
{


	lunar_lockout_ship::spaceship red_ship={lunar_lockout_ship::spaceship_type::red,2,0};
	lunar_lockout_ship::spaceship green_ship={lunar_lockout_ship::spaceship_type::green,0,1};
	lunar_lockout_ship::spaceship yellow_ship={lunar_lockout_ship::spaceship_type::yellow,4,1};
	lunar_lockout_ship::spaceship orange_ship={lunar_lockout_ship::spaceship_type::orange,0,3};
	lunar_lockout_ship::spaceship purple_ship={lunar_lockout_ship::spaceship_type::purple,4,3};
	lunar_lockout_ship::spaceship blue_ship={lunar_lockout_ship::spaceship_type::blue,2,4};

	spaceships.push_back(red_ship);
	spaceships.push_back(green_ship);
	spaceships.push_back(yellow_ship);
	spaceships.push_back(purple_ship);
	spaceships.push_back(orange_ship);
	spaceships.push_back(blue_ship);

	
	possible_ships.push_back(lunar_lockout_ship::spaceship_type::red);
	possible_ships.push_back(lunar_lockout_ship::spaceship_type::green);
	possible_ships.push_back(lunar_lockout_ship::spaceship_type::yellow);
	possible_ships.push_back(lunar_lockout_ship::spaceship_type::purple);
	possible_ships.push_back(lunar_lockout_ship::spaceship_type::orange);
	possible_ships.push_back(lunar_lockout_ship::spaceship_type::blue);



	
	
	possible_directions.push_back(lunar_lockout_ship::direction::up);
	possible_directions.push_back(lunar_lockout_ship::direction::down);
	possible_directions.push_back(lunar_lockout_ship::direction::left);
	possible_directions.push_back(lunar_lockout_ship::direction::right);
	
	// std::cout.setstate(std::ios_base::failbit);


}
void init_cell_statespace(lunar_lockout_cell::grid_type& grid,
	std::vector<lunar_lockout_cell::direction>& possible_directions
	)
{

	unsigned int grid_world[lunar_lockout_cell::grid_x][lunar_lockout_cell::grid_y] = 
	{
		{0,0,2,0,0},
		{6,0,0,0,3},
		{0,0,0,0,0},
		{5,0,0,0,4},
		{0,0,7,0,0}	
	};

	copy_grid(grid_world,grid);

	possible_directions.push_back(lunar_lockout_cell::direction::up);
	possible_directions.push_back(lunar_lockout_cell::direction::down);
	possible_directions.push_back(lunar_lockout_cell::direction::left);
	possible_directions.push_back(lunar_lockout_cell::direction::right);


}


void init_planning_spaceship_statespace()
{
	std::vector<lunar_lockout_ship::spaceship> spaceships;
	std::vector<lunar_lockout_ship::spaceship_type> possible_ships;
	std::vector<lunar_lockout_ship::direction> possible_directions;


	init_spaceship_statespace(spaceships,possible_ships, possible_directions);
	
	std::stack<std::shared_ptr<lunar_lockout_ship::board_ship_state>> states;
	std::vector<std::shared_ptr<lunar_lockout_ship::board_ship_state>> visited_states;
	std::shared_ptr<lunar_lockout_ship::board_ship_state> initial_state_ptr(new lunar_lockout_ship::board_ship_state(spaceships));
	states.push(initial_state_ptr);

	std::shared_ptr<lunar_lockout_ship::board_ship_state> final_state;
	bool goal_reached=false;

	std::cout<<"=======Initial Grid======== ";
	initial_state_ptr->print_grid();

	//Search the state space iteratively using a Breadth First Search till the goal is reached
	while (!goal_reached && !states.empty())
	{	
		//Get the next element in line and pop it from the list;

		std::cout<<"\n++++++++++++++++Changed my current pointer++++++++++++\n";
		std::shared_ptr<lunar_lockout_ship::board_ship_state> current_state_ptr = states.top();
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
						std::shared_ptr<lunar_lockout_ship::board_ship_state> new_state_ptr(new lunar_lockout_ship::board_ship_state(current_state_ptr->spaceships_));
						
						std::cout<<"\n========CHILD========\n";
					// new_state_ptr->print_grid();
						new_state_ptr->set_parent(current_state_ptr);
						new_state_ptr->manipulate_ship(ship,move);

						for (auto& state:visited_states)
						{
							if(equal_ship_states(state,new_state_ptr))
							{
								new_state_ptr->set_valid(false);
								std::cout<<"......REPEATED GRID......\nSize of Visited = "<<visited_states.size()<<std::endl;
								new_state_ptr->print_grid();

								break;
							}
						}

				// std::shared_ptr<lunar_lockout_ship::board_ship_state> new_state(std::make_shared<lunar_lockout_ship::board_ship_state>(current_state->manipulate_ship(ship,move)));

				//Check if this is the goal state
						if (new_state_ptr->check_goal_reached())
						{	
					// final_state = std::make_shared<lunar_lockout_ship::board_ship_state>(new_state);
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


//////////Planner Definition for the Cell World Representation///////////////

void init_planning_cell_statespace()
{	
	//Initialize the cell state space for search
	lunar_lockout_cell::grid_type initial_grid;

	std::vector<lunar_lockout_cell::direction> possible_directions;

	init_cell_statespace(initial_grid, possible_directions);
	
	//Initialize the stack for states that need to be visited next
	std::stack<std::shared_ptr<lunar_lockout_cell::board_cell_state>> states;
	std::vector<std::shared_ptr<lunar_lockout_cell::board_cell_state>> visited_states;

	std::shared_ptr<lunar_lockout_cell::board_cell_state> initial_state_ptr(new lunar_lockout_cell::board_cell_state(initial_grid));
	states.push(initial_state_ptr);

	std::shared_ptr<lunar_lockout_cell::board_cell_state> final_state;
	bool goal_reached=false;

	std::cout<<"=======Initial Grid======== ";
	initial_state_ptr->print_grid();

	//Search the state space iteratively using a Breadth First Search till the goal is reached
	while (!goal_reached && !states.empty())
	{	
		//Get the next element in line and pop it from the list;

		std::cout<<"\n++++++++++++++++Changed my current pointer++++++++++++\n";
		std::shared_ptr<lunar_lockout_cell::board_cell_state> current_state_ptr = states.top();
		visited_states.push_back(current_state_ptr);
		states.pop();
		std::cout<<"\n$$$$$$$$$States Remaining: "<<states.size();
		
		// current_state.print_grid();

		if (current_state_ptr->get_valid() && !final_state)
		{
			for( size_t x=0;x<lunar_lockout_cell::grid_x;++x)
			{
				for( size_t y=0;y<lunar_lockout_cell::grid_y;++y)
				{
					
					if(current_state_ptr->get_xy(x,y)!=0)
					{
						std::cout<<"\n=========PARENT======\n";
						current_state_ptr->print_grid();
						std::cout<<"========\n";
						if(!final_state)
						{
							for(const auto& move:possible_directions)
							{	
								std::cout<<"Coord:                 "<<x<<","<<y<<" "<<"Dir:                "<<move<<std::endl;
				//Create a new state after manipulating the grid
								std::shared_ptr<lunar_lockout_cell::board_cell_state> new_state_ptr(new lunar_lockout_cell::board_cell_state(current_state_ptr->get_grid()));

								std::cout<<"\n========CHILD========\n";
								new_state_ptr->set_parent(current_state_ptr);
								new_state_ptr->manipulate_grid(lunar_lockout_cell::grid_coord(x,y),move);

								for (auto& state:visited_states)
								{
									if(equal_cell_states(state,new_state_ptr))
									{
										new_state_ptr->set_valid(false);
										std::cout<<"......REPEATED GRID......\nSize of Visited = "<<visited_states.size()<<std::endl;
										new_state_ptr->print_grid();

										break;
									}
								}

				// std::shared_ptr<lunar_lockout_cell::board_cell_state> new_state(std::make_shared<lunar_lockout_cell::board_cell_state>(current_state->manipulate_ship(ship,move)));

				//Check if this is the goal state
								if (new_state_ptr->check_goal_reached())
								{	
					// final_state = std::make_shared<lunar_lockout_cell::board_cell_state>(new_state);
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