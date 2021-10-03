#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
							  boost::no_property, boost::property<boost::edge_weight_t, int>>
	weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc_m;

void testcase()
{
	int n, m, a, s, c, d;
	std::cin >> n >> m >> a >> s >> c >> d;

	weighted_graph G(n + c * s);
	weight_map weights = boost::get(boost::edge_weight, G);
	for (int i = 0; i < m; i++)
	{
		char w;
		int x, y, z;
		std::cin >> w >> x >> y >> z;
		edge_desc e;
		e = boost::add_edge(x, y, G).first;
		weights[e] = z;
		if (w == 'L')
		{
			e = boost::add_edge(y, x, G).first;
			weights[e] = z;
		}
	}

	std::vector<int> agents(a);
	for (int i = 0; i < a; i++)
	{
		std::cin >> agents[i];
	}
	std::vector<int> shelter(s);
	for (int i = 0; i < s; i++)
	{
		std::cin >> shelter[i];
	}
	for (int i = 0; i < s; i++)
	{
		edge_desc e;
		e = boost::add_edge(shelter[i], i + n, G).first;
		weights[e] = d;
		if (c > 1)
		{
			e = boost::add_edge(i + n, i + n + s, G).first;
			weights[e] = d;
		}
	}
	std::vector<std::vector<long>> distances(a, std::vector<long>(c * s));

	std::vector<int> dist_map(n + c * s);
	long max = 0;
	for (int i = 0; i < a; i++)
	{
		boost::dijkstra_shortest_paths(G, agents[i],
									   boost::distance_map(boost::make_iterator_property_map(
										   dist_map.begin(), boost::get(boost::vertex_index, G))));
		for (int j = 0; j < c * s; j++)
		{
			distances[i][j] = dist_map[j + n];
			max = std::max(max, distances[i][j]);
		}
	}

	long min = 0;
	max++;
	while(min < max){
		graph Gm(a + c*s);
		long t = min + (max-min)/2;
		for(int i = 0; i < a; i++){
			for(int j = 0; j < c*s; j++){
				if(distances[i][j] <= t){
					boost::add_edge(i, j+a, Gm);
				}
			}
		}
		std::vector<vertex_desc> mate_map(a + c*s); 
		  boost::edmonds_maximum_cardinality_matching(Gm,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, Gm)));
  int matching_size = boost::matching_size(Gm,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, Gm)));
		if(matching_size == a){
			max = t;
		}else
			min = t+1;
	}

	std::cout << max << std::endl;


}

int main()
{
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
