<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
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

<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
    //! Implements a elitism selector 
=======
    //! A do-nothing selector
    /*!
        The all_selector returns a copy of the original population, all organisms survive.
        This is primarily used for development and testing, and is of little practical use.
        \param OrganismType - The type of organism
    */
    template <class OrganismType>
    class all_selector : public selector<OrganismType>
    {
    public:
        // Do-nothing selection function
        /*!
            Has no effect on the target population.
            \param a_population - A population of organisms
        */
        virtual vector<OrganismType> select_survivors(vector<OrganismType> & a_population)
        {
            vector<OrganismType> result;

            for (int n = 0; n < a_population.size(); ++n)
                result.push_back(a_population[n]);

            return result;
        }
    };

    //! Implements a elitism selector
>>>>>>> version 4.0.2
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
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            \param a_how_many - The maximum number of survivors
        */
        elitism_selector(size_t a_how_many = 1)
            : m_how_many(a_how_many)
=======
            \param a_factor - Percentage of bets fitness required to surivive
        */
        elitism_selector(double a_factor = 0.9)
            : m_factor(a_factor)
>>>>>>> version 4.0.2
        {
            // nada
        }

        //! Copy constructor
        /*!
            Creates a new object identical to an existing one.
            \param a_source - The source object
        */
        elitism_selector(const elitism_selector<OrganismType> & a_source)
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            : m_how_many(a_source.how_many)
=======
            : m_factor(a_source.m_factor)
>>>>>>> version 4.0.2
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
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            m_how_many = a_source.m_how_many;
=======
            m_factor = a_source.m_factor;
>>>>>>> version 4.0.2
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
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        size_t m_how_many;
=======
        double m_factor;
>>>>>>> version 4.0.2
    };

    template <class OrganismType>
    vector<OrganismType> elitism_selector<OrganismType>::select_survivors(vector<OrganismType> & a_population)
    {
        // create a new vector
        vector<OrganismType> chosen_ones;
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            
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
            
=======

        // get population stats
        fitness_stats<OrganismType> stats(a_population);

        // calculate survival based on percentage of best fitness
        double threshold = m_factor * stats.getBest().fitness;

        // pick survivors
        for (int n = 0; n < a_population.size(); ++n)
        {
            if (a_population[n].fitness > threshold)
                chosen_ones.push_back(a_population[n]);
>>>>>>> version 4.0.2
        }

        // return result
        return chosen_ones;
    }

};

#endif
