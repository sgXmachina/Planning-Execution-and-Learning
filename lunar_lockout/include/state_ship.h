///// Initialization of the state representation of the lunar lockout game/////
///// Author: Shivam Gautam
///// 		  MRSD, CMU
#ifndef STATE_SPACESHIP
#define STATE_SPACESHIP

#include <vector>
#include <array>
#include <memory>
#include <algorithm>
#include <iostream>

namespace lunar_lockout_ship
{
	namespace
	{

    //Coordinates for the goal state
		const unsigned int goal_x =2;
		const unsigned int goal_y =2;

    //Grid size for the lunar lockout problem. Typically 5x5
		const size_t grid_x = 5;
		const size_t grid_y = 5;
	
    }//namespace

// Possible directions the spaceship can be moved.
enum direction
{	
	down = 1,
	up = -2,
	left = -3,
	right = 4,
	none = 0

};

// All possible spaceship colors in the puzzle.
enum spaceship_type
{	
	invalid = -1,
	red =2,
	green =3,
	yellow =4,
	purple =5,
	orange =6,
	blue=7
};

// Compact spaceship state representation.
struct spaceship
{
spaceship_type type;// = spaceship_type::invalid;
unsigned int x_coord = 0;
unsigned int y_coord = 0;

    spaceship(spaceship_type s_type,unsigned int x_val, unsigned int y_val)
    {
    	type = s_type;
    	x_coord = x_val;
    	y_coord = y_val;
    }
};



class board_ship_state
{
public: 

	//Initialize the grid based on the tpyes of spaceships and their positions
	board_ship_state(const std::vector<spaceship> spaceships);

	//Manipulate the ship based on the current state of the board
	void manipulate_ship(const spaceship_type ship_type, const direction dir);

	//Check if we have reached the goal state
	bool check_goal_reached() const;

	//Get the valid flag
	bool get_valid() const;	

	//Set the valid flag of the state
	void set_valid(bool value);

	//Set X,Y of the grid
	void set_xy(const unsigned int x,const unsigned int y, const unsigned int value);

	//Get X,Y of the grid
	int get_xy(const unsigned int x,const unsigned int y) const;

	//Print the current state of the grid
	void print_grid() const;

	//Set the parent of the current state
	void set_parent(std::shared_ptr<board_ship_state>& parent_state);

	//Get the parent
	std::shared_ptr<board_ship_state> get_parent() const;

	//Print the next valid move at this step
	void print_move() const;

	//The spaceships in the grid
	std::vector<spaceship> spaceships_;

private:

	mutable unsigned int grid_[5][5] = {{0}};

		//Pointer to parent of this state
	std::shared_ptr<board_ship_state> parent_;

		//Move chosen at this point
	std::pair<spaceship_type,direction> move_;

		//Flag which notes if this state is a valid
	bool valid_ = true;

};

} // end namespace lunar lockout

#endif