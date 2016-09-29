///// Initialization of the state representation of the lunar lockout game
///// Author: Shivam Gautam
///// 		  MRSD, CMU

#include "state.h"

//Implementation for the state class of the lunar lockout world

namespace lunar_lockout
{
board_state::board_state(const std::vector<spaceship>& spaceships)
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

board_state board_state::manipulate_ship(const spaceship_type ship_type, const direction &dir)
{	

	// Create a new vector of spaceships to intialize a new board state
	std::vector<spaceship> new_spaceships(spaceships_);

	//Create a copy of the number of ship to be manipulated
	auto ship = std::find_if(new_spaceships.begin(),new_spaceships.end(),
							[&ship_type](const spaceship ship) 
							{
								return ship.type == ship_type;
							});

	//Create a new baord state with the existing pieces
	board_state new_board_state(new_spaceships);

	//Store this move
	move_ = std::make_pair(ship_type,dir);

	//Steps moved by this manipulation
	unsigned int steps = 0;

	//Spaceship leaves its current spot to move to this new position
	new_board_state.set_xy(ship->x_coord,ship->y_coord,0);

	if (dir == left || dir ==right)
	{
		//Move until you reach the end of the grid or hit some other obstacle
		while (ship->x_coord < grid_x-1 && ship->x_coord >0 &&	
			new_board_state.get_xy(ship->x_coord,ship->y_coord)==0)
		{
			ship->x_coord+= dir;
			++steps;
		}
		
		//if the ship did not find some other ship to collide against, this move is invalid
		if(ship->x_coord == grid_x-1 || ship->x_coord ==0 ||steps==1)
		{
			new_board_state.set_valid(false);
		}

		//Move back one step because of the collision
		ship->x_coord-=dir;
	}

	if (dir == up || dir ==down)
	{
		while (ship->y_coord < grid_y-1 && ship->y_coord >0 &&
			new_board_state.get_xy(ship->x_coord,ship->y_coord)==0)
		{
			ship->y_coord+= dir;
			++steps;
		}

		//if the ship did not find some other ship to collide against, this move is invalid
		if(ship->y_coord == grid_y-1 || ship->y_coord ==0 ||steps==1)
		{
			new_board_state.set_valid(false);
		}

		//Move back one step because of the collision
		ship->y_coord-=dir;
	}

	//Set the grid position in the new grid of the spaceship manipulated
	new_board_state.set_xy(ship->x_coord,ship->y_coord,ship->type);

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

//Check if the row/column contains another spaceship to hit
// bool board_state::check_valid_move(unsigned int x_coord, unsigned int y_coord, direction dir)

// {

// }

bool board_state::get_valid()
{
	return valid_;
}

void board_state::set_valid(bool value)
{
	valid_=value;
}

void board_state::set_xy(const unsigned int x, const unsigned int y, const int value)
{
	grid_[x][y] = value;
}

int board_state::get_xy(const unsigned int x, const unsigned int y)
{
	return grid_[x][y];
}

}// end namespace lunar lockout