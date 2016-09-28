///// Initialization of the state representation of the lunar lockout game/////
///// Author: Shivam Gautam
///// 		  MRSD, CMU

#include <vector>
#include <array>
#include <memory>

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
	red =0,
	green =1,
	yellow =2,
	purple =3,
	orange =4,
	blue = 5
	
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
	board_state(std::vector<spaceship> spaceships);

	//Manipulate the ship based on the current state of the board
	board_state manipulate_ship(spaceship_type ship_type, direction &dir);

	//Check if we have reached the goal state
	bool check_goal_reached();

private:

		//Initialize the grid to zero
		std::array<std::array<int, grid_y>, grid_x> grid_;// = {0};

		//The spaceships in the grid
		std::vector<spaceship> spaceships_;

		//Pointer to parent of this state
		std::shared_ptr<board_state> parent;

		//Move chosen at this point
		std::pair<spaceship_type,direction> move;

};

} // end namespace lunar lockout