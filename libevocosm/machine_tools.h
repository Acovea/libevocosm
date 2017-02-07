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

#if !defined(LIBEVOCOSM_FSM_TOOLS_H)
#define LIBEVOCOSM_FSM_TOOLS_H

// libevocosm
#include "roulette.h"

namespace libevocosm
{
    //! A set of common tools for finite state machines
    /*!
        A set of common tools for finite state machines.
    */
    class machine_tools
    {
    protected:
        //! Types of mutation supported
        enum mutation_id
        {
            MUTATE_OUTPUT_SYMBOL, //!< Mutate an output symbol
            MUTATE_TRANSITION,    //!< Mutate a state transition
            MUTATE_REPLACE_STATE, //!< Replace a new state with a randomly-generated one
            MUTATE_SWAP_STATES,   //!< Swap two states
            MUTATE_INIT_STATE     //!< Mutate that initial state
        };

        //! Wraps a roulette wheel for selecting mutations
        /*!
            This class encapsulates a roulette wheel for selecting mutations.
            By default, the <i>simple_fsm::mutate</i> operator uses a pre-defined
            <i>mutation_selector</i> with default percentages of:

            - 20% MUTATE_OUTPUT_SYMBOL
            - 20% MUTATE_TRANSITION
            - 20% MUTATE_REPLACE_STATE
            - 20% MUTATE_SWAP_STATES
            - 20% MUTATE_INIT_STATE

            The default values were chosen based on my past experience. You can
            define your own <i>mutation_selector</i> with different weights,
            and pass it to <i>simple_fsm::mutate</i>.
            \sa roulette_wheel
        */
        class mutation_selector
        {
        public:
            //! Creation constructor
            /*!
                Constructs a new mutation_selector with the default weights
                for the roulette wheel.
            */
            mutation_selector()
              : m_selector(NULL)
            {
                static const double default_weights [] = { 20.0, 20.0, 20.0, 20.0, 20.0 };

                m_selector = new roulette_wheel(default_weights,5);
            }

            //! Copy constructor
            /*!
                Creates a copy of an existing object.
                \param a_source - The source object to be copied
            */
            mutation_selector(const mutation_selector & a_source)
              : m_selector(new roulette_wheel(*a_source.m_selector))
            {
                // nada
            }

            //! Destructor
            /*!
                Destroys a mutation selector, freeing resources.
            */
            ~mutation_selector()
            {
                delete m_selector;
            }

            //! Assignment operator
            /*!
                Assigns the state of one mutation selector to another.
                \param a_source - The source object
            */
            mutation_selector & operator = (const mutation_selector & a_source)
            {
                m_selector = new roulette_wheel(*a_source.m_selector);
                return *this;
            }

            //! Change a given weight
            /*!
                Changes a specific mutation weight to a new value.
                \param a_type - Identifies the specific mutation weight to be set
                \param a_new_weight - New weight to be assigned
            */
            void set_weight(mutation_id a_type, double & a_new_weight)
            {
                m_selector->set_weight(a_type,a_new_weight);
            }

            //! Get a mutation index
            /*
                Returns an index, shosen by roulette wheel, corresponding to a
                <i>mutation_id</i> value.
                \return A mutation_id index
            */
            size_t get_index() const
            {
                return m_selector->get_index();
            }

        private:
            // The actual roulette wheel
            roulette_wheel * m_selector;
        };
    };
}

#endif
