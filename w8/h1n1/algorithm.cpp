#include <climits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
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
			f->info() = 0;
			q.push({0, f});
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
			K::FT new_dist = CGAL::min(dist, t.segment(f,i).squared_length());
			if(new_dist > neighbor->info()){
				neighbor->info() = new_dist;
				q.push({new_dist, neighbor});
			}
		}
	}
}
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
	precompute(t);

	int m;
	std::cin >> m;
	//TODO: rest of code

	for(int i = 0; i < m; i++){
		int x, y; double d;
		std::cin >> x >> y >> d;
		P loc(x,y);
		if(CGAL::squared_distance(t.nearest_vertex(loc)->point(), loc)<d){
			std::cout << "n";
			continue;
		}

		Face f = t.locate(loc);
		if(f->info() <  4*d){
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
	while(t){
		testcase(t);
		std::cin >> t;
	}
}
