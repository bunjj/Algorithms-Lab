#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <set>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
const P zero(0,0);

struct bike{
	long y0;
	long x;
	long y;
	bool up;
	int ind;
};

bool smaller(bike& b1, bike& b2){
	auto o = CGAL::orientation(zero, P(b1.x, b1.y), P(b2.x, b2.y));
	return o == CGAL::LEFT_TURN;
}

bool equal(bike& b1, bike& b2){
	auto o = CGAL::orientation(zero, P(b1.x, b1.y), P(b2.x, b2.y));
	return o == CGAL::COLLINEAR;
}

void testcase() {
	int n;
	std::cin >> n;
	std::vector<bike> biker(n);
	for(int i = 0; i < n; i++){
		long y0, x, y;
		std::cin >> y0 >> x >> y;
		y -= y0;
		bool up = true;
		if(y < 0) {
			y = -y;
			up = false;
		}

		biker[i] = {y0, x, y, up, i};
	}

	std::set<int> result;

	std::sort(biker.begin(), biker.end(), [](bike& b1, bike& b2){
		if(smaller(b1,b2)) return true;
		else if(equal(b1, b2)){
			if(b1.up != b2.up && b1.up) return true;
			if(b1.up && b2.up && b1.y0 < b2.y0) return true;
			if(!b1.up && !b2.up && b1.y0 > b2.y0) return true;
		}

		return false;
	});
	result.insert(biker[0].ind );
	long max = biker[0].y0;
	long min = biker[0].y0;

	for(int i = 1; i < n; i++){
		if((equal(biker[i], biker[0]) && biker[i].up == biker[0].up ) ||
		 (biker[i].up && biker[i].y0 > max) ||
		 (!biker[i].up && biker[i].y0 < min)){
			 result.insert(biker[i].ind);
		 }

		 max = std::max(max, biker[i].y0);
		 min = std::min(min, biker[i].y0);
	}

	for(int i : result){
		std::cout << i << " ";
	}
	std::cout << std::endl;

}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
