<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  Roulette Wheel -- A Tool for Weighted Selection
//
//  roulette.cpp
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

// Standard C++ Library
#include <cstdio>
#include <cstring>
#include <stdexcept>

// libcoyotl
#include "libcoyotl/validator.h"
using namespace libcoyotl;

// libevocosm
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

#include <stdexcept>
#include <cstring>

// libevocosm
#include "validator.h"
>>>>>>> version 4.0.2
#include "roulette.h"
using namespace libevocosm;

// creation constructor
roulette_wheel::roulette_wheel(const vector<double> & a_weights, double a_min_weight, double a_max_weight)
  : m_size(a_weights.size()),
    m_weights(NULL),
    m_total_weight(0.0),
    m_min_weight(fabs(a_min_weight)),
    m_max_weight(fabs(a_max_weight))
{
    validate_less(a_min_weight,a_max_weight,"Minimum weight must be less than maximum");
    validate_not(m_size,size_t(0),"Roulette wheel can not have zero size");

    m_weights = new double[m_size];

    for (size_t i = 0; i < m_size; ++i)
    {
        m_weights[i]   = fabs(a_weights[i]);
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        if (m_weights[i] < m_min_weight)
            m_weights[i] = m_min_weight;
        else
            if (m_weights[i] > m_max_weight)
                m_weights[i] = m_max_weight;
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        m_total_weight += m_weights[i];
    }

    validate_greater(m_total_weight,0.0,"Roulette wheel must have a total weight > zero");
}

// create from C array
roulette_wheel::roulette_wheel(const double * a_weights, size_t a_size, double a_min_weight, double a_max_weight)
  : m_size(a_size),
    m_weights(NULL),
    m_total_weight(0.0),
    m_min_weight(fabs(a_min_weight)),
    m_max_weight(fabs(a_max_weight))
{
    validate_not(m_size,size_t(0),"Roulette wheel can not have zero size");
    validate_less(m_min_weight,m_max_weight,"Minimum weight must be less than maximum");
    validate_greater(m_min_weight,0.0,"Minimum weight must be > 0");
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
    
=======

>>>>>>> version 4.0.2
    m_weights = new double[m_size];

    for (size_t i = 0; i < m_size; ++i)
    {
        m_weights[i]   = fabs(a_weights[i]);
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        if (m_weights[i] < m_min_weight)
            m_weights[i] = m_min_weight;
        else
            if (m_weights[i] > m_max_weight)
                m_weights[i] = m_max_weight;
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
        
=======

>>>>>>> version 4.0.2
        m_total_weight += m_weights[i];
    }

    validate_greater(m_total_weight,0.0,"Roulette wheel must have a total weight > zero");
}

// copy constructor
roulette_wheel::roulette_wheel(const roulette_wheel & a_source)
  : m_size(a_source.m_size),
    m_weights(NULL),
    m_total_weight(a_source.m_total_weight),
    m_min_weight(a_source.m_min_weight),
    m_max_weight(a_source.m_max_weight)
{
    m_weights = new double[m_size];
    memcpy(m_weights,a_source.m_weights,sizeof(double) * m_size);
}

// assignment operator
roulette_wheel & roulette_wheel::operator = (const roulette_wheel & a_source)
{
    if (this != &a_source)
    {
        m_size         = a_source.m_size;
        m_weights      = new double[m_size];
        memcpy(m_weights,a_source.m_weights,sizeof(double) * m_size);
        m_total_weight = a_source.m_total_weight;
        m_min_weight   = a_source.m_min_weight;
        m_max_weight   = a_source.m_max_weight;
    }
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
    
=======

>>>>>>> version 4.0.2
    return *this;
}

// destructor
roulette_wheel::~roulette_wheel()
{
    delete [] m_weights;
}

// change the a_weight of an entry
double roulette_wheel::set_weight(size_t a_index, double a_weight)
{
    validate_less(a_index,m_size,"invalid roulette wheel index");
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
    
=======

>>>>>>> version 4.0.2
    a_weight = fabs(a_weight);

    if (a_weight < m_min_weight)
        a_weight = m_min_weight;
    else
        if (a_weight > m_max_weight)
            a_weight = m_max_weight;
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
    
    m_total_weight -= m_weights[a_index];
    m_total_weight += a_weight;
    
=======

    m_total_weight -= m_weights[a_index];
    m_total_weight += a_weight;

>>>>>>> version 4.0.2
    double res = m_weights[a_index];
    m_weights[a_index] = a_weight;

    return res;
}

// interrogator
double roulette_wheel::get_weight(size_t a_index) const
{
    validate_less(a_index,m_size,"invalid roulette wheel index");
    return m_weights[a_index];
}

// retrieve a random index
size_t roulette_wheel::get_index() const
{
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
    double choice = g_random.get_rand_real2() * m_total_weight;

    size_t i = 0;
    
=======
    double choice = g_random.get_real() * m_total_weight;

    size_t i = 0;

>>>>>>> version 4.0.2
    while ((i < m_size) && (choice > m_weights[i]))
    {
        choice -= m_weights[i];
        ++i;
    }
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
    
=======

>>>>>>> version 4.0.2
    return i;
}

