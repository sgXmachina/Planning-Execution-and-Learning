///// Initialization of the state representation of the lunar lockout game/////
///// Author: Shivam Gautam
///// 		  MRSD, CMU
#ifndef STATE_CELL
#define STATE_CELL

#include <vector>
#include <array>
#include <memory>
#include <algorithm>
#include <iostream>

namespace lunar_lockout_cell
{
	namespace
	{

//Coordinates for the goal state
		const unsigned int goal_x =2;
		const unsigned int goal_y =2;

//Grid size for the lunar lockout problem. Typically 5x5
		const size_t grid_x = 5;
		const size_t grid_y = 5;

		typedef std::array<std::array<unsigned int,5>,5> grid_type;
	}
	enum direction
	{	
	down = 1, //Translate up the grid
	up = -2,
	left = -3,
	right = 4,
	none = 0

};



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

struct grid_coord
{
	unsigned int x_coord = 0;
	unsigned int y_coord = 0;

	grid_coord(unsigned int x_val, unsigned int y_val)
	{
		x_coord=x_val;
		y_coord=y_val;
	}
};

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



class board_cell_state
{
public: 

	//Initialize the grid based on the tpyes of spaceships and their positions
	board_cell_state(grid_type grid);

	//Manipulate the grid coordinate based on the current state of the board, based on the set of actions
	void manipulate_grid(const grid_coord coord, const direction dir);

	//Check if we have reached the goal state
	bool check_goal_reached();

	//Check if the row/column contains another spaceship to hit
	// bool check_valid_move(unsigned int x_coord, unsigned int y_coord, direction dir);

	//Get the valid flag
	bool get_valid();	

	//Set the valid flag of the state
	void set_valid(bool value);

	//Set X,Y of the grid
	void set_xy(const unsigned int x,const unsigned int y, const unsigned int value);

	//Get X,Y of the grid
	int get_xy(const unsigned int x,const unsigned int y);

	//Print the current state of the grid
	void print_grid();

	//Set the parent of the current state
	void set_parent(std::shared_ptr<board_cell_state>& parent_state);

	//Get the parent
	std::shared_ptr<board_cell_state> get_parent();

	//The spaceships in the grid
	std::vector<spaceship> spaceships_;

	//Return the current grid state
	grid_type get_grid();

	//Print the next valid move at this step
	void print_move();


private:

		//Initialize the grid to zero
		// std::array<std::array<int, grid_y>, grid_x> grid_={{{0,0,0,0,0}}};
		// unsigned int grid_[grid_x][grid_y] = {{0}};
	grid_type  grid_;


		//Pointer to parent of this state
	std::shared_ptr<board_cell_state> parent_;

		//Move chosen at this point
	std::pair<spaceship_type,direction> move_;

		//Flag which notes if this state is a valid
	bool valid_ = true;

};

} // end namespace lunar lockout

#endif