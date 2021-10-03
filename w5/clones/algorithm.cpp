#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>

struct jedi{
	int a, b;
};

int range(int start, int end, std::vector<jedi>& j){
	int count = 0;
	for(int i = 0; i < j.size() && j[i].b < end; i++){
		if(j[i].a > start){
			count++;
			start = j[i].b;
		}
	}

	return count;
}

void testcase() {
	int n, m;
	std::cin >> n >> m;

	std::map<int, int> covered;
	std::vector<jedi> j(n);
	for(int i =0 ;i < n; i++){
		int a, b;
		std::cin >> a >> b;
		a--;b--;
		j[i] = {a,b};
		covered[a]++;
		covered[b+1]--;
		if(b < a) covered[0]++;
	}

	int min = 11;
	int start = 0;
	int current = 0;
	for(auto it : covered){
		current += it.second;
		if(current < min){
			min = current;
			start = it.first;
		}
	}

	int diff = m-start;
	std::vector<jedi> j2; j2.reserve(n);
	std::vector<jedi> j_zone;

	for(int i = 0; i < n; i++){
		int a = (j[i].a + diff) % m;
		int b = (j[i].b + diff) % m;
		if(b < a) j_zone.push_back({a,b});
		else j2.push_back({a,b});
	}
	std::sort(j2.begin(), j2.end(), [](jedi& fst, jedi& snd){
		return fst.b < snd.b;
	});

	int result = range(-1. ,m, j2);

	for(int i = 0; i < j_zone.size(); i++){
		result = std::max( result, range(j_zone[i].b, j_zone[i].a, j2) + 1);
	}

	std::cout << result << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
