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

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef K::Point_2 P;
typedef std::pair<P, int> IP;

void testcase(int n)
{
	std::vector<double> distance(n);
	std::vector<IP> pts;
	pts.reserve(n);
	int l, b, r, t;
	std::cin >> l >> b >> r >> t;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		std::cin >> x >> y;
		int min_x = std::min(r - x, x - l);
		int min_y = std::min(t - y, y - b);
		distance[i] = std::min(min_x, min_y);
		distance[i] *= 4 * distance[i];

		pts.emplace_back(P(x, y), i);
	}

	Triangulation tri;
	tri.insert(pts.begin(), pts.end());

	for (auto e = tri.finite_edges_begin(); e != tri.finite_edges_end(); e++)
	{
		int i1 = e->first->vertex((e->second + 1) % 3)->info();
		int i2 = e->first->vertex((e->second + 2) % 3)->info();
		double len = tri.segment(e).squared_length();
		distance[i1] = std::min(distance[i1], len );
		distance[i2] = std::min( distance[i2], len);
	}
	std::sort(distance.begin(), distance.end());

	int first = std::ceil(std::sqrt( (std::sqrt(distance[0])- 1) / 2));
	int middle = std::ceil(std::sqrt( (std::sqrt(distance[n/2])- 1) / 2));
	int last = std::ceil(std::sqrt( (std::sqrt(distance[n-1])- 1) / 2));

	std::cout << first << " " << middle << " " << last << std::endl;
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	while (t)
	{
		testcase(t);
		std::cin >> t;
	}
}
