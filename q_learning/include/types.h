#ifndef __TYPES__
#define __TYPES__


#include <vector>
#include <utility>
#include <unordered_map>
#include <map>
#include <boost/functional/hash.hpp>

#include "mdp-simulation.h"

using boost::hash_value;
using boost::hash_combine;

namespace q_learning
{	
    // Create a new struct "state" which derives from the provided 
    // "State" interface and defines the < operator for hashing.
	struct state : public State
	{	
		state(int x, int y) : State(x,y) 
		{
		}

		friend bool operator<(const state &state1,const state &state2) 
		{ 
			return state1.x==state2.x?state1.y<state2.y:state1.x<state2.x; 
		}
	};
    // Store the reward value and the number of visits.
    typedef std::pair<double,unsigned int> reward_visits_pair;

    //Create a container to store action-reward pair. Explicitly keep track of the number
    // of times the action has been played and the reward associated with it.
    typedef std::map<Action,reward_visits_pair> actions;

    // Create a Q table from the state-action pairs.
	typedef std::map<state,actions> Q_table;

    // typedef std::unordered_map<Action,reward_visits_pair,std::hash<double>> actions;
    // typedef std::unordered_map<Action,Reward,std::hash<int>> actions;
    // typedef std::vector<action_reward> actions;
    //Create a hash function for the Q function

    // auto q_func_hash = [](const state &cstate)
    // {
    //  std::size_t seed = 0;

    //  hash_combine(seed,hash_value(cstate.x));
    //  hash_combine(seed,hash_value(cstate.y));

    //  return seed;
    // };
	// typedef std::map<
	// typedef std::unordered_map<state,actions,decltype(q_func_hash)> Q_table;

}
#endif 