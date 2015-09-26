<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  Evocosm -- An Object-Oriented Framework for Evolutionary Algorithms
//
//  roulette.h
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

#if !defined(LIBEVOCOSM_ROULETTE_H)
#define LIBEVOCOSM_ROULETTE_H

// standard C++ Library
#include <cmath>
#include <vector>
#include <limits>

// libevocosm
#include "evocommon.h"

namespace libevocosm
{
    using std::vector;

    //! A simulated roulette wheel for weighted selection.
    /*!
        You've probably seen a standard gambler's roulette wheel, a spinning
        circle divided into thirty-seven or thirty-eight equal-sized, pie-shaped
        sections. The croupier sets the wheel spinning and at the same time
        tosses an marble into the bowl in the direction opposite to that in
        which the wheel is moving; when the motion of the wheel ceases, the ball
        comes to rest in one of the numbered sections.
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        As an algorithm, a roulette wheel is an array of weights, and the marble
        is a random integer less than the sum of all weights in the population.
        To pick on of the "section" (in this case, an index), the algorithm
        simulates the bouncing metal ball by iterating through the array of
        weights; if the marble value is less than the current weight (i.e., the
        ball has stopped), the algorithm returns the index of that weight.
        Otherwise, the algorithm subtracts the current weight from the
        marble value, and repeats the process with the next element in the
        weight array. Thus the largest weights values tend to be the most likely
        resting places for the marble, since they use a larger area of the
        abstract wheel.
    */
    class roulette_wheel : protected globals
    {
    public:
        //! Creation constructor (from vector)
        /*!
            Creates a new roulette_wheel based on a set of weights.
            \param a_weights - A vector of weights defining the wheel
            \param a_min_weight - Minimum possible weight value (defaults to epsilon for type)
            \param a_max_weight - Maximum possible weight value (defaults to max for type)
        */
        roulette_wheel(const vector<double> & a_weights,
                       double a_min_weight = std::numeric_limits<double>::epsilon(),
                       double a_max_weight = std::numeric_limits<double>::max());
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        //! Creation constructor (from c-type array)
        /*!
            Creates a new roulette_wheel based on a set of weights.
            \param a_weights - An array of weights defining the wheel
            \param a_length - Number of elements in <i>a_weights</i>
            \param a_min_weight - Minimum possible weight value (defaults to 1.0)
            \param a_max_weight - Maximum possible weight value (defaults to 100.0)
        */
        roulette_wheel(const double * a_weights,
                       size_t a_length,
                       double a_min_weight = std::numeric_limits<double>::epsilon(),
                       double a_max_weight = std::numeric_limits<double>::max());
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        //! Copy constructor
        /*!
            Creates a new roulette_wheel from an existing one.
            \param a_source - The source object
        */
        roulette_wheel(const roulette_wheel & a_source);
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        //! Assignment operator
        /*!
            Assigns a roulette_wheel the state of another.
            \param a_source - The source object
        */
        roulette_wheel & operator = (const roulette_wheel & a_source);
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        //! Destructor
        /*!
            Destroys a roulette_wheel, freeing resources.
        */
        ~roulette_wheel();
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        //! Get size (number of weights)
        /*!
            Gets the number of weights indexed by the roulette wheel.
            \return The number of weights
        */
        size_t get_size() const
        {
            return m_size;
        }

        //! Change the weight assigned to an entry
        /*!
            Changes the weight assigned to a specific wheel index.
            \param a_index - Index to change
            \param a_weight - New weight Value
            \return Previous weight for this index, or -1 if a_index is invalid
        */
        double set_weight(size_t a_index, double a_weight);
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        //! Get the weight for an index
        /*!
            Gets the weight assigned to a specific index.
            \param a_index Index for which weight should be returned
            \return Weight for this index, or -1 if a_index is invalid
        */
        double get_weight(size_t a_index) const;
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        //! Retrieve a random index
        /*!
            Returns a randomly-selected index value by simulating the
            bouncing of a ball on a roulette wheel, where each index is
            a "slot" with a width determined by its assigned weight.
            \return A random index value
        */
        size_t get_index() const;
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
    protected:
        //! Number of weights in this wheel
        size_t m_size;

        //! Array of m_weights
        double * m_weights;
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
        //! Total weight of all indexes
        double m_total_weight;
        
        //! Minimum possible weight value
        double m_min_weight;
        
=======

        //! Total weight of all indexes
        double m_total_weight;

        //! Minimum possible weight value
        double m_min_weight;

>>>>>>> version 4.0.2
        //! Maximum possible weight value
        double m_max_weight;

    private:
        // internal copy function
        void copy(const roulette_wheel & a_source);
    };
};

#endif
