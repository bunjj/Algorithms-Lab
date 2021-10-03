#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <unordered_map>

int bonus(int a, int b, int c){
	return ((a && a != b && a != c) + (b && b != c) + 1) * 1000;
}

void insert(std::unordered_map<uint32_t, int> & next, uint32_t key, int previous_round, int current_round){
	if(current_round < 0) return;
	auto it = next.find(key);
	if(it == next.end()) next[key] = previous_round + current_round;
	else it->second = std::max(it->second, previous_round + current_round);
}

void testcase() {
	int n, k, m;
	std::cin >> n >> k >> m;
	const int mask = (m == 3) ? 255 : 15;
	const uint32_t offset = 12;
	std::vector<int> fighter(n);
	for(int i = 0; i < n; i++){
		std::cin >> fighter[i];
		fighter[i]++;
	}

	std::unordered_map<uint32_t, int> current, next;
	next[offset << 16] = 0;

	for(int f : fighter){
		std::swap(current, next);
		next.clear();
		for(auto it: current){
			uint32_t key = it.first;
			int value = it.second;

			int difference = (key >> 16) - offset;

			int south_history = (key >> 8) & mask;
			int north_history = key & mask;

			int new_south = ((south_history << 4) + f) & mask;
			int new_north = ((north_history << 4) + f) & mask;

			int south_value = bonus( (south_history >> 4) & 15, south_history & 15, f);
			south_value -= 1<<std::abs(difference - 1);
			int north_value = bonus((north_history >> 4) & 15, north_history & 15, f);
			north_value -= 1 <<std::abs(difference + 1);

			uint32_t south_key = (difference + offset - 1) << 16;
			south_key += new_south << 8;
			south_key += north_history;

			uint32_t north_key = (difference + offset + 1) << 16;
			north_key += south_history << 8;
			north_key += new_north;

			insert(next, north_key, value, north_value);
			insert(next, south_key, value, south_value);

		}

	}

	int max = 0;
	for(auto it : next){
		max = std::max(max, it.second);
	}

	std::cout << max << std::endl;

}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
