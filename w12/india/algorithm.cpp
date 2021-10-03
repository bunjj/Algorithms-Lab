//include STL libraries
#include<iostream>
#include<iomanip>
#include<vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

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

void testCase(){
	int c, g, b, k, a;
	std::cin >> c >> g >> b >> k >> a;
	graph G(c);
	edge_adder adder(G);
	auto c_map = boost::get(boost::edge_capacity, G);
	const int v_target = a;
	const auto v_source = boost::add_vertex(G);

	for(int i = 0; i < g; i++){
		int x, y, d, e;
		std::cin >>x>> y >> d >> e;
		adder.add_edge(x, y, e, d);
	}

	long max = 1 + boost::push_relabel_max_flow(G, k, v_target);
	long min = 0;
	edge_desc e = adder.add_edge(v_source, k, max, 0);

	while(min < max){
		long p = (max+min)/2;
		c_map[e] = p;
		boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
		long cost = boost::find_flow_cost(G);
		//std::cout << cost << std::endl;
		if(cost <= b){
			min = p+1;
		}else max = p;
	}

	std::cout << min-1 << std::endl;
}


int main(){
	std::ios_base::sync_with_stdio(false);
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

	int t;
	std::cin >> t;

	while(t--) testCase();

	return 0;
}