///// Initialization of the planners of the lunar lockout game
///// Author: Shivam Gautam
///// 		  MRSD, CMU

#include "planner_utils.h"

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
	std::vector<lunar_lockout_ship::direction>& possible_directions,
	int puzzle_number
	)
{

	lunar_lockout_ship::spaceship red_ship={lunar_lockout_ship::spaceship_type::red,0,0};
	lunar_lockout_ship::spaceship green_ship={lunar_lockout_ship::spaceship_type::green,0,0};
	lunar_lockout_ship::spaceship yellow_ship={lunar_lockout_ship::spaceship_type::yellow,0,0};
	lunar_lockout_ship::spaceship orange_ship={lunar_lockout_ship::spaceship_type::orange,0,0};
	lunar_lockout_ship::spaceship purple_ship={lunar_lockout_ship::spaceship_type::purple,0,0};
	lunar_lockout_ship::spaceship blue_ship={lunar_lockout_ship::spaceship_type::blue,0,0};

	possible_ships.push_back(lunar_lockout_ship::spaceship_type::red);
	possible_ships.push_back(lunar_lockout_ship::spaceship_type::green);
	possible_ships.push_back(lunar_lockout_ship::spaceship_type::purple);
	possible_ships.push_back(lunar_lockout_ship::spaceship_type::orange);

	switch(puzzle_number)
	{
		case 1:
		red_ship={lunar_lockout_ship::spaceship_type::red,2,0};
		green_ship={lunar_lockout_ship::spaceship_type::green,2,2};
		yellow_ship={lunar_lockout_ship::spaceship_type::yellow,3,4};
		orange_ship={lunar_lockout_ship::spaceship_type::orange,4,0};
		purple_ship={lunar_lockout_ship::spaceship_type::purple,1,3};

		spaceships.push_back(red_ship);
		spaceships.push_back(green_ship);
		spaceships.push_back(yellow_ship);
		spaceships.push_back(purple_ship);
		spaceships.push_back(orange_ship);
		possible_ships.push_back(lunar_lockout_ship::spaceship_type::yellow);

		break;
		case 2:
		red_ship={lunar_lockout_ship::spaceship_type::red,2,0};
		green_ship={lunar_lockout_ship::spaceship_type::green,2,4};
		orange_ship={lunar_lockout_ship::spaceship_type::orange,0,4};
		purple_ship={lunar_lockout_ship::spaceship_type::purple,4,4};
		spaceships.push_back(red_ship);
		spaceships.push_back(green_ship);
		spaceships.push_back(purple_ship);
		spaceships.push_back(orange_ship);
		break;
		case 3:
		red_ship={lunar_lockout_ship::spaceship_type::red,4,4};
		green_ship={lunar_lockout_ship::spaceship_type::green,4,0};
		yellow_ship={lunar_lockout_ship::spaceship_type::yellow,3,2};
		orange_ship={lunar_lockout_ship::spaceship_type::orange,1,0};
		purple_ship={lunar_lockout_ship::spaceship_type::purple,0,2};
		blue_ship={lunar_lockout_ship::spaceship_type::blue,0,4};
		spaceships.push_back(red_ship);
		spaceships.push_back(green_ship);
		spaceships.push_back(yellow_ship);
		spaceships.push_back(purple_ship);
		spaceships.push_back(orange_ship);
		spaceships.push_back(blue_ship);
		possible_ships.push_back(lunar_lockout_ship::spaceship_type::blue);
		possible_ships.push_back(lunar_lockout_ship::spaceship_type::yellow);
			break;
		case 4:
		red_ship={lunar_lockout_ship::spaceship_type::red,2,0};
		green_ship={lunar_lockout_ship::spaceship_type::green,4,1};
		yellow_ship={lunar_lockout_ship::spaceship_type::yellow,4,3};
		orange_ship={lunar_lockout_ship::spaceship_type::orange,0,1};
		purple_ship={lunar_lockout_ship::spaceship_type::purple,0,3};
		blue_ship={lunar_lockout_ship::spaceship_type::blue,2,4};
		spaceships.push_back(red_ship);
		spaceships.push_back(green_ship);
		spaceships.push_back(yellow_ship);
		spaceships.push_back(purple_ship);
		spaceships.push_back(orange_ship);
		spaceships.push_back(blue_ship);
		possible_ships.push_back(lunar_lockout_ship::spaceship_type::blue);
		possible_ships.push_back(lunar_lockout_ship::spaceship_type::yellow);
		break;

		default: std::cout<<"\nERROR! Invalid Puzzle!\n";
	}




	
	
	possible_directions.push_back(lunar_lockout_ship::direction::up);
	possible_directions.push_back(lunar_lockout_ship::direction::down);
	possible_directions.push_back(lunar_lockout_ship::direction::left);
	possible_directions.push_back(lunar_lockout_ship::direction::right);
	


}
void init_cell_statespace(lunar_lockout_cell::grid_type& grid,
	std::vector<lunar_lockout_cell::direction>& possible_directions,
	int puzzle_number
	)
{


	switch(puzzle_number)
	{
		case 1:
		{
			unsigned int grid_world[lunar_lockout_cell::grid_x][lunar_lockout_cell::grid_y] = 
			{
				{0,0,2,0,6},
				{0,0,0,0,0},
				{0,0,3,0,0},
				{0,5,0,0,0},
				{0,0,0,4,0}	
			};
			copy_grid(grid_world,grid);
		}

		break;
		case 2:
		{
			unsigned int grid_world[lunar_lockout_cell::grid_x][lunar_lockout_cell::grid_y] = 
			{
				{0,0,2,0,0},
				{0,0,0,0,0},
				{0,0,0,0,0},
				{0,0,0,0,0},
				{6,0,3,0,5}	
			};
			copy_grid(grid_world,grid);
		}
		break;
		case 3:
		{
			unsigned int grid_world[lunar_lockout_cell::grid_x][lunar_lockout_cell::grid_y] = 
			{
				{0,6,0,0,3},
				{0,0,0,0,0},
				{5,0,0,4,0},
				{0,0,0,0,0},
				{7,0,0,0,2}	
			};
			copy_grid(grid_world,grid);
		}
		break;
		case 4:
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
		}
		break;
	}

	possible_directions.push_back(lunar_lockout_cell::direction::up);
	possible_directions.push_back(lunar_lockout_cell::direction::down);
	possible_directions.push_back(lunar_lockout_cell::direction::left);
	possible_directions.push_back(lunar_lockout_cell::direction::right);


}

//////////Planner Definition for the Spaceship Representation///////////////

void init_planning_spaceship_statespace(int puzzle_number)
{

	int states_expanded = 0;
	std::vector<lunar_lockout_ship::spaceship> spaceships;
	std::vector<lunar_lockout_ship::spaceship_type> possible_ships;
	std::vector<lunar_lockout_ship::direction> possible_directions;

	init_spaceship_statespace(spaceships,possible_ships, possible_directions,puzzle_number);
	
	std::stack<std::shared_ptr<lunar_lockout_ship::board_ship_state>> states;
	std::vector<std::shared_ptr<lunar_lockout_ship::board_ship_state>> visited_states;
	std::shared_ptr<lunar_lockout_ship::board_ship_state> initial_state_ptr(new lunar_lockout_ship::board_ship_state(spaceships));
	states.push(initial_state_ptr);

	std::shared_ptr<lunar_lockout_ship::board_ship_state> final_state;
	bool goal_reached=false;

	//Print the initial State
	std::cout<<"Initial State of the grid is: \n";
	initial_state_ptr->print_grid();
	//Search the state space iteratively using a Breadth First Search till the goal is reached
	while (!goal_reached && !states.empty())
	{	
		//Get the next element in line and pop it from the list;
		std::shared_ptr<lunar_lockout_ship::board_ship_state> current_state_ptr = states.top();
		visited_states.push_back(current_state_ptr);
		states.pop();

		if (current_state_ptr->get_valid() && !final_state)
		{
			//increase the number of states expanded
			++states_expanded;			
			for (const auto& ship:possible_ships)
			{
				if(!final_state)
				{
					for(const auto& move:possible_directions)
					{	
				//Create a new state after manipulating the grid
						std::shared_ptr<lunar_lockout_ship::board_ship_state> new_state_ptr(new lunar_lockout_ship::board_ship_state(current_state_ptr->spaceships_));
						
						new_state_ptr->set_parent(current_state_ptr);
						new_state_ptr->manipulate_ship(ship,move);

						for (auto& state:visited_states)
						{
							if(equal_ship_states(state,new_state_ptr))
							{
								new_state_ptr->set_valid(false);

								break;
							}
						}

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

	if(final_state)
	{
		std::cout<<"Solution is found\n";
		print_solution<lunar_lockout_ship::board_ship_state>(final_state);
		std::cout<<"\n--States Expanded = "<<states_expanded<<std::endl;
	}

	else
	{
		std::cout<<"Can't find the solution.";
	}

}


//////////Planner Definition for the Cell World Representation///////////////

void init_planning_cell_statespace(int puzzle_number)
{	
	//States Expanded
	int states_expanded=0;

	//Initialize the cell state space for search
	lunar_lockout_cell::grid_type initial_grid;

	std::vector<lunar_lockout_cell::direction> possible_directions;

	init_cell_statespace(initial_grid, possible_directions,puzzle_number);
	
	//Initialize the stack for states that need to be visited next
	std::stack<std::shared_ptr<lunar_lockout_cell::board_cell_state>> states;
	std::vector<std::shared_ptr<lunar_lockout_cell::board_cell_state>> visited_states;

	std::shared_ptr<lunar_lockout_cell::board_cell_state> initial_state_ptr(new lunar_lockout_cell::board_cell_state(initial_grid));
	states.push(initial_state_ptr);

	std::shared_ptr<lunar_lockout_cell::board_cell_state> final_state;
	bool goal_reached=false;

	//Print the initial State
	std::cout<<"Initial State of the grid is: \n";
	initial_state_ptr->print_grid();

	//Search the state space iteratively using a Breadth First Search till the goal is reached
	while (!goal_reached && !states.empty())
	{	
		//Get the next element in line and pop it from the list;

		std::shared_ptr<lunar_lockout_cell::board_cell_state> current_state_ptr = states.top();
		visited_states.push_back(current_state_ptr);
		states.pop();


		if (current_state_ptr->get_valid() && !final_state)
		{
			//increase the number of states expanded
			++states_expanded;

			for( size_t x=0;x<lunar_lockout_cell::grid_x;++x)
			{
				for( size_t y=0;y<lunar_lockout_cell::grid_y;++y)
				{
					
					if(current_state_ptr->get_xy(x,y)!=0)
					{
						if(!final_state)
						{
							for(const auto& move:possible_directions)
							{	
								//Create a new state after manipulating the grid
								std::shared_ptr<lunar_lockout_cell::board_cell_state> new_state_ptr(new lunar_lockout_cell::board_cell_state(current_state_ptr->get_grid()));

								new_state_ptr->set_parent(current_state_ptr);
								new_state_ptr->manipulate_grid(lunar_lockout_cell::grid_coord(x,y),move);

								for (auto& state:visited_states)
								{
									if(equal_cell_states(state,new_state_ptr))
									{
										new_state_ptr->set_valid(false);
										break;
									}
								}
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

	if(final_state)
	{
		std::cout<<"\nSolution is found\n";
		print_solution<lunar_lockout_cell::board_cell_state>(final_state);
		std::cout<<"\n--States Expanded = "<<states_expanded<<std::endl;
	}

	else
	{
		std::cout<<"Can't find the solution";
	}

}