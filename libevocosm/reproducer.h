//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  Evocosm -- An Object-Oriented Framework for Evolutionary Algorithms
//
//  reproducer.h
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

#if !defined(LIBEVOCOSM_REPRODUCER_H)
#define LIBEVOCOSM_REPRODUCER_H

// libevocosm
#include "organism.h"

namespace libevocosm
{
    //! Creates new organisms from an existing population
    /*!
        In most cases, a reproducer generates new organisms using parents
        selected (by fitness) from an existing population. In some singular
        (and probably rare) cases, a reproducer might generate new, random
        organisms in order to keep diversity high.
        Reproduction techniques can include crossover and asexual, sexual
        and (my favorite) try-sexual models.
        \param OrganismType - The type of organism
    */
    template <class OrganismType>
    class reproducer : protected globals
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
        virtual ~reproducer()
        {
            // nada
        }

        //! Creates children
        /*!
            A population provides genetic material for the creation of new children (who,
            will, like real children, forget where they left their shoes).
            \param a_population - A population of organisms
            \param a_limit - The maximum number of children the generate
            \return A vector containing new "child" organisms
        */
        virtual vector<OrganismType> breed(const vector<OrganismType> & a_population, size_t a_limit) = 0;
    };
};

#endif
