#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <unordered_map>


// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

void testcase() {
	int n, c, f;
	std::cin >> n >> c >> f;
	std::vector<std::vector<int>> adj_mat(n, std::vector<int>(n,0));

	std::unordered_map<std::string, std::vector<int>> dict;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < c; j++){
			std::string s;
			std::cin >> s;
			dict[s].push_back(i);
		}
	}

	for(auto it = dict.begin(); it != dict.end(); it++){
		std::sort(it->second.begin(), it->second.end());
		for(int i = 0; i < it->second.size()-1; i++){
			for(int j = i+1; j < it->second.size(); j++){
				adj_mat[it->second[i]][it->second[j]] ++;
			}
		}
	}
	graph G(n);
	for(int i = 0; i < n-1; i++){
		for(int j = i+1; j < n; j++){
			if(adj_mat[i][j] > f){
				boost::add_edge(i,j,G);
			}
		}
	}

std::vector<vertex_desc> mate_map(n);

  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
	if(matching_size < n/2) std::cout << "optimal" << std::endl;
	else std::cout << "not optimal" << std::endl;

}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
