#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

// BGL include
#include <boost/graph/adjacency_list.hpp>

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

// Custom edge adder class, highly recommended
class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};
int n,m;

int ind(int i, int j){
	return i * m + j;
}

void testcase() {
	int k, c;
	std::cin >> m >> n >> k >> c;
	graph G(2*n*m);
	int nm = n*m;
	edge_adder adder(G);

	auto v_source = boost::add_vertex(G);
	auto v_sink = boost::add_vertex(G);

	for(int i = 0; i < k; i++){
		int x, y;
		std::cin >> x >> y;
		adder.add_edge(v_source, ind(y,x), 1);
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			int out = ind(i, j) + nm;
			adder.add_edge(ind(i,j), out, c);

			if(i > 0) adder.add_edge(out, ind(i-1,j), 1);
			else adder.add_edge(out, v_sink, 1);

			if(j>0) adder.add_edge(out, ind(i, j-1), 1);
			else adder.add_edge(out, v_sink, 1);

			if( i < n-1) adder.add_edge(out, ind(i+1, j), 1);
			else adder.add_edge(out, v_sink, 1);

			if(j < m-1) adder.add_edge(out, ind(i, j+1), 1);
			else adder.add_edge(out, v_sink, 1);
		}
	}

	  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);

	  std::cout << flow << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
