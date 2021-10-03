#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/adjacency_list.hpp>

namespace boost
{
struct edge_component_t
{
    enum
    {
        num = 555
    };
    typedef edge_property_tag kind;
} edge_component;
}


void testcase() {
	    using namespace boost;
    typedef adjacency_list< vecS, vecS, undirectedS, no_property,
        property< edge_component_t, std::size_t > >
        graph_t;
    typedef graph_traits< graph_t >::vertex_descriptor vertex_t;
	int n;
	std::cin >> n;
	int m;
	std::cin >> m;
	graph_t g(n);
	for(int i = 0; i < m; i++){
		int x, y;
		std::cin >> x >> y;
		if(x > y) std::swap(x,y);
		add_edge(x,y,g);
	}

	    property_map< graph_t, edge_component_t >::type component
        = get(edge_component, g);
std::size_t num_comps = biconnected_components(g, component);
std::map<int, std::vector<std::pair<int,int>>> comp;
 graph_traits< graph_t >::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei){
         int x = source(*ei, g);
		 int y = target(*ei, g);
		if(x > y) std::swap(x,y);

		comp[component[*ei]].push_back({x,y});
	}

	std::set<std::pair<int,int>> result;
	for(auto it: comp){
		if(it.second.size() == 1){
			result.insert(it.second[0]);
		}
	}
	std::cout << result.size() << std::endl;
	for(auto it: result){
		std::cout << it.first << " " << it.second << std::endl;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
