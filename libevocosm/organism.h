<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  Evocosm -- An Object-Oriented Framework for Evolutionary Algorithms
//
//  organism.h
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

#if !defined(LIBEVOCOSM_ORGANISM_H)
#define LIBEVOCOSM_ORGANISM_H

// Standard C++ Library
#include <cstddef>

// libevocosm
#include "evocommon.h"

namespace libevocosm
{
    using std::vector;

    //! An evolving organism
    /*!
        An organism is a solution to a problem posed by a fitness landscape;
        it has "genes" that define its behavior, and a fitness value assigned
        during fitness testing.

        Evocosm provides the freedom to define organisms as anything: bit
        strings, floating-point numbers, finite state machines, LISP programs,
        or external robots controlled via radio waves.
        \param Genotype - The type of genes for this organism class
    */
    template <typename Genotype>
    class organism : protected globals
    {
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
    protected:
        //! Fitness value
        double m_fitness;

        //! Genetic material; could be almost anything
        Genotype m_genes;

    public:
=======
    public:
        /*!
            Fitness is assigned by the landscape in which an organism is tested.
            A scaler object may alter fitness values after testing; a selector
            uses fitness to determine which organisms survive from one generation
            to the next, and a reproducer creates new organisms from parents
            selected by fitness.
        */
        double fitness;

        /*!
            Genes define an organism's behavior in a fitness landscape. An initial
            population usually (but not always) contains organisms with random genes;
            a landscape tests the behavior defined by genes to calculate the fitness
            of an organism. A reproducer will create children from the genes of their
            parents, and a mutator may make random changes in those genes.
        */
        Genotype genes;

>>>>>>> version 4.0.2
        //! Creation constructor
        /*!
            Creates a new organism, with default genes and zero fitness.
        */
        organism()
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            : m_fitness(0.0),
              m_genes()
=======
            : fitness(0.0),
              genes()
>>>>>>> version 4.0.2
        {
            // nada
        }

        //! Value constructor
        /*!
            Creates a new organism with specific genes.
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            \param a_value - Gene value for the new organism
        */
        organism(const Genotype & a_value)
            : m_fitness(0.0),
              m_genes(a_value)
=======
            \param a_genes - Gene value for the new organism
        */
        organism(const Genotype & a_genes)
            : fitness(0.0),
              genes(a_genes)
>>>>>>> version 4.0.2
        {
            // nada
        }

        //! Copy constructor
        /*!
            Creates a new object identical to an existing one.
            \param a_source - The source object
        */
        organism(const organism & a_source)
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            : m_fitness(a_source.m_fitness),
              m_genes(a_source.m_genes)
        {
            // nada
        }

        //! Crossover constructor
        /*!
            Creates a new object identical to an existing one.
            \param a_parent1 - First parent object
            \param a_parent2 - Second parent object
        */
        organism(const organism & a_parent1, const organism & a_parent2)
            : m_fitness(a_parent1.m_fitness),
              m_genes(a_parent1.m_genes,a_parent2.m_genes)
=======
            : fitness(a_source.fitness),
              genes(a_source.genes)
>>>>>>> version 4.0.2
        {
            // nada
        }

        //! Virtual destructor
        /*!
            A virtual destructor. By default, it does nothing; this is
            a placeholder that identifies this class as a potential base,
            ensuring that objects of a derived class will have their
            destructors called if they are destroyed through a base-class
            pointer.
        */
        virtual ~organism()
        {
            // nada
        }

        //! assignment operator
        /*!
            Assigns an existing object the state of another.
            \param a_source - The source object
            \return A reference to <i>this</i>
        */
        organism & operator = (const organism & a_source)
        {
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            m_fitness = a_source.m_fitness;
            m_genes   = a_source.m_genes;
=======
            fitness = a_source.fitness;
            genes   = a_source.genes;
            return *this;
        }

        //! assignment operator
        /*!
            Assigns an existing object the state of another.
            \param a_genes - The source object
            \return A reference to <i>this</i>
        */
        organism & operator = (const Genotype & a_genes)
        {
            fitness = 0.0;
            genes   = a_genes;
>>>>>>> version 4.0.2
            return *this;
        }

        //! Comparison operator for algorithms
        /*!
            Many Standard C++ algorithms require a "less than" comparison operator
            for container elements.
            \param a_right - Right hand argument for less than operator
        */
        virtual bool operator < (const organism & a_right) const
        {
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
            return (m_fitness > a_right.m_fitness);
        }
        
        //! Comparison operator for algorithms
=======
            return (fitness > a_right.fitness);
        }

        //! Resets an object to it's initial state
>>>>>>> version 4.0.2
        /*!
            Resets all data in an organisim to the initial (or startup) state, including
            setting the fitness to zero. Derived classes should override this method to
            "clear" any data.
        */
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        virtual void reset_all()
        {
            m_fitness = 0.0;
        }
    
        //! Get fitness (read-write)
        /*!
            Fitness is assigned by the landscape in which an organism is tested.
            A scaler object may alter fitness values after testing; a selector
            uses fitness to determine which organisms survive from one generation
            to the next, and a reproducer creates new organisms from parents
            selected by fitness.

            Giving direct access to a member violates encapsulation, but it
            vastly simplifies the numerous functions that manipulate organisms.
            \return Fitness for this organism
            \sa landscape, scaler, selector, reproducer
        */
        double & fitness()
        {
            return m_fitness;
        }

        //! Get fitness (read-only)
        /*!
            Fitness is assigned by the landscape in which an organism is tested.
            A scaler object may alter fitness values after testing; a selector
            uses fitness to determine which organisms survive from one generation
            to the next, and a reproducer creates new organisms from parents
            selected by fitness.

            Giving direct access to a member violates encapsulation, but it
            vastly simplifies the numerous functions that manipulate organisms.
            \return Fitness for this organism
            \sa landscape, scaler, selector, reproducer
        */
        double fitness() const
        {
            return m_fitness;
        }

        //! Get genes (read-write)
        /*!
            Genes define an organism's behavior in a fitness landscape. An initial
            population usually (but not always) contains organisms with random genes;
            a landscape tests the behavior defined by genes to calculate the fitness
            of an organism. A reproducer will create children from the genes of their
            parents, and a mutator may make random changes in those genes.
            \return Genes encapsulated by this organism
            \sa landscape, mutator, reproducer
        */
        Genotype & genes()
        {
            return m_genes;
        }

        //! Get genes (read-only)
        /*!
            Genes define an organism's behavior in a fitness landscape. An initial
            population usually (but not always) contains organisms with random genes;
            a landscape tests the behavior defined by genes to calculate the fitness
            of an organism. A reproducer will create children from the genes of their
            parents, and a mutator may make random changes in those genes.
            \return Genes encapsulated by this organism
            \sa landscape, mutator, reproducer
        */
        const Genotype & genes() const
        {
            return m_genes;
=======
        virtual void reset()
        {
            fitness = 0.0;
>>>>>>> version 4.0.2
        }
    };

};

#endif
