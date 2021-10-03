#include<iostream>
#include<iomanip>
#include<vector>


void testCase(){
	int n, k;
	std::cin >> n >> k;
	std::vector<int> v(n);
	for(auto it = v.begin(); it != v.end(); it++){
		std::cin >> *it;
	}

	//sliding window
	int sum = v[0];
	int i = 0, j = 0;

	int dif = std::abs(sum - k);
	int best_i = i;
	int best_j = j;
	while(i < n && j < n){
		if(std::abs(sum - k) < dif){
			dif = std::abs(sum-k);
			best_i = i;
			best_j = j;
		}
		if(sum == k) break;
		if(sum > k){
			sum -= v[i];
			i++;
			if(i > j){
				j++;
				sum = v[j];
			}
		}
		if(sum < k){
			j++;
			sum += v[j];
		}
	}
	std::cout << best_i << " " << best_j << std::endl;


}


int main(){

	std::ios_base::sync_with_stdio(false);
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

	int t;
	std::cin >> t;
	while(t--) testCase();

	return 0;
}
