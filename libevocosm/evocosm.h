<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  Evocosm -- An Object-Oriented Framework for Evolutionary Algorithms
//
//  evocosm.h
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

#if !defined(LIBEVOCOSM_EVOCOSM_H)
#define LIBEVOCOSM_EVOCOSM_H

#if defined(_MSC_VER)
#pragma warning (disable : 4786)
#else
   #include <unistd.h>
#endif

#if defined(_OPENMP)
#include <omp.h>
#endif

// Standard C++ library
#include <vector>

<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
// libcoyotl
#include "libcoyotl/validator.h"

// libevocosm
=======
// libevocosm
#include "validator.h"
#include "listener.h"
>>>>>>> version 4.0.2
#include "organism.h"
#include "landscape.h"
#include "mutator.h"
#include "reproducer.h"
#include "scaler.h"
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
#include "migrator.h"
#include "selector.h"
#include "reporter.h"

//! A toolkit and framework for implementing evolutionary algorithms.
/*!
    Evocosm is a set of classes that abstract the fundamental components of an
=======
#include "selector.h"
#include "analyzer.h"

//! A toolkit and framework for implementing evolutionary algorithms.
/*!
    Evocosm classes abstract the fundamental components of an
>>>>>>> version 4.0.2
    evolutionary algorithm. Evolutionary algorithms come in a variety of shapes
    and flavors, but at their core, they all share certain characteristics:
    populations that reproduce and mutate through a series of generations,
    producing future generations based on some measure of fitness. An amazing
    variety of algorithms can be built on that general framework, which lead
    me to construct a set of core classes as the basis for future applications.
*/
namespace libevocosm
{
    using std::vector;
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
    
    //! Interface for an organism factory
    /*!
        Defines an interface for a class implementing an organism factory.
        \param OrganismType The type of organism generated by this factory.
    */
    template <class OrganismType>
    class organism_factory
    {
    public:
        //! Organism factory
        /*!
            Generates a  single organism.
        */
        virtual OrganismType create() = 0;
    
        //! Organism population factory
        /*!
            Appends new organisms to a population.
        */
        virtual void append(vector<OrganismType> & a_population, size_t a_size) = 0;
    };

    //! Interface for a landscape factory
    /*!
        Defines an interface for a class implementing a landscape factory.
        \param LandscapeType The type of landscape generated by this factory.
    */
    template <class LandscapeType>
    class landscape_factory
    {
    public:
        //! Landscape factory
        /*!
            Generates landscapes for an evocosm. I called this funtion "generate"
            to avoid collisions with the "create" method in organism_factory.
        */
        virtual LandscapeType generate() = 0;
    };
=======
>>>>>>> version 4.0.2

    //! Associates organisms with the components of an evolutionary system.
    /*!
        This is where it all comes together: An evocosm binds a
        evocosm of organisms to a set of objects that define how
        those organisms evolve.
        \param OrganismType - The type of organism
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        \param LandscapeType - The type of landscape
    */
    template <class OrganismType, class LandscapeType>
    class evocosm : protected globals
    {
    protected:
        //! A listener for evocosm progress
        listener &                 m_listener;
            
        //! The initial evocosm size
        size_t                     m_population_size;

        //! The populations of organisms
        vector< vector<OrganismType> > m_populations;

        //! The number of populations
        size_t                     m_number_of_populations;

        //! The number of fitness landscapes unique to individual populations
        size_t                     m_number_of_unique_landscapes;

        //! The number of fitness landscapes common to all populations
        size_t                     m_number_of_common_landscapes;

        //! Fitness landscapes unique to individual populations
        vector< vector<LandscapeType> > m_unique_landscapes;

        //! Fitness landscapes common to all populations
        vector<LandscapeType>      m_common_landscapes;
        
        //! A mutator to randomly influence genes
        mutator<OrganismType>    & m_mutator;
=======
    */
    template <class OrganismType>
    class evocosm : protected globals
    {
    protected:
        //! The populations of organisms
        vector<OrganismType> & m_population;

        //! Fitness landscapes common to all populations
        landscape<OrganismType> & m_landscape;

        //! A mutator to randomly influence genes
        mutator<OrganismType> & m_mutator;
>>>>>>> version 4.0.2

        //! Creates new organisms
        reproducer<OrganismType> & m_reproducer;

        //! Scales the fitness of the evocosm
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        scaler<OrganismType>     & m_scaler;

        //! Handles emigration and immigration
        migrator<OrganismType>   & m_migrator;

        //! Selects organisms that survive from one generation to the next
        selector<OrganismType>   & m_selector;

        //! Reports the a evocosm for analysis or display
        reporter<OrganismType,LandscapeType> & m_reporter;
        
        //! Count of iterations made
        size_t                     m_iteration;
        
        //! Set true when minimizing; i.e., best fitness < worst fitness
        bool                       m_minimizing;
        
        //! termination flag
        bool                       m_running;
=======
        scaler<OrganismType> & m_scaler;

        //! Selects organisms that survive from one generation to the next
        selector<OrganismType> & m_selector;

        //! Reports the a evocosm for analysis or display
        analyzer<OrganismType> & m_analyzer;

        //! A listener for evocosm progress
        listener<OrganismType> & m_listener;

        //! Count of iterations made
        size_t m_iteration;

        //! Number microseconds for process to sleep on yield
        unsigned int m_sleep_time;
>>>>>>> version 4.0.2

    public:
        //! Creation constructor
        /*!
            Creates a new evocosm. Think of an evocosm as a director, a tool for
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            associating organisms with their environment.
            Note that these arguments are modifiable references, and that the
            referenced objects must continue to exist during the lifetime of the
            evocosm.
            \param a_listener - a listener for events
            \param a_population_size - Initial population size
            \param a_number_of_populations - Number of organisms in each population 
            \param a_number_of_unique_landscapes - Number of landscapes unique to each populations
            \param a_number_of_common_landscapes - Number of landscapes common to all populations
            \param a_mutator - A concrete implementation of mutator
            \param a_reproducer - A concrete implementation of reproducer
            \param a_scaler - A concrete implementation of scaler
            \param a_migrator - A concrete implementation of migrator
            \param a_selector - A concrete implementation of selector
            \param a_reporter - A concrete implementation of reporter
            \param a_organism_factory - A factory to create organisms
            \param a_landscape_factory - A factory to create landscapes
            \param a_minimizing - Set true when minimizing; i.e., best fitness &lt; worst fitness
        */
        evocosm(listener &                 a_listener,
                size_t                     a_population_size,
                size_t                     a_number_of_populations,
                size_t                     a_number_of_unique_landscapes,
                size_t                     a_number_of_common_landscapes,
                mutator<OrganismType>    & a_mutator,
                reproducer<OrganismType> & a_reproducer,
                scaler<OrganismType>     & a_scaler,
                migrator<OrganismType>   & a_migrator,
                selector<OrganismType>   & a_selector,
                reporter<OrganismType,LandscapeType> & a_reporter,
                organism_factory<OrganismType>   & a_organism_factory,
                landscape_factory<LandscapeType> & a_landscape_factory,
                bool                       a_minimizing = false);
=======
            associating organisms with their landscape.
            Note that these arguments are modifiable references, and that the
            referenced objects must continue to exist during the lifetime of the
            evocosm.
            \param a_population Initial population of organisms
            \param a_landscape Initial set of landscaoes for testing organism fitness
            \param a_mutator - A concrete implementation of mutator
            \param a_reproducer - A concrete implementation of reproducer
            \param a_scaler - A concrete implementation of scaler
            \param a_selector - A concrete implementation of selector
            \param a_analyzer - A concrete implementation of analyzer
            \param a_listener - a listener for events
        */
        evocosm(vector<OrganismType> &     a_population,
                landscape<OrganismType> &  a_landscape,
                mutator<OrganismType> &    a_mutator,
                reproducer<OrganismType> & a_reproducer,
                scaler<OrganismType> &     a_scaler,
                selector<OrganismType> &   a_selector,
                analyzer<OrganismType> &   a_analyzer,
                listener<OrganismType> &   a_listener);
>>>>>>> version 4.0.2

        //! Copy constructor
        /*!
            Creates a new evocosm identical to an existing one.
            \param a_source - The source object
        */
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        evocosm(const evocosm<OrganismType, LandscapeType> & a_source);
=======
        evocosm(const evocosm<OrganismType> & a_source);
>>>>>>> version 4.0.2

        //! Virtual destructor
        /*!
            A virtual destructor. By default, it does nothing; this is
            a placeholder that identifies this class as a potential base,
            ensuring that objects of a derived class will have their
            destructors called if they are destroyed through a base-class
            pointer.
        */
        virtual ~evocosm();

        //! Assignment operator
        /*!
            Assigns an existing object the state of another.
            \param a_source - The source object
            \return Reference to target object
        */
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        evocosm & operator = (const evocosm<OrganismType, LandscapeType> & a_source);
=======
        evocosm & operator = (const evocosm<OrganismType> & a_source);
>>>>>>> version 4.0.2

        //! Compute next generation
        /*!
            A generation represents a cycle in the life of an evocosm; this
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            function performs one sequence of fitness testing & scaling,        void append(vector<gccga_organism> a_population, size_t a_size);

            reporting, migration, breeding, and mutation. This method can be
            replaced by in a derived class to define a different processing
            sequence; the default sequence defined here is good for most
            evolutionary algorithms I've created.
            \return Returns <i>false</i> when the generation has reached a specific goal.
        */
        virtual bool run_generation(bool a_finished, double & a_fitness);
=======
            function performs one sequence of fitness testing & scaling,
            reporting, breeding, and mutation. This method can be
            replaced by in a derived class to define a different processing
            sequence; the default sequence defined here is good for most
            evolutionary algorithms I've created.
            \return Returns <i>true</i> when the generation has reached a specific goal.
        */
        virtual bool run_generation();
>>>>>>> version 4.0.2

        //! Directly view population
        /*! <b>Use with caution!</b> This function provides direct read-write
            access to an evocosm's population. This is necessary when the
            organisms need special manipulation, such as when they can not be
            randomized by a default constructor.
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            \param a_index Number of the population to return; defaults to 0 .
        */
        vector<OrganismType, LandscapeType> & population(size_t a_index = 0)
        {
            return m_populations[a_index];
        }
        
        //! Terminate this run
        /*! Calling this function sets a flag that tells the evocosm to stop running
            as soon as possible.
        */
        void terminate()
        {
            m_running = false;
        }
    };

    // constructors
    template <class OrganismType, class LandscapeType>
    evocosm<OrganismType, LandscapeType>::evocosm(listener &                 a_listener,
                                                  size_t                     a_population_size,
                                                  size_t                     a_number_of_populations,
                                                  size_t                     a_number_of_unique_landscapes,
                                                  size_t                     a_number_of_common_landscapes,
                                                  mutator<OrganismType>    & a_mutator,
                                                  reproducer<OrganismType> & a_reproducer,
                                                  scaler<OrganismType>     & a_scaler,
                                                  migrator<OrganismType>   & a_migrator,
                                                  selector<OrganismType>   & a_selector,
                                                  reporter<OrganismType, LandscapeType> & a_reporter,
                                                  organism_factory<OrganismType>   & a_organism_factory,
                                                  landscape_factory<LandscapeType> & a_landscape_factory,
                                                  bool                       a_minimizing)
      : m_listener(a_listener),
        m_population_size(a_population_size),
        m_populations(),
        m_number_of_populations(a_number_of_populations),
        m_number_of_unique_landscapes(a_number_of_unique_landscapes),
        m_number_of_common_landscapes(a_number_of_common_landscapes),
        m_unique_landscapes(),
        m_common_landscapes(),
        m_mutator(a_mutator),
        m_reproducer(a_reproducer),
        m_scaler(a_scaler),
        m_migrator(a_migrator),
        m_selector(a_selector),
        m_reporter(a_reporter),
        m_iteration(0),
        m_minimizing(a_minimizing),
        m_running(true)
    {
        // adjust evocosm size if necessary
        libcoyotl::enforce_lower_limit(m_population_size,size_t(1));
        libcoyotl::enforce_lower_limit(m_number_of_populations,size_t(1));

        // calculate number of common and unique landscapes
        if ((m_number_of_unique_landscapes < 1) && (m_number_of_common_landscapes == 0))
            m_number_of_unique_landscapes = 1;
        
        a_landscape_factory.generate();
        
        // allocate vectors of landscapes
        for (size_t n = 0; n < m_number_of_common_landscapes; ++n)
            m_common_landscapes.push_back(a_landscape_factory.generate());

        // create initial populations
        m_unique_landscapes.resize(m_number_of_populations);
        m_populations.resize(m_number_of_populations);
        
        for (size_t p = 0; p < m_number_of_populations; ++p)
        {
            // add organisms to populations
            a_organism_factory.append(m_populations[p], m_population_size);
            
            // create unique landscapes for this population
            for (size_t n = 0; n < m_number_of_unique_landscapes; ++n)
                m_unique_landscapes[p].push_back(a_landscape_factory.generate());
        }
    }

    // copy constructor
    template <class OrganismType, class LandscapeType>
    evocosm<OrganismType, LandscapeType>::evocosm(const evocosm<OrganismType, LandscapeType> & a_source)
      : m_population_size(a_source.m_population_size),
        m_populations(a_source.m_populations),
        m_number_of_populations(a_source.m_number_of_populations),
        m_number_of_common_landscapes(a_source.m_number_of_common_landscapes),
        m_number_of_unique_landscapes(a_source.m_number_of_unique_landscapes),
        m_common_landscapes(a_source.m_common_landscapes),
        m_unique_landscapes(a_source.m_unique_landscapes),
        m_mutator(a_source.m_mutator),
        m_reproducer(a_source.m_reproducer),
        m_scaler(a_source.m_scaler),
        m_migrator(a_source.m_migrator),
        m_selector(a_source.m_selector),
        m_iteration(a_source.m_iteration)
=======
        */
        vector<OrganismType> & get_population()
        {
            return m_population;
        }

        //! Get the sleep time property value
        /*!
            Get the sleep time setting for this listerner.
            /return current value of sleep time (microseconds)
        */
        unsigned int get_sleep_time()
        {
            return m_sleep_time;
        }

        //! Set the sleep time property value
        /*!
            Set the sleep time property value.
            /param a_sleep_time new value of sleep time (microseconds)
        */
        void set_sleep_time(unsigned int a_sleep_time)
        {
            m_sleep_time = a_sleep_time;
        }

    protected:
        //! Yield
        /*!
            Evocosm periodically invokes this function to allow other processes
            to run. In most cases, this will be some sort of platform-specific
            sleep function, such as usleep.
        */
        void yield()
        {
            if (m_sleep_time > 0)
            {
              #if defined(_MSC_VER)
                Sleep(m_sleep_time);
              #else
                usleep((useconds_t)m_sleep_time);
              #endif
            }
        }

    };

    // constructors
    template <class OrganismType>
    evocosm<OrganismType>::evocosm(vector<OrganismType> &     a_population,
                                   landscape<OrganismType> &  a_landscape,
                                   mutator<OrganismType> &    a_mutator,
                                   reproducer<OrganismType> & a_reproducer,
                                   scaler<OrganismType> &     a_scaler,
                                   selector<OrganismType> &   a_selector,
                                   analyzer<OrganismType> &   a_analyzer,
                                   listener<OrganismType> &   a_listener)
      : m_population(a_population),
        m_landscape(a_landscape),
        m_mutator(a_mutator),
        m_reproducer(a_reproducer),
        m_scaler(a_scaler),
        m_selector(a_selector),
        m_analyzer(a_analyzer),
        m_listener(a_listener),
        m_iteration(0),
        m_sleep_time(10000) // default to 10ms sleep time
    {
        // nada
    }

    // copy constructor
    template <class OrganismType>
    evocosm<OrganismType>::evocosm(const evocosm<OrganismType> & a_source)
      : m_population(a_source.a_population),
        m_landscape(a_source.m_landscape),
        m_mutator(a_source.m_mutator),
        m_reproducer(a_source.m_reproducer),
        m_scaler(a_source.m_scaler),
        m_selector(a_source.m_selector),
        m_analyzer(a_source.m_analyzer),
        m_listener(a_source.m_listener),
        m_iteration(a_source.m_iteration),
        m_sleep_time(a_source.m_sleep_time)
>>>>>>> version 4.0.2
    {
        // nada
    }

    // destructor
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
    template <class OrganismType, class LandscapeType>
    evocosm<OrganismType, LandscapeType>::~evocosm()
=======
    template <class OrganismType>
    evocosm<OrganismType>::~evocosm()
>>>>>>> version 4.0.2
    {
        // nada
    }

    // assignment operator
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
    template <class OrganismType, class LandscapeType>
    evocosm<OrganismType, LandscapeType> & evocosm<OrganismType, LandscapeType>::operator = (const evocosm<OrganismType, LandscapeType> & a_source)
    {
        m_population_size       = a_source.m_population_size;
        m_populations           = a_source.m_populations;
        m_number_of_populations = a_source.m_number_of_populations;

        m_number_of_common_landscapes = a_source.m_number_of_common_landscapes;
        m_number_of_unique_landscapes = a_source.m_number_of_unique_landscapes;
        m_common_landscapes           = a_source.m_common_landscapes;
        m_unique_landscapes           = a_source.m_unique_landscapes;
                
        m_mutator     = a_source.m_mutator;
        m_reproducer  = a_source.m_reproducer;
        m_scaler      = a_source.m_scaler;
        m_migrator    = a_source.m_migrator;
        m_selector    = a_source.m_selector;
        
        m_iteration   = a_source.m_iteration;
=======
    template <class OrganismType>
    evocosm<OrganismType> & evocosm<OrganismType>::operator = (const evocosm<OrganismType> & a_source)
    {
        m_population  = a_source.m_population;
        m_landscape   = a_source.m_landscape;
        m_scaler      = a_source.m_scaler;
        m_analyzer    = a_source.m_analyzer;
        m_listener    = a_source.m_analyzer;
        m_iteration   = a_source.m_iteration;
        m_sleep_time  = a_source.m_sleep_time;
>>>>>>> version 4.0.2

        return *this;
    }

    // compute next generation
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
    template <class OrganismType, class LandscapeType>
    bool evocosm<OrganismType, LandscapeType>::run_generation(bool a_finished, double & a_fitness)
    {
        int n, p;

        ++m_iteration;

        // announce beginning of new generation        
        m_listener.ping_generation_begin(m_iteration);
        
        // test fitness for each chromosome
        for (p = 0; p < (int)m_number_of_populations; p++)
        {
            // announce beginning of population processing
            m_listener.ping_population_begin(p + 1);
            
            // clear fitness
            // using an iterator here crashes MSVC++ 13.0 (.Net) with an internal error
            for (n = 0; n < (int)m_population_size; ++n) // vector<OrganismType>::iterator organism = m_populations[p].begin(); organism != m_populations[p].end; ++organism)
                m_populations[p][n].reset_all();
            
            // let other processes do something
            m_listener.yield();

            // accumulate fitness for each population common to all populations
            if (m_number_of_common_landscapes > 0)
            {
                #ifdef _OPENMP
                #pragma omp parallel for private(p,n)
                #endif
                for (n = 0; n < (int)m_number_of_common_landscapes; ++n)
                    m_common_landscapes[n].test(m_populations[p]);
            }
            
            // let other processes do something
            m_listener.yield();

            // accumulate fitness for each landscape unique to this population
            if (m_number_of_unique_landscapes > 0)
            {
                #ifdef _OPENMP
                #pragma omp parallel for private(p,n)
                #endif
                for (n = 0; n < (int)m_number_of_unique_landscapes; ++n)
                    m_unique_landscapes[p][n].test(m_populations[p]);
            }
            
            // announce completion of population processing
            m_listener.ping_population_end(p + 1);
        }

        // report on new generation
        bool keep_going = m_reporter.report(m_populations,m_iteration,a_fitness,a_finished);
        
        // let other processes do something
        m_listener.yield();
        
        if (keep_going && m_running)
        {
            // create next generation
            #ifdef _OPENMP
            #pragma omp parallel for private(p,n)
            #endif
            for (p = 0; p < (int)m_number_of_populations; ++p)
            {
                // reverse the sense of fitness when minimizing (i.e., best fitness is smallest value)
                if (m_minimizing)
                    m_scaler.invert(m_populations[p]);
                
                // let other processes do something
                m_listener.yield();

                // scale the population's fitness
                m_scaler.scale_fitness(m_populations[p]);
                
                // let other processes do something
                m_listener.yield();

                // get survivors and number of chromosomes to add
                vector<OrganismType> survivors = m_selector.select_survivors(m_populations[p]); 

                // let other processes do something
                m_listener.yield();

                // give birth to new chromosomes
                vector<OrganismType> children = m_reproducer.breed(m_populations[p], m_population_size - survivors.size());

                // let other processes do something
                m_listener.yield();

                // mutate the child chromosomes
                m_mutator.mutate(children);

                // let other processes do something
                m_listener.yield();

                // replace old evocosm with new one
                m_populations[p] = survivors;
                m_populations[p].insert(m_populations[p].end(),children.begin(),children.end());
            }

            if (m_number_of_populations > 1)
                m_migrator.migrate(m_populations);
        }

        // we're done with this generation        
        m_listener.ping_generation_end(m_iteration);
        
        // let other processes do something
        m_listener.yield();

        return keep_going & m_running;
=======
    template <class OrganismType>
    bool evocosm<OrganismType>::run_generation()
    {
        bool keep_going = true;

        OrganismType * best = NULL;

        ++m_iteration;

        // announce beginning of new generation
        m_listener.ping_generation_begin(m_population, m_iteration);

        // check population fitness
        m_landscape.test(m_population);
        yield();

        // we're done testing this generation
        m_listener.ping_generation_end(m_population, m_iteration);
        yield();

        // analyze the results of testing, and decide if we're going to stop or not
        keep_going = m_analyzer.analyze(m_population, m_iteration);

        if (keep_going)
        {
            // fitness scaling
            m_scaler.scale_fitness(m_population);
            yield();

            // get survivors and number of chromosomes to add
            vector<OrganismType> survivors = m_selector.select_survivors(m_population);
            yield();

            // give birth to new chromosomes
            vector<OrganismType> children = m_reproducer.breed(m_population, m_population.size() - survivors.size());
            yield();

            // debugging only
            //fitness_stats<OrganismType> s(survivors);
            //fitness_stats<OrganismType> c(children);

            // mutate the child chromosomes
            m_mutator.mutate(children);
            yield();

            // append children to survivors and replace existing population form combined vector
            survivors.insert(survivors.end(),children.begin(),children.end());
            m_population = survivors;
            yield();
        }
        else
        {
            m_listener.run_complete(m_population);
        }

        return keep_going;
>>>>>>> version 4.0.2
    }
};

#endif
