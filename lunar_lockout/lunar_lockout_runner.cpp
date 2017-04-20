// A state space planner for the lunar lockout world
#include <iostream>
#include <queue>
#include <stack>
#include <memory>
#include <cstring>

#include "planner_utils.h"
#include <time.h>


int main(int argc,char* argv[0])
{
	std::cout<<"Starting the game....\n";

    // Check the number of arguments, error out if either the domain name or the puzzle number have not been specified.
    // TODO: Replace with boost::program options.
	if (argc!=3)
	{	
		std::cout<<"Invalid Number of arguments!\n";
		std::cout<<"Usage is ./lunar_lockout_runner <domain_name> <puzzle_number>";
		std::cout<<"Valid Arguements are domain1 (for spaceship representation) and domain2 (for grid representation)\n";
		std::cout<<"Valid puzzle numbers are: 1 ,2, 3, 4.\n";
	}

	else
    {   
		int puzzle_number = argv[2][0]-'0';
        
        // Only puzzles 1,2,3,4 are valid options.
        if (puzzle_number<1 || puzzle_number>4)  
        {
            std::cout<<"Invalid Puzzle Number\n";
        }

        else
        {
		// Profile the planning process.
        clock_t t1,t2;
		t1=clock();
        
        // Run the planning on either the spaceship representation or the cell based representation.		
        if (!strcmp(argv[1],"domain1"))  
				init_planning_spaceship_statespace(puzzle_number);
		if (!strcmp(argv[1],"domain2"))  
				init_planning_cell_statespace(puzzle_number);
		
        t2=clock();
		std::cout<<"\nTime taken: "<<((float)t2 - (float)t1)/CLOCKS_PER_SEC<<std::endl;
		}

	}
}