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

#if !defined(LIBEVOCOSM_LISTENER_H)
#define LIBEVOCOSM_LISTENER_H

// Standard C++ Library
#include <string>
#include <iostream>
#include <iomanip>
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
#include <vector>
=======
>>>>>>> version 4.0.2

// Windows
#if defined(_MSC_VER)
#include "windows.h"
#undef max
#undef min
#endif

<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
using std::vector;

=======
>>>>>>> version 4.0.2
namespace libevocosm
{
    template<typename T> class population;

    //! An abstract interface defining a listener
    /*!
        Evocosm reports its activities through a listener object derived from this abstract
        class. Some events state that a given event has occurred (e.g., the beginning of a new
        generation), while others provide text for display.
    */
    template <typename OrganismType>
    class listener
    {
        public:
            //! Ping that a generation begins
            /*!
                Ping that processing a generation begins.
                \param a_population Population before this generation's evolution
                \param a_iteration One-based number of the generation begun
            */
            virtual void ping_generation_begin(const vector<OrganismType> & a_population, size_t a_iteration) = 0;

            //! Ping that a generation ends
            /*!
                Ping that processing a generation has ended.
                \param a_population Population for which processing has ended
                \param a_iteration One-based number of the generation ended
            */
            virtual void ping_generation_end(const vector<OrganismType> & a_population, size_t a_iteration) = 0;

            //! Ping that a test run begins
            /*!
                Ping that fitness testing of an organism begins.
                \param a_organism_number One-based number of the organism
            */
            virtual void ping_fitness_test_begin(const OrganismType & a_organism_number) = 0;

            //! Ping that a test run ends
            /*!
                Ping that processing a generation has ended.
                \param a_organism_number One-based number of the organism
            */
            virtual void ping_fitness_test_end(const OrganismType & a_organism_number) = 0;

            //! Report non-specific text
            /*!
                This event provide status text specific to a given type of
                evocosm. The base <code>evocosm</code> class does not call this function. The
                intention is that this function will be called from classes
                derived from <code>evocosm</code> to report progress, statistics, or other
                useful information.
                \param a_text Application-specific text
            */
            virtual void report(const std::string & a_text) = 0;

            //! Send error message
            /*!
                This event provides error text specific to a given type of
                evocosm. The base <code>evocosm</code> class does not call this function. The
                intention is that this function will be called from classes
                derived from <code>evocosm</code> to report problems.
                \param a_text Application-specific error text
            */
            virtual void report_error(const std::string & a_text) = 0;

            //! Evocosm is finished
            /*!
                Invoked when an evocosm finishes all processing. This way God can
                rest on the seventh day.
            */
            virtual void run_complete(const vector<OrganismType> & a_population) = 0;
    };

    //! An listener implementation that ignores all events
    /*!
        This listener ignores anything it hears.
    */
    template <typename OrganismType>
    class null_listener : public listener<OrganismType>
    {
        public:
            //! Ping that a generation begins
            /*!
                Ping that processing a generation begins.
                \param a_population Population before this generation's evolution
                \param a_iteration One-based number of the generation begun
            */
            virtual void ping_generation_begin(const vector<OrganismType> & a_population, size_t a_iteration)
            {
                // do nothing
            }

            //! Ping that a generation ends
            /*!
                Ping that processing a generation has ended.
                \param a_population population for which processing has ended
                \param a_iteration One-based number of the generation ended
            */
            virtual void ping_generation_end(const vector<OrganismType> & a_population, size_t a_iteration)
            {
                // do nothing
            }

            //! Ping that a test run begins
            /*!
                Ping that fitness testing of an organism begins.
                \param a_organism_number One-based number of the organism
            */
            virtual void ping_fitness_test_begin(const OrganismType & a_organism_number)
            {
                // do nothing
            }

            //! Ping that a test run ends
            /*!
                Ping that processing a generation has ended.
                \param a_organism_number One-based number of the organism
            */
            virtual void ping_fitness_test_end(const OrganismType & a_organism_number)
            {
                // do nothing
            }

            //! Report non-specific text
            /*!
                This event provide status text specific to a given type of
                evocosm. The base <code>evocosm</code> class does not call this function. The
                intention is that this function will be called from classes
                derived from <code>evocosm</code> to report progress, statistics, or other
                useful information.
                \param a_text Application-specific text
            */
            virtual void report(const std::string & a_text)
            {
                // do nothing
            }

            //! Send error message
            /*!
                This event provides error text specific to a given type of
                evocosm. The base <code>evocosm</code> class does not call this function. The
                intention is that this function will be called from classes
                derived from <code>evocosm</code> to report problems.
                \param a_text Application-specific error text
            */
            virtual void report_error(const std::string & a_text)
            {
                // do nothing
            }

            //! Evocosm is finished
            /*!
                Invoked when an evocosm finishes all processing. This way God can
                rest on the seventh day.
            */
            virtual void run_complete(const vector<OrganismType> & a_population)
            {
                // do nothing
            }
    };

}

#endif
