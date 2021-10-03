#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>

void testcase() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> friends(n);
	for(int i = 0; i < n; i++){
		std::cin >> friends[i];
	}
	std::sort(friends.begin(), friends.end(), std::greater<int>());

	std::multiset<int, std::greater<int>> box;
	for(int i = 0; i < m; i++){
		int w;
		std::cin >> w;
		box.insert(w);
	}

	if(friends[0] < *box.begin()){
		std::cout << "impossible" << std::endl;
		return ;
	}

	int count = 0;
	while(!box.empty()){
		count ++;
		for(int i = 0; i < n; i++){
			auto it = box.lower_bound(friends[i]);
			if(it == box.end()) break;
			box.erase(it);
		}
	}
	std::cout << count * 3 -1 << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
