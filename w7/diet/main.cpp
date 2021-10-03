//stl includes
#include<iostream>
#include<iomanip>
#include<vector>

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
	int m;
	std::cin >> m;
	std::vector<int> max(n);
	std::vector<int> min(n);
	std::vector<int> p(m);
	std::vector<std::vector<int>> C(m, std::vector<int> (n));

	for(int i = 0; i < n; i++){
		std::cin >> min[i] >> max[i];
	}

	for(int i = 0; i < m; i++){
		std::cin >> p[i];
		for(int j = 0; j < n; j++){
			std::cin >> C[i][j];
		}
	}

	Program lp (CGAL::SMALLER, true, 0, false, 0);

	int count = 0;

	for(int j = 0; j < n; j++){
		for(int i = 0; i < m; i++){
			lp.set_a(i, count, C[i][j]);
		}
		lp.set_b(count, max[j]);
		count++;

		for(int i = 0; i < m; i++){
			lp.set_a(i, count, -C[i][j]);
		}
		lp.set_b(count, -min[j]);
		count++;
	}

	for(int i = 0; i < m; i++){
		lp.set_c(i, p[i]);
	}
	
	Solution s = CGAL::solve_linear_program(lp,ET());

	if(s.is_infeasible()) std::cout << "No such diet." << std::endl;
	else std::cout << std::floor(CGAL::to_double(s.objective_value())) <<std::endl;

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
