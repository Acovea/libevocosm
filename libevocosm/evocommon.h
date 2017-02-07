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
        }

        //! Set the seed for the random number generator
        static uint32_t get_seed()
        {
            return g_random.get_seed();
        }
        
        //! Get version number
        static std::string version()
        {
            return g_version;
        }
    };
    
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
    
}

#endif
