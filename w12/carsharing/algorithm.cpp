#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
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
  void add_edge(int from, int to, long capacity, long cost) {
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
  }
};

struct booking{
	int start;
	int target;
	int dep;
	int arr;
	int profit;
};
void testcase() {
	int n,s;
	std::cin >> n>> s;
	std::vector<booking> bookings(n);
	std::vector<int> l(s);
	long l_sum = 0;
	for(int i =0; i < s; i++){
		std::cin >> l[i];
		l_sum += l[i];
	} 
	std::vector<std::set<int>> times(s);
	int latest = 0;
	for(int i = 0; i < n; i++){
		int start, t, d, a, p;
		std::cin >> start >> t >> d >> a >> p;
		start--;
		t--;
		bookings[i] = {start,t,d,a,p};
		times[start].insert(d);
		times[t].insert(a);
		latest = std::max(latest, a);
	}

	for(int i = 0; i < s; i++){
		times[i].insert(0);
		times[i].insert(latest);
	}

	int count = 0;
	std::map<std::pair<int,int>, int> ind;
	for(int i = 0; i < s; i++){
		for(auto it = times[i].begin(); it != times[i].end(); it++){
			ind[{i,*it}] = count++;
		}
	}
	graph G(count);
	edge_adder adder(G);
	auto v_source = boost::add_vertex(G);
	auto v_target = boost::add_vertex(G);

	for(int i = 0; i < s; i++){
		adder.add_edge(v_source, ind[{i, 0}], l[i], 0);
		adder.add_edge(ind[{i, latest}],v_target, l_sum, 0 );

		for(auto it = times[i].begin(); it != std::prev(times[i].end()); it++ ){
			int from = ind[{i, *it}];
			int to = ind[{i, *std::next(it)}];
			adder.add_edge(from, to, l_sum, 100*(*std::next(it) - *it));
		}
	}

	for(auto it = bookings.begin(); it != bookings.end(); it++){
		int from = ind[{it->start, it->dep}];
		int to = ind[{it->target, it->arr}];
		adder.add_edge(from, to, 1, 100*(it->arr - it->dep) - it->profit);
	}
	boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
	long cost = boost::find_flow_cost(G);

	std::cout << l_sum * 100 * latest - cost << std::endl;





	
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
