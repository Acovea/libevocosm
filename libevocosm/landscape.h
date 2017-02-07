//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  Evocosm -- An Object-Oriented Framework for Evolutionary Algorithms
//
//  landscape.h
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

#if !defined(LIBEVOCOSM_LANDSCAPE_H)
#define LIBEVOCOSM_LANDSCAPE_H

// libevocosm
#include "organism.h"

namespace libevocosm
{
    //! An abstract interface defining a fitness landscape
    /*!
        A "fitness" landscape defines the environment in which an
        organism competes for survival. A class implementing this
        interface will test each organism in a list against some criteria.
        The landscape is tied to the nature of the organism; think of an
        organism as a potential solution to a problem posed by the landscape.
         
        A floating-point organism, for example, could be tested by a fitness
        landscape that represents a function to be maximized. Or, an organsism
        describing the shape of wing could be tested by a landscape
        implementation that understands airflow.
        \param OrganismType - A concrete implementation of the organism template (e.g., the type of organism that "lives" in this landscape)
    */
    template <class OrganismType>
    class landscape : protected globals
    {
        public:
            //! Constructor
            /*!
                Creates a new landscape object
                \param a_listener - a listener for events
            */
            landscape(listener & a_listener)
              : m_listener(a_listener)
            {
                // nada
            }

            //! Copy constructor
            landscape(const landscape & a_source)
              : m_listener(a_source.m_listener)
            {
                // nada
            }

            //! Assignment operator
            landscape & operator = (const landscape & a_source)
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
            virtual ~landscape()
            {
                // nada
            }

            //! Performs fitness testing
            /*!
                Tests a single chromosome for fitness.
                \param a_organism - The organism to be tested by the landscape.
                \param a_verbose - Display verbose information for test
                \return Computed fitness for this organism
            */
            virtual double test(OrganismType & a_organism, bool a_verbose = false) const = 0;

            //! Performs fitness testing
            /*!
                Tests each chromosome in a_population for fitness.
                \param a_population - A vector containing organisms to be tested by the landscape.
                \return A fitness value for the population as a whole; application-defined.
            */
            virtual double test(vector<OrganismType> & a_population) const = 0;
        
        protected:
            //! The listener for landscape events
            listener & m_listener;
    };
};

#endif
