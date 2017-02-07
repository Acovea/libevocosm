//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  Evocosm -- An Object-Oriented Framework for Evolutionary Algorithms
//
//  reporter.h
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

#if !defined(LIBEVOCOSM_REPORTER_H)
#define LIBEVOCOSM_REPORTER_H

// libevocosm
#include "organism.h"

namespace libevocosm
{
    //! Reports on a given population
    /*!
        A reporter can be many things; essentially, after fitness testing, the
        standard evocosm implementation calls a reporter to display information
        about the population and to find out if the population has reached some
        "final" or "finished" state.
        \param OrganismType - The type of organism
    */
    template <typename OrganismType, typename LandscapeType>
    class reporter : protected globals
    {
        public:
            //! Constructor
            /*!
                Creates a new reporter object
                \param a_listener - a listener for events
            */
            reporter(listener & a_listener)
              : m_listener(a_listener)
            {
                // nada
            }

            //! Copy constructor
            reporter(const reporter & a_source)
              : m_listener(a_source.m_listener)
            {
                // nada
            }

            //! Assignment operator
            reporter & operator = (const reporter & a_source)
            {
                m_listener = a_source.m_listener;
            }

            //! Virtual destructor
            /*!
                A virtual destructor. By default, it does nothing; this is
                a placeholder that identifies this class as a potential base,
                ensuring that objects of a derived class will have their
                destructors called if they are destroyed through a base-class
                pointer.
            */
            virtual ~reporter()
            {
                // nada
            }

            //! Reports on a population
            /*!
                The report method can do almost anything. In most case, it will display
                the "best" chromosome, draw a progress graph, or notify the user that
                another generation has passed. The return value tells an evocosm whether
                to continue evolution (changes in the population) or not.
                \param a_population - A population of organisms
                \param a_iteration - Iteration count for this report
                \param a_fitness - Assigned the fitness value; implementation-defined
                \param a_finished - When true, indicates that this is the last report for a given run
                \return <b>true</b> if the evocosm should evolve the population more; <b>false</b> if no evolution is required.
            */
            virtual bool report(const vector< vector<OrganismType> > & a_population, size_t a_iteration, double & a_fitness, bool a_finished = false) = 0;
        
        protected:
            //! The listener for events
            listener & m_listener;
    };
};

#endif
