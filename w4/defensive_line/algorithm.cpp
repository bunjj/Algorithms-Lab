#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
std::vector<std::vector<int>> dp;
std::vector<int> def;
int recursive(int i, int j){
	if(i < 0) return 0;
	if(j < 0) return 0;
	if(dp[i][j] != -1) return dp[i][j];

	int max = 0;
	if(def[i] != 0){
		int tmp = recursive(i - def[i], j-1);
		if(tmp != 0) max = tmp + def[i];
	}
	max = std::max(max, recursive(i-1,j));
	dp[i][j] = max;
	return max;

}
void testcase() {
	int n, m, k;
	std::cin >> n >> m >> k;
	std::vector<int> v(n);
	for(int i = 0; i < n; i++){
		std::cin >> v[i];
	}

	def = std::vector<int> (n,0);

	int start = 0;
	int end = 0;
	int sum = v[0];
	while(end < n){
		if(sum == k){
			def[end] = end-start+1;
			end++;
			sum += v[end];
			continue;
		}
		if(sum < k){
			end++;
			sum += v[end];
		}else{
			sum-= v[start];
			start++;
			if(start > end){
				end = start;
				sum =v[start];
			}
		}
	}
dp = std::vector<std::vector<int>> (n, std::vector<int>(m+1, -1));
	int max = 0;
	for(int i = 0; i < n; i++){
		max = std::max(max, def[i]);
		dp[i][1] = max;
	}
	
	int result = recursive(n-1, m);
	if(result)	std::cout << result << std::endl;
	else std::cout << "fail" << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
