#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef int Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef K::Point_2 P;

typedef std::pair<P, int> IP;

struct edge
{
	int x, y;
	double length;
};

void testcase()
{
	int n, k, f0;
	double s0;
	std::cin >> n >> k >> f0 >> s0;
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
	edges.reserve(3 * n);
	for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); e++)
	{
		int i1 = e->first->vertex((e->second + 1) % 3)->info();
		int i2 = e->first->vertex((e->second + 2) % 3)->info();
		if (i1 > i2)
			std::swap(i1, i2);
		edges.push_back({i1, i2, t.segment(e).squared_length()});
	}

	std::sort(edges.begin(), edges.end(), [](const edge &e1, const edge &e2) {
		return e1.length < e2.length;
	});
	boost::disjoint_sets_with_storage<> uf(n);
	int n_components = n;
	bool found_f = false;
	int f= 1;
	double s;

	for (auto e = edges.begin(); e != edges.end(); e++)
	{
		if (!found_f && e->length >= s0)
		{
			found_f = true;
			if (k == 1)
				f = n_components;
			else
			{
				std::map<int, int> comp;
				for (int i = 0; i < n; i++)
				{
					comp[uf.find_set(i)]++;
				}
				int count = 0;
				std::vector<int> rest;
				rest.reserve(n);

				for (auto i : comp)
				{
					if (i.second >= k)
						count++;
					else
					{
						rest.push_back(i.second);
					}
				}
				std::sort(rest.begin(), rest.end());
				int left = 0, right = rest.size() - 1;
				while (left < right)
				{
					if (rest[left] + rest[right] >= k)
					{
						count++;
						left++;
						right--;
					}
					else
					{
						rest[left + 1] += rest[left];
						left++;
					}
				}
				f = count;
			}
			break;
		}

		int c1 = uf.find_set(e->x);
		int c2 = uf.find_set(e->y);
		if (c1 != c2)
		{
			uf.link(c1, c2);
			if (--n_components == 1)
				break;
		}
	}

	int min = 0, max = edges.size();
	while (min < max)
	{
		int p = min + (max - min) / 2;
		uf = boost::disjoint_sets_with_storage<>(n);
		n_components = n;

		for (auto e = edges.begin(); e != edges.begin() + p; e++)
		{
			int c1 = uf.find_set(e->x);
			int c2 = uf.find_set(e->y);
			if (c1 != c2)
			{
				uf.link(c1, c2);
				if (--n_components == 1)
					break;
			}
		}

		std::map<int, int> comp;
		for (int i = 0; i < n; i++)
		{
			comp[uf.find_set(i)]++;
		}
		int count = 0;
		std::vector<int> rest;
		rest.reserve(n);

		for (auto i : comp)
		{
			if (i.second >= k)
				count++;
			else
			{
				rest.push_back(i.second);
			}
		}
		std::sort(rest.begin(), rest.end());
		int left = 0, right = rest.size() - 1;
		while (left < right)
		{
			if (rest[left] + rest[right] >= k)
			{
				count++;
				left++;
				right--;
			}
			else
			{
				rest[left + 1] += rest[left];
				left++;
			}
		}

		if(count >= f0){
			min = p + 1;
		}else{
			max = p;
		}
	}

	std::cout << edges[min-1].length << " " << f << std::endl;
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
