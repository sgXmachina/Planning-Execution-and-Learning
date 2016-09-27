///// Class that implements the state representation of the lunar lockout game/////
///// author: Shivam Gautam
///// MRSD, CMU

#include <vector>


namespace lunar_lockout
{
enum directions
{	
	up = 1,
	down = -1,
	left = -1,
	right = 1

};

enum spaceship_type
{
	leader = 0,
	allies = 1,
	invalid = -1
}

struct spaceship()
{
	spaceship_type type = spaceship_type::invalid;
	unsigned int x_coord = 0;
	unsigned int y_coord = 0;
};

//Coordinates for the goal state
unsigned int goal_x =2;
unsigned int goal_y =2;

//Grid size for the lunar lockout problem. Typically 5x5
size_t grid_x = 5;
size_t grid_y = 5;


class board_state()
{
public: 

	//Initialize the grid based on the tpyes of spaceships and their positions
	board_state(std::vector<spaceship> &spaceships);

	//Manipulate the ship based on the current state of the board
	void manipulate_ship(spaceship &ship, direction &dir);

	//Check if we have reached the goal state
	bool check_goal_reached();

private:

		//Initialize the grid to zero
		std::array<std::array<int, grid_y>, grid_x> grid = {0};


};

} // end namespace lunar lockout