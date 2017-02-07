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

#include <iostream>
#include <iomanip>
using namespace std;

#include "roulette.h"
#include "function_optimizer.h"
using namespace libevocosm;

// floating-point manipulator
libevocosm::evoreal fopt_global::g_evoreal;

// mutate a set of organisms
void function_mutator::mutate(vector<function_solution> & a_population)
{
    for (int i = 0; i < a_population.size(); ++i)
    {
        for (int n = 0; n < a_population[i].genes.size(); ++n)
        {
            if (g_random.get_real() <= m_mutation_rate)
                a_population[i].genes[n] = g_evoreal.mutate(a_population[i].genes[n]);
        }

    }
}

// create children
vector<function_solution> function_reproducer::breed(const vector<function_solution> & a_population, size_t a_limit)
{
    // construct a fitness wheel
    vector<double> wheel_weights;

    for (int i = 0; i < a_population.size(); ++i)
        wheel_weights.push_back(a_population[i].fitness > 0.0 ? a_population[i].fitness : 0.0);

    roulette_wheel fitness_wheel(wheel_weights);

    // create children
    vector<function_solution> children;

    while (a_limit > 0)
    {
        // clone an existing organism as a child
        size_t g1 = fitness_wheel.get_index();
        vector<double> parent1 = a_population[g1].genes;

        // do we crossover?
        if (g_random.get_real() < m_crossover_rate)
        {
            // select a second parent
            size_t g2 = g1;

            while (g2 == g1)
                g2 = fitness_wheel.get_index();

            const vector<double> parent2 = a_population[g2].genes;

            // reproduce
            for (size_t n = 0; n < parent1.size(); ++n)
                parent1[n] = g_evoreal.crossover(parent1[n],parent2[n]);
        }

        // add child to new population
        children.push_back(function_solution(parent1));

        // one down, more to go?
        --a_limit;
    }

    // outa here!
    return children;
}

// say something about a population
bool function_analyzer::analyze(const vector<function_solution> & a_population,
                                size_t a_iteration,
                                double & a_fitness)
{
    fitness_stats<function_solution> stats(a_population);

    // see if the current best equals the previous best
    if (m_prev_best.genes.size() == stats.getBest().genes.size())
    {
        bool equal = true;

        for (int n = 0; n < m_prev_best.genes.size(); ++n)
        {
            if (m_prev_best.genes[n] != stats.getBest().genes[n])
            {
                equal = false;
                break;
            }
        }

        if (equal)
            ++m_count;
        else
            m_count = 0;
    }

    m_prev_best = stats.getBest();

    // if the best is the same ten generations in a row, we're done (in theory)
    return ((m_count < 20) || (m_max_iterations == a_iteration));
}

void function_listener::ping_generation_begin(size_t a_iteration)
{
    // nada
}

void function_listener::ping_generation_end(const vector<function_solution> & a_population, size_t a_iteration)
{
    // get stats for population
    fitness_stats<function_solution> stats(a_population);

    // save format state of cout
    ios_base::fmtflags save_state = cout.flags();

    // display best solution
    cout << setw(5) << setfill(' ') << a_iteration << ": (";

    cout << showpoint << setprecision(8) << showpos;

    for (int n = 0; n < stats.getBest().genes.size(); ++n)
        cout << right << setw(11) << stats.getBest().genes[n] << ", " ;

    cout << noshowpos << "\b\b) = " <<  stats.getBest().value << " [fit = " << stats.getBest().fitness << "]" << endl;

    // restore format state of cout
    cout.flags(save_state);
}


// constructor
function_optimizer::function_optimizer(t_function * a_function,
                                       size_t       a_nargs,
                                       double       a_minarg,
                                       double       a_maxarg,
                                       size_t       a_norgs,
                                       double       a_mutation_rate,
                                       size_t       a_iterations)
  : m_population(),
    m_landscape(a_function, *this),
    m_mutator(a_mutation_rate),
    m_reproducer(0.9),      // use crossover 90% of the time during reproduction
    m_scaler(10.0),         // scale fitness(0..10)
    m_selector(0.90),       // keep those with fitness >= .9 best
    m_evocosm(NULL),
    m_iterations(a_iterations),
    m_analyzer(*this, a_iterations)
{
    // create the population
    for (int n = 0; n < a_norgs; ++n)
        m_population.push_back(function_solution(a_nargs,a_minarg,a_maxarg));

    // create an evocosm to evolve the population
    m_evocosm = new evocosm<function_solution>(m_population,
                                               m_landscape,
                                               m_mutator,
                                               m_reproducer,
                                               m_scaler,
                                               m_selector,
                                               m_analyzer,
                                               *this);
}

function_optimizer::~function_optimizer()
{
    delete m_evocosm;
}

void function_optimizer::run()
{
    m_evocosm->set_sleep_time(0);

    cout << "generation,x,y,fitness" << endl;

    // continue for specified number of iterations
    while (m_evocosm->run_generation()) { /* nada */ }

    cout << "run complete" << endl;
}

