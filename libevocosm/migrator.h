//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  Evocosm -- An Object-Oriented Framework for Evolutionary Algorithms
//
//  migrator.h
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

#if !defined(LIBEVOCOSM_MIGRATOR_H)
#define LIBEVOCOSM_MIGRATOR_H

// libevocosm
#include "organism.h"

namespace libevocosm
{
    //! Defines migration between populations.
    /*!
        A migrator removes individuals (via "emigration") from a population
        of organisms, transferring them to another population (via
        "immigration"). A concrete implementation of this interface will
        probably contain some sort of organism "pool"; migration will place
        organisms into the pool, and immigration will remove them.
        \param OrganismType - The type of organism that will be migrating
    */
    template <class OrganismType>
    class migrator : protected globals
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
        virtual ~migrator()
        {
            // nada
        }

        //! Removes organisms from a population for later immigration
        /*!
            Calling emigrate will remove organisms from a population;
            these "mgrating" organisms will then be available for addition to
            another population via the immigrate method. The criteria for
            emigration is application-specific. Nothing requires that an
            organism be removed from its original population -- that is simply
            how "real" life works, when an animal leaves its home (say, a male
            lion leaving its pride) to join another population.
            \param a_populations - Set of organism populations between which members will "migrate"
        */
        virtual void migrate(vector< vector<OrganismType> > & a_populations) = 0;
    };

    //! A do-nothing migrator
    /*!
        The null_migrator doesn't migrate anything; it's just a placeholder used
        in evolutionary algorithms that do not use migration.
        \param OrganismType - The type of organism
    */
    template <class OrganismType>
    class null_migrator : public migrator<OrganismType>
    {
    public:
        //! Do-nothing emigration
        /*!
            Has no effect on the target populations.
            \param a_populations - Set of organism populations between which members will "migrate"
        */
        virtual void migrate(vector< vector<OrganismType> > & a_populations)
        {
            // nada
        }
    };

    //! A pool-based migrator
    /*!
        The pool_migrator maintains a pool of organisms taken from one or
        more populations, which are then available for immigration to 
        other populations.
    */
    template <class OrganismType>
    class random_pool_migrator : public migrator<OrganismType>
    {
    public:
        //! Constructor
        /*!
            Creates a new pool_migrator.
        */
        random_pool_migrator(size_t a_how_many)
          : m_how_many(a_how_many)
        {
            // nada
        }

        //! Emigrate organisms to pool
        /*!
            Copies organisms from the target population based on the constructor setting.
            \param a_populations - Set of organism populations between which members will "migrate"
        */
        virtual void migrate(vector< vector<OrganismType> > & a_populations)
        {
            // don't do anything is the value is zero
            if (m_how_many == 0)
                return;
            
            // get this value now so we don't keep calling size()
            size_t pop_count = a_populations.size();

            // keeps track of how many organisms have change in a given population
            size_t * move_count = new size_t [pop_count];

            for (size_t n = 0; n < pop_count; ++n)
                move_count[n] = 0;

            // migrate organisms
            for (size_t p = 0; p < pop_count; ++p)
            {
                // don't move any more organisms if this population is at its limit
                if (move_count[p] < m_how_many)
                {
                    size_t pop_size = a_populations[p].size();
                    size_t number_to_move = m_how_many - move_count[p];

                    for (size_t n = 0; n < number_to_move; ++n);
                    {
                        // pick a random organism
                        size_t org1 = globals::g_random.get_rand_index(pop_size);

                        // pick another population
                        size_t trader = globals::g_random.get_rand_index(pop_count);

                        // Sequential search for someone who hasn't reached their trade limit;
                        // can't keep randomly selecting because we might never hit the "one"
                        // open trader late in the sequence. Can't skip the current "p" 
                        // population because it might be the only one that hasn't swapped yet!
                        while (move_count[trader] >= m_how_many) 
                        {
                            ++trader;

                            if (trader == pop_count)
                                trader = 0;
                        }

                        if (trader != p)
                        {
                            // pick random member of other population
                            size_t org2 = globals::g_random.get_rand_index(a_populations[trader].size());
    
                            // exchange organisms
                            OrganismType temp = a_populations[p][org1];
                            a_populations[p][org1] = a_populations[trader][org2];
                            a_populations[trader][org2] = temp;

                            // increment counts
                            ++move_count[p];
                            ++move_count[trader];
                        }
                    }
                }
            }

            delete [] move_count;
        }

    private:
        // How many to migrate 
        size_t m_how_many;
    };

};

#endif
