//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  Evocosm -- An Object-Oriented Framework for Evolutionary Algorithms
//
//  scaler.h
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

#if !defined(LIBEVOCOSM_SCALER_H)
#define LIBEVOCOSM_SCALER_H

// Standard C Library
#include <cmath>

// Standard C++
#include <limits>
#include <algorithm>

// libevocosm
#include "organism.h"

namespace libevocosm
{
    //! Fitness scaling for a population
    /*!
        As a population converges on a definitive solution, the difference
        between fitness values may become very small. That prevents the
        best solutions from having a significant advantage in reproduction.
        Fitness scaling solves this problem by adjusting the fitness values
        to the advantage of the most-fit chromosomes.
        \param OrganismType - The type of organism
    */
    template <class OrganismType>
    class scaler : protected globals
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
        virtual ~scaler()
        {
            // nada
        }

        //! Scale a population's fitness values
        /*!
            The scale_fitness method can adjust the fitness of a population
            to make it more likely that the "best" (whatever that menas)
            organisms have the best chance of reproduction.
            \param a_population - A population of organisms
        */
        virtual void scale_fitness(vector<OrganismType> & a_population) = 0;
        
        //! Invert a population's fitness values
        /*!
            Scales a population's fitness values 
        */
        void invert(vector<OrganismType> & a_population)
        {
            double base = min_element(a_population.begin(), a_population.end())->fitness()
                        + max_element(a_population.begin(), a_population.end())->fitness();
            
            for (typename vector<OrganismType>::iterator organism = a_population.begin(); organism != a_population.end(); ++organism)
               organism->fitness() = base - organism->fitness();
        }                
    };

    //! A do-nothing scaler
    /*!
        The null_scaler doesn't scale anything; it's just a placeholder used
        in evolutionary algorithms that do not use fitness scaling.
        \param OrganismType - The type of organism
    */
    template <class OrganismType>
    class null_scaler : public scaler<OrganismType>
    {
    public:
        //! Do-nothing scaling function
        /*!
            Has no effect on the target population.
            \param a_population - A population of organisms
        */
        virtual void scale_fitness(vector<OrganismType> & a_population)
        {
            // nada
        }
    };

    //! A linear normalization scaler
    /*!
        A simple scaler implementing a configurable linear normalization scaler, as
        per Goldberg 1979.
        \param OrganismType - The type of organism
    */
    template <class OrganismType>
    class linear_norm_scaler : public scaler<OrganismType>
    {
    public:
        //! Constructor
        /*!
            Creates a new scaler for linear normalization.
        */
        linear_norm_scaler(double a_fitness_multiple = 2.0)
            : m_fitness_multiple(a_fitness_multiple)
        {
            // nada
        }

        //! Scaling function
        /*!
            Performs linear normalization on the fitness of the target population.
            \param a_population - A population of organisms
        */
        virtual void scale_fitness(vector<OrganismType> & a_population)
        {
            // calculate max, average, and minimum fitness for the population
            double max_fitness = std::numeric_limits<double>::min();
            double min_fitness = std::numeric_limits<double>::max();
            double avg_fitness = 0.0;
            
            for (typename vector<OrganismType>::iterator org = a_population.begin(); org != a_population.end(); ++org)
            {
                // do we have a new maximum?
                if (org->fitness() > max_fitness)
                    max_fitness = org->fitness();
                
                // do we have a new minimum?
                if (org->fitness() < min_fitness)
                    min_fitness = org->fitness();
                
                // accumulate for average
                avg_fitness += org->fitness();
            }
            
            avg_fitness /= double(a_population.size());
            
            // calculate coefficients for fitness scaling
            double slope;
            double intercept;
            double delta;
            
            if (min_fitness > ((m_fitness_multiple * avg_fitness - max_fitness) / (m_fitness_multiple - 1.0)))
            {
                // normal scaling
                delta = max_fitness - avg_fitness;
                slope = (m_fitness_multiple - 1.0) * avg_fitness / delta;
                intercept = avg_fitness * (max_fitness - m_fitness_multiple * avg_fitness) / delta;
            }
            else
            {
                // extreme scaling
                delta = avg_fitness - min_fitness;
                slope = avg_fitness / delta;
                intercept = -min_fitness * avg_fitness / delta;
            }
            
            // adjust fitness values
            for (typename vector<OrganismType>::iterator org = a_population.begin(); org != a_population.end(); ++org)
                org->fitness() = slope * org->fitness() + intercept;
        }
        
    private:
        double m_fitness_multiple;
    };

    //! A windowed fitness scaler
    /*!
        Implements windowed fitness scaling, whereby all fitness values are modified
        by subtracting the minimum fitness in the population.
        \param OrganismType - The type of organism
    */
    template <class OrganismType>
    class windowed_scaler : public scaler<OrganismType>
    {
    public:
        //! Constructor
        /*!
            Creates a new windowed scaler with a given set of parameters.
        */
        windowed_scaler()
        {
            // nada
        }

        //! Scaling function
        /*!
            Performs windowed scaling on the fitness of the target population.
            \param a_population - A population of organisms
        */
        virtual void scale_fitness(vector<OrganismType> & a_population)
        {
            // Find minimum fitness
            // Note that organisms sort in reverse order of fitness, such that
            // the "maximum" value has the smallest fitness.
            double min_fitness = min_element(a_population.begin(), a_population.end())->fitness();
            
            // assign new fitness values
            for (typename vector<OrganismType>::iterator org = a_population.begin(); org != a_population.end(); ++org)
                org->fitness() -= min_fitness;
        }
    };
    
    //! An exponential fitness scaler
    /*!
        Implements an exponential fitness scaling, whereby all fitness values are modified
        such that new fitness = (a * fitness + b) ^ n.
        \param OrganismType - The type of organism
    */
    template <class OrganismType>
    class exponential_scaler : public scaler<OrganismType>
    {
    public:
        //! Constructor
        /*!
            Creates a new exponential scaler with a given set of parameters. The
            formula used is new_fitness = (a * fitness + b) ^ power.
            \param a_a - A multplier against the fitness
            \param a_b - Added to fitness before exponentiation
            \param a_power - Power applied to the value
        */
        exponential_scaler(double a_a = 1.0, double a_b = 1.0, double a_power = 2.0)
          : m_a(a_a),
            m_b(a_b),
            m_power(a_power)
        {
            // nada
        }

        //! Scaling function
        /*!
            Performs exponential scaling on the fitness of the target population.
            \param a_population - A population of organisms
        */
        virtual void scale_fitness(vector<OrganismType> & a_population)
        {
            // assign new fitness values
            for (typename vector<OrganismType>::iterator org = a_population.begin(); org != a_population.end(); ++org)
                org->fitness() = pow((m_a * org->fitness() + m_b),m_power);
        }

    private:
        double m_a;
        double m_b;
        double m_power;
    };
    
    //! A quadratic scaler
    /*!
        Uses a quadratic equation to scale the fitness of organisms.
        \param OrganismType - The type of organism
    */
    template <class OrganismType>
    class quadratic_scaler : public scaler<OrganismType>
    {
    public:
        //! Constructor
        /*!
            Creates a new scaler for quadratic scaling.
        */
        quadratic_scaler(double a_a, double a_b, double a_c)
            : m_a(a_a), m_b(a_b), m_c(a_c)
        {
            // nada
        }

        //! Scaling function
        /*!
            Performs quadratic scling on the fitness of the target population.
            \param a_population - A population of organisms
        */
        virtual void scale_fitness(vector<OrganismType> & a_population)
        {
            // adjust fitness values
            for (typename vector<OrganismType>::iterator org = a_population.begin(); org != a_population.end(); ++org)
            {
                double f = org->fitness();
                org->fitness() = m_a * pow(f,2.0) + m_b * f + m_c;
            }
        }
        
    private:
        double m_a;
        double m_b;
        double m_c;
    };

    //! A sigma scaler
    /*!
        A sigma scaler, as per Forrest and Tanese.
        \param OrganismType - The type of organism
    */
    template <class OrganismType>
    class sigma_scaler : public scaler<OrganismType>
    {
    public:
        //! Constructor
        /*!
            Creates a new sigma scaler
        */
        sigma_scaler()
        {
        }

        //! Scaling function
        /*!
            Performs sigma scaling, which maintains selection pressure over the
            length of a run, thus minimizing the affects of convergence on
            reproductive selection. The function adjusts an organism's fitness
            in relation to the standard deviation of the population's fitness.
            \param a_population - A population of organisms
        */
        virtual void scale_fitness(vector<OrganismType> & a_population)
        {
            // calculate the mean
            double mean = 0.0;
            for (typename vector<OrganismType>::iterator org = a_population.begin(); org != a_population.end(); ++org)
                mean += org->fitness();
            
            mean /= static_cast<double>(a_population.size());
            
            // calculate variance
            double variance = 0.0;
            for (typename vector<OrganismType>::iterator org = a_population.begin(); org != a_population.end(); ++org)
            {
                double diff = org->fitness() - mean;
                variance += (diff * diff);
            }
            
            variance /= static_cast<double>(a_population.size() - 1);

            // calculate 2 times the std. deviation (sigma)
            double sigma2 = 2.0 * sqrt(variance);
            
            // now assign new fitness values
            if (sigma2 == 0.0)
            {
                for (typename vector<OrganismType>::iterator org = a_population.begin(); org != a_population.end(); ++org)
                    org->fitness() = 1.0;
            }
            else   
            {
                for (typename vector<OrganismType>::iterator org = a_population.begin(); org != a_population.end(); ++org)
                {
                    // change fitness
                    org->fitness() = (1.0 + org->fitness() / mean) / sigma2;
                    
                    // avoid tiny or zero fitness value; everyone gets to reproduce
                    if (org->fitness() < 0.1)
                        org->fitness() = 0.1;
                }
            }
        }
    };

};

#endif
