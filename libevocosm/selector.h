//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  Evocosm -- An Object-Oriented Framework for Evolutionary Algorithms
//
//  selector.h
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

#if !defined(EVOCOSM_SELECTOR_H)
#define EVOCOSM_SELECTOR_H

// Standard C++ Library
#include <algorithm>

// libevocosm
#include "organism.h"

namespace libevocosm
{
    //! Selects organisms that survive
    /*!
        A selector decides which organisms survive from one generation to the
        next. Some evolutionary algorithms will not use a selector; others will.
        In general, it is effective to keep the "best" organisms from one
        generation ot the next, so that good genes do not become lost at
        random.
        <p>
        Of course, "real" nature isn't so kind; just because you're the
        biggest stag in the forest doesn't mean you won't get shot! In fact,
        that may say something about the "best" -- maybe the "best" stag is
        the one that is too ugly for anyone to hunt?
        \param OrganismType - The type of organism being selected
    */
    template <class OrganismType>
    class selector : protected globals
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
        virtual ~selector()
        {
            // nada
        }

        //! Select individuals that survive
        /*!
            Produces a vector containing copies of the organisms selected for
            survival.
            \param a_population - A population of organisms
            \return A population of copied survivors
        */
        virtual vector<OrganismType> select_survivors(vector<OrganismType> & a_population) = 0;
    };

    //! A do-nothing selector
    /*!
        The null_selector doesn't select anything; it's just a placeholder used
        in evolutionary algorithms that do not use survival.
        \param OrganismType - The type of organism
    */
    template <class OrganismType>
    class null_selector : public selector<OrganismType>
    {
    public:
        // Do-nothing selection function
        /*!
            Has no effect on the target population.
            \param a_population - A population of organisms
        */
        virtual vector<OrganismType> select_survivors(vector<OrganismType> & a_population)
        {
            return vector<OrganismType>(); // an empty vector
        }
    };

    //! Implements a elitism selector 
    /*!
        Elitism is one of the simplest type of selection -- it simply says that
        the <i>n</i> best organisms will survive into the next generation.
        \param OrganismType - The type of organism
    */
    template <class OrganismType>
    class elitism_selector : public selector<OrganismType>
    {
    public:
        //! Constructor
        /*!
            Constructs a new elistism_selector with a value that defines the number of
            organisms that should survive into the next generation.
            \param a_how_many - The maximum number of survivors
        */
        elitism_selector(size_t a_how_many = 1)
            : m_how_many(a_how_many)
        {
            // nada
        }

        //! Copy constructor
        /*!
            Creates a new object identical to an existing one.
            \param a_source - The source object
        */
        elitism_selector(const elitism_selector<OrganismType> & a_source)
            : m_how_many(a_source.how_many)
        {
            // nada
        }

        //! Assignment operator
        /*!
            Assigns an existing object the state of another.
            \param a_source - The source object
        */
        elitism_selector & operator = (const elitism_selector<OrganismType> & a_source)
        {
            m_how_many = a_source.m_how_many;
        }

        //! Select individuals that survive
        /*!
            Produces a vector containing copies of the organisms selected for
            survival.
            \param a_population - A population of organisms
            \return A population of copied survivors
        */
        virtual vector<OrganismType> select_survivors(vector<OrganismType> & a_population);

    private:
        // number of organisms to keep
        size_t m_how_many;
    };

    template <class OrganismType>
    vector<OrganismType> elitism_selector<OrganismType>::select_survivors(vector<OrganismType> & a_population)
    {
        // create a new vector
        vector<OrganismType> chosen_ones;
            
        if (m_how_many > 0)
        {
            for (typename vector<OrganismType>::iterator i = a_population.begin(); i != a_population.end(); ++i)
            {
                typename vector<OrganismType>::iterator c = chosen_ones.begin();
                size_t n = 0;
                
                while ((c != chosen_ones.end()) && (n < m_how_many))
                {
                    if (i->fitness() > c->fitness())
                        break;
                        
                    ++c;
                    ++n;
                }
                
                if (n < m_how_many)
                    chosen_ones.insert(c,*i);
                
                if (chosen_ones.size() > m_how_many)
                    chosen_ones.pop_back();
            }
            
        }

        // return result
        return chosen_ones;
    }

};

#endif
