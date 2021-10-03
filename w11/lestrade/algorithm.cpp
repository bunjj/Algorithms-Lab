#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef K::Point_2 P;
typedef std::pair<P, int> IP;

typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

struct gang{
	int u, v, w;
	int agent;
};

void testcase() {
	int z , u, v, w;
	std::cin >> z >> u >> v >> w;
	int a , g;
	std::cin >> a >> g;
	std::vector<gang> gangs(g);
	std::vector<IP> pts;
	pts.reserve(g);
	for(int i = 0; i < g; i++){
		int x, y, ug, vg, wg;
		std::cin >> x >> y >> ug >> vg >> wg;
		gangs[i] = {ug, vg, wg, -1};
		pts.emplace_back(P(x,y), i);
	}

	Triangulation t;
	t.insert(pts.begin(), pts.end());

	for(int i = 0; i < a; i++){
		int x, y , h;
		std::cin >> x >> y >> h;
		int ind = t.nearest_vertex(P(x,y))->info();

		if(gangs[ind].agent == -1 || gangs[ind].agent > h){
			gangs[ind].agent = h;	
		}
	}

	int count = 0;
	Program lp(CGAL::LARGER, true, 0, true, 24);

	for(int i = 0; i < g; i++){
		if(gangs[i].agent == -1)continue;
		lp.set_a(count, 0, gangs[i].u);
		lp.set_a(count, 1, gangs[i].v);
		lp.set_a(count, 2, gangs[i].w);
		lp.set_c(count, gangs[i].agent);
		count ++;
	}
	lp.set_b(0, u);
	lp.set_b(1, v);
	lp.set_b(2, w);

	Solution s  = CGAL::solve_linear_program(lp, ET());

	if(s.is_infeasible()){
		std::cout << "H" << std::endl;
	}else{
		if(CGAL::to_double(s.objective_value()) <= z){
			std::cout << "L" << std::endl;
		}else{
			std::cout << "H" << std::endl;
		}
	}

}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
