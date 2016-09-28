///// Initialization of the state representation of the lunar lockout game
///// Author: Shivam Gautam
///// 		  MRSD, CMU

#include "state.h"

//Implementation for the state class of the lunar lockout world

namespace lunar_lockout
{
board_state::board_state(std::vector<spaceship> spaceships)
	{	
		//Create a copy of the spaceships 
		spaceships_ = spaceships;

		//Construct the grid world
		for (auto &ship: spaceships_)
		{
			if (ship.type == spaceship_type::red)
			{
				grid_[ship.x_coord][ship.y_coord] = 2;
			}

			else
			{
				grid_[ship.x_coord][ship.y_coord] = 1;	
			}
		}
	}

board_state board_state::manipulate_ship(spaceship_type ship_type, direction &dir)
{	
	//Create a copy of the number of ship to be manipulated
	auto &ship = spaceships_[ship_type];

	//Store this move
	move = std::make_pair(ship_type,dir);

	//Spaceship leaves its current spot to move to this new position
	grid_[ship.x_coord][ship.y_coord]=0;

	if (dir == left || dir ==right)
	{
		//Move until you reach the end of the grid or hit some other obstacle
		while (ship.x_coord < grid_x && ship.x_coord >=0 &&
			grid_[ship.x_coord][ship.y_coord]==0)
		{
			ship.x_coord+= dir;
		}
	//Since the above loop ends at a collision, move back one step
	ship.x_coord-=dir;
	}

	if (dir == up || dir ==down)
	{
		while (ship.y_coord < grid_y && ship.y_coord >=0 &&
			grid_[ship.x_coord][ship.y_coord]==0)
		{
			ship.y_coord+= dir;
		}

	//Again, move back
	ship.y_coord-=dir;
	}

	//Update the new position of the spaceship in the grid
	grid_[ship.x_coord][ship.y_coord]=ship.type;
}

bool board_state::check_goal_reached()
{
	if (grid_[goal_x][goal_y] == spaceship_type::red)
	{
		return true;
	}

	else 
	{
		return false;
	}
}

}// end namespace lunar lockout