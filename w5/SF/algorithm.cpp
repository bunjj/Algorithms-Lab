#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

void testcase() {
	int n, m, k;
	long x;
	std::cin >> n >> m >> x >> k;

	std::vector<std::vector<long>> dp(n, std::vector<long> (k+1, -1));
	dp[0][0] = 0;
	std::vector<std::vector<std::pair<int,long>>> adj(n);
	for(int i = 0; i < m; i++){
		int u, v; long p;
		std::cin >> u >> v >> p;
		adj[u].push_back({v,p});
	}

	for(int i = 0; i < n; i++){
		if(adj[i].size() == 0){
			adj[i] = adj[0];
		}
	}

	for(int j = 0; j <k; j++){
		for(int i = 0; i < n; i++){
			if(dp[i][j] == -1) continue;
			
			for(auto it = adj[i].begin(); it != adj[i].end(); it++){
				long p = it->second;
				int target = it->first;
				dp[target][j+1] = std::max(dp[target][j+1], dp[i][j] + p);
				if(dp[target][j+1] >= x){
					std::cout << j + 1 << std::endl;
					return;
				}
			}
		}
	}

	std::cout << "Impossible" << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
