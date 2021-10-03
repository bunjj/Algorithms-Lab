#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <set>
#include <stack>

struct specie{
	std::string name;
	int age;
	std::vector<std::string> children;
};

struct query{
	std::string name;
	int age;
	int ind;
};

void testcase() {
	int n, q;
	std::cin >> n >> q;
	std::unordered_map<std::string, specie> species;
	std::set<std::pair<int, std::string>> result;
	std::unordered_map<std::string, std::vector<query>> queries;

	std::string luca;
	int oldest = 0;
	for(int i = 0; i < n; i++){
		std::string s; int a;
		std::cin >> s >> a;
		species[s] = {s, a, std::vector<std::string> ()};
		if(a > oldest){
			oldest = a;
			luca = s;
		}
	}

	for(int i = 1; i < n; i++){
		std::string s, p;
		std::cin >> s >> p;
		species[p].children.push_back(s);
	}

	for(int i = 0; i < q; i++){
		std::string s; int b;
		std::cin >> s >> b;
		queries[s].push_back({s, b, i});
	}

	std::unordered_map<std::string, bool> vis;
	std::stack<std::string> stack;
	std::vector<std::string> path;
	stack.push(luca);
	while(!stack.empty()){
		std::string current = stack.top();
		if(vis[current]){
			path.pop_back();
			stack.pop();
			continue;
		}
		vis[current] = true;
		for(auto it = species[current].children.begin(); it != species[current].children.end(); it++){
			stack.push(*it);
		}
		path.push_back(current);
		for(auto it = queries[current].begin(); it != queries[current].end(); it++){
			int age = it->age;
			int max = path.size();
			int min = 0;
			while(min < max){
				int p = min + (max-min)/2;
				if(species[path[p]].age > age){
					min = p + 1;
				}else{
					max = p;
				}
			}
			result.insert({it->ind, path[max]});
		}
	}

	for(auto out : result){
		std::cout << out.second << " ";
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
