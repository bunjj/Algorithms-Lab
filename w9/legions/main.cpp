//STL includes
#include<iostream>
#include<iomanip>
#include<vector>
#include<cmath>

//CGL includes
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef long IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


void testCase(){


	Program lp(CGAL::SMALLER, false, 0, false, 0);
	const int X = 0;
	const int Y = 1;
	const int time = 2;

	int x, y, n;
	std::cin >> x >> y >> n;

	lp.set_l(time, 0);

	for(int i = 0; i < n; i++){
		long a, b, c;
		int v;
		std::cin >> a >> b >> c >> v;
		int sign = (a*x + b *y +c >= 0) ? 1 : -1;
		long delta = v * std::sqrt(a * a + b * b);
		lp.set_a(time, i, delta);
		lp.set_a(X, i, -sign*a);
		lp.set_a(Y, i, -sign*b);
		lp.set_b(i, sign * c);
	}

	lp.set_c(time, -1);

	Solution s = CGAL::solve_linear_program(lp, ET());
	std::cout << std::floor(CGAL::to_double(-s.objective_value())) << std::endl;
}


int main(){
	std::ios_base::sync_with_stdio(false);
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

	int t;
	std::cin >> t;

	while(t--) testCase();

	return 0;
}
