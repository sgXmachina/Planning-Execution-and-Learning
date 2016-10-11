// A state space planner for the lunar lockout world
#include <iostream>
#include <queue>
#include <stack>
#include <memory>
#include <cstring>

#include "planners.h"
#include <time.h>




int main(int argc,char* argv[0])
{
	std::cout<<"Starting the game....\n";

	if (argc!=3)
	{	
		std::cout<<argv[1];

		std::cout<<"Invalid Number of arguments.\n";
		std::cout<<"Usage is ./a.out <domain_name> <puzzle_number>";
		std::cout<<"Valid Arguements are domain1 (for spaceship representation) and domain2 (for grid representation)\n";
		std::cout<<"Valid puzzle numbers are: 1 ,2, 3, 4\n";
	}

	else
	{	
		if (strlen(argv[2])>1)	
		{
			std::cout<<"Invalid Puzzle Number\n";
		}

		else
		{
		int puzzle_number = argv[2][0]-'0';
		clock_t t1,t2;
		t1=clock();
		if (!strcmp(argv[1],"domain1"))  
				init_planning_spaceship_statespace(puzzle_number);
		if (!strcmp(argv[1],"domain2"))  
				init_planning_cell_statespace(puzzle_number);
		t2=clock();
		std::cout<<"\nTime taken: "<<((float)t2 - (float)t1)/CLOCKS_PER_SEC<<std::endl;
		}

	}
}