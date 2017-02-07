//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//  An example of using a function optimizer based on Evocosm
//
//  runfuncopt.cpp
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

#include <cerrno>
#include <cmath>
#include <limits>
using namespace std;

#include "libcoyotl/mwc1038.h"
using namespace libcoyotl;

#include "funcopt.h"
using namespace funcopt;

// function to initialize a solution
function_solution init_solution()
{
    // just for this routine
    static mwc1038 random;

    // make sure the args are empty
    vector<double> solution;

    // values fall in the range [-1,1]
    for (size_t n = 0; n < 2; ++n)
        solution.push_back(random.get_rand_real2() * 2.0 - 1.0);
    
    return function_solution(solution);
}

double scotts_test(vector<double> p_args)
{
    // if the genes are malformed, this organism is very unfit
    if (p_args.size() < 2)
        return numeric_limits<double>::min();

    // run it through the formula
    static const double PI = 3.141592653589793238;
    double x = p_args[0];
    double y = p_args[1];

    // automatically reject out-of-range values    
    if ((x > 1.0) || (x < -1.0) || (y > 1.0) || (y < -1.0))
        return numeric_limits<double>::min();

    // number crunch -- chomp, chomp
    double result = 1.0
                  / (0.8 + (x + 0.5) * (x + 0.5)
                      + 2.0 * (y - 0.5) * (y - 0.5)
                      - 0.3 * cos(3.0 * PI * x)
                      - 0.4 * cos(4.0 * PI * y));
	 
    // check for cos errors (MS uses errno for cos errors)
    if (errno != 0)
    {
    	result = numeric_limits<double>::min();
    	errno = 0;
    }
	 
    return result;
}

int main()
{
    // create the optimizer
    function_optimizer optimizer(scotts_test,init_solution,1000,0.10F,100);

    // run the optimizer
    optimizer.run();

    // done -- wasn't that easy? ;}
    return 0;
}
