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

#if !defined(LIBEVOCOSM_STATS_H)
#define LIBEVOCOSM_STATS_H

// libevocosm
#include "organism.h"

// Standard C Library
#include <cmath>

// Standard C++
#include <limits>

namespace libevocosm
{
    //! Population fitness statistics
    /*!
        Produces a set of basic statistics from a given population. Used by various
        scaling, analysis, and reporting algorithms.
        \param OrganismType The type of organism in the population
     */
    template <class OrganismType>
    class fitness_stats
    {
    private:

        double min;
        double max;
        double mean;
        double variance;
        double sigma;
        OrganismType * best;
        OrganismType * worst;

    public:

        //! Construct a statistics object for a specific population
        /*!
            Analyzes a population, find highest and lowest fitness
            organisms and computing various statistical values.

            \param a_population Population ot be analyzed.
         */
        fitness_stats(const vector<OrganismType> & a_population)
          : best(new OrganismType(a_population[0])),
            worst(new OrganismType(a_population[0]))
        {
            // calculate max, average, and minimum fitness for the population
            max = std::numeric_limits<double>::min();
            min = std::numeric_limits<double>::max();
            mean = 0.0;
            variance = 0.0;

            for (int n = 0; n < a_population.size(); ++n)
            {
                // do we have a new maximum?
                if (a_population[n].fitness > max)
                {
                    max = a_population[n].fitness;

                    if (best != NULL)
                        delete best;

                    best = new OrganismType(a_population[n]);
                }

                // do we have a new minimum?
                if (a_population[n].fitness < min)
                {
                    min = a_population[n].fitness;

                    if (worst != NULL)
                        delete worst;

                    worst = new OrganismType(a_population[n]);
                }

                // accumulate for average
                mean += a_population[n].fitness;
            }

            mean /= double(a_population.size());

            for (int n = 0; n < a_population.size(); ++n)
            {
                double diff = a_population[n].fitness - mean;
                variance += (diff * diff);
            }

            variance /= static_cast<double>(a_population.size() - 1);

            // calculate 2 times the std. deviation (sigma)
            sigma = sqrt(variance);
        }

        //! Destructor
        /*!
            Frees resources.
        */
        virtual ~fitness_stats()
        {
            if (best != NULL)
                delete best;

            if (worst != NULL)
                delete worst;
        }


        //! Get the minimum fitness value for analyzed population
        double getMin() { return min; }

        //! Get the maximum fitness value for analyzed population
        double getMax() { return max; }

        //! Get the mean (average) fitness value for analyzed population
        double getMean() { return mean; }

        //! Get the fitness variance for analyzed population
        double getVariance() { return variance; }

        //! Get the standard deviation (sigma) value for fitness
        double getSigma() { return sigma; }

        //! Get the organism with the highest fitness for analyzed population
        OrganismType getBest() { return *best; }

        //! Get the organism with the lowest fitness for analyzed population
        OrganismType getWorst() { return *worst; }
    };

};

#endif
