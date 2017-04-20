// Definition of the Q learning interface.
// Author : Shivam Gautam
#ifndef __Q_LEARNER__
#define __Q_LEARNER__

#include "types.h"
#include <vector>
#include <iostream>
#include <random>
#include <libconfig.h++>

namespace q_learning
{

	class q_learner
	{

	public:
	q_learner();

	q_learner(libconfig::Config &cfg);

    // Returns the best action in a given state.
	Action get_best_action(const state &st) const;

    // Returns the highest reward across actions in the state.
	double get_max_reward(const state &st) const;

    // Prints the q table for all state-action pairs.
    void print_q_table() const;

    // Prints the max rewards for all states.
    void print_max_rewards() const;

    // Prints the learned policy.
    void print_policy() const;

    // Queries the Q-table for the Q value of a particular state.
    double query_q_func(const state &st,const Action &ac);

    private:

        // Runs the q learning algorithm.
        void run_q_learning();

        // Updates the q table with a reward for the given state action pair.
    	void update_q_table(state &st, Action &action, Reward &reward);

        // Reward in a given episode.
        Reward episode_reward_;

        // The amount to decay the greedy factor by. Helps to switch from initial
        // exploration to later exploitation.
        double decay_factor_;

        double epsilon_; //Exploration factor
        const double alpha_; // Learning Rate
        const double gamma_; //Discount Factor
        
        const int it_limit_;
		
        mutable Q_table q_table_;

	};

}

#endif