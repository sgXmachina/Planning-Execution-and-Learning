///// Utility functions for the lunar lockout game./////
///// Author: Shivam Gautam
/////         MRSD, CMU
#ifndef PLANNER_UTILS
#define PLANNER_UTILS

#include <iostream>
#include <queue>
#include <stack>
#include <memory>
#include "state_ship.h"
#include "state_cell.h"

// Helper to print the solution for the cell representation or the spaceship representation of the lunar lockout puzzle.
template<typename state_representation>
void print_solution(const std::shared_ptr<state_representation>& final_node)
{
    
    if(final_node->get_parent()==NULL)
        {return;}
    
    print_solution<state_representation>(final_node->get_parent());    

    final_node->print_move();
    final_node->print_grid();
    std::cout<<"\n";
}

//TODO: Templatize equality functions.
// Check whether two states in the ship representation are equal.
bool equal_ship_states(const std::shared_ptr<lunar_lockout_ship::board_ship_state>& state1, const std::shared_ptr<lunar_lockout_ship::board_ship_state>& state2);

// Check whether two states in the cell representation are equal.
bool equal_cell_states(const std::shared_ptr<lunar_lockout_cell::board_cell_state>& state1, const std::shared_ptr<lunar_lockout_cell::board_cell_state>& state2);

// Copy the values from one grid to another.
void copy_grid(const unsigned int original_grid[][lunar_lockout_cell::grid_y],lunar_lockout_cell::grid_type &target_grid);

// Initialize the spaceship statespace.
void init_spaceship_statespace(std::vector<lunar_lockout_ship::spaceship>& spaceships,
    std::vector<lunar_lockout_ship::spaceship_type>& possible_ships,
    std::vector<lunar_lockout_ship::direction>& possible_directions,
    int puzzle_number
    );

// Initialize the cell statespace.
void init_cell_statespace(lunar_lockout_cell::grid_type& grid,
    std::vector<lunar_lockout_cell::direction>& possible_directions,
    int puzzle_number
    );

// Initialize the planning environment for the spaceship statespace.
void init_planning_spaceship_statespace(int puzzle_number);

// Initialize the planning environment for the cell statespace.
void init_planning_cell_statespace(int puzzle_number);


#endif
