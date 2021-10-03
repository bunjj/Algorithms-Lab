//STL includes
#include<iostream>
#include<iomanip>
#include<vector>


//bgl includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;



void testCase(){
	int n, m;
	std::cin >> n >> m;

	weighted_graph G(n);
	weight_map weights = boost::get(boost::edge_weight, G);
	edge_desc e;

	for(int i = 0; i < m; i++){
		int x, y, w;
		std::cin >> x >> y >> w;
		e = boost::add_edge(x,y,G).first; weights[e] = w;
	}

	  std::vector<edge_desc> mst;    // vector to store MST edges (not a property map!)

  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));

  int sum = 0;
  for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
	  sum += weights[*it];
  }

    std::vector<int> dist_map(n);
      boost::dijkstra_shortest_paths(G, 0,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

      int max = *std::max_element(dist_map.begin(), dist_map.end());

      std::cout << sum << " " << max << std::endl;
}


int main(){

	std::ios_base::sync_with_stdio(false);
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

	int t;
	std::cin >> t;

	while(t--) testCase();

	return 0;
}
