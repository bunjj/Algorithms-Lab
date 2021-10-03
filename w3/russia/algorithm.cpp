#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
std::vector<int> x;
std::vector<std::vector<int>> dp;
int n, k, m;
int recursive(int i, int j){
	if(dp[i][j] != -1) return dp[i][j];
	bool turn = (((n -j + i - 1)% m )== k ? true : false);

	if(i == j){
		dp[i][j] = (turn ? x[i] : 0);
		return dp[i][j];
	}

	if(turn){
		dp[i][j] = std::max(recursive(i+1, j) + x[i] , recursive(i, j-1) + x[j]);
		return dp[i][j];
	}else{
		dp[i][j] = std::min(recursive(i+1, j), recursive(i, j-1));
		return dp[i][j];
	}
	
}
void testcase() {
	std::cin >> n >> m >> k;
	x = std::vector<int>(n);
	dp=std::vector<std::vector<int>> (n, std::vector<int>(n, -1));
	for(int i = 0; i < n; i++){
		std::cin >> x[i];
	}

	int result = recursive(0, n-1);

	std::cout << result << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
