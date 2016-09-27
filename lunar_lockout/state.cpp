#include <state.h>

//Implementation for the state class of the lunar lockout world

namespace lunar_lockout
{
board_state::board_state(std::vector<spaceship> &spaceships)
	{
		for (auto &ship: spaceships)
		{
			if (ship == spaceship_type::leader)
			{
				grid[ship.x_coord][ship.y_coord] = 2;
			}

			else
			{
				grid[ship.x_coord][ship.y_coord] = 1;	
			}
		}
	}

void board_state::manipulate_ship(spaceship %ship, direction &dir)
{	
	//Spaceship leaves its current spot to move to this new position
	grid[spaceship.x_coord][spaceship.y_coord]=0;

	if (dir == left || dir ==right)
	{
		while (spaceship.x_coord < grid_x && spaceship.x_coord >=0 &&
			grid[spaceship.x_coord][spaceship.y_coord]==0)
		{
			spaceship.x_coord+= dir;
		}
	//Since the above loop ends at a collision, move back one step
	spaceship.x_coord-=dir;
	}

	if (dir == up || dir ==down)
	{
		while (spaceship.y_coord < grid_y && spaceship.y_coord >=0 &&
			grid[spaceship.x_coord][spaceship.y_coord]==0)
		{
			spaceship.y_coord+= dir;
		}

	//Again, move back
	spaceship.y_coord-=dir;
	}

	//Update the new position of the spaceship in the grid
	grid[spaceship.x_coord][spaceship.y_coord]=spaceship.type;
}

bool board_state::check_goal_reached()
{
	if (grid[goal_x][goal_y] == spaceship_type::leader)
	{
		return true;
	}

	else 
	{
		return false;
	}
}

}// end namespace lunar lockout