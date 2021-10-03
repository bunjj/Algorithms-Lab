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

void testcase() {
	int l, q;
	std::cin >> l >> q;
	graph G(l);
	edge_adder adder(G);
	auto v_source = boost::add_vertex(G);
	auto v_sink = boost::add_vertex(G);
	auto v_def = boost::add_vertex(G);
	auto v_path = boost::add_vertex(G);

	int sum_def = 0;
	for(int i = 0; i < l; i++){
		int g, d;
		std::cin >> g >> d;
		sum_def += d;
		adder.add_edge(v_source, i, g);
		adder.add_edge(i, v_def, d);
	}
	adder.add_edge(v_def, v_sink, sum_def);

	int sum_path = 0;
	for(int i = 0; i < q; i++){
		int f, t, c, C;
		std::cin >> f >> t >> c >> C;
		adder.add_edge(f,t, C -c );
		adder.add_edge(v_source, t, c);
		adder.add_edge(f, v_path, c);
		sum_path += c;
	}

	adder.add_edge(v_path, v_sink, sum_path);

	long flow = boost::push_relabel_max_flow(G, v_source, v_sink);

	if(flow < sum_path + sum_def){
		std::cout << "no" << std::endl;
	}else{
		std::cout << "yes" << std::endl;
	}

}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
