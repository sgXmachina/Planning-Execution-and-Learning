///// Initialization of the state representation of the lunar lockout game
///// Author: Shivam Gautam
///// 		  MRSD, CMU

#include "state_ship.h"
#include <iostream>

//Implementation for the state class of the lunar lockout world

namespace lunar_lockout_ship
{	
	//Convert direction to string
	const char* get_direction_as_string(direction dir) {
		switch (dir) {
			case up: return "up";
			case down: return "down";
			case left: return "left";
			case right: return "right";
		}
	}

	board_ship_state::board_ship_state(const std::vector<spaceship> spaceships)
	{	
		//Create a copy of the spaceships 
		spaceships_ = spaceships;

		//Construct the grid world
		for (auto &ship: spaceships_)
		{
			grid_[ship.x_coord][ship.y_coord] = ship.type;
		}
	}

	void board_ship_state::manipulate_ship(const spaceship_type ship_type, const direction dir)
	{	

	//Store this move
	move_ = std::make_pair(ship_type,dir);
	
	//Create a copy of the number of ship to be manipulated
		auto ship = std::find_if(spaceships_.begin(),spaceships_.end(),
			[&ship_type](const spaceship t_ship) 
			{	
				return t_ship.type == ship_type;
			});



	//Steps moved by this manipulation
		unsigned int steps = 0;


	//Spaceship leaves its current spot to move to this new position
		this->set_xy(ship->x_coord,ship->y_coord,0);
		unsigned int orig_x=ship->x_coord;
		unsigned int orig_y=ship->y_coord;

		if (dir == left || dir == right)
		{	
			int dirn = dir < 0 ? -1 : 1;

		//Move until you reach the end of the grid or hit some other obstacle
			while (ship->x_coord < grid_x && ship->x_coord >=0 &&	
				this->get_xy(ship->x_coord,ship->y_coord)==0)
			{	
				ship->x_coord+= (dirn);
				++steps;
			}

		//if the ship did not find some other ship to collide against, this move is invalid
			if((ship->x_coord == grid_x || ship->x_coord ==-1)||steps==1)
			{	
				this->set_valid(false);
				this->set_xy(orig_x,orig_y,ship->type);
			}

		//Move back one step because of the collision
			else
			{
				ship->x_coord-=(dirn);
				this->set_xy(ship->x_coord,ship->y_coord,ship->type);

			}
		}

		else
		{	
			int dirn = dir < 0 ? -1 : 1;

			while (ship->y_coord < grid_y && ship->y_coord >=0 &&
				this->get_xy(ship->x_coord,ship->y_coord)==0)
			{	
				ship->y_coord+= dirn;
				++steps;
			}

		//if the ship did not find some other ship to collide against, this move is invalid
			if((ship->y_coord == grid_y || ship->y_coord ==-1 )||steps==1)
			{	
				this->set_valid(false);
				this->set_xy(orig_x,orig_y,ship->type);
				ship->y_coord-= (steps*dirn);
			}
		//Move back one step because of the collision
			else
			{	
				ship->y_coord-=dirn;
				this->set_xy(ship->x_coord,ship->y_coord,ship->type);

			}
		}

	}

	bool board_ship_state::check_goal_reached() const
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

	bool board_ship_state::get_valid() const
	{
		return valid_;
	}

	void board_ship_state::set_valid(bool value)
	{
		valid_=value;
	}

	void board_ship_state::set_xy(const unsigned int x, const unsigned int y, const unsigned int value)
	{	
		grid_[x][y] = value;
	}

	int board_ship_state::get_xy(const unsigned int x, const unsigned int y) const
	{
		return grid_[x][y];
	}

	void board_ship_state::print_grid() const
	{	
		for (unsigned int i=0;i<5;++i)
		{
			for (unsigned int j=0;j<5;++j)
			{
				std::cout<<grid_[j][i]<<" ";
			}
			std::cout<<std::endl;
		}
	}


//Set the parent of the current state
	void board_ship_state::set_parent(std::shared_ptr<board_ship_state>& parent_state)
	{
		parent_ = parent_state;
	}

	//Get the parent
	std::shared_ptr<board_ship_state> board_ship_state::get_parent() const
	{
		return parent_;
	}

	//Print the move stored at this ship state
	void board_ship_state::print_move() const
	{
		std::cout<<"[Move] Ship Type:"<<move_.first<<" Direction: "<<get_direction_as_string(move_.second)<<std::endl;
	}
}// end namespace lunar lockout