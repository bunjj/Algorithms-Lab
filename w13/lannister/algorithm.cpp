#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

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

void testcase() {
	int n, m; long s;
	std::cin >> n >> m>> s;
	Program lp (CGAL::SMALLER, false, 0, false, 0); 
	const int b_s = 0, c_s = 1, c_w = 2, d = 3;
	int count = 0;
	long sum_x = 0;
	long sum_y = 0;
	for(int i = 0; i < n + m; i++){
		int sign = (i < n) ? -1 : 1;
		int x, y;
		std::cin >> x >> y;
		sum_x += sign * x;
		sum_y -= sign * y;

		lp.set_a(b_s, count, sign * y);
		lp.set_a(c_s, count, sign);
		lp.set_b(count, sign * x);
		count ++;

		lp.set_a(c_w, count, 1);
		lp.set_a(b_s, count, -x);
		lp.set_a(d, count, -1);
		lp.set_b(count, y);
		count++;

		lp.set_r(count, CGAL::LARGER);
		lp.set_a(c_w, count, 1);
		lp.set_a(b_s, count, -x);
		lp.set_a(d, count, 1);
		lp.set_b(count, y);
		count++;
	}
	lp.set_l(d, true, 0);
	lp.set_c(d, 1);

	Solution sol = CGAL::solve_linear_program(lp, ET());
	if(sol.is_infeasible()){
		std::cout << "Yuck!" << std::endl;
	}else{
		if(s == -1){
			std::cout << std::ceil(CGAL::to_double(sol.objective_value()))<<std::endl;
		}else{
			lp.set_a(b_s, count, sum_y);
			lp.set_a(c_s, count, n-m);
			lp.set_b(count, s- sum_x);
			sol = CGAL::solve_linear_program(lp, ET());

			if(sol.is_infeasible()){
				std::cout << "Bankrupt!"<< std::endl;
			}else{
				std::cout << std::ceil(CGAL::to_double(sol.objective_value())) << std::endl;
			}
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
