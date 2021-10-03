#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

struct boat{
	int l,p;
};

void testcase() {
	int n;
	std::cin >> n;
	std::vector<boat> b(n);
	for(int i = 0; i < n; i++){
		int l,p;
		std::cin >> l >> p;

		b[i] = {l,p};
	}
	std::sort(b.begin(), b.end(), [](boat& b1, boat& b2){
		return b1.p < b2.p;
	});

	int count = 1;
	int current_end = b[0].p;
	int previous_end = b[0].p;

	for(int i = 1; i < n; i++){
		if(b[i].p >= current_end){
			count++;
			previous_end = current_end;
			current_end = std::max(b[i].p, current_end +b[i].l);
		}else if(previous_end + b[i].l < current_end){
			current_end = std::max(b[i].p, previous_end + b[i].l);
		}
	}

	std::cout << count << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
