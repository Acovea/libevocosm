//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  A multiargument function optimizer based on Evocosm
//
//  funcopt.h
//---------------------------------------------------------------------
//
//  COPYRIGHT NOTICE, DISCLAIMER, and LICENSE:
//
//  This notice applies *only* to this specific expression of this
//  algorithm, and does not imply ownership or invention of the
//  implemented algorithm.
//  
//  If you modify this file, you may insert additional notices
//  immediately following this sentence.
//  
//  Copyright 2002 Scott Robert Ladd. All rights reserved.
//  All rights reserved, except as noted herein.
//
//  This computer program source file is supplied "AS IS". Scott Robert
//  Ladd (hereinafter referred to as "Author") disclaims all warranties,
//  expressed or implied, including, without limitation, the warranties
//  of merchantability and of fitness for any purpose. The Author
//  assumes no liability for direct, indirect, incidental, special,
//  exemplary, or consequential damages, which may result from the use
//  of this software, even if advised of the possibility of such damage.
//  
//  The Author hereby grants anyone permission to use, copy, modify, and
//  distribute this source code, or portions hereof, for any purpose,
//  without fee, subject to the following restrictions:
//  
//      1. The origin of this source code must not be misrepresented.
//  
//      2. Altered versions must be plainly marked as such and must not
//         be misrepresented as being the original source.
//  
//      3. This Copyright notice may not be removed or altered from any
//         source or altered source distribution.
//  
//  The Author specifically permits (without fee) and encourages the use
//  of this source code for entertainment, education, or decoration. If
//  you use this source code in a product, acknowledgment is not required
//  but would be appreciated.
//  
//  Acknowledgement:
//      This license is based on the wonderful simple license that
//      accompanies libpng.
//
//-----------------------------------------------------------------------
//  For more information on this software package, please visit
//  Scott's web site, Coyote Gulch Productions, at:
//
//      http://www.coyotegulch.com
//-----------------------------------------------------------------------

#include <vector>
#include <stdexcept>
#include <limits>

#include "../libevocosm/evocosm.h"
#include "../libevocosm/evoreal.h"

#if !defined(FUNCOPT_H)
#define FUNCOPT_H

namespace funcopt
{
    using namespace libevocosm;

    //! Global things used by all optimizer classes
    /*!
        I put all cross-class, shared items into a single base class; this
        encapsulates global data, and also show why multiple inheritance
        is a useful tool.
    */
    class fopt_global
    {
    protected:
        //! Definition of a function type
        /*!
            This is the type of function being optimized. <i><b>The inner nature
            of this function is not defined by this optimizer.</i><b> A t_function
            can be anything -- a simple numerical formula or a simulation. For
            example: Consider a set of arguments that describe the shape of a wing,
            and a t_function that tests shapes in a simulated wind tunnel, the
            fitness representing how well the arguments "fly".
        */
        typedef double t_function(vector<double> a_args);

        //! Provides mutation and crossover services for doubles
        static evoreal g_evoreal;
    };

    //! A potential solution to the problem at hand
    /*!
        To support a wide variety of applications, I defined a function solution
        as a vector of doubles. This allows functions of any dimension to be
        optimized (within platform limits, of course). Note that the solution
        begins with an empty vector; this is because the number of elements and
        their initialization is application specific. Initialization of the genes
        takes place in the constructor for function_optimizer through a pointer
        to a user-supplied function.
    */
    class function_solution : public organism< vector<double> >, protected fopt_global
    {
    public:
        //! Creation constructor
        /*!
            Creates a new solution with an empty vector.
        */
        function_solution()
          : organism< vector<double> >()
        {
            // need to call randomize, or genes will be empty!
        }

        //! Construct from base class
        /*!
            Constructs a function solution from a base-class object.
            \param a_source - The source object
        */
        function_solution(const organism< vector<double> > & a_source)
          : organism< vector<double> >(a_source)
        {
            // nada
        }

        //! Copy constructor
        /*!
            Duplicates an existing object.
            \param a_source - The source object
        */
        function_solution(const function_solution & a_source)
          : organism< vector<double> >(a_source)
        {
            // nada
        }

        //! Virtual destructor
        /*!
            Satisfies the requirements of the base class; does nothing at this time.
        */
        virtual ~function_solution()
        {
            // nada
        }

        //! Assignment operator
        /*!
            Assigns the state of one solution to another.
            \param a_source - The source object
            \return A reference to <i>this</i>
        */
        function_solution & operator = (const function_solution & a_source)
        {
            organism< vector<double> >::operator = (a_source);
            return *this;
        }

        //! Comparison operator for algorithms
        /*!
            Returns true if the target object is greater than a_source. While the
            operator may be "less than", what it really meands for algorithms is
            "comes before" -- and I want the highest fitness to come first.
            \param p_right - Right hand argument for less than operator
        */
        virtual bool operator < (const organism< vector<double> > & p_right) const
        {
            return (m_fitness > p_right.fitness());
        }
    };

    //! Mutates solutions
    /*!
        Implements chance-based mutation of solutions.
    */
    class function_mutator : public mutator<function_solution>, protected fopt_global
    {
    public:
        //! Creation constructor
        /*!
            Creates a new mutator with a given mutation rate.
        */
        function_mutator(double a_mutation_rate)
          : m_mutation_rate(a_mutation_rate)
        {
            // adjust mutation rate if necessary
            if (m_mutation_rate > 1.0)
                m_mutation_rate = 1.0;
            else if (m_mutation_rate < 0.0)
                m_mutation_rate = 0.0;
        }

        //! Copy constructor
        /*!
            Duplicates an existing object.
            \param a_source - The source object
        */
        function_mutator(const function_mutator & a_source)
            : m_mutation_rate(a_source.m_mutation_rate)
        {
            // nada
        }

        //! Virtual destructor
        /*!
            Satisfies the requirements of the base class; does nothing at this time.
        */
        virtual ~function_mutator()
        {
            // nada
        }

        //! Assignment operator
        /*!
            Assigns the state of one object to another.
            \param a_source - The source object
            \return A reference to <i>this</i>
        */
        function_mutator & operator = (const function_mutator & a_source)
        {
            m_mutation_rate = a_source.m_mutation_rate;
	    return *this;
        }

        //! Gets the mutation rate
        /*!
            Returns the mutation rate set for this mutator.
            \return Mutation rate
        */
        double mutation_rate() const
        {
            return m_mutation_rate;
        }

        //! Performs mutations
        /*!
            Mutates a solution using the facilities provided by g_evoreal.
            \param a_population - Solutions to be mutated
        */
        void mutate(vector<function_solution> & a_population);

    private:
        // rate of mutation
        double m_mutation_rate;
    };

    //! Implements reproduction
    /*!
        Handles reproduction for solutions.
    */
    class function_reproducer : public reproducer<function_solution>, protected fopt_global
    {
    public:
        //! Creation constructor
        /*!
            Creates a new reproducer with a given crossover rate.
        */
        function_reproducer(double p_crossover_rate = 1.0)
            : m_crossover_rate(p_crossover_rate)
        {
            // adjust crossover rate if necessary
            if (m_crossover_rate > 1.0)
                m_crossover_rate = 1.0;
            else if (m_crossover_rate < 0.0)
                m_crossover_rate = 0.0;
        }

        //! Copy constructor
        /*!
            Duplicates an existing object.
            \param a_source - The source object
        */
        function_reproducer(const function_reproducer & a_source)
            : m_crossover_rate(a_source.m_crossover_rate)
        {
            // nada
        }

        //! Virtual destructor
        /*!
            Satisfies the requirements of the base class; does nothing at this time.
        */
        virtual ~function_reproducer()
        {
            // nada
        }

        //! Assignment operator
        /*!
            Assigns the state of one object to another.
            \param a_source - The source object
            \return A reference to <i>this</i>
        */
        function_reproducer & operator = (const function_reproducer & a_source)
        {
            m_crossover_rate = a_source.m_crossover_rate;
            return *this;
        }

        //! Gets the crossover rate
        /*!
            Returns the crossover rate set for this reproducer.
            \return Crossover rate
        */
        double crossover_rate() const
        {
            return m_crossover_rate;
        }

        //! Reproduction for solutions
        /*!
            Breeds new solutions, by cloning or the combination of elements from parent organisms. By
            default, the crossover rate is 1.0 (100%), meaning that all children stem from crossover
            between two parents. The crossover is implemented on a argument-by-argument basis; in other
            words, crossover occurs between corresponding elements of the parent solutions.
            \param a_population - A population of solutions
            \param p_limit - Maximum number of children
            \return A vector containing new "child" chromosomes
        */
        virtual vector<function_solution> breed(const vector<function_solution> & a_population, size_t p_limit);

    private:
        // crossover chance
        double m_crossover_rate;
    };

    //! Defines the test for a population of solutions
    /*!
        A "fitness" landscape defines the environment in which an organism 
        competes for survival. In the case of function optimization, the
        "test" is (obviously!) a function.
    */
    class function_landscape : public landscape<function_solution>, protected fopt_global
    {
    public:
        //! Creation constructor
        /*!
            Creates a new landscape with a given fitness function.
        */
        function_landscape(t_function * a_function, listener & a_listener)
          : landscape<function_solution>(a_listener),
            m_function(a_function)
        {
            // nada
        }
        
        //! Copy constructor
        function_landscape(const function_landscape & a_source)
          : landscape<function_solution>(a_source),
            m_function(a_source.m_function)
        {
            // nada
        }

        //! Assignment
        function_landscape & operator = (const function_landscape & a_source)
        {
            landscape<function_solution>::operator = (a_source);
            m_function = a_source.m_function;
        }

        //! Virtual destructor
        /*!
            Satisfies the requirements of the base class; does nothing at this time.
        */
        ~function_landscape()
        {
            // nada
        }

        //! Performs fitness testing
        /*!
            Tests a single chromosome for fitness by calling the fitness function provided
            in the constructor.
            \param a_organism - The organism to be tested by the landscape.
            \return Computed fitness for this organism
        */
        virtual double test(function_solution & a_organism, bool a_verbose = false) const
        {
            a_organism.fitness() = m_function(a_organism.genes());
            return a_organism.fitness();
        }
        
        //! Fitness testing
        /*!
            Tests each chromosome by calling the fitness function provided in the constructor.
            \param a_population - Population undergoing fitness testing
            \return Average fitness of population
        */
        virtual double test(vector<function_solution> & a_population) const
        {
            double result = 0.0;
            
            for (vector<function_solution>::iterator solution = a_population.begin(); solution != a_population.end(); ++solution)
            {
                solution->fitness() = m_function(solution->genes());
                result += solution->fitness();
            }
            
            // algorithm doesn't use this return value, so return nothing.
            return result / (double)a_population.size();
        }

    private:
        // fitness function pointer
        t_function * m_function;
    };

    //! Reports the state of a population of solutions
    /*!
        A simple reporter for diaplying information about the populations
        as it evolves.
    */
    class function_reporter : public reporter<function_solution, function_landscape>
    {
        public:
            //! Constructor
            /*!
                Creates a new reporter object
                \param a_listener - a listener for events
            */
            function_reporter()
              : reporter<function_solution, function_landscape>(m_listener)
            {
                // nada
            }
                
            //! Say something about a population
            /*!
                Reports the genes and fitness for the best solution.
                \param a_populations - Population for reporting
                \param a_iteration - Iteration count for this report
                \param a_fitness - Not used in function_reporter; ignored
                \param a_finished - Not used in function_reporter; ignored
            */
            virtual bool report(const vector< vector<function_solution> > & a_population, size_t a_iteration, double & a_fitness, bool a_finished = false);

        protected:
            listener_stdout m_listener;
    };

    //! A generic function optimizer
    /*!
        Using instances of the other classes, this class binds together the pieces to
        create a complete function optimizer. A user of this class defines two functions
        -- a solution initializer and a fitness test -- that define the target problem.
    */
    class function_optimizer : protected fopt_global,
                               protected organism_factory<function_solution>,
                               protected landscape_factory<function_landscape>
    {
    private:
        // a function type
        typedef function_solution t_init();

        // objects that define the characteristics of the genetic algorithm
        function_mutator                    m_mutator;
        function_reproducer                 m_reproducer;
        null_scaler<function_solution>      m_scaler;
        null_migrator<function_solution>    m_migrator;
        elitism_selector<function_solution> m_selector;
        function_reporter                   m_reporter;
        
        // the evocosm binds it all together; kinda like the "one ring" Bilbo found!
        evocosm<function_solution,function_landscape> * m_evocosm;
        
        // number of iterations to run
        const size_t                        m_iterations;
        
        // a function that provides initialized, random solutions
        t_init *                            m_init;
        
        // the function to be optimized
        t_function *                        m_function;

        // null listener
        null_listener                       m_listener;

    public:
        //! Constructor
        /*!
            Creates a new function_optimizer with the given set of parameters.
            \param a_function - Address of the function to be optimized.
            \param a_init - Address of a function that initializes solutions.
            \param a_population - The size of the solution population.
            \param a_mutation_rate - Mutation rate in the range [0,1].
            \param a_iterations - Number of iterations to perform when doing a run.
        */
        function_optimizer(t_function * a_function,
                           t_init * a_init,
                           size_t a_population,
                           double a_mutation_rate,
                           size_t a_iterations);

        //! Destructor
        /*!
            Cleans up resources by removing allocated objects.
        */
        virtual ~function_optimizer()
        {
            delete m_evocosm;
        }

        //! Performs optimization
        /*!
            This is where the work gets done; run iterates the number of times specificed when creating
            this function_optimizer, reporting via a function_reporter object on the progress of
            optimization.
        */
        void run();
        
        //! Organism factory
        /*!
            Generates organisms for the initial populations in the evocosm.
        */
        virtual function_solution create();

        //! Organism factory
        /*!
            Appends several organisms to a population.
        */
        virtual void append(vector<function_solution> & a_population, size_t a_size);
        
        //! Landscape factory
        /*!
            Generates landscapes for an evocosm. I called this funtion "generate"
            to avoid collisions with the "create" method in organism_factory.
        */
        virtual function_landscape generate();
    };

};

#endif
