<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  Evocosm -- An Object-Oriented Framework for Evolutionary Algorithms
//
//  fuzzy_machine.h
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
=======
/*
    Evocosm is a C++ framework for implementing evolutionary algorithms.

    Copyright 2011 Scott Robert Ladd. All rights reserved.

    Evocosm is user-supported open source software. Its continued development is dependent
    on financial support from the community. You can provide funding by visiting the Evocosm
    website at:

        http://www.coyotegulch.com

    You may license Evocosm in one of two fashions:

    1) Simplified BSD License (FreeBSD License)

    Redistribution and use in source and binary forms, with or without modification, are
    permitted provided that the following conditions are met:

    1.  Redistributions of source code must retain the above copyright notice, this list of
        conditions and the following disclaimer.

    2.  Redistributions in binary form must reproduce the above copyright notice, this list
        of conditions and the following disclaimer in the documentation and/or other materials
        provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY SCOTT ROBERT LADD ``AS IS'' AND ANY EXPRESS OR IMPLIED
    WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
    FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SCOTT ROBERT LADD OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
    ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
    ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    The views and conclusions contained in the software and documentation are those of the
    authors and should not be interpreted as representing official policies, either expressed
    or implied, of Scott Robert Ladd.

    2) Closed-Source Proprietary License

    If your project is a closed-source or proprietary project, the Simplified BSD License may
    not be appropriate or desirable. In such cases, contact the Evocosm copyright holder to
    arrange your purchase of an appropriate license.

    The author can be contacted at:

          scott.ladd@coyotegulch.com
          scott.ladd@gmail.com
          http:www.coyotegulch.com
*/
>>>>>>> version 4.0.2

#if !defined(LIBEVOCOSM_FUZZY_MACHINE_H)
#define LIBEVOCOSM_FUZZY_MACHINE_H

// Standard C++ Library
#include <cstddef>
#include <stack>
#include <stdexcept>
#ifdef DEBUG
#include <iostream>
#include <iomanip>
#endif
using namespace std;

// libevocosm
#include "evocommon.h"
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
#include "fsm_tools.h"
=======
#include "machine_tools.h"
>>>>>>> version 4.0.2

namespace libevocosm
{
    //! A finite state machine
    /*!
        The class defines an abstract fuzzy state machine that uses integer
        input and output types.
        <p>
        A fuzzy state machine differs from a finite state machine in the selection
        of state transitions and outputs. In a finite state machine, each input
        maps to specific output and state transitions for a given current state.
        The fuzzy state machine contains probability maps for outputs and inputs;
        for any given state an input, there is a probability that any valid output
        could be returned, for example.
        \param InSize Number of input states
        \param OutSize Number of output states
    */
    template <size_t InSize, size_t OutSize>
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
    class fuzzy_machine : protected globals, protected fsm_tools
=======
    class fuzzy_machine : protected globals, protected machine_tools
>>>>>>> version 4.0.2
    {
    public:
        //! Defines a transition and output state pair
        struct tranout_t
        {
            //! The state to be transitioned to
            roulette_wheel m_new_state;
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            
            //! The output value
            roulette_wheel m_output;
            
=======

            //! The output value
            roulette_wheel m_output;

>>>>>>> version 4.0.2
            //! Creation Constructor
            tranout_t(double * state_weights, size_t num_states, double * output_weights)
              : m_new_state(state_weights, num_states),
                m_output(output_weights, OutSize)
            {
                // nada
            }
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            
=======

>>>>>>> version 4.0.2
            //! Copy constructor
            tranout_t(const tranout_t & source)
              : m_new_state(source.m_new_state),
                m_output(source.m_output)
            {
                // nada
            }
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            
=======

>>>>>>> version 4.0.2
            //! Assignment
            tranout_t & operator = (const tranout_t & source)
            {
                m_new_state = source.m_new_state;
                m_output    = source.m_output;
                return *this;
            }
        };

        //! Creation constructor
        /*!
            Creates a new finite state machine with a given number of states. The four weight values
            define the range of weights assigned to outputs and state transitions; the actual
            roulette tables are randomized in the range (base,base+range).
            \param a_size - Initial number of states in this machine
            \param a_output_base - Minimum (base) value for an output roulette wheel weight
            \param a_output_range - Range for an output roulette wheel weight
            \param a_state_base - Minimum (base) value for a new roulette wheel weight
            \param a_state_range - Range for a new state roulette wheel weight
        */
        fuzzy_machine(size_t a_size,
                      double a_output_base,
                      double a_output_range,
                      double a_state_base,
                      double a_state_range);

        //! Creation constructor
        /*!
            Creates a new finite state machine with a given number of states.
            \param a_size - Initial number of states in this machine
        */
        fuzzy_machine(size_t a_size);

        //! Construct via bisexual crossover
        /*!
            Creates a new fuzzy_machine by combining the states of two parent machines.
            \param a_parent1 - The first parent organism
            \param a_parent2 - The second parent organism
        */
        fuzzy_machine(const fuzzy_machine<InSize,OutSize> & a_parent1, const fuzzy_machine<InSize,OutSize> & a_parent2);

        //! Copy constructor
        /*!
            Creates a new fuzzy_machine identical to an existing one.
            \param a_source - Object to be copied
        */
        fuzzy_machine(const fuzzy_machine<InSize,OutSize> & a_source);

        //! Virtual destructor
        /*!
            Does nothing in the base class; exists to allow destruction of derived
            class objects through base class (fuzzy_machine) pointers.
        */
        virtual ~fuzzy_machine();

        //  Assignment
        /*!
            Sets an existing fuzzy_machine to duplicate another.
            \param a_source - Object to be copied
            \return Reference to target object
        */
        fuzzy_machine & operator = (const fuzzy_machine<InSize,OutSize> & a_source);

        //!  Mutation
        /*!
            Mutates a finite state machine object. The four mutations supported are:
            - Change a random output symbol
            - Change a random state transition
            - Swap two randomly-selected states
            - Randomly change the initial state
            Why not store the input and output sets in the machine itself? That would
            duplicate information across every machine of a given type, greatly
            increasing the memory footprint of each fuzzy_machine. The same principle holds for
            the mutation selector.
            \param a_rate - Chance that any given state will mutate
        */
        void mutate(double a_rate);
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        //! Set a mutation weight
        /*!
            Sets the weight value associated with a specific mutation; this changes the
            relative chance of this mutation happening.
            \param a_type - ID of the weight to be changed
            \param a_weight - New weight to be assigned
        */
        static void set_mutation_weight(mutation_id a_type, double a_weight);
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        //! Cause state transition
        /*!
            Based on an input symbol, this function changes the state of an fuzzy_machine and
            returns an output symbol.
            \param a_input - An input symbol
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
            Returns the size of a fuzzy_machine.
            \return The size, in number of states
        */
        size_t size() const;

        //! Get a transition from the internal state table.
        /*!
            Get a transition from the internal state table.
            \param a_state - Target state
            \param a_input - State information to return
            \return A transition from the internal state table.
        */
        const tranout_t & get_transition(size_t a_state, size_t a_input) const;
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
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
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
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
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
        //! Get current transition table
        /*!
            Returns the state transition table pointer.
            
=======

        //! Get current transition table
        /*!
            Returns the state transition table pointer.

>>>>>>> version 4.0.2
            This is a very dangerous function, as it gives unrestricted access
            to the transition table that defines a machine. Given the complexity
            of fuzzy state machines, I implemented this function for debugging
            purposes; it is not intended as a tool for directly altering the
            transition table.
            /return Pointer to the transition table for the target machine
        */
        tranout_t *** state_table()
        {
            return m_state_table;
        }

        #ifdef DEBUG
        void dump(const char * description, ostream & a_stream = cerr) const;
        #endif

    private:
        // release resources
        void release();

        // deep copy
        void deep_copy(const fuzzy_machine<InSize,OutSize> & a_source);

    protected:
        //!  State table (the machine definition)
        tranout_t *** m_state_table;

        //!  Number of states
        size_t m_size;

        //!  Initial state
        size_t m_init_state;

        //!  Current state
        size_t m_current_state;

        //! base value for output weights
        double m_output_base;
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
        //! range for output weights
        double m_output_range;
        
        //! base value for state weights
        double m_state_base;
        
        //! range for state weights
        double m_state_range;
        
=======

        //! range for output weights
        double m_output_range;

        //! base value for state weights
        double m_state_base;

        //! range for state weights
        double m_state_range;

>>>>>>> version 4.0.2
        //!  Global mutation selector
        static mutation_selector g_selector;
    };

    //  Static initializer
    template <size_t InSize, size_t OutSize>
    typename fuzzy_machine<InSize,OutSize>::mutation_selector fuzzy_machine<InSize,OutSize>::g_selector;

    // release resources
    template <size_t InSize, size_t OutSize>
    void fuzzy_machine<InSize,OutSize>::release()
    {
        for (size_t s = 0; s < m_size; ++s)
        {
            for (size_t i = 0; i < InSize; ++i)
                delete m_state_table[s][i];
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            
=======

>>>>>>> version 4.0.2
            delete [] m_state_table[s];
        }

        delete [] m_state_table;
    }

    // deep copy
    template <size_t InSize, size_t OutSize>
    void fuzzy_machine<InSize,OutSize>::deep_copy(const fuzzy_machine<InSize,OutSize> & a_source)
    {
        // allocate state table
        m_state_table = new tranout_t ** [m_size];

        for (size_t s = 0; s < m_size; ++s)
        {
            // allocate an array corresponding to inputs
            m_state_table[s] = new tranout_t * [InSize];

            // set transition values
            for (size_t i = 0; i < InSize; ++i)
                m_state_table[s][i] = new tranout_t(*(a_source.m_state_table[s][i]));
        }
    }

    //  Creation constructor
    template <size_t InSize, size_t OutSize>
    fuzzy_machine<InSize,OutSize>::fuzzy_machine(size_t a_size,
                                                 double a_output_base,
                                                 double a_output_range,
                                                 double a_state_base,
                                                 double a_state_range)
      : m_state_table(NULL),
        m_size(a_size),
        m_init_state(0),
        m_current_state(0),
        m_output_base(a_output_base),
        m_output_range(a_output_range),
        m_state_base(a_state_base),
        m_state_range(a_state_range)
    {
        // verify parameters
        if (m_size < 2)
            throw std::runtime_error("invalid fuzzy_machine creation parameters");

        // allocate state table
        m_state_table = new tranout_t ** [m_size];

        // tables of weights for roulette wheels
        double * output_weights = new double[OutSize];
        double * state_weights  = new double[m_size];
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        for (size_t s = 0; s < m_size; ++s)
        {
            // allocate an array corresponding to inputs
            m_state_table[s] = new tranout_t * [InSize];

            for (size_t i = 0; i < InSize; ++i)
            {
                // define weights
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
                size_t n; 

                for (n = 0; n < OutSize; ++n)
                    output_weights[n] = g_random.get_rand_real2() * a_output_range + a_output_base;

                for (n = 0; n < m_size; ++n)
                    state_weights[n] = g_random.get_rand_real2() * a_state_range + a_state_base;
=======
                size_t n;

                for (n = 0; n < OutSize; ++n)
                    output_weights[n] = g_random.get_real() * a_output_range + a_output_base;

                for (n = 0; n < m_size; ++n)
                    state_weights[n] = g_random.get_real() * a_state_range + a_state_base;
>>>>>>> version 4.0.2

                // set transition values
                m_state_table[s][i] = new tranout_t(state_weights,m_size,output_weights);
            }
        }
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            
=======

>>>>>>> version 4.0.2
        delete [] output_weights;
        delete [] state_weights;

        // set initial state and start there
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        m_init_state    = g_random.get_rand_index(m_size);
=======
        m_init_state    = rand_index(m_size);
>>>>>>> version 4.0.2
        m_current_state = m_init_state;
    }

    //  Creation constructor
    template <size_t InSize, size_t OutSize>
    fuzzy_machine<InSize,OutSize>::fuzzy_machine(size_t a_size)
      : m_state_table(NULL),
        m_size(a_size),
        m_init_state(0),
        m_current_state(0),
        m_output_base(1.0),
        m_output_range(100.0),
        m_state_base(1.0),
        m_state_range(100.0)
    {
        // verify parameters
        if (m_size < 2)
            throw std::runtime_error("invalid fuzzy_machine creation parameters");

        // allocate state table
        m_state_table = new tranout_t ** [m_size];

        // tables of weights for roulette wheels
        double * output_weights = new double[OutSize];
        double * state_weights  = new double[m_size];
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        for (size_t s = 0; s < m_size; ++s)
        {
            // allocate an array corresponding to inputs
            m_state_table[s] = new tranout_t * [InSize];

            for (size_t i = 0; i < InSize; ++i)
            {
                // define weights
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
                size_t n; 

                for (n = 0; n < OutSize; ++n)
                    output_weights[n] = 1.0; 
                
                output_weights[g_random.get_rand_index(OutSize)] = 100.0;

                for (n = 0; n < m_size; ++n)
                    state_weights[n] = 1.0;
                
                state_weights[g_random.get_rand_index(m_size)] = 100.0;
=======
                size_t n;

                for (n = 0; n < OutSize; ++n)
                    output_weights[n] = 1.0;

                output_weights[rand_index(OutSize)] = 100.0;

                for (n = 0; n < m_size; ++n)
                    state_weights[n] = 1.0;

                state_weights[rand_index(m_size)] = 100.0;
>>>>>>> version 4.0.2

                // set transition values
                m_state_table[s][i] = new tranout_t(state_weights,m_size,output_weights);
            }
        }
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            
=======

>>>>>>> version 4.0.2
        delete [] output_weights;
        delete [] state_weights;

        // set initial state and start there
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        m_init_state = g_random.get_rand_index(m_size);
=======
        m_init_state = rand_index(m_size);
>>>>>>> version 4.0.2
        m_current_state = m_init_state;
    }

    // Construct via bisexual crossover
    template <size_t InSize, size_t OutSize>
    fuzzy_machine<InSize,OutSize>::fuzzy_machine(const fuzzy_machine<InSize,OutSize> & a_parent1, const fuzzy_machine<InSize,OutSize> & a_parent2)
      : m_state_table(NULL),
        m_size(a_parent1.m_size),
        m_init_state(0),
        m_current_state(0),
        m_output_base(a_parent1.m_output_base),
        m_output_range(a_parent1.m_output_range),
        m_state_base(a_parent1.m_state_base),
        m_state_range(a_parent1.m_state_range)
    {
        #ifdef DEBUG
        cerr << "\n<< crossover operation >>\n";
        a_parent1.dump("PARENT1");
        a_parent2.dump("PARENT2");
        #endif

        // copy first parent
        deep_copy(a_parent1);

        // don't do anything else if fsms differ is size
        if ((a_parent1.m_size != a_parent2.m_size) || (&a_parent1 == &a_parent2))
            return;

        // pick a crossover point
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        size_t x = g_random.get_rand_index(m_size);
        
        #ifdef DEBUG
        cerr << "crossover at " << x << "\n";
        #endif
                
=======
        size_t x = rand_index(m_size);

        #ifdef DEBUG
        cerr << "crossover at " << x << "\n";
        #endif

>>>>>>> version 4.0.2
        for (size_t n = x; n < m_size; ++n)
        {
            // set transition values
            for (size_t i = 0; i < InSize; ++i)
            {
                delete m_state_table[n][i];
                m_state_table[n][i] = new tranout_t(*a_parent2.m_state_table[n][i]);
            }
        }

        // randomize the initial state (looks like mom and dad but may act like either one!)
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        if (g_random.get_rand_real2() < 0.5)
=======
        if (g_random.get_real() < 0.5)
>>>>>>> version 4.0.2
            m_init_state = a_parent1.m_init_state;
        else
            m_init_state = a_parent2.m_init_state;

        // reset for start
        m_current_state = m_init_state;
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        #ifdef DEBUG
        dump("CHILD");
        #endif
    }

    //  Copy constructor
    template <size_t InSize, size_t OutSize>
    fuzzy_machine<InSize,OutSize>::fuzzy_machine(const fuzzy_machine<InSize,OutSize> & a_source)
      : m_state_table(NULL),
        m_size(a_source.m_size),
        m_init_state(a_source.m_init_state),
        m_current_state(a_source.m_current_state),
        m_output_base(a_source.m_output_base),
        m_output_range(a_source.m_output_range),
        m_state_base(a_source.m_state_base),
        m_state_range(a_source.m_state_range)
    {
        // copy first parent
        deep_copy(a_source);
    }

    //  Virtual destructor
    template <size_t InSize, size_t OutSize>
    fuzzy_machine<InSize,OutSize>::~fuzzy_machine()
    {
        release();
    }

    //  Assignment
    template <size_t InSize, size_t OutSize>
    fuzzy_machine<InSize,OutSize> & fuzzy_machine<InSize,OutSize>::operator = (const fuzzy_machine<InSize,OutSize> & a_source)
    {
        // release resources
        release();

        // set values
        m_init_state    = a_source.m_init_state;
        m_current_state = a_source.m_current_state;
        m_size          = a_source.m_size;
        m_output_base   = a_source.m_output_base;
        m_output_range  = a_source.m_output_range;
        m_state_base    = a_source.m_state_base;
        m_state_range   = a_source.m_state_range;

        // copy source
        deep_copy(a_source);

        return *this;
    }

    //! Set a mutation weight
    template <size_t InSize, size_t OutSize>
    inline void fuzzy_machine<InSize,OutSize>::set_mutation_weight(mutation_id a_type, double a_weight)
    {
        g_selector.set_weight(a_type,a_weight);
    }
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
    
=======

>>>>>>> version 4.0.2
    //  Mutation
    template <size_t InSize, size_t OutSize>
    void fuzzy_machine<InSize,OutSize>::mutate(double a_rate)
    {
        // the number of chances for mutation is based on the number of states in the machine;
        // larger machines thus encounter more mutations
        #ifdef DEBUG
        cerr << "\n<< mutation operation >>\n";
        dump("BEFORE");
        #endif

        for (size_t n = 0; n < m_size; ++n)
        {
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            if (g_random.get_rand_real2() < a_rate)
=======
            if (g_random.get_real() < a_rate)
>>>>>>> version 4.0.2
            {
                // pick a mutation
                switch (g_selector.get_index())
                {
                    case MUTATE_OUTPUT_SYMBOL:
                    {
                        // mutate output symbol
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
                        size_t state  = g_random.get_rand_index(m_size);
                        size_t input  = g_random.get_rand_index(InSize);
                        size_t index  = g_random.get_rand_index(OutSize);
=======
                        size_t state  = rand_index(m_size);
                        size_t input  = rand_index(InSize);
                        size_t index  = rand_index(OutSize);
>>>>>>> version 4.0.2

                        #ifdef DEBUG
                        cerr << "MUTATE_OUTPUT_SYMBOL, state " << state << ", input " << input << ", index " << index << "\n";
                        #endif
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
                        
                        double new_weight = m_output_base + m_output_range * g_random.get_rand_real3();
                        m_state_table[state][input]->m_output.set_weight(index,new_weight);
                        break;
                    }    
                    case MUTATE_TRANSITION:
                    {
                        // mutate state transition
                        size_t state  = g_random.get_rand_index(m_size);
                        size_t input  = g_random.get_rand_index(InSize);
                        size_t index  = g_random.get_rand_index(m_size);
=======

                        double new_weight = m_output_base + m_output_range * g_random.get_real();
                        m_state_table[state][input]->m_output.set_weight(index,new_weight);
                        break;
                    }
                    case MUTATE_TRANSITION:
                    {
                        // mutate state transition
                        size_t state  = rand_index(m_size);
                        size_t input  = rand_index(InSize);
                        size_t index  = rand_index(m_size);
>>>>>>> version 4.0.2

                        #ifdef DEBUG
                        cerr << "MUTATE_TRANSITION, state " << state << ", input " << input << ", index " << index << "\n";
                        #endif
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
                        
                        double new_weight = m_state_base + m_state_range * g_random.get_rand_real3();
=======

                        double new_weight = m_state_base + m_state_range * g_random.get_real();
>>>>>>> version 4.0.2
                        m_state_table[state][input]->m_new_state.set_weight(index,new_weight);
                        break;
                    }
                    case MUTATE_REPLACE_STATE:
                    {
                        // select mutated state
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
                        size_t state  = g_random.get_rand_index(m_size);
=======
                        size_t state  = rand_index(m_size);
>>>>>>> version 4.0.2

                        #ifdef DEBUG
                        cerr << "REPLACE_STATE, state " << state << "\n";
                        #endif
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
                        
=======

>>>>>>> version 4.0.2
                        // allocate an array corresponding to inputs
                        delete [] m_state_table[state];
                        m_state_table[state] = new tranout_t * [InSize];

                        // tables of weights for roulette wheels
                        double * output_weights = new double[OutSize];
                        double * state_weights  = new double[m_size];

                        for (size_t i = 0; i < InSize; ++i)
                        {
                            // define weights
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
                            size_t n; 

                            for (n = 0; n < OutSize; ++n)
                                output_weights[n] = 1.0; 

                            output_weights[g_random.get_rand_index(OutSize)] = 100.0;
=======
                            size_t n;

                            for (n = 0; n < OutSize; ++n)
                                output_weights[n] = 1.0;

                            output_weights[rand_index(OutSize)] = 100.0;
>>>>>>> version 4.0.2

                            for (n = 0; n < m_size; ++n)
                                state_weights[n] = 1.0;

<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
                            state_weights[g_random.get_rand_index(m_size)] = 100.0;
=======
                            state_weights[rand_index(m_size)] = 100.0;
>>>>>>> version 4.0.2

                            // set transition values
                            m_state_table[state][i] = new tranout_t(state_weights,m_size,output_weights);
                        }

                        delete [] output_weights;
                        delete [] state_weights;

<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
                        break;                        
=======
                        break;
>>>>>>> version 4.0.2
                    }
                    case MUTATE_SWAP_STATES:
                    {
                        // swap two states (by swapping pointers)
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
                        size_t state1 = g_random.get_rand_index(m_size);
                        size_t state2;
            
                        do
                            state2 = static_cast<size_t>(g_random.get_rand_index(m_size));
                        while (state2 == state1);
                        
                        #ifdef DEBUG
                        cerr << "MUTATE_SWAP_STATES, " << state1 << " with " << state2 << "\n";
                        #endif
            
=======
                        size_t state1 = rand_index(m_size);
                        size_t state2;

                        do
                            state2 = static_cast<size_t>(rand_index(m_size));
                        while (state2 == state1);

                        #ifdef DEBUG
                        cerr << "MUTATE_SWAP_STATES, " << state1 << " with " << state2 << "\n";
                        #endif

>>>>>>> version 4.0.2
                        for (size_t i = 0; i < InSize; ++i)
                        {
                            tranout_t * temp         = m_state_table[state1][i];
                            m_state_table[state1][i] = m_state_table[state2][i];
                            m_state_table[state2][i] = temp;
                        }

                        break;
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
                    }    
=======
                    }
>>>>>>> version 4.0.2
                    case MUTATE_INIT_STATE:
                    {
                        // change initial state
                        #ifdef DEBUG
                        cerr << "MUTATE_INIT_STATE\n";
                        #endif
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
                        m_init_state  = g_random.get_rand_index(m_size);
=======
                        m_init_state  = rand_index(m_size);
>>>>>>> version 4.0.2
                        break;
                    }
                    #ifdef DEBUG
                    default:
                        cerr << "UNKNOWN MUTATION!\n";
                    #endif
                }
            }
        }
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
        // reset current state because init state may have changed
        
=======

        // reset current state because init state may have changed

>>>>>>> version 4.0.2
        m_current_state = m_init_state;
        #ifdef DEBUG
        dump("AFTER");
        #endif
    }

    //  Cause state transition
    template <size_t InSize, size_t OutSize>
    inline size_t fuzzy_machine<InSize,OutSize>::transition(size_t a_input)
    {
        // get output symbol for given input for current state
        size_t output = m_state_table[m_current_state][a_input]->m_output.get_index();

        // change to new state
        m_current_state = m_state_table[m_current_state][a_input]->m_new_state.get_index();

        // return output symbol
        return output;
    }

    //  Reset to start-up state
    template <size_t InSize, size_t OutSize>
    inline void fuzzy_machine<InSize,OutSize>::reset()
    {
        m_current_state = m_init_state;
    }

    // Get size
    template <size_t InSize, size_t OutSize>
    inline size_t fuzzy_machine<InSize,OutSize>::size() const
    {
        return m_size;
    }

    //  Get a copy of the internal table
    template <size_t InSize, size_t OutSize>
    inline const typename fuzzy_machine<InSize,OutSize>::tranout_t & fuzzy_machine<InSize,OutSize>::get_transition(size_t a_state, size_t a_input) const
    {
        return *m_state_table[a_state][a_input];
    }

    // Get number of input states
    template <size_t InSize, size_t OutSize>
    inline size_t fuzzy_machine<InSize,OutSize>::num_input_states() const
    {
        return InSize;
    }

    // Get number of output states
    template <size_t InSize, size_t OutSize>
    inline size_t fuzzy_machine<InSize,OutSize>::num_output_states() const
    {
        return OutSize;
    }
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
    //  Get initial state
    template <size_t InSize, size_t OutSize>
    inline size_t fuzzy_machine<InSize,OutSize>::init_state() const
    {
        return m_init_state;
    }

    //  Get current state
    template <size_t InSize, size_t OutSize>
    inline size_t fuzzy_machine<InSize,OutSize>::current_state() const
    {
        return m_current_state;
    }
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
    
=======

>>>>>>> version 4.0.2
    #ifdef DEBUG
    template <size_t InSize, size_t OutSize>
    void fuzzy_machine<InSize,OutSize>::dump(const char * description, ostream & a_stream) const
    {
        a_stream << "----------\nDumping machine " << description << " (" << hex << this
                 << ")\ninitial state = " << m_init_state
                 << "\ncurrent state = " << m_current_state << "\n\n";
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
        for (size_t s = 0; s < m_size; ++s)
        {
            a_stream << "state " << s;
            
            for (size_t i = 0; i < InSize; ++i)
            {
                size_t n;
                
                a_stream << "\n  output weights:";
                
=======

        for (size_t s = 0; s < m_size; ++s)
        {
            a_stream << "state " << s;

            for (size_t i = 0; i < InSize; ++i)
            {
                size_t n;

                a_stream << "\n  output weights:";

>>>>>>> version 4.0.2
                for (n = 0; n < OutSize; ++n)
                    a_stream << " " << m_state_table[s][i]->m_output.get_weight(n);

                a_stream << "\n  state  weights:";
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
                
                for (n = 0; n < m_size; ++n)
                    a_stream << " " << m_state_table[s][i]->m_new_state.get_weight(n);
                
                a_stream << endl;
            }
        }
        
        a_stream << "----------" << endl;
    }
    #endif    
=======

                for (n = 0; n < m_size; ++n)
                    a_stream << " " << m_state_table[s][i]->m_new_state.get_weight(n);

                a_stream << endl;
            }
        }

        a_stream << "----------" << endl;
    }
    #endif
>>>>>>> version 4.0.2
};

#endif
