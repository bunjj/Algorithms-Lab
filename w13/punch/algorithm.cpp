#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
struct drink{
	int c,v;
};
void testcase() {
	int n, k;
	std::cin >> n >> k;
	std::vector<drink> drinks(n);
	for(int i = 0; i < n; i++){
		int c, v;
		std::cin >> c >> v;
		drinks[i] = {c,v};
	}
	std::vector<std::vector<std::pair<int,int>>> dp(n, std::vector<std::pair<int,int>>(k+1, {0,0}));
	for(int i = 1; i <=k; i++){
		dp[0][i].second = 1;
		dp[0][i].first = (i+ drinks[0].v - 1) /drinks[0].v * drinks[0].c;
	}
	for(int i = 1; i < n; i++){
		for(int j = 1; j <= k; j++){
			int last_volume = std::max(0, j-drinks[i].v);

			int leave_cost = dp[i-1][j].first;
			int leave_count = dp[i-1][j].second;

			int take_cost = dp[i][last_volume].first + drinks[i].c;
			int take_count = dp[i][last_volume].second + (int)(dp[i][last_volume] == dp[i-1][last_volume]);

			if(take_cost < leave_cost ||
				(take_cost == leave_cost && take_count > leave_count)){
					dp[i][j] = {take_cost, take_count};
				}else{
					dp[i][j] = dp[i-1][j];
				}
		}
	}

	std::cout << dp[n-1][k].first << " " << dp[n-1][k].second << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
