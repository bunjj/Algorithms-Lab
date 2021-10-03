#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;


void testcase(int n) {
	std::vector<P> pts;
	pts.reserve(n);
	for(int i = 0; i < n; i++){
		int x, y;
		std::cin >> x >> y;
		pts.emplace_back(x,y);
	}
	Triangulation t;
	t.insert(pts.begin(), pts.end());
	int m;
	std::cin >> m;
	for(int i = 0; i < m; i++){
		int x, y;
		std::cin >> x >> y;
		P loc(x,y);
		std::cout << CGAL::squared_distance(t.nearest_vertex(loc)->point(), loc) <<std::endl;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
	int t;
	std::cin >> t;
	while(t){
		testcase(t);
		std::cin >> t;
	}
}
