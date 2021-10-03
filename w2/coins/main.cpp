#include <iostream>
#include <iomanip>
#include <vector>


int n;
std::vector<std::vector<int>> dp;
std::vector<int> v;
int recursive(int i, int j){

	if(dp[i][j] != -1) return dp[i][j];

	int turn = (n-j+i)%2;
	if(i==j){
		if(turn){
			dp[i][j] = v[j];
			return v[j];
		}else{
			dp[i][j] = 0;
			return 0;
		}
	}

	int result; 
	if(turn){
		result = std::max(v[i] + recursive(i+1 , j), v[j] + recursive(i, j-1));
	}else{
		result = std::min(recursive(i+1, j), recursive(i, j-1));
	}
	dp[i][j] = result;

	return result;
}
void testCase(){

	std::cin >> n;
	v = std::vector<int> (n);
	for(int i = 0; i < n; i++){
		std::cin >> v[i];
	}

	dp = std::vector<std::vector<int>> (n, std::vector<int> (n,-1));
	int result = recursive(0, n-1);

	std::cout << result << std::endl;

}


int main(){

	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	while(t--) testCase();

	return 0;
}
