#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

void testcase() {
	int n;
	std::cin >> n;
	std::vector<int> t(n);
	for(int i = 0; i < n; i++){
		std::cin >> t[i];
	}
	for(int j = 0; j < (n-1)/2; j++){
		t[2*j + 1] = std::min(t[2*j + 1], t[j]-1);
		t[2*j + 2] = std::min(t[2*j + 2], t[j] -1);
	}
	std::sort(t.begin(),t.end());
	for(int i = 0; i < n; i++){
		if(t[i] <= i){
			std::cout << "no" << std::endl;
			return;
		}
	}
	std::cout << "yes" << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
