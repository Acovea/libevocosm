//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  Evocosm -- An Object-Oriented Framework for Evolutionary Algorithms
//
//  fsm.h
//---------------------------------------------------------------------
//
//  Copyright 1996, 1999, 2002, 2003, 2004, 2005 Scott Robert Ladd
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the
//      Free Software Foundation, Inc.
//      59 Temple Place - Suite 330
//      Boston, MA 02111-1307, USA.
//
//-----------------------------------------------------------------------
//
//  For more information on this software package, please visit
//  Scott's web site, Coyote Gulch Productions, at:
//
//      http://www.coyotegulch.com
//  
//-----------------------------------------------------------------------

#if !defined(LIBEVOCOSM_FSM_H)
#define LIBEVOCOSM_FSM_H

// Standard C++ Library
#include <cstddef>
#include <vector>
#include <map>
#include <stack>
#include <stdexcept>
using namespace std;

// libevocosm
#include "evocommon.h"
#include "roulette.h"
#include "fsm_tools.h"

namespace libevocosm
{
    //! A finite state machine
    /*!
        The class defines an abstract finite state machine with parameterized
        input and output types. A machine could take character inputs and return
        integer outputs, for example.
        
        While this class provides great flexibility in FSM design (given that inputs
        and outputs can be almost any type of object), the class suffers from 
        performance problems, especially when used in a genetic algorithm, where
        many, many objects are copied and created. In general, I've switched to
        using the simple_fsm class, mapping integer inputs and outputs to object
        tables where required.
        \param InputT Input type
        \param OutputT Output type
    */
    template <typename InputT, typename OutputT>
    class fsm : protected globals, protected fsm_tools
    {
    public:
        //! Exported input type
        typedef InputT  t_input;

        //! Exported output type
        typedef OutputT t_output;

        //! Type of a transition
        typedef typename std::pair<t_output, size_t> t_transition;

        //! Mapping inputs to outputs and state transitions
        typedef typename std::map<t_input, t_transition> t_input_map;

        //! State table (the machine)
        typedef typename std::vector<t_input_map> t_state_table;

        //! Creation constructor
        /*!
            Creates a new finite state machine with a given number of states,
            and input set and an output set.
            \param a_size - Initial number of states in this machine
            \param a_inputs - A list of input values
            \param a_outputs - A list of output values
        */
        fsm(size_t a_size, const std::vector<t_input> & a_inputs, const std::vector<t_output> & a_outputs);

        //! Construct via bisexual crossover
        /*!
            Creates a new fsm by combining the states of two parent machines.
            Each state in the child has an equal likelihood of being a copy
            of the corresponding state in either a_parent1 or a_parent2. If
            one parent has more states than the other, the child will also
            have copies of the "extra" states taken from the longer parent.
            \param a_parent1 - The first parent organism
            \param a_parent2 - The second parent organism
        */
        fsm(const fsm<InputT,OutputT> & a_parent1, const fsm<InputT,OutputT> & a_parent2);

        //! Copy constructor
        /*!
            Creates a new fsm identical to an existing one.
            \param a_source - Object to be copied
        */
        fsm(const fsm<InputT,OutputT> & a_source);

        //! Virtual destructor
        /*!
            Does nothing in the base class; exists to allow destruction of derived
            class objects through base class (fsm) pointers.
        */
        virtual ~fsm();

        //  Assignment
        /*!
            Sets an existing fsm to duplicate another.
            \param a_source - Object to be copied
        */
        fsm & operator = (const fsm<InputT,OutputT> & a_source);

        //!  Mutation
        /*!
            Mutates a finite state machine object. The four mutations supported are:
            - Change a random output symbol
            - Change a random state transition
            - Swap two randomly-selected states
            - Randomly change the initial state
            Why not store the input and output sets in the machine itself? That would
            duplicate information across every machine of a given type, greatly
            increasing the memory footprint of each fsm. The same principle holds for
            the mutation selector.
            \param a_rate - Chance that any given state will mutate
            \param a_inputs - A list of valid input states
            \param a_outputs - A list of valid output states
            \param a_selector - A mutation selector
        */
        void mutate(double a_rate, const std::vector<t_input> & a_inputs, const std::vector<t_output> & a_outputs, mutation_selector & a_selector = g_default_selector);
        
        //! Cause state transition
        /*!
            Based on an input symbol, this function changes the state of an fsm and
            returns an output symbol.
            \param a_input - An input symbol
        */
        t_output transition(const fsm<InputT,OutputT>::t_input & a_input);

        //! Reset to start-up state
        /*!
            Prepares the FSM to start running from its initial state.
        */
        void reset();

        //! Get a copy of the internal table
        /*!
            Returns a copy of the state transition table. Useful for reporting the "program"
            stored in an fsm.
            \return A copy of the internal state transition table
        */
        t_state_table get_table() const;

        //! Get initial state
        /*!
            Returns the initial (start up) state.
            \return The initial state
        */
        size_t get_init_state() const;

        //! Get current state
        /*!
            Returns the current (active) state.
            \return The current state
        */
        size_t get_current_state() const;

    protected:
        //!  State table (the machine definition)
        t_state_table m_state_table;

        //!  Number of states
        size_t m_size;

        //!  Initial state
        size_t m_init_state;

        //!  Current state
        size_t m_current_state;

        //!  A static, default mutation selector
        static mutation_selector g_default_selector;
        
    private:
        // create a state map
        t_input_map create_input_map(const std::vector<t_input> & a_inputs, const std::vector<t_output> & a_outputs);
    };

    //  Static initializer
    template <typename InputT, typename OutputT>
    typename fsm<InputT,OutputT>::mutation_selector fsm<InputT,OutputT>::g_default_selector;

    //  Creation constructor
    template <typename InputT, typename OutputT>
    fsm<InputT,OutputT>::fsm(size_t a_size, const std::vector<t_input> & a_inputs, const std::vector<t_output> & a_outputs)
      : m_state_table(),
        m_init_state(0),
        m_current_state(0),
        m_size(a_size)
    {
        // verify parameters
        if ((a_size < 2) || (a_inputs.size() < 1) || (a_outputs.size() < 1))
            throw std::runtime_error("invalid fsm creation parameters");

        for (size_t n = 0; n < m_size; ++n)
        {
            // add input map to state table
            m_state_table.push_back(create_input_map(a_inputs,a_outputs));
        }

        // set initial state and start there
        m_init_state = g_random.get_rand_index(m_size);
        m_current_state = m_init_state;
    }

    //  Construct via bisexual crossover
    template <typename InputT, typename OutputT>
    fsm<InputT,OutputT>::fsm(const fsm<InputT,OutputT> & a_parent1, const fsm<InputT,OutputT> & a_parent2)
      : m_state_table(a_parent1.m_state_table),
        m_init_state(0),
        m_current_state(0),
        m_size(0)
    {
        size_t n;

        // don't do anything else if fsms differ is size
        if (a_parent1.m_size != a_parent2.m_size)
            return;

        // replace states from those in second parent 50/50 chance
        for (size_t n = 0; n < m_size; ++n)
        {
            if (g_random.get_rand_real2() > 0.5)
                m_state_table[n] = a_parent2.m_state_table[n];
        }

        // calculate the size
        m_size = m_state_table.size();

        // randomize the initial state (looks like mom and dad but may act like either one!)
        if (g_random.get_rand_real2() < 0.5)
            m_init_state = a_parent1.m_init_state;
        else
            m_init_state = a_parent2.m_init_state;

        // reset for start
        m_current_state = m_init_state;
    }

    //  Copy constructor
    template <typename InputT, typename OutputT>
    fsm<InputT,OutputT>::fsm(const fsm<InputT,OutputT> & a_source)
      : m_state_table(a_source.m_state_table),
        m_init_state(a_source.m_init_state),
        m_current_state(a_source.m_current_state),
        m_size(a_source.m_size)
    {
        // nada
    }

    //  Virtual destructor
    template <typename InputT, typename OutputT>
    fsm<InputT,OutputT>::~fsm()
    {
        // nada
    }

    //  Assignment
    template <typename InputT, typename OutputT>
    fsm<InputT,OutputT> & fsm<InputT,OutputT>::operator = (const fsm<InputT,OutputT> & a_source)
    {
        if (this != &a_source)
        {
            m_state_table   = a_source.m_state_table;
            m_init_state    = a_source.m_init_state;
            m_current_state = a_source.m_current_state;
            m_size          = a_source.m_size;
        }

        return *this;
    }

    //  Mutation
    template <typename InputT, typename OutputT>
    void fsm<InputT,OutputT>::mutate(double a_rate, 
                                     const std::vector<t_input> & a_inputs,
                                     const std::vector<t_output> & a_outputs,
                                     mutation_selector & a_selector)
    {
        if (g_random.get_rand_real2() < a_rate)
        {
            // pick a mutation
            switch (a_selector.get_index())
            {
                case MUTATE_OUTPUT_SYMBOL:
                {
                    // mutate output symbol
                    size_t state  = g_random.get_rand_index(m_size);
                    size_t input  = g_random.get_rand_index(a_inputs.size());
                    size_t output = g_random.get_rand_index(a_outputs.size());
                    m_state_table[state][a_inputs[input]].first = a_outputs[output];
                    break;
                }    
                case MUTATE_TRANSITION:
                {
                    // mutate state transition
                    size_t state  = g_random.get_rand_index(m_size);
                    size_t input  = g_random.get_rand_index(a_inputs.size());
                    size_t new_state = g_random.get_rand_index(m_size);
                    m_state_table[state][a_inputs[input]].second = new_state;
                    break;
                }
                case MUTATE_REPLACE_STATE:
                {
                    // select state
                    size_t state  = g_random.get_rand_index(m_size);
                    m_state_table[state] = create_input_map(a_inputs,a_outputs);
                }
                case MUTATE_SWAP_STATES:
                {
                    // swap two states
                    size_t state1 = g_random.get_rand_index(m_size);
                    size_t state2;
        
                    do
                        state2 = g_random.get_rand_index(m_size);
                    while (state2 == state1);
        
                    t_input_map temp = m_state_table[state1];
                    m_state_table[state1] = m_state_table[state2];
                    m_state_table[state2] = temp;
                    break;
                }    
                case MUTATE_INIT_STATE:
                {
                    // change initial state
                    m_init_state  = g_random.get_rand_index(m_size);
                    break;
                }
            }
        }
        
        // reset current state because init state may have changed
        m_current_state = m_init_state;
    }

    //  Cause state transition
    template <typename InputT, typename OutputT>
    typename fsm<InputT,OutputT>::t_output fsm<InputT,OutputT>::transition(const fsm<InputT,OutputT>::t_input & a_input)
    {
        // get transition state
        t_transition & trans = m_state_table[m_current_state][a_input];

        // change to new state
        m_current_state = trans.second;

        // return output symbol
        return trans.first;
    }

    //  Reset to start-up state
    template <typename InputT, typename OutputT>
    inline void fsm<InputT,OutputT>::reset()
    {
        m_current_state = m_init_state;
    }

    //  Get a copy of the internal table
    template <typename InputT, typename OutputT>
    inline typename fsm<InputT,OutputT>::t_state_table fsm<InputT,OutputT>::get_table() const
    {
        return m_state_table;
    }

    //  Get initial state
    template <typename InputT, typename OutputT>
    inline size_t fsm<InputT,OutputT>::get_init_state() const
    {
        return m_init_state;
    }

    //  Get current state
    template <typename InputT, typename OutputT>
    inline size_t fsm<InputT,OutputT>::get_current_state() const
    {
        return m_current_state;
    }

    // create a state map
    template <typename InputT, typename OutputT>
    typename fsm<InputT,OutputT>::t_input_map fsm<InputT,OutputT>::create_input_map(const std::vector<t_input> & a_inputs, const std::vector<t_output> & a_outputs)
    {
        // maximum output index
        size_t max_output = a_outputs.size();

        // create an input map for this state
        t_input_map input_map;

        // for each input, define an output and a state transition
        for (typename std::vector<t_input>::const_iterator input = a_inputs.begin(); input != a_inputs.end(); ++input)
        {
            // pick a random output symbol and new state
            t_output out_symbol = a_outputs[g_random.get_rand_index(max_output)];
            size_t   new_state  = g_random.get_rand_index(m_size);

            // add transition data to map
            input_map[*input] = std::make_pair(out_symbol,new_state);
        }

        return input_map;
    }
};

#endif
