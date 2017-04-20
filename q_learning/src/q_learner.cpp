// Implementation of the Q learning algorithm.
// Author : Shivam Gautam

#include "../include/q_learner.h"

namespace q_learning

{	

	namespace
	{
		// Create helper functions.

        // Random number generator to sample from a uniform distribution.
        std::mt19937 mt(1729);
		double sample_from_uniform(const double min, const double max)
		{
			std::uniform_real_distribution<> dis(min, max);
			return dis(mt);
		}

        // Given the enum, prints the action name.
		void print_action(Action &ac)
		{
			switch(ac)
			{
				case 0: std::cout<<"N";
				break;
				case 1: std::cout<<"S";
				break;
				case 2: std::cout<<"E";
				break;
				case 3: std::cout<<"W";
				break;

				default : std::cout<<"?";
			}
		}
		
	}

    // Initialize the Q learner from the config parameters. Also runs the q learning
    // algorithm.
	q_learner::q_learner(libconfig::Config &cfg):
                    	epsilon_(cfg.lookup("epsilon")),
                    	alpha_(cfg.lookup("alpha")),
                    	gamma_(cfg.lookup("gamma")),
                    	it_limit_(cfg.lookup("iterations"))
	{

		//Set initial reward to 0
		episode_reward_=0;

		//Initialize the Q-table with 0 rewards.
		// Create a action-visit container, initializing it to zero visits.
        actions empty;
		empty[Action::S].first=0;
		empty[Action::N].first=0;
		empty[Action::E].first=0;
		empty[Action::W].first=0;
		empty[Action::S].second=0;
		empty[Action::N].second=0;
		empty[Action::E].second=0;
		empty[Action::W].second=0;

        // Push this 0-visit action into the Q table for all states.
		for (size_t i =0; i<MAX_GRID; ++i)
		{
			for (size_t j =0; j<MAX_GRID; ++j)
			{	
				auto s = state(i,j);
				q_table_[s]=empty;
			}

		}

		const int32_t number_of_episodes = cfg.lookup("episodes");
		
        // Calculate the decay factor for decaying the greedy exploration.
        // As the number of episodes increase, we'll decay the greedy factor by
        // this value.
        decay_factor_= 1.0/number_of_episodes;


		// Run the episodic training for the number of episodes.
		for (int32_t ep = 0 ; ep <number_of_episodes;++ep)
		{
			run_q_learning();
		}

	}

    // Prints the q table for all state-action pairs.
	void q_learner::print_q_table() const
	{
        // Iterate over all state-action pairs and print the q value.
		for ( auto &st : q_table_)
		{
			std::cout<<"\nState: ("<<st.first.x<<","<<st.first.y<<")** ";

			for (auto &ac : st.second)
			{
				std::cout <<" Action "<<ac.first<<" Reward= "<<ac.second.first<<"|||";
			}
		}


	}

    // Prints the max rewards for all states.
	void q_learner::print_max_rewards() const
	{
		int i =0;
		std::cout<<"\n\nFinal reward Table\n";
		for ( auto &st : q_table_)
		{
			++i;
			// std::cout<<std::lround(get_max_reward(st.first))<<"              ";
			printf("%+.2e      ",static_cast<float>(std::lround(get_max_reward(st.first))));
			if(i%MAX_GRID==0)
			{
				std::cout<<std::endl;
			}
		}
	}

    // Returns the best action in a given state.
	Action q_learner::get_best_action(const state &st) const
	{	
		auto action_set = q_table_[st];

		Action best_action = Action::N;
		double max_reward = -1;//action_set[best_action].first;//std::numeric_limits<double>::min();

		for (const auto & ac : action_set)
		{
			if(ac.second.first > max_reward)
			{
				max_reward = ac.second.first;
				best_action = ac.first;
			}
		}
		// std::cout<<"\nBest Action: "<<best_action;

		// std::cout<<"\nMax reward in best action: "<<max_reward;
		return best_action;
	}

    // Returns the highest reward across actions in the state.
	double q_learner::get_max_reward(const state &st) const
	{
		auto action_set = q_table_[st];
		Action best_action = Action::N;

		double max_reward = -1;//action_set[best_action].first;//std::numeric_limits<double>::min();
		for (const auto & ac : action_set)
		{	
			// std::cout<<"Action "<<ac.first<<" "<<ac.second.first<<std::endl;
			// std::cout<<"\nAction"<<ac.first<<" "<<ac.second.first<<" "<<ac.second.second;
			if(ac.second.first > max_reward)
			{	
				max_reward = ac.second.first;
				// std::cout<<"\nMax rewrd :"<<max_reward;

			}
		}

		return max_reward;
	}

    // Updates the q table with a reward for the given state action pair.
	void q_learner::update_q_table(state &st, Action &action, Reward &reward)
	{
		q_table_[st][action].first= reward;
	}

    // Runs the q learning algorithm for a single episode.
	void q_learner::run_q_learning()
	{	
		episode_reward_ = 0;
		//Start the episode from a random state
		int x_rand = sample_from_uniform(0,MAX_GRID);
		int y_rand = sample_from_uniform(0,MAX_GRID);

        // Set the current state.
    	state current_state(x_rand,y_rand);

        // Run the episode for a fixed number of iterations.
		for (int iteration = 0 ; iteration < it_limit_;++iteration)
		{    
            // Select the best action or a random action based on the 
            // probability of a random number being less than the greedy factor-
            // like an epsilon greedy algorithm.
			double rd_num = sample_from_uniform(0,1);
			Action best_action;

			if (rd_num > epsilon_)
			{	
				// std::cout<<"\nExploited";
				best_action = get_best_action(current_state);
			}

			else
			{	
				// std::cout<<"\nExplored";
				best_action = static_cast<Action>(rand() % (Action::W+1));
			}

            // Increment the number of times the action has been played.
			q_table_[current_state][best_action].second+=1;

			// Get the next state from this state action pair.
            auto next_state =  my_next_state(State(current_state.x,current_state.y),best_action);
			
            // Get the reward in the current state.
			Reward current_reward = my_reward(current_state);

            // Add to the overall episodic reward.
			episode_reward_+= current_reward;

            // Perform the Q learning update.
			double alpha = 1.0/q_table_[current_state][best_action].second; 
			double q_val = ((1.0-alpha)*q_table_[current_state][best_action].first) + alpha*(current_reward + 
				(gamma_*get_max_reward(state(next_state.x,next_state.y)))); 
			update_q_table(current_state,best_action,q_val);

            // Set the current state to where you ended up being.
			current_state = state(next_state.x,next_state.y);
		}

        // Decay the epsilon. This encourages more exploitation towards the end.
		epsilon_-=decay_factor_; 

		// std::cout<<episode_reward_<<std::endl;
		// std::cout<<"\nEpsilon: "<<epsilon_;
	}

    // Prints the learned policy.
	void q_learner::print_policy() const
	{
		int i =0;
		std::cout<<std::endl;

		for ( auto &st : q_table_)
		{
			++i;
			Action best_action = get_best_action(st.first);
			print_action(best_action);
			std::cout<<" ";

			if(i%MAX_GRID==0)
			{
				std::cout<<std::endl;
			}
		}



	}

    // Queries the Q-table for the Q value of a particular state.
	double q_learner::query_q_func(const state &st, const Action &ac)
	{
		return q_table_[st][ac].first;
	}

}//end namespace q_learning