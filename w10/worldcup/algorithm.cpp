#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef CGAL::Gmpq IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;


struct warehouse{
	P loc;
	int sup;
	int alc;
};

struct stadium{
	P loc;
	int dem;
	int lim;
};

struct contour{
	P loc;
	double r;
};

void testcase() {
	int n, m, con;
	std::cin >> n >> m >> con;
	std::vector<P> pts;
	pts.reserve(n + m);

	std::vector<std::vector<int>> a(n, std::vector<int> (m));
	std::vector<std::vector<double>> r(n, std::vector<double> (m));
	std::vector<warehouse> w(n);
	std::vector<stadium> s(m);
	std::vector<contour> c;
	c.reserve(100);

	for(int i = 0; i < n; i ++){
		int x, y, sup, alc;
		std::cin >> x >> y >> sup >> alc;
		w[i] = {P(x,y), sup, alc};
		pts.emplace_back(x,y);
	}

	for(int i = 0; i < m; i++){
		int x, y, dem, lim;
		std::cin >> x >> y >> dem >> lim;
		s[i] = {P(x,y), dem, lim * 100};
		pts.emplace_back(x,y);
	}
	int count = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			a[i][j] = count++;
			std::cin >> r[i][j];
		}
	}
	
	Triangulation t;
	t.insert(pts.begin(), pts.end());

	for(int i = 0; i < con; i++){
		int x, y; double r;
		std::cin >> x >> y >>  r;
		r *= r;
		P loc(x,y);
		if(CGAL::squared_distance(loc, t.nearest_vertex(loc)->point()) < r){
			c.push_back({loc, r});
		}
	}


	for(int k = 0; k < c.size(); k ++){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				if((CGAL::squared_distance(c[k].loc, w[i].loc)< c[k].r) 
				!= (CGAL::squared_distance(c[k].loc, s[j].loc)< c[k].r)){
					r[i][j] -= 0.01;
				}
			}
		}
	}

	Program lp(CGAL::SMALLER, true, 0, false, 0);
	count = 0;
	for(int j = 0; j < m; j++){
		lp.set_r(count, CGAL::EQUAL);
		for(int i = 0; i < n; i++){
			lp.set_a(a[i][j], count, 1);
		}
		lp.set_b(count, s[j].dem);
		count ++;
	}

	for(int j = 0; j < m; j++){
		for(int i = 0; i < n; i++){
			lp.set_a(a[i][j], count, w[i].alc);
		}
		lp.set_b(count, s[j].lim);
		count++;
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			lp.set_a(a[i][j], count, 1);
		}
		lp.set_b(count, w[i].sup);
		count++;
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			lp.set_c(a[i][j], -r[i][j]);
		}
	}

	Solution sol = CGAL::solve_linear_program(lp, ET());
	if(sol.is_infeasible()){
		std::cout << "RIOT!" << std::endl;
	}else{
		std::cout << std::floor(CGAL::to_double(-sol.objective_value())) << std::endl;
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
