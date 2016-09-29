///// Initialization of the state representation of the lunar lockout game/////
///// Author: Shivam Gautam
///// 		  MRSD, CMU

#include <vector>
#include <array>
#include <memory>
#include <algorithm>

namespace lunar_lockout
{
namespace
{

//Coordinates for the goal state
const unsigned int goal_x =2;
const unsigned int goal_y =2;

//Grid size for the lunar lockout problem. Typically 5x5
const size_t grid_x = 5;
const size_t grid_y = 5;
}
enum direction
{	
	up = 1,
	down = -1,
	left = -1,
	right = 1,
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
	blue = 7
	
};

struct spaceship
{
	spaceship_type type = spaceship_type::invalid;
	unsigned int x_coord = 0;
	unsigned int y_coord = 0;
};



class board_state
{
public: 

	//Initialize the grid based on the tpyes of spaceships and their positions
	board_state(const std::vector<spaceship>& spaceships);

	//Manipulate the ship based on the current state of the board
	board_state manipulate_ship(const spaceship_type ship_type, const direction &dir);

	//Check if we have reached the goal state
	bool check_goal_reached();

	//Check if the row/column contains another spaceship to hit
	// bool check_valid_move(unsigned int x_coord, unsigned int y_coord, direction dir);

	//Get the valid flag
	bool get_valid();	

	//Set the valid flag of the state
	void set_valid(bool value);

	//Set X,Y of the grid
	void set_xy(const unsigned int x,const unsigned int y, const int value);

	//Get X,Y of the grid
	int get_xy(const unsigned int x,const unsigned int y);

private:

		//Initialize the grid to zero
		std::array<std::array<int, grid_y>, grid_x> grid_;// = {0};

		//The spaceships in the grid
		std::vector<spaceship> spaceships_;

		//Pointer to parent of this state
		std::shared_ptr<board_state> parent_;

		//Move chosen at this point
		std::pair<spaceship_type,direction> move_;

		//Flag which notes if this state is a valid
		bool valid_ = true;

};

} // end namespace lunar lockout