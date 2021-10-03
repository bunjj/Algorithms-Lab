#include<iostream>
#include<iomanip>
#include<vector>
#include<queue>
#include<cmath>
#include<climits>

struct word{
	int index;
	int position;
};

void testCase(){

	int n;
	std::cin >> n;
	std::vector<int> m(n);
	for(auto it = m.begin(); it != m.end(); it++){
		std::cin >> *it;
	}

	std::vector<std::vector<int>> p(n, std::vector<int>());
	for(int i = 0; i < n; i++){
		p[i].reserve(m[i]);
		for(int j = 0; j < m[i]; j++){
			int position;
			std::cin >> position;
			p[i].push_back(position);
		}
	}

	std::vector<int> current(n,0);
	auto cmp = [](const word& w1, const word& w2){ return w1.position > w2.position;};
	std::priority_queue<word, std::vector<word>, decltype(cmp)> q(cmp);


	int min = INT_MAX;
	int max = INT_MIN;
	for(int i = 0; i < n; i++){
		current[i];
		q.push({i, p[i][0]});
		min = std::min(min, p[i][0]);
		max = std::max(max, p[i][0]);
	}

	int best_max = max;
	int best_min = min;

	while(true){
		word last = q.top();
		q.pop();
		current[last.index]++;
		if(current[last.index] == m[last.index]) break;

		word new_word;
		new_word.index = last.index;
		new_word.position = p[last.index][current[last.index]];
		max = std::max(max, new_word.position);
		q.push(new_word);
		min = q.top().position;

		if(max - min < best_max-best_min){
			best_max = max;
			best_min = min;
		}

	}

	std::cout << best_max - best_min + 1 << std::endl;
}



int main(){
	std::ios_base::sync_with_stdio(false);
	std::cout <<  std::setiosflags(std::ios::fixed) << std::setprecision(0);


	int t;
	std::cin >> t;

	while(t--) testCase();
	
	return 0;
}
