<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
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

#if !defined(LIBEVOCOSM_LANDSCAPE_H)
#define LIBEVOCOSM_LANDSCAPE_H

// libevocosm
#include "organism.h"

<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
=======
#ifdef _OPENMP
#include "omp.h"
#endif

>>>>>>> version 4.0.2
namespace libevocosm
{
    //! An abstract interface defining a fitness landscape
    /*!
        A "fitness" landscape defines the environment in which an
        organism competes for survival. A class implementing this
        interface will test each organism in a list against some criteria.
        The landscape is tied to the nature of the organism; think of an
        organism as a potential solution to a problem posed by the landscape.
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
         
=======

>>>>>>> version 4.0.2
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
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            landscape(listener & a_listener)
=======
            landscape(listener<OrganismType> & a_listener)
>>>>>>> version 4.0.2
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
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
=======
                return *this;
>>>>>>> version 4.0.2
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
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            virtual double test(vector<OrganismType> & a_population) const = 0;
        
        protected:
            //! The listener for landscape events
            listener & m_listener;
=======
            virtual double test(vector<OrganismType> & a_population) const
            {
                double result = 0.0;

                for (int n = 0; n < (int)a_population.size(); ++n)
                {
                    a_population[n].fitness = test(a_population[n]);
                    result += a_population[n].fitness;
                }

                // return average fitness
                return 0.0; // result / (double)a_population.size();
            }

        protected:
            //! The listener for landscape events
            listener<OrganismType> & m_listener;
>>>>>>> version 4.0.2
    };
};

#endif
