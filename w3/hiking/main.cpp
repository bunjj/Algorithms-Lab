//STL includes
#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<queue>
#include<climits>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;

struct triangle{
	std::vector<S> s;
};

bool contains(triangle t, P pt){
	for(int i = 0; i < 3; i++){
		auto orientation = CGAL::orientation(t.s[i].source(),t.s[i].target(), pt);
		if(!(orientation == CGAL::COLLINEAR || orientation == CGAL::orientation(t.s[i].source(), t.s[i].target(), t.s[(i+1)%3].source()) )) return false;
	}

	return true;
}

struct word{
	int triangle;
	int leg;
};

void testCase(){
	int m, n;
	std::cin >> m >> n;

	std::vector<P> pts;	
	pts.reserve(m);

	for(int i = 0; i < m; i++){
		int x,y;
		std::cin >> x >> y;
		pts.emplace_back(x,y);
	}

	std::vector<triangle> triangles(n);
	
	for(int i = 0; i < n; i++){
		triangles[i].s = std::vector<S> (3);
		for(int j = 0; j < 3; j++){
			int x, y, a, b;
			std::cin >> x >> y >> a >> b;
			triangles[i].s[j] = S(P(x,y), P(a,b));
		}
	}

	std::vector<std::vector<int>> dict (m-1, std::vector<int>());
	std::vector<int> current(m-1, 0);

	bool previous = false;
	for(int i = 0; i< n; i++){
		previous = false;
		for(int j = 0; j < m; j++){
			if(contains(triangles[i], pts[j])){
				if(previous) dict[j-1].push_back(i);
				previous = true;
			}else previous = false;
		}
	}

	int min = INT_MAX;
	int max = INT_MIN;

	auto cmp = [] (word & w1, word& w2) { return w1.triangle > w2.triangle; };
	std::priority_queue<word, std::vector<word>, decltype(cmp)> q(cmp);
	for(int i = 0; i < m-1; i++){
		q.push({dict[i][0], i});
		min = std::min(min, dict[i][0]);
		max = std::max(max, dict[i][0]);
	}

	int best_min = min;
	int best_max = max;
		

	while(true){
		word last = q.top();
		q.pop();
		current[last.leg]++;
		if(current[last.leg] == dict[last.leg].size()) break;
		word new_word;
		new_word.triangle = dict[last.leg][current[last.leg]];
		new_word.leg = last.leg;

		q.push(new_word);

		min = q.top().triangle;
		max = std::max(max, new_word.triangle);

		if(max - min < best_max- best_min){
			best_max = max;
			best_min = min;
		}

	}

	std::cout << best_max - best_min + 1 << std::endl;


}




int main(){
	std::ios_base::sync_with_stdio(false);
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

	int t;
	std::cin >> t;

	while(t--) testCase();

	return 0;
} 
