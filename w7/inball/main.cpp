//STL includes
#include<iostream>
#include<iomanip>
#include<vector>

//CGAL includes
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;



void testCase(int n){
	int d;
	std::cin >>d;

	Program lp (CGAL::SMALLER, false, 0 , false ,0);
	const int R = d;
	std::vector<int> b(n);
	std::vector<std::vector<int>> a (n, std::vector<int> (d));
	for(int i = 0; i < n; i++){
		for(int j = 0;  j < d; j++){
			std::cin >> a[i][j];
		}
		std::cin >> b[i];
	}

	lp.set_l(R, true, 0);
	for(int i = 0; i < n; i++){
		long sum_a = 0;
		for(int j = 0; j < d; j++){
			lp.set_a(j, i, a[i][j]);
			sum_a += a[i][j] * a[i][j];
		}
		sum_a = std::sqrt(sum_a);
		lp.set_a(R, i, sum_a);
		lp.set_b(i, b[i]);
	}

	lp.set_c(R, -1);
	Solution s = CGAL::solve_linear_program(lp, ET());

	if(s.is_infeasible())
		std::cout << "none" << std::endl;
	else if(s.is_unbounded()) std::cout<< "inf" <<std::endl;
	else std::cout << -s.objective_value_numerator() / s.objective_value_denominator() << std::endl;



}



int main(){
	std::ios_base::sync_with_stdio(false);
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

	int n;
	std::cin >> n;
	while(n){
		testCase(n);
		std::cin >> n;
	}

	return 0;
}
