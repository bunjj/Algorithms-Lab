#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs


typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  edge_desc add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
	return e;
  }
};
void testcase() {
	int n ,m, s ,f;
	std::cin >> n >> m >> s >> f;

	graph G(n);
	edge_adder adder(G);
	auto c_map = boost::get(boost::edge_capacity, G);
	auto const v_source = boost::add_vertex(G);
	const int v_target = f;

	for(int i = 0; i < m; i++){
		int a, b, c, d;
		std::cin >> a >> b >> c >> d;
		adder.add_edge(a, b, c, d);
		adder.add_edge(b,a, c, d);
	}

	edge_desc e = adder.add_edge(v_source, s, 1, 0);

	boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);

	long dist = boost::find_flow_cost(G);
	long min = 0;
	long max = boost::push_relabel_max_flow(G, s, v_target) + 1;

	//std::cout << "dist :" << dist << " || flow :" << max -1 << std::endl;

	while(min < max){
		long p = (max + min) / 2;
		c_map[e] = p;
		boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);	
		long cost = boost::find_flow_cost(G);
		if(cost > p * dist){
			max = p;
		}else{
			min = p+1;
		}
	}

	std::cout << min - 1 << std::endl; 

}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();

	return 0;
}
