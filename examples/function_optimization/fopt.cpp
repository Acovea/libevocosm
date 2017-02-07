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

// Function optimizer
#include "../../libevocosm/function_optimizer.h"
using namespace libevocosm;

// we're looking for a peak of ~7.9468 at ~(-0.6550, 0.5)
vector<double> sample_test(vector<double> p_args)
{
    double z = 0.0;

    // Make certain we have two, and only two values
    if (p_args.size() == 2)
    {
        // run it through the formula
        double x = p_args[0];
        double y = p_args[1];

        // automatically reject out-of-range values
        if ((x <= 1.0) && (x >= -1.0) && (y <= 1.0) && (y >= -1.0))
        {
            // the actual formula
            z = 0.8 + pow(x + 0.5, 2.0) + 2.0 * pow(y - 0.5, 2.0) - 0.3 * cos(3.0 * BRAHE_PI * x) - 0.4 * cos(4.0 * BRAHE_PI * y);

            // check for cosine errors (MS uses errno for cos errors)
            if (errno != 0)
            {
                // bad cosine equals lousy fitness
                z = 0.0;
                errno = 0;
            }
        }
    }

    vector<double> result;

    result.push_back(z);
    result.push_back((z != 0) ? (1.0 / z) : 0.0); // fitness is recip of value

    return result;
}

int main()
{
    // create the optimizer
    cout << "Creating optimizer... " << flush;
    function_optimizer optimizer(&sample_test, 2, -1.0, +1.0, (size_t)10000, 0.25, (size_t)1000);
    cout << "done" << endl;

    // run the optimizer
    cout << "Beginning optimizer run" << endl;
    optimizer.run();

    // done -- wasn't that easy? ;}
    cout << "Done" << endl;
    return 0;
}
