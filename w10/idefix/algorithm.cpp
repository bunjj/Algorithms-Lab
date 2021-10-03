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
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef K::Point_2 P;
typedef std::pair<P, int> IP;

struct edge
{
	int x;
	int y;
	double length;
	bool bone;
};
void testcase()
{
	int n, m, k;
	double s;
	std::cin >> n >> m >> s >> k;
	std::vector<IP> pts;
	pts.reserve(n);
	for (int i = 0; i < n; i++)
	{
		int x, y;
		std::cin >> x >> y;
		pts.emplace_back(P(x, y), i);
	}
	Triangulation t;
	t.insert(pts.begin(), pts.end());

	std::vector<edge> edges;
	edges.reserve(3 * n + m);
	for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); e++)
	{
		int i1 = e->first->vertex((e->second + 1) % 3)->info();
		int i2 = e->first->vertex((e->second + 2) % 3)->info();
		// ensure smaller index comes first
		if (i1 > i2)
			std::swap(i1, i2);

		edges.push_back({i1, i2, t.segment(e).squared_length(), false});
	}

	for(int i = 0; i < m; i++){
		int x, y;
		std::cin >> x >> y;
		P loc(x,y);
		auto v = t.nearest_vertex(loc);
		edges.push_back({v->info(), -1,4* CGAL::squared_distance(v->point(), loc), true});
	}

	std::sort(edges.begin(), edges.end(), [](edge& e1, edge& e2){
		return e1.length < e2.length;
	});

	long a = 0;
	double q = 0;
	bool found_a = false;
	bool found_q = false;
	int max = 0;
	  boost::disjoint_sets_with_storage<> uf(n);
  	int n_components = n;
	std::vector<int> bones_per_comp(n, 0);
	for(auto e = edges.begin(); e != edges.end(); e++){
		if(e->length > s && !found_a){
			found_a = true;
			a = max;
		}
		int new_component;
		if(e->bone){
			new_component = ++bones_per_comp[uf.find_set(e->x)];
		}else{
			int c1 = uf.find_set(e->x);

			int c2 = uf.find_set(e->y);
			if(c1!=c2){
				uf.link(c1,c2);
				bones_per_comp[uf.find_set(c1)] = bones_per_comp[c1]+bones_per_comp[c2];
			}
			new_component = bones_per_comp[uf.find_set(c1)];
		}
		max =std::max(max, new_component);

		if(!found_q && max >= k){
			q = e->length;
			found_q = true;
		}

		if(found_q && found_a) break;
	}

	if(!found_a) a = m;

	std::cout << a << " " << q << std::endl;


	return;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
