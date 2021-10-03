#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::pair<int, bool> Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef K::Point_2 P;
typedef Triangulation::Vertex_handle Vertex;
K::FT r;


bool precompute(Triangulation& t){
	for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); v++){
		v->info() = {0,false};
	}

	int count = 0;

	Triangulation t1, t2;

	for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); v++){
		if(!v->info().first){
			v->info().first = ++count;
			std::stack<Vertex> stack;
			stack.push(v);

			while(!stack.empty()){
				Vertex current = stack.top();
				stack.pop();

				auto c = t.incident_vertices(current);
				do{
					if(t.is_infinite(c) || 
						CGAL::squared_distance(c->point(), current->point()) > r) continue;
					if(c->info() == current->info()) return false;
					if(c->info().first == 0){
						c->info() = {current->info().first, !current->info().second};
						stack.push(c);
					}
				}while(++c != t.incident_vertices(current));	
			}
		}

		if(v->info().second) t1.insert(v->point());
		else t2.insert(v->point());
	}

	for(auto e = t1.finite_edges_begin(); e != t1.finite_edges_end(); e ++){
		if(t1.segment(e).squared_length() <= r) return false;
	}
	for(auto e = t2.finite_edges_begin(); e != t2.finite_edges_end(); e++){
		if(t2.segment(e).squared_length() <= r)return false;
	}	
	return true;


}

void testcase() {
	int n, m;
	std::cin >> n >> m >> r;
	r *= r;

	std::vector<P> pts;
	pts.reserve(n);

	for(int i = 0; i < n; i++){
		int x, y;
		std::cin >> x >> y;
		pts.emplace_back(x,y);
	}

	Triangulation t;
	t.insert(pts.begin(), pts.end());

	if(precompute(t)){
		for(int i = 0; i < m; i++){
			P a, b;
			std::cin >> a >> b;
			if(CGAL::squared_distance(a,b) <= r){
				std::cout << "y";
				continue;
			}

			Vertex s_a = t.nearest_vertex(a);
			Vertex s_b = t.nearest_vertex(b);

			if(CGAL::squared_distance(a, s_a->point()) <= r &&
				CGAL::squared_distance(b, s_b->point()) <= r &&
				s_a->info().first == s_b->info().first){
					std::cout << "y";
				}else{
					std::cout << "n";
				}
		}
	}else{
		for(int i = 0; i < m; i++){
			P a, b;
			std::cin >> a >> b;
			std::cout << "n";
		}
	}
	std::cout << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
