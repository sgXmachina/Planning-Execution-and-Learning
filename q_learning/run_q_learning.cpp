// Runs the q learning algorithm given a set of config paramters.
#include "include/mdp-simulation.h"
#include "include/q_learner.h"
#include <iostream>
#include <libconfig.h++>

int main (void)
{   
    // Read the config file with the q learning parameters.
	libconfig::Config cfg;
    cfg.readFile("config/params.cfg");

	// Initialize the q learner with the discount factor and greedy factor
    // from the config.
	q_learning::q_learner q_learn(cfg);
	
	q_learn.print_policy();

	//Function that Queries for a q value of a state action
	const q_learning::state st(0,0);

	Action ac(Action::N);
	double q_val=q_learn.query_q_func(st,ac);
	std::cout<<"\nQ Value: "<<q_val;

	ac= Action::S;
	q_val=q_learn.query_q_func(st,ac);
	std::cout<<"\nQ Value: "<<q_val;

	ac= Action::E;
	q_val=q_learn.query_q_func(st,ac);
	std::cout<<"\nQ Value: "<<q_val;

	ac= Action::W;
	q_val=q_learn.query_q_func(st,ac);
	std::cout<<"\nQ Value: "<<q_val;
	return 0;
}
