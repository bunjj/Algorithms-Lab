#include <climits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <stack>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;
void testcase() {
	int n, tatt;
	std::cin >> n >> tatt;
	std::vector<std::vector<int>> adj_mat(n,std::vector<int> (n,0));
	std::vector<std::vector<int>> adj_list(n);
	
	weighted_graph G(n);
	weight_map weights = boost::get(boost::edge_weight, G);

	for(int i = 0; i < n-1; i ++){
		for(int j = i + 1; j < n; j++){
			std::cin >> adj_mat[i][j];
			edge_desc e;
			e = boost::add_edge(i, j, G).first;
			weights[e] = adj_mat[i][j];
		}
	}

	std::vector<edge_desc> mst;
	boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));

	long mst_value = 0;
	  for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
    	int i1 = boost::source(*it, G);
		int i2 = boost::target(*it, G);
		if(i1 > i2) std::swap(i1, i2);
		adj_mat[i2][i1] = -1;
		adj_list[i1].push_back(i2);
		adj_list[i2].push_back(i1);
		mst_value += adj_mat[i1][i2];
  }

	std::vector<std::vector<int>> max_edge(n, std::vector<int> (n, -1));
	for(int i = 0; i < n; i++){
		max_edge[i][i] = 0;
	}

	for(int i = 0; i < n; i ++){
		std::stack<int> stack;
		stack.push(i);
		while(!stack.empty()){
			int current = stack.top();
			stack.pop();
			for(auto it = adj_list[current].begin(); it != adj_list[current].end(); it++){
				if(max_edge[i][*it] != -1)continue;
				stack.push(*it);
				int first = std::min(current, *it);
				int last = std::max(current, *it);
				max_edge[i][*it] = std::max(max_edge[i][current], adj_mat[first][last]);
			}
		}
	}
	int min_diff = INT_MAX;
	for(int i = 0; i < n-1; i++){
		for(int j = i+1; j < n; j++){
			if(adj_mat[j][i] == -1) continue;
				min_diff = std::min(min_diff, adj_mat[i][j] - max_edge[i][j]);
		}
	}

	std::cout << min_diff + mst_value << std::endl;

	


}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
