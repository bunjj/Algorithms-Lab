#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include<queue>
#include <climits>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_2<K>   Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef K::Point_2 P;
typedef Triangulation::Face_handle Face;

void precompute(Triangulation& t){
	std::priority_queue<std::pair<K::FT, Face>> q;
	for(auto f = t.all_faces_begin(); f != t.all_faces_end(); f++){
		if(t.is_infinite(f)){
			f->info() = DBL_MAX;
			q.push({DBL_MAX, f});
		}else{
			K::FT radius = CGAL::squared_distance(t.dual(f), f->vertex(0)->point());
			f->info() = radius;
			q.push({radius, f});
		}
	}


	while(!q.empty()){
		Face f = q.top().second;
		K::FT dist = q.top().first;
		q.pop();

		if(dist < f->info()) continue;

		for(int i = 0; i < 3; i++){
			Face neighbor = f->neighbor(i);
			if(t.is_infinite(neighbor))continue;
			K::FT new_dist = CGAL::min(dist, t.segment(f, i).squared_length());
			if(new_dist > neighbor->info()){
				neighbor->info() = new_dist;
				q.push({new_dist, neighbor});
			}
		}
	}
}

void testcase() {
	int n, m; long r;
	std::cin >> n >> m >> r;
	std::vector<P> pts;
	pts.reserve(n);
	for(int i = 0; i < n; i++){
		long x, y;
		std::cin >> x >> y;
		pts.emplace_back(x,y);
	}
	Triangulation t;
	t.insert(pts.begin(), pts.end());

	precompute(t);

	for(int i = 0; i < m; i++){
		long x, y, s;
		std::cin >> x >> y >> s;
		K::FT dist = s + r;
		dist *= dist;

		P loc(x,y);
		if(CGAL::squared_distance(loc, t.nearest_vertex(loc)->point()) < dist){
			std::cout << "n";
			continue;
		}

		Face f = t.locate(loc);
		if(f->info() < dist * 4){
			std::cout << "n";
		}else{
			std::cout << "y";
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
