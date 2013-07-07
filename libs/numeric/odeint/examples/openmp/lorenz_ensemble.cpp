/* Boost libs/numeric/odeint/examples/openmp/lorenz_ensemble.cpp

 Copyright 2009-2012 Karsten Ahnert
 Copyright 2009-2012 Mario Mulansky

 Parallelized Lorenz ensembles

 Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifdef _OPENMP

#include <omp.h>
#include <vector>
#include <iostream>
#include <iterator>
#include <boost/numeric/odeint.hpp>
#include <boost/numeric/odeint/external/openmp/openmp.hpp>
#include "point_type.hpp"

using namespace std;

typedef point<double, 3> point_type;
typedef vector< point_type > inner_state_type;

const double sigma = 10.0;
const double b = 8.0 / 3.0;


struct sys_func {
    const vector<double> &R;
    sys_func( vector<double> &R ) : R(R) {}

    void operator()( const inner_state_type &x , inner_state_type &dxdt , double t , size_t offset ) const {
        for(size_t i = 0 ; i < x.size() ; i++) {
            const point_type &xi = x[i];
            point_type &dxdti = dxdt[i];
            dxdti[0] = -sigma * (xi[0] - xi[1]);
            dxdti[1] = R[offset + i] * xi[0] - xi[1] - xi[0] * xi[2];
            dxdti[2] = -b * xi[2] + xi[0] * xi[1];
        }
    }
};


int main() {
    using namespace boost::numeric::odeint;

    typedef openmp_state<inner_state_type> state_type;

    const size_t n = 1024;
    vector<double> R(n);
    const double Rmin = 0.1, Rmax = 50.0;
#   pragma omp parallel for
    for(size_t i = 0 ; i < n ; i++)
        R[i] = Rmin + (Rmax - Rmin) / (n - 1) * i;

    inner_state_type inner(n, point_type(10, 10, 10));
    state_type state(inner);

    typedef runge_kutta4< state_type, double > stepper;

    const double t_max = 10.0, dt = 0.01;

    integrate_const(
        stepper(),
        openmp_wrapper( sys_func(R) ),
        state,
        0.0, t_max, dt
    );

    for(size_t i = 0 ; i < state.size() ; i++)
        copy( state[i].begin(), state[i].end(), ostream_iterator<point_type>(cout, "\n") );

    return 0;
}

#else

int main() { return -1; }

#endif
