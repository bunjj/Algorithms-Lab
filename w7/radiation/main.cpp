//STL incldues
#include<iostream>
#include<iomanip>
#include<vector>
#include<math.h>

//CGAL imports
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef CGAL::Gmpz IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


struct cell{
	int x;
	int y;
	int z;
};

int h, t;
std::vector<cell> h_cell;
std::vector<cell> t_cell;

bool solvable(int d){
	int count = 0; //counter to count the constraint
	Program lp(CGAL::SMALLER, false, 0, false, 0);

	for(int i = 0; i < h; i++){
		lp.set_r(count, CGAL::LARGER);
		int param = 0; //counter for the paramter
		for(int j = 0; j <= d; j++){
			for(int k = 0; k <= d-j; k++){
				for(int l = 0; l <= d -j -k; l++){
					IT mono = std::pow(h_cell[i].x, j) * std::pow(h_cell[i].y, k) *std::pow(h_cell[i].z, l);
					lp.set_a(param, count, mono);
					param++;
				}
			}
		}
		lp.set_b(count, 1);
		count++;
	}

	for(int i = 0; i < t; i++){
		int param = 0;
		for(int j = 0; j <= d;j++){
			for(int k = 0; k <= d-j; k++){
				for(int l = 0; l <= d - j - k; l++){
					IT mono = std::pow(t_cell[i].x, j) * std::pow(t_cell[i].y, k) * std::pow(t_cell[i].z, l);
				lp.set_a(param, count, mono);
				param++;	
				}
			}
		}
		lp.set_b(count, -1);
		count++;
	}


	CGAL::Quadratic_program_options options;
	options.set_pricing_strategy(CGAL::QP_BLAND);
	
	Solution s = CGAL::solve_linear_program(lp, ET(), options);

	return !s.is_infeasible();
}

void testCase(){
	std::cin >> h >> t;
	h_cell = std::vector<cell>(h);
	t_cell = std::vector<cell>(t);

	for(int i = 0; i < h; i++){
		int x, y, z;
		std::cin >> x >> y >> z;
		h_cell[i]= {x, y, z};
	}
	for(int i = 0; i < t; i++){
		int x,y,z;
		std::cin >> x >> y >> z;
		t_cell[i] = {x,y,z};
	}

	int min  = 0;
	int max = 31;

	while(min < max){
		int d = (max + min) / 2;
		if(solvable(d)) max = d;
		else min = d+1;
	}
	if(min > 30) std::cout<< "Impossible!"<< std::endl;
	else std::cout << min<< std::endl;

}




int main(){
	std::ios_base::sync_with_stdio(false);
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

	int t;
	std::cin >> t;

	while(t--) testCase();

	return 0;
}
	
	
