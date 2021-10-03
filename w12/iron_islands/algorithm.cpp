#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>

void testcase() {
	int n, k, w;
	std::cin >> n >> k >> w;
	std::vector<int> c(n);
	for(int i = 0; i < n; i++){
		std::cin >> c[i];
	}

	std::vector<std::tuple<int,int,int>> pairs;
	pairs.reserve(n);
	int best = 0;
	for(int i = 0; i < w; i++){
		bool first = true;
		int sum = 0;
		int l;
		std::cin >> l;
		std::queue<int> path;
		for(int j = 0; j < l; j++){
			int current_ind;
			std::cin >> current_ind;
			int current = c[current_ind];
			path.push(current);
			sum += current;
			if(sum < k && first){
				pairs.push_back(std::make_tuple(sum, j, i));
			}else{
				first = false;
				while(sum > k){
				sum -= path.front();
				path.pop();}
			
			if(sum == k){
				best = std::max(best, (int) path.size());
			}
			}
		}
	}

	std::sort(pairs.begin(), pairs.end());
	int left = 0;
	int right = pairs.size()-1;
	while(left < right){
		int left_men = std::get<0>(pairs[left]);
		int left_path = std::get<2>(pairs[left]);
		int left_count = std::get<1>(pairs[left]);

		int right_men = std::get<0>(pairs[right]);
		int right_path = std::get<2>(pairs[right]);
		int right_count = std::get<1>(pairs[right]);

		int sum = right_men + left_men - c[0];
		if(sum < k){
			left++;
		}else if(sum > k){
			right--;
		}else{
			if(left_path != right_path){
				best = std::max(best, right_count + left_count + 1);
			}
			left++;
		}
	}
	std::cout << best << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
