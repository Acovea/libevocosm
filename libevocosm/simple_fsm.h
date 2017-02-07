//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  Evocosm -- An Object-Oriented Framework for Evolutionary Algorithms
//
//  simple_fsm.h
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
#include <stack>
#include <stdexcept>
using namespace std;

// libevocosm
#include "evocommon.h"
#include "fsm_tools.h"

namespace libevocosm
{
    //! A finite state machine
    /*!
        The class defines an abstract finite state machine that uses unsigned
        integer input and output types. This is much faster than the generic
        fsm class because the transition table can be represented as a simple
        two-dimensional array.
        \param InputSize Number of input states
        \param OutputSize Number of output states
    */
    template <size_t InSize, size_t OutSize>
    class simple_fsm : protected globals, protected fsm_tools
    {
    public:
        //! Defines a transition and output state pair
        struct tranout_t
        {
            //! The state to be transitioned to
            size_t m_new_state;
            
            //! The output value
            size_t m_output;
        };

        //! Creation constructor
        /*!
            Creates a new finite state machine with a given number of states.
            \param a_size - Initial number of states in this machine
        */
        simple_fsm(size_t a_size);

        //! Construct via bisexual crossover
        /*!
            Creates a new simple_fsm by combining the states of two parent machines.
            \param a_parent1 - The first parent organism
            \param a_parent2 - The second parent organism
        */
        simple_fsm(const simple_fsm<InSize,OutSize> & a_parent1, const simple_fsm<InSize,OutSize> & a_parent2);

        //! Copy constructor
        /*!
            Creates a new simple_fsm identical to an existing one.
            \param a_source - Object to be copied
        */
        simple_fsm(const simple_fsm<InSize,OutSize> & a_source);

        //! Virtual destructor
        /*!
            Does nothing in the base class; exists to allow destruction of derived
            class objects through base class pointers.
        */
        virtual ~simple_fsm();

        //  Assignment
        /*!
            Copies the state of an existing simple_fsm.
            \param a_source - Object to be copied
            \return A reference to the target object
        */
        simple_fsm & operator = (const simple_fsm<InSize,OutSize> & a_source);

        //!  Mutation
        /*!
            Mutates a finite state machine object. The four mutations supported are:
            - Change a random output symbol
            - Change a random state transition
            - Swap two randomly-selected states
            - Randomly change the initial state
            Why not store the input and output sets in the machine itself? That would
            duplicate information across every machine of a given type, greatly
            increasing the memory footprint of each simple_fsm. The same principle holds for
            the mutation selector.
            \param a_rate - Chance that any given state will mutate
        */
        void mutate(double a_rate);
        
        //! Set a mutation weight
        /*!
            Sets the weight value associated with a specific mutation; this changes the
            relative chance of this mutation happening.
            \param a_type - ID of the weight to be changed
            \param a_weight - New weight to be assigned
        */
        static void set_mutation_weight(mutation_id a_type, double a_weight);
        
        //! Cause state transition
        /*!
            Based on an input symbol, this function changes the state of an simple_fsm and
            returns an output symbol.
            \param a_input - An input value
            \return Output value resulting from transition
        */
        size_t transition(size_t a_input);

        //! Reset to start-up state
        /*!
            Prepares the FSM to start running from its initial state.
        */
        void reset();

        //! Get size
        /*!
            Returns the size of a simple_fsm.
            \return The size, in number of states
        */
        size_t size() const;

        //! Get a transition from the internal state table.
        /*!
            Get a transition from the internal state table.
            \param a_state - Target state
            \param a_input - State information to return
            \return A transition from the internal state table
        */
        const tranout_t & get_transition(size_t a_state, size_t a_input) const;
        
        //! Get number of input states
        /*!
            Returns the number of input states
            \return The number of input states
        */
        size_t num_input_states() const;

        //! Get number of output states
        /*!
            Returns the number of output states
            \return The number of output states
        */
        size_t num_output_states() const;
        
        //! Get initial state
        /*!
            Returns the initial (start up) state.
            \return The initial state
        */
        size_t init_state() const;

        //! Get current state
        /*!
            Returns the current (active) state.
            \return The current state
        */
        size_t current_state() const;

    private:
        // release resources
        void release();

        // deep copy
        void deep_copy(const simple_fsm<InSize,OutSize> & a_source);

    protected:
        //!  State table (the machine definition)
        tranout_t ** m_state_table;

        //!  Initial state
        size_t m_init_state;

        //!  Current state
        size_t m_current_state;

        //!  Number of states
        size_t m_size;

        //!  Global mutation selector
        static mutation_selector g_selector;
    };

    //  Static initializer
    template <size_t InSize, size_t OutSize>
    typename simple_fsm<InSize,OutSize>::mutation_selector simple_fsm<InSize,OutSize>::g_selector;

    // release resources
    template <size_t InSize, size_t OutSize>
    void simple_fsm<InSize,OutSize>::release()
    {
        for (size_t s = 0; s < m_size; ++s)
            delete [] m_state_table[s];

        delete [] m_state_table;
    }

    // deep copy
    template <size_t InSize, size_t OutSize>
    void simple_fsm<InSize,OutSize>::deep_copy(const simple_fsm<InSize,OutSize> & a_source)
    {
        // allocate state table
        m_state_table = new tranout_t * [m_size];

        for (size_t s = 0; s < m_size; ++s)
        {
            // allocate an array corresponding to inputs
            m_state_table[s] = new tranout_t [InSize];

            // set transition values
            for (size_t i = 0; i < InSize; ++i)
            {
                m_state_table[s][i].m_new_state = a_source.m_state_table[s][i].m_new_state;
                m_state_table[s][i].m_output    = a_source.m_state_table[s][i].m_output;
            }
        }
    }

    //  Creation constructor
    template <size_t InSize, size_t OutSize>
    simple_fsm<InSize,OutSize>::simple_fsm(size_t a_size)
      : m_state_table(NULL),
        m_init_state(0),
        m_current_state(0),
        m_size(a_size)
    {
        // verify parameters
        if (m_size < 2)
            throw std::runtime_error("invalid simple_fsm creation parameters");

        // allocate state table
        m_state_table = new tranout_t * [m_size];

        for (size_t s = 0; s < m_size; ++s)
        {
            // allocate an array corresponding to inputs
            m_state_table[s] = new tranout_t [InSize];

            // set transition values
            for (size_t i = 0; i < InSize; ++i)
            {
                m_state_table[s][i].m_new_state = g_random.get_rand_index(m_size);
                m_state_table[s][i].m_output    = g_random.get_rand_index(OutSize);
            }
        }

        // set initial state and start there
        m_init_state = g_random.get_rand_index(m_size);
        m_current_state = m_init_state;
    }

    // Construct via bisexual crossover
    template <size_t InSize, size_t OutSize>
    simple_fsm<InSize,OutSize>::simple_fsm(const simple_fsm<InSize,OutSize> & a_parent1, const simple_fsm<InSize,OutSize> & a_parent2)
      : m_state_table(NULL),
        m_init_state(0),
        m_current_state(0),
        m_size(a_parent1.m_size)
    {
        // copy first parent
        deep_copy(a_parent1);

        // don't do anything else if fsms differ is size
        if (a_parent1.m_size != a_parent2.m_size)
            return;

        // replace states from those in second parent 50/50 chance
        size_t x = g_random.get_rand_index(m_size);
                
        for (size_t n = x; n < m_size; ++n)
        {
            // set transition values
            for (size_t i = 0; i < InSize; ++i)
            {
                m_state_table[n][i].m_new_state = a_parent2.m_state_table[n][i].m_new_state;
                m_state_table[n][i].m_output    = a_parent2.m_state_table[n][i].m_output;
            }
        }

        // randomize the initial state (looks like mom and dad but may act like either one!)
        if (g_random.get_rand_real2() < 0.5)
            m_init_state = a_parent1.m_init_state;
        else
            m_init_state = a_parent2.m_init_state;

        // reset for start
        m_current_state = m_init_state;
    }

    //  Copy constructor
    template <size_t InSize, size_t OutSize>
    simple_fsm<InSize,OutSize>::simple_fsm(const simple_fsm<InSize,OutSize> & a_source)
      : m_state_table(NULL),
        m_init_state(a_source.m_init_state),
        m_current_state(a_source.m_current_state),
        m_size(a_source.m_size)
    {
        // copy first parent
        deep_copy(a_source);
    }

    //  Virtual destructor
    template <size_t InSize, size_t OutSize>
    simple_fsm<InSize,OutSize>::~simple_fsm()
    {
        release();
    }

    //  Assignment
    template <size_t InSize, size_t OutSize>
    simple_fsm<InSize,OutSize> & simple_fsm<InSize,OutSize>::operator = (const simple_fsm<InSize,OutSize> & a_source)
    {
        // release resources
        release();

        // set values
        m_init_state    = a_source.m_init_state;
        m_current_state = a_source.m_current_state;
        m_size          = a_source.m_size;

        // copy source
        deep_copy(a_source);

        return *this;
    }

    //! Set a mutation weight
    template <size_t InSize, size_t OutSize>
    inline void simple_fsm<InSize,OutSize>::set_mutation_weight(mutation_id a_type, double a_weight)
    {
        g_selector.set_weight(a_type,a_weight);
    }
    
    //  Mutation
    template <size_t InSize, size_t OutSize>
    void simple_fsm<InSize,OutSize>::mutate(double a_rate)
    {
        // the number of chances for mutation is based on the number of states in the machine;
        // larger machines thus encounter more mutations
        for (size_t n = 0; n < m_size; ++n)
        {
            if (g_random.get_rand_real2() < a_rate)
            {
                // pick a mutation
                switch (g_selector.get_index())
                {
                    case MUTATE_OUTPUT_SYMBOL:
                    {
                        // mutate output symbol
                        size_t state  = g_random.get_rand_index(m_size);
                        size_t input  = g_random.get_rand_index(InSize);
                        
                        size_t choice;
                        
                        do
                        {
                            choice = g_random.get_rand_index(OutSize);
                        }
                        while (m_state_table[state][input].m_output == choice);
                                
                        m_state_table[state][input].m_output = choice;
                        break;
                    }    
                    case MUTATE_TRANSITION:
                    {
                        // mutate state transition
                        size_t state  = g_random.get_rand_index(m_size);
                        size_t input  = g_random.get_rand_index(InSize);
                        
                        size_t choice;
                        
                        do
                        {
                            choice = g_random.get_rand_index(m_size);
                        }
                        while (m_state_table[state][input].m_new_state == choice);
                                
                        m_state_table[state][input].m_new_state = choice;
                        break;
                    }    
                    case MUTATE_REPLACE_STATE:
                    {
                        // mutate state transition
                        size_t state  = g_random.get_rand_index(m_size);
                        
                        // allocate an array corresponding to inputs
                        delete [] m_state_table[state];
                        m_state_table[state] = new tranout_t [InSize];

                        // set transition values
                        for (size_t i = 0; i < InSize; ++i)
                        {
                            m_state_table[state][i].m_new_state = g_random.get_rand_index(m_size);
                            m_state_table[state][i].m_output    = g_random.get_rand_index(OutSize);
                        }
                        
                        break;
                    }    
                    case MUTATE_SWAP_STATES:
                    {
                        // swap two states (by swapping pointers)
                        size_t state1 = g_random.get_rand_index(m_size);
                        size_t state2;
            
                        do
                            state2 = g_random.get_rand_index(m_size);
                        while (state2 == state1);
            
                        for (size_t i = 0; i < InSize; ++i)
                        {
                            tranout_t temp = m_state_table[state1][i];
                            m_state_table[state1][i] = m_state_table[state2][i];
                            m_state_table[state2][i] = temp;
                        }

                        break;
                    }    
                    case MUTATE_INIT_STATE:
                    {
                        // change initial state
                        size_t choice;
                        
                        do
                        {
                            choice = g_random.get_rand_index(m_size);
                        }
                        while (m_init_state == choice);
                                
                        m_init_state  = choice;
                        
                        break;
                    }
                }
            }
        }
        
        // reset current state because init state may have changed
        m_current_state = m_init_state;
    }

    //  Cause state transition
    template <size_t InSize, size_t OutSize>
    inline size_t simple_fsm<InSize,OutSize>::transition(size_t a_input)
    {
        // get output symbol for given input for current state
        size_t output = m_state_table[m_current_state][a_input].m_output;

        // change to new state
        m_current_state = m_state_table[m_current_state][a_input].m_new_state;

        // return output symbol
        return output;
    }

    //  Reset to start-up state
    template <size_t InSize, size_t OutSize>
    inline void simple_fsm<InSize,OutSize>::reset()
    {
        m_current_state = m_init_state;
    }

    // Get size
    template <size_t InSize, size_t OutSize>
    inline size_t simple_fsm<InSize,OutSize>::size() const
    {
        return m_size;
    }

    //  Get a copy of the internal table
    template <size_t InSize, size_t OutSize>
    inline const typename simple_fsm<InSize,OutSize>::tranout_t & simple_fsm<InSize,OutSize>::get_transition(size_t a_state, size_t a_input) const
    {
        return m_state_table[a_state][a_input];
    }

    // Get number of input states
    template <size_t InSize, size_t OutSize>
    inline size_t simple_fsm<InSize,OutSize>::num_input_states() const
    {
        return InSize;
    }

    // Get number of output states
    template <size_t InSize, size_t OutSize>
    inline size_t simple_fsm<InSize,OutSize>::num_output_states() const
    {
        return OutSize;
    }
        
    //  Get initial state
    template <size_t InSize, size_t OutSize>
    inline size_t simple_fsm<InSize,OutSize>::init_state() const
    {
        return m_init_state;
    }

    //  Get current state
    template <size_t InSize, size_t OutSize>
    inline size_t simple_fsm<InSize,OutSize>::current_state() const
    {
        return m_current_state;
    }
};

#endif
