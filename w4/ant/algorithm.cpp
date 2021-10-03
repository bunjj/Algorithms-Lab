#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
							  boost::no_property, boost::property<boost::edge_weight_t, int>>
	weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

void testcase()
{
	int n, e, s, a, b;
	std::cin >> n >> e >> s >> a >> b;
	std::vector<weighted_graph> G(s, weighted_graph(n));
	std::vector<weight_map> weights(s);
	for (int i = 0; i < s; i++)
	{
		weights[i] = boost::get(boost::edge_weight, G[i]);
	}

	for (int i = 0; i < e; i++)
	{
		int x, y;
		std::cin >> x >> y;
		for (int j = 0; j < s; j++)
		{
			int w;
			std::cin >> w;
			edge_desc edge;
			edge = boost::add_edge(x, y, G[j]).first;
			weights[j][edge] = w;
		}
	}

	for (int i = 0; i < s; i++)
	{
		int h;
		std::cin >> h;
	}

	weighted_graph G_d(n);
	weight_map w_d = boost::get(boost::edge_weight, G_d);

	for (int i = 0; i < s; i++)
	{
		std::vector<edge_desc> mst; // vector to store MST edges (not a property map!)

		boost::kruskal_minimum_spanning_tree(G[i], std::back_inserter(mst));
		for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it)
		{
			int x = boost::source(*it, G[i]);
			int y = boost::target(*it, G[i]);
			edge_desc edge = boost::add_edge(x, y, G_d).first;
			w_d[edge] = weights[i][*it];
		}
	}

	std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G_d, a,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G_d))));

	  std::cout << dist_map[b] << std::endl;
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
