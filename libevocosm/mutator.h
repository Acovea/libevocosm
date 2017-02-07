//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  Evocosm -- An Object-Oriented Framework for Evolutionary Algorithms
//
//  mutator.h
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

#if !defined(LIBEVOCOSM_MUTATOR_H)
#define LIBEVOCOSM_MUTATOR_H

// libevocosm
#include "organism.h"

namespace libevocosm
{
    //! Mutates organisms
    /*!
        A mutator applies mutations (random, usually small changes) to a
        set of organisms. Mutation is highly dependent on the type of
        organism. In traditional genetic algorithms, a mutation flips one
        or more bits in an integer (i.e., chromosome). Evolving a path for
        the Traveling Salesman Problem involves complex mutations that
        maintain valid permutations of destination points.
        \param OrganismType - The type of organism
    */
    template <class OrganismType>
    class mutator : protected globals
    {
    public:
        //! Virtual destructor
        /*!
            A virtual destructor. By default, it does nothing; this is
            a placeholder that identifies this class as a potential base,
            ensuring that objects of a derived class will have their
            destructors called if they are destroyed through a base-class
            pointer.
        */
        virtual ~mutator()
        {
            // nada
        }

        //! Mutate a set of organisms
        /*!
            Mutates some (maybe none, maybe all) organisms in a given set.
            \param a_population - Set of organisms to be mutated
        */
        virtual void mutate(vector<OrganismType> & a_population) = 0;
    };
};

#endif
