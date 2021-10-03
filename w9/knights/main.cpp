#include<iostream>
#include<iomanip>
#include<vector>

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

void testCase(){
	int n;
	std::cin >> n;
	std::vector<std::vector<int>> board(n, std::vector<int> (n,-1));
	int count = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			int present;
			std::cin >> present;
			if(present) board[i][j] = count++;
		}
	}
	graph G(count);
	edge_adder adder(G);

	  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);

  	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(board[i][j] == -1) continue;
			int parity = (i+j)%2;
			if(parity) adder.add_edge(v_source, board[i][j], 1);
			else adder.add_edge(board[i][j], v_sink, 1);

			if(i > 1 && j > 0 && board[i-2][j-1] != -1){
				if(parity) adder.add_edge(board[i][j], board[i-2][j-1], 1);
				else adder.add_edge(board[i-2][j-1], board[i][j], 1);
			}
			if(i > 1 && j < n-1 && board[i-2][j+1] != -1){
				if(parity) adder.add_edge(board[i][j], board[i-2][j+1], 1);
				else adder.add_edge(board[i-2][j+1], board[i][j], 1);
			}

			if(i > 0 && j > 1 && board[i-1][j-2] != -1){
				if(parity) adder.add_edge(board[i][j], board[i-1][j-2], 1);
				else adder.add_edge(board[i-1][j-2], board[i][j], 1);
			}

			if(i < n-1 && j > 1 && board[i+1][j-2] != -1){
				if(parity) adder.add_edge(board[i][j], board[i+1][j-2], 1);
				else adder.add_edge(board[i+1][j-2], board[i][j], 1);
			}
		}
	}

	long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
	std::cout << count - flow << std::endl;


}


int main(){
	std::ios_base::sync_with_stdio(false);
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

	int t;
	std::cin >> t;

	while(t--) testCase();

	return 0;
}
