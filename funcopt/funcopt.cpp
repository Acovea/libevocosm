//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  A multiargument function optimizer based on Evocosm
//
//  funcopt.cpp
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
//
//  For more information on this software package, please visit
//  Scott's web site, Coyote Gulch Productions, at:
//
//      http://www.coyotegulch.com
//  
//-----------------------------------------------------------------------

#include <iostream>
#include <iomanip>
using namespace std;

#include "funcopt.h"
using namespace funcopt;

#include "../libevocosm/roulette.h"

// floating-point manipulator
libevocosm::evoreal fopt_global::g_evoreal;

// mutate a set of organisms
void function_mutator::mutate(vector<function_solution> & a_population)
{
    for (vector<function_solution>::iterator solution = a_population.begin(); solution != a_population.end(); ++solution)
    {
        for (vector<double>::iterator arg = solution->genes().begin(); arg != solution->genes().end(); ++arg)
        {
            if (g_random.get_rand_real2() <= m_mutation_rate)
                *arg = g_evoreal.mutate(*arg);
        }
    }
}

// create children
vector<function_solution> function_reproducer::breed(const vector<function_solution> & a_population, size_t p_limit)
{
    // result
    vector<function_solution> children;

    // construct a fitness wheel
    vector<double> wheel_weights;

    for (vector<function_solution>::const_iterator solution = a_population.begin(); solution != a_population.end(); ++solution)
        wheel_weights.push_back(solution->fitness());

    roulette_wheel fitness_wheel(wheel_weights);

    // create children
    while (p_limit > 0)
    {
        // clone an existing organism as a child
        size_t genes_index = fitness_wheel.get_index();
        function_solution child = a_population[genes_index];
        vector<double> & child_genes = child.genes();

        // do we crossover?
        if (g_random.get_rand_real2() <= m_crossover_rate)
        {
            // select a second parent
            size_t second_index = genes_index;

            while (second_index == genes_index)
                second_index = fitness_wheel.get_index();

            const vector<double> & second_genes = a_population[second_index].genes();

            // reproduce
            for (size_t n = 0; n < child_genes.size(); ++n)
                child_genes[n] = g_evoreal.crossover(child_genes[n],second_genes[n]);
        }

        // add child to new population
        children.push_back(child);

        // one down, more to go?
        --p_limit;
    }

    // outa here!
    return children;
}

// say something about a population
bool function_reporter::report(const vector< vector<function_solution> > & a_populations, size_t a_iteration, double & a_fitness, bool a_finished)
{
    // search for best chromosome; there will be only one population for this application
    function_solution best = *(a_populations.begin()->begin());

    for (vector<function_solution>::const_iterator solution = a_populations.begin()->begin(); solution != a_populations.begin()->end(); ++solution)
    {
        if (solution->fitness() > best.fitness())
            best = *solution;
    }
    
    // return best fitness via argument (actually ignored by calling function right now)
    a_fitness = best.fitness();

    // display best solution
    size_t n = 0;

    cout.precision(15);

    for (vector<double>::iterator arg = best.genes().begin(); arg != best.genes().end(); ++arg, ++n)
        cout << "[" << n << "] " << *arg << "\n";

    cout << setfill(' ') << "fitness = " << setw(2) << best.fitness() << endl;

    return true;
}

// constructor
function_optimizer::function_optimizer(t_function * a_function,
                                       t_init * a_init,
                                       size_t a_population,
                                       double a_mutation_rate,
                                       size_t a_iterations)
  : m_mutator(a_mutation_rate),
    m_reproducer(1.0),
    m_scaler(),
    m_migrator(),
    m_selector(a_population / 10),
    m_reporter(),
    m_evocosm(NULL),
    m_iterations(a_iterations),
    m_init(a_init),
    m_function(a_function),
    m_listener()
{
    if (a_function == NULL)
        throw runtime_error("NULL landscape pointer in optimizer construction");

    if (a_init == NULL)
        throw runtime_error("NULL organism initializer in optimizer construction");

    m_evocosm = new evocosm<function_solution,function_landscape>(m_listener,
                                                                  a_population,
                                                                  1,
                                                                  0,
                                                                  1,
                                                                  m_mutator,
                                                                  m_reproducer,
                                                                  m_scaler,
                                                                  m_migrator,
                                                                  m_selector,
                                                                  m_reporter,
                                                                  *this,
                                                                  *this);
}

void function_optimizer::run()
{
    // continue for specified number of iterations
    for (size_t count = 1; count <= m_iterations; ++count)
    {
        // display generation number
        cout << "\ngen " << count << endl;

        // run a generation
        double dummy;
        m_evocosm->run_generation(true,dummy);
    }
}
        
// Organism factory
function_solution function_optimizer::create()
{
    return m_init();
}

void function_optimizer::append(vector<function_solution> & a_population, size_t a_size)
{
    // fill remaining population with random values    
    for (size_t i = 0; i < a_size; ++i)
        a_population.push_back(m_init());
}

// Landscape factory
function_landscape function_optimizer::generate()
{
    return function_landscape(m_function, m_listener);
}
