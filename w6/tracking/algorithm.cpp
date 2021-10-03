#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
							  boost::no_property, boost::property<boost::edge_weight_t, int>>
	weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

void testcase()
{
	int n, m, k, x, y;
	std::cin >> n >> m >> k >> x >> y;
	weighted_graph G(n * (k + 1));
	weight_map weights = boost::get(boost::edge_weight, G);

	edge_desc e;
	for (int i = 0; i < m; i++)
	{
		int a, b, c, d;
		std::cin >> a >> b >> c >> d;
		for (int j = 0; j <= k; j++)
		{
			int aj = a + (j * n);
			int bj = b + (j * n);
			e = boost::add_edge(aj, bj, G).first;
			weights[e] = c;
			e = boost::add_edge(bj, aj, G).first;
			weights[e] = c;
		}
		if (!d)
			continue;
		for (int j = 0; j < k; j++)
		{
			int aj = a + (j * n);
			int bj = b + (j * n);
			e = boost::add_edge(aj, bj + n, G).first;
			weights[e] = c;
			e = boost::add_edge(bj, aj + n, G).first;
			weights[e] = c;
		}
	}

	std::vector<int> dist_map(n * (k + 1));
	  boost::dijkstra_shortest_paths(G, x,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));
	std::cout << dist_map[k*n + y] << std::endl;
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
