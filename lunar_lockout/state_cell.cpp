///// Initialization of the state representation of the lunar lockout game
///// Author: Shivam Gautam
///// 		  MRSD, CMU

#include "state_cell.h"
#include <iostream>

//Implementation for the state class of the lunar lockout world

namespace lunar_lockout_cell
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

	
	board_cell_state::board_cell_state(grid_type grid)
	{	
		//Create a copy of the grid
		grid_ = grid;

		//Construct the grid world
		for( size_t x=0;x<grid_x;++x)
		{
			for( size_t y=0;y<grid_y;++y)
			{
				if(grid_[x][y]!=0)
				{
					spaceships_.push_back(spaceship(static_cast<spaceship_type>(grid_[x][y]),x,y));
				}
			}
		}
	}

	void board_cell_state::manipulate_grid(const grid_coord coord, const direction dir)
	{	

	// Create a new vector of spaceships to intialize a new board state
	// std::vector<spaceship> new_spaceships(spaceships_);

	//Create a copy of the number of ship to be manipulated
		auto ship = std::find_if(spaceships_.begin(),spaceships_.end(),
			[&coord](const spaceship t_ship) 
			{	
				return (t_ship.x_coord == coord.x_coord && t_ship.y_coord == coord.y_coord);
			});


	//Store this move
	this->move_ = std::make_pair(ship->type,dir);

	//Steps moved by this manipulation
		unsigned int steps = 0;

	// std::cout<<"X: "<<ship->x_coord<<" Y: "<<ship->y_coord<<std::endl;

	//Spaceship leaves its current spot to move to this new position
		this->set_xy(ship->x_coord,ship->y_coord,0);
		unsigned int orig_x=ship->x_coord;
		unsigned int orig_y=ship->y_coord;
	// new_board_cell_state.set_parent(*this);

		if (dir == left || dir == right)
		{	
			int dirn = dir < 0 ? -1 : 1;

		//Move until you reach the end of the grid or hit some other obstacle
			while (ship->x_coord < grid_x && ship->x_coord >=0 &&	
				this->get_xy(ship->x_coord,ship->y_coord)==0)
			{	
				std::cout<<" Left Ship x: "<<ship->x_coord;
				ship->x_coord+= (dirn);
				++steps;
			}

		//if the ship did not find some other ship to collide against, this move is invalid
			if((ship->x_coord == grid_x || ship->x_coord ==-1)||steps==1)
			{	
				std::cout<<"Setting false ";
				std::cout<<ship->x_coord;
				this->set_valid(false);
				this->set_xy(orig_x,orig_y,ship->type);
			}

		//Move back one step because of the collision
			else
			{
				std::cout<<"\n Not setting to false";

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
				std::cout<<" Left Ship y: "<<ship->y_coord;
				ship->y_coord+= dirn;
				++steps;
			}

		//if the ship did not find some other ship to collide against, this move is invalid
			if((ship->y_coord == grid_y || ship->y_coord ==-1 )||steps==1)
			{	
				std::cout<<"Setting false";
				std::cout<<ship->y_coord;
				this->set_valid(false);
				this->set_xy(orig_x,orig_y,ship->type);
				ship->y_coord-= (steps*dirn);
			}
		//Move back one step because of the collision
			else
			{	
				std::cout<<"\n Not setting to false";
				ship->y_coord-=dirn;
				this->set_xy(ship->x_coord,ship->y_coord,ship->type);

			}
		}

	//Set the grid position in the new grid of the spaceship manipulated
		std::cout<<"Setting xy to "<<ship->type;


	// new_board_cell_state.print_grid();
		std::cout<<" This grid is "<<this->get_valid()<<std::endl;
		if(this->get_valid())
		{	
			std::cout<<"\n*******Valid Grid*********\n";
			this->print_grid();
		}

	// return new_board_cell_state;

	}

	bool board_cell_state::check_goal_reached()
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
// bool board_cell_state::check_valid_move(unsigned int x_coord, unsigned int y_coord, direction dir)

// {

// }

	bool board_cell_state::get_valid()
	{
		return valid_;
	}

	void board_cell_state::set_valid(bool value)
	{
		valid_=value;
	}

	void board_cell_state::set_xy(const unsigned int x, const unsigned int y, const unsigned int value)
	{	
		std::cout<<"Setting x: "<<x<<" y: "<<y<<" to "<<value;
		grid_[x][y] = value;
	}

	int board_cell_state::get_xy(const unsigned int x, const unsigned int y)
	{
		return grid_[x][y];
	}

	void board_cell_state::print_grid()
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
	void board_cell_state::set_parent(std::shared_ptr<board_cell_state>& parent_state)
	{
		parent_ = parent_state;
	}

	//Get the parent
	std::shared_ptr<board_cell_state> board_cell_state::get_parent()
	{
		return parent_;
	}

	//Return the current grid state
	grid_type board_cell_state::get_grid()
	{
		return grid_;
	}

	//Print the move stored at this cell state
	void board_cell_state::print_move()
	{
		std::cout<<"[Move] Ship Type:"<<move_.first<<" Direction: "<<get_direction_as_string(move_.second)<<std::endl;
	}


}// end namespace lunar lockout