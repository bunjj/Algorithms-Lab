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
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef int                                     Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef K::Point_2 P;
typedef std::pair<P, int> IP;

void testcase() {
	int n; K::FT r;
	std::cin >> n >> r;
	r *= r;
	std::vector<IP> pts;
	pts.reserve(n);
	for(int i = 0; i < n; i++){
		int x, y;
		std::cin >> x >> y;
		pts.emplace_back(P(x,y), i);
	}

	int min = 0;
	int max = n;
	while(min < max){
		int p = min + (max-min)/2;
		Triangulation t;
		t.insert(pts.begin() + p, pts.end());
		int max_comp = 1;
		boost::disjoint_sets_with_storage<> uf(n);
		std::vector<int> comp_size(n,1);
		for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); e++){
			if(t.segment(e).squared_length() > r) continue;
			int i1 = e->first->vertex((e->second +1)%3) ->info();
			int i2 =e->first->vertex((e->second +2)%3) ->info();

			int c1 = uf.find_set(i1);
			int c2 = uf.find_set(i2);
			if(c1 != c2){
				int new_comp = comp_size[c1] + comp_size[c2];
				uf.link(c1,c2);
				comp_size[uf.find_set(c1)] = new_comp;
				max_comp = std::max(max_comp, new_comp);
			}
		}
		if(max_comp >= p){
			min = p+1;
		}else
		{
			max = p;
		}
	}

	std::cout << min-1 << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
