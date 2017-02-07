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

// Standard C++
#include <cerrno>
#include <cmath>
#include <limits>
#include <iostream>
#include <iomanip>
using namespace std;

// other elements of Evocosm
#include "../../libevocosm/evocosm.h"
#include "../../libevocosm/simple_machine.h"
using namespace libevocosm;

#include "command_line.h"

typedef organism< simple_machine<2,2> > pdsm_strategy;

// Stream output operator
ostream & operator << (ostream & strm, const pdsm_strategy & strategy)
{
    static string choices[] = { "C", "D" };

    strm << "initial state: " << strategy.genes.init_state() << endl;

    for (size_t s = 0; s < strategy.genes.size(); ++s)
    {
        strm << "state " << s << endl;

        for (size_t i = 0; i < 2; ++i)
        {
            const typename simple_machine<2, 2>::tranout_t & tran = strategy.genes.get_transition(s,i);

            strm << "  in "       << choices[i]
                    << " -> "     << tran.m_new_state
                    << ", out = " << choices[tran.m_output]
                    << endl;
        }
    }

    return strm;
}

class pdsm_mutator : public mutator<pdsm_strategy>
{
public:
    pdsm_mutator(double a_mutation_rate)
        : m_mutation_rate(a_mutation_rate)
    {
        // adjust mutation rate if necessary
        if (m_mutation_rate > 1.0)
            m_mutation_rate = 1.0;
        else if (m_mutation_rate < 0.0)
            m_mutation_rate = 0.0;
    }

    pdsm_mutator(const pdsm_mutator & a_source)
        : m_mutation_rate(a_source.m_mutation_rate)
    {
        // nada
    }

    virtual ~pdsm_mutator()
    {
        // nada
    }

    pdsm_mutator & operator = (const pdsm_mutator & a_source)
    {
        m_mutation_rate = a_source.m_mutation_rate;
        return *this;
    }

    double mutation_rate() const
    {
        return m_mutation_rate;
    }

    void mutate(vector<pdsm_strategy> & a_population)
    {
        for (int i = 0; i < a_population.size(); ++i)
            a_population[i].genes.mutate(m_mutation_rate);
    }

private:
    // rate of mutation
    double m_mutation_rate;
};

class pdsm_reproducer : public reproducer<pdsm_strategy>
{
public:
    pdsm_reproducer(double p_crossover_rate = 1.0)
        : m_crossover_rate(p_crossover_rate)
    {
        // adjust crossover rate if necessary
        if (m_crossover_rate > 1.0)
            m_crossover_rate = 1.0;
        else if (m_crossover_rate < 0.0)
            m_crossover_rate = 0.0;
    }

    pdsm_reproducer(const pdsm_reproducer & a_source)
        : m_crossover_rate(a_source.m_crossover_rate)
    {
        // nada
    }

    virtual ~pdsm_reproducer()
    {
        // nada
    }

    pdsm_reproducer & operator = (const pdsm_reproducer & a_source)
    {
        m_crossover_rate = a_source.m_crossover_rate;
        return *this;
    }

    double crossover_rate() const
    {
        return m_crossover_rate;
    }

    virtual vector<pdsm_strategy> breed(const vector<pdsm_strategy> & a_population, size_t a_limit)
    {
        // construct a fitness wheel
        vector<double> wheel_weights;

        for (int i = 0; i < a_population.size(); ++i)
            wheel_weights.push_back(a_population[i].fitness > 0.0 ? a_population[i].fitness : 0.0);

        roulette_wheel fitness_wheel(wheel_weights);

        // create children
        vector<pdsm_strategy> children;

        while (a_limit > 0)
        {
            // clone an existing organism as a child
            size_t p1 = fitness_wheel.get_index();

            // do we crossover?
            if (g_random.get_real() < m_crossover_rate)
            {
                // select a second parent
                size_t p2 = p1;

                while (p2 == p1)
                    p2 = fitness_wheel.get_index();

                children.push_back(pdsm_strategy(simple_machine<2,2>(a_population[p1].genes, a_population[p2].genes)));
            }
            else
                children.push_back(pdsm_strategy(a_population[p1].genes));

            // one down, more to go?
            --a_limit;
        }

        // outa here!
        return children;
    }

private:
    // crossover chance
    double m_crossover_rate;
};

class pdsm_landscape : public landscape<pdsm_strategy>
{
private:
    // number of rounds played in each contest
    size_t m_rounds;

public:
    pdsm_landscape(listener<pdsm_strategy> & a_listener, size_t a_rounds)
        : landscape<pdsm_strategy>(a_listener),
        m_rounds(a_rounds > 0 ? a_rounds : 1)
    {
        // nada
    }

    pdsm_landscape(const pdsm_landscape & a_source)
        : landscape<pdsm_strategy>(a_source),
          m_rounds(a_source.m_rounds)
    {
        // nada
    }

    pdsm_landscape & operator = (const pdsm_landscape & a_source)
    {
        landscape<pdsm_strategy>::operator = (a_source);
        m_rounds = a_source.m_rounds;
        return *this;
    }

    ~pdsm_landscape()
    {
        // nada
    }

    virtual double test(pdsm_strategy & a_organism, bool a_verbose = false) const
    {
        // this function is merely a placeholder; it is never called
        return a_organism.fitness;
    }

    virtual double test(vector<pdsm_strategy> & a_population) const
    {
        static const double P = 1.0; // punishment for mutual defection
        static const double R = 3.0; // reward for mutual cooperation
        static const double S = 0.0; // sucker's payoff (you lose)
        static const double T = 5.0; // temptation to defect

        static const double payout[2][2][2] = { { { R, R }, { S, T } },
                                                { { T, S }, { P, P } } };

        double result = 0.0;

        for (int red = 0; red < (int)a_population.size(); ++red)
        {
            // reset fitness (to zero) for test strategy
            a_population[red].reset();

            for (size_t blue = 0; blue < (int)a_population.size(); ++blue)
            {
                // don;t test against self
                if (red != blue)
                {
                    // reset starting state for machine
                    a_population[red].genes.reset();
                    a_population[blue].genes.reset();

                    // random "previous" move to get things going
                    size_t prev_red_move  = 0; //rand_index(2);
                    size_t prev_blue_move = 0; //rand_index(2);

                    // play game for a given number of rounds
                    for (int round = 0; round < m_rounds; ++round)
                    {
                        // transition to new state based on previous move
                        size_t red_move  = a_population[red].genes.transition(prev_blue_move);
                        size_t blue_move = a_population[blue].genes.transition(prev_red_move);

                        // update fitness of test strategy
                        a_population[red].fitness += payout[red_move][blue_move][0];

                        // get ready for next round
                        prev_red_move  = red_move;
                        prev_blue_move = blue_move;
                    }
                }
            }

            a_population[red].fitness /= static_cast<double>((a_population.size() - 1) * m_rounds);

            result += a_population[red].fitness;
        }

        // return average fitness
        return result / (double)a_population.size();
    }
};

class pdsm_listener : public null_listener<pdsm_strategy>
{
public:
    virtual void ping_generation_begin(size_t a_iteration)
    {
        // nada
    }

    virtual void ping_generation_end(const vector<pdsm_strategy> & a_population, size_t a_iteration)
    {
        // get stats for population
        fitness_stats<pdsm_strategy> stats(a_population);

        // display best solution
        cout << a_iteration << ","
             << stats.getBest().fitness << ","
             << stats.getMean() << ","
             << stats.getSigma() << endl;
    }

    virtual void run_complete(const vector<pdsm_strategy> & a_population)
    {
        // get stats for population
        fitness_stats<pdsm_strategy> stats(a_population);

        // display best solution
        cout << "\nRUN COMPLETE\n\n"
             << "    best fitness = " << stats.getBest().fitness << "\n"
             << "    mean fitness = " << stats.getMean() << "\n"
             << "  std. deviation = " << stats.getSigma() << "\n\n"
             << stats.getBest().genes << endl;
    }
};

int main(int argc, char * argv[])
{
    size_t pop_size        =  500;
    size_t test_length     =  100;
    size_t machine_size    =    4;
    size_t rounds          =   20;
    double mutation_rate   =    0.25;
    double survival_factor =    0.5;
    double crossover_rate  =    1.0;

    // parse arguments
    set<string> bool_options; // empty list
    command_line args(argc,argv,bool_options);

    for (vector<command_line::option>::const_iterator opt = args.get_options().begin(); opt != args.get_options().end(); ++opt)
    {
        if (opt->m_name == "size")
        {
            machine_size = (size_t)atoi(opt->m_value.c_str());

            if (machine_size < 2)
                machine_size = 2;
        }
        else if (opt->m_name == "population")
        {
            pop_size = (size_t)atoi(opt->m_value.c_str());

            if (pop_size < 10)
                machine_size = 10;
        }
        else if (opt->m_name == "generations")
        {
            test_length = (size_t)atoi(opt->m_value.c_str());

            if (test_length < 10)
                test_length = 10;
        }
        else if (opt->m_name == "rounds")
        {
            rounds = (size_t)atoi(opt->m_value.c_str());

            if (rounds < 10)
                rounds = 10;
        }
        else if (opt->m_name == "mutation")
        {
            mutation_rate = atof(opt->m_value.c_str());

            if (mutation_rate < 0.0)
                mutation_rate = 0.0;

            if (mutation_rate > 0.5)
                mutation_rate = 0.5;
        }
        else if (opt->m_name == "crossover")
        {
            crossover_rate = atof(opt->m_value.c_str());

            if (crossover_rate < 0.0)
                crossover_rate = 0.0;

            if (crossover_rate > 1.0)
                crossover_rate = 1.0;
        }
        else if (opt->m_name == "survival")
        {
            survival_factor = atof(opt->m_value.c_str());

            if (survival_factor < 0.0)
                survival_factor = 0.0;

            if (survival_factor > 1.0)
                survival_factor = 1.0;
        }
    }

    // create population
    vector< pdsm_strategy > population;

    for (int n = 0; n < pop_size; ++n)
        population.push_back(pdsm_strategy(simple_machine<2,2>(machine_size)));

    // create the optimizer and its components
    pdsm_listener                     test_listener;
    pdsm_landscape                    test_landscape(test_listener, rounds);
    pdsm_mutator                      test_mutator(mutation_rate);
    pdsm_reproducer                   test_reproducer(crossover_rate);
    linear_norm_scaler<pdsm_strategy> test_scaler;
    elitism_selector<pdsm_strategy>   test_selector(survival_factor);
    analyzer<pdsm_strategy>           test_analyzer(test_listener, test_length);

    evocosm<pdsm_strategy> test_evocosm(population,
                                        test_landscape,
                                        test_mutator,
                                        test_reproducer,
                                        test_scaler,
                                        test_selector,
                                        test_analyzer,
                                        test_listener);

    test_evocosm.set_sleep_time(0);

    // continue for specified number of iterations
    cout << "iteration,best fitness,mean fitness, std deviation" << endl;
    while (test_evocosm.run_generation()) { /* nada */ }

    // done
    cout << "run complete\n" << endl;
    return 0;
}
