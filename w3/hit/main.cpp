#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;


void testCase(int n){
	long x, y, a, b;
	std::cin >> x >> y >> a >> b;
	R ray(P(x,y), P(a,b));
	std::vector<S> segments;
	segments.reserve(n);

	for(int i = 0; i < n; i++){
		std::cin >> x >> y >> a >> b;
		segments.emplace_back(P(x,y), P(a,b));
	}
	std::random_shuffle(segments.begin(), segments.end());

	for(int i = 0; i < n; i++){
		if(CGAL::do_intersect(ray, segments[i])){
			std::cout << "yes" << std::endl;
			return;
		}
	}

	std::cout << "no" << std::endl;
		

}



int main(){
	std::ios_base::sync_with_stdio(false);

	int n;
	std::cin >> n;

	while(n){
		testCase(n);
		std::cin >> n;
	}


	return 0;
}
