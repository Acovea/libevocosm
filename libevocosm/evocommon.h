<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  Evocosm -- An Object-Oriented Framework for Evolutionary Algorithms
//
//  evocommon.h
//---------------------------------------------------------------------
//
//  Copyright 1996-2005 Scott Robert Ladd
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

#if !defined(LIBEVOCOSM_EVOGLOBAL_H)
#define LIBEVOCOSM_EVOGLOBAL_H

// Standard C++ Library
#include <string>
#include <iostream>
#include <iomanip>
#if !defined(_MSC_VER)
   #include <unistd.h>
#endif
// libcoyotl
#include "libcoyotl/mtwister.h"

namespace libevocosm
{
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

#if !defined(LIBEVOCOSM_EVOCOMMON_H)
#define LIBEVOCOSM_EVOCOMMON_H

// Brahe library
#include "libbrahe/prng.h"

// Standard C++ Library
#include <string>

namespace libevocosm
{
    //! The random number generator used by Evocosm
    /*!
        This class encapsulates the random number generator used by the
        Evocosm classes.
    */
    class prng
    {
    private:
        brahe_prng_state_t m_random;

    public:
        //! Constructor
        prng()
        {
            brahe_prng_init(&m_random,BRAHE_PRNG_MWC1038,0);
        }

        //! Destructor
        ~prng()
        {
            brahe_prng_free(&m_random);
        }

        //! Set the seed for the random number generator
        void set_seed(uint32_t a_seed)
        {
            brahe_prng_init(&m_random,BRAHE_PRNG_MWC1038,a_seed);
        }

        //! get seed value
        uint32_t get_seed()
        {
            return m_random.m_seed;
        }

        //! get a random index value
        size_t get_index(size_t n)
        {
            return brahe_prng_index(&m_random,n);
        }

        //! get the next value in the range [0,1)
        double get_real()
        {
            return brahe_prng_real2(&m_random);
        }
    };

>>>>>>> version 4.0.2
    //! Elements shared by all classes in Evocosm
    /*!
        All Evocosm classes are derived from this class, a singleton for shared
        attributes.
    */
    class globals
    {
    protected:
        //! Static function to allow use of g_random function pointer in random_shuffle
        static size_t rand_index(size_t n)
        {
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            return g_random.get_rand_index(n);
        }

        //! A shared random number generator
        static libcoyotl::mtwister g_random;
        
        //! Version number
        static std::string g_version;
        
    public:        
        //! Set the seed for the random number generator
        static void set_random_seed(uint32_t a_seed)
        {
            g_random.init(a_seed);
=======
            return g_random.get_index(n);
        }

        //! A shared random number generator
        static prng g_random;

        //! Version number
        static std::string g_version;

    public:
        //! Set the seed for the random number generator
        static void set_seed(uint32_t a_seed)
        {
            g_random.set_seed(a_seed);
>>>>>>> version 4.0.2
        }

        //! Set the seed for the random number generator
        static uint32_t get_seed()
        {
            return g_random.get_seed();
        }
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        //! Get version number
        static std::string version()
        {
            return g_version;
        }
    };
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
    
    //! An abstract interface defining a listener
    /*!
        Evocosm reports its activities through a listener object derived from this abstract
        class. Some events state that a given event has occurred (e.g., the beginning of a new
        generation), while others provide text for display.
    */
    class listener
    {
        public:
            //! Ping that a generation begins
            /*!
                Ping that processing a generation begins.
                \param a_generation_number One-based number of the generation begun
            */
            virtual void ping_generation_begin(size_t a_generation_number) = 0;
        
            //! Ping that a generation ends
            /*!
                Ping that processing a generation has ended.
                \param a_generation_number One-based number of the generation ended
            */
            virtual void ping_generation_end(size_t a_generation_number) = 0;
        
            //! Ping that a population begins
            /*!
                Ping that processing a population begins.
                \param a_population_number One-based number of the population begun
            */
            virtual void ping_population_begin(size_t a_population_number) = 0;
            
            //! Ping that a population ends
            /*!
                Ping that processing a population has ended.
                \param a_population_number One-based number of the population ended
            */
            virtual void ping_population_end(size_t a_population_number) = 0;
            
            //! Ping that a test run begins
            /*!
                Ping that fitness testing of an organism begins.
                \param a_organism_number One-based number of the organism
            */
            virtual void ping_fitness_test_begin(size_t a_organism_number) = 0;
            
            //! Ping that a test run ends
            /*!
                Ping that processing a generation has ended.
                \param a_organism_number One-based number of the organism
            */
            virtual void ping_fitness_test_end(size_t a_organism_number) = 0;
            
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
            virtual void run_complete() = 0;
            
            //! Yield
            /*!
                Evocosm periodically invokes this function to allow other processes
                to run. In most cases, this will be some sort of platform-specific
                sleep function, such as usleep.
            */
            virtual void yield() = 0;
    };
    
    //! An listener implementation that ignores all events
    /*!
        This listener ignores anything it hears.
    */
    class null_listener : public listener
    {
        public:
            //! Ping that a generation begins
            /*!
                Ping that processing a generation begins.
                \param a_generation_number One-based number of the generation begun
            */
            virtual void ping_generation_begin(size_t a_generation_number)
            {
                // do nothing
            }
        
            //! Ping that a generation ends
            /*!
                Ping that processing a generation has ended.
                \param a_generation_number One-based number of the generation ended
            */
            virtual void ping_generation_end(size_t a_generation_number)
            {
                // do nothing
            }
        
            //! Ping that a population begins
            /*!
                Ping that processing a population begins.
                \param a_population_number One-based number of the population begun
            */
            virtual void ping_population_begin(size_t a_population_number)
            {
                // do nothing
            }
            
            //! Ping that a population ends
            /*!
                Ping that processing a population has ended.
                \param a_population_number One-based number of the population ended
            */
            virtual void ping_population_end(size_t a_population_number)
            {
                // do nothing
            }
            
            //! Ping that a test run begins
            /*!
                Ping that fitness testing of an organism begins.
                \param a_organism_number One-based number of the organism
            */
            virtual void ping_fitness_test_begin(size_t a_organism_number)
            {
                // do nothing
            }
            
            //! Ping that a test run ends
            /*!
                Ping that processing a generation has ended.
                \param a_organism_number One-based number of the organism
            */
            virtual void ping_fitness_test_end(size_t a_organism_number)
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
            virtual void run_complete()
            {
                // do nothing
            }
            
            //! Yield
            /*!
                Evocosm periodically invokes this function to allow other processes
                to run. In most cases, this will be some sort of platform-specific
                sleep function, such as usleep.
            */
            virtual void yield()
            {
                // do nothing
            }
    };
    
    //! An listener implementation that ignores all events
    /*!
        This listener displays information about events to stdout
        (standard ouput).
    */
    class listener_stdout : public listener
    {
        public:
            //! Ping that a generation begins
            /*!
                Ping that processing a generation begins.
                \param a_generation_number One-based number of the generation begun
            */
            virtual void ping_generation_begin(size_t a_generation_number)
            {
                std::cout << "------------------------------------------------------------\ngeneration "
                          << a_generation_number << " begins" << std::endl;
            }

            //! Ping that a generation ends
            /*!
                Ping that processing a generation has ended.
                \param a_generation_number One-based number of the generation ended
            */
            virtual void ping_generation_end(size_t a_generation_number)
            {
                // nada
            }

            //! Ping that a population begins
            /*!
                Ping that processing a population begins.
                \param a_population_number One-based number of the population begun
            */
            virtual void ping_population_begin(size_t a_population_number)
            {
                std::cout << "\npopulation " << std::setw(2) << a_population_number << ": " << std::flush;
            }

            //! Ping that a population ends
            /*!
                Ping that processing a population has ended.
                \param a_population_number One-based number of the population ended
            */
            virtual void ping_population_end(size_t a_population_number)
            {
                // nada
            }

            //! Ping that a test run begins
            /*!
                Ping that fitness testing of an organism begins.
                \param a_organism_number One-based number of the organism
            */
            virtual void ping_fitness_test_begin(size_t a_organism_number)
            {
                // nada
            }

            //! Ping that a test run ends
            /*!
                Ping that processing a generation has ended.
                \param a_organism_number One-based number of the organism
            */
            virtual void ping_fitness_test_end(size_t a_organism_number)
            {
                std::cout << "." << std::flush;
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
                std::cout << a_text;
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
                std::cerr << a_text;
            }

            //! Evocosm is finished
            /*!
                Invoked when an evocosm finishes all processing. This way God can
                rest on the seventh day.
            */
            virtual void run_complete()
            {
                // nada
            }

            //! Yield
            /*!
                Evocosm periodically invokes this function to allow other processes
                to run. In most cases, this will be some sort of platform-specific
                sleep function, such as usleep.
            */
            virtual void yield()
            {
                usleep(50000);
            }
    };
    
=======

>>>>>>> version 4.0.2
}

#endif
