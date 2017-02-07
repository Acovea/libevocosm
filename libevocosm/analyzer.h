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

#if !defined(LIBEVOCOSM_ANALYZER_H)
#define LIBEVOCOSM_ANALYZER_H

// libevocosm
#include "organism.h"
#include "listener.h"

namespace libevocosm
{
    //! Reports on a given population
    /*!
        After fitness testing, the Evocosm invokes an analyzer. At a minimum,
        the analyzer determines if the population has reached a "final" or
        "finished" state.
        \param OrganismType - The type of organism
    */
    template <typename OrganismType>
    class analyzer : protected globals
    {
    public:
        //! Constructor
        /*!
            Creates a new reporter object
            \param a_listener - a listener for events
        */
        analyzer(listener<OrganismType> & a_listener, size_t max_iterations = 0)
            : m_listener(a_listener),
              m_max_iterations(max_iterations)
        {
            // nada
        }

        //! Copy constructor
        analyzer(const analyzer & a_source)
            : m_listener(a_source.m_listener),
              m_max_iterations(a_source.m_max_iterations)
        {
            // nada
        }

        //! Assignment operator
        analyzer & operator = (const analyzer & a_source)
        {
            m_listener = a_source.m_listener;
            m_max_iterations = a_source.m_max_iterations;
        }

        //! Virtual destructor
        /*!
            A virtual destructor. By default, it does nothing; this is
            a placeholder that identifies this class as a potential base,
            ensuring that objects of a derived class will have their
            destructors called if they are destroyed through a base-class
            pointer.
        */
        virtual ~analyzer()
        {
            // nada
        }

        //! Reports on a population
        /*!
            The report method can do almost anything. In most case, it will display
            the "best" chromosome, draw a progress graph, or notify the user that
            another generation has passed. The return value tells an evocosm whether
            to continue evolving or not. The default implementation simply watches
            to see if a maximum number of iterations ahve been perfromed.
            \param a_population - A population of organisms
            \param a_iteration - Iteration count for this report
            \return <b>true</b> if evolution should continue; <b>false</b> if not
        */
        virtual bool analyze(const vector<OrganismType> & a_population,  size_t a_iteration)
        {
            if (m_max_iterations > 0)
                return (a_iteration < m_max_iterations);
            else
                return true;
        }

    protected:
        //! The listener for events
        listener<OrganismType> & m_listener;

        //! Maximum iterations; ignored if zero
        size_t m_max_iterations;
    };
};

#endif
