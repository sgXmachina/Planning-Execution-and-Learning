#include "mdp-simulation.h"
#include <iostream>
using namespace std;

int main (void)
{

	
	for (size_t i =0;i<MAX_GRID;++i)
	{
		for (size_t j =0;j<MAX_GRID;++j)
		{

			State nextState = my_next_state(State(i, j), N);
			cout << "\nFrom "<<i<<","<<j<<" to "<< nextState.x << ", " << nextState.y;
			Reward reward = my_reward(nextState);
			cout << "Receiving reward " << reward << endl;

		}
	}
	return 0;
}
