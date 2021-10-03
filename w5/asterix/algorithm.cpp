#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
struct move{
	long d, t;
};

int n; long D,T;
std::vector<move> moves;

bool reachable(long bonus){
	int n1 = n/2;
	int n2 = n-n1;
	std::vector<move> cand;	
	std::vector<move> m1(moves.begin(), moves.begin() + n1);
	std::vector<move> m2(moves.begin()+ n1, moves.end());

	for(int s = 0;  s < 1<<n1; s++){
		long sum_d = 0;
		long sum_t = 0;
		for(int i = 0;  i < n1; i++){
			if(s & 1<<i){
				sum_d += m1[i].d + bonus;
				sum_t += m1[i].t;
				if(sum_t >= T) break;
			}
		}

		if(sum_t >= T) continue;
		if(sum_d >= D) return true;
		cand.push_back({sum_d, sum_t});
	}
	std::sort(cand.begin(), cand.end(), [](move& m1, move& m2){
		return m1.d < m2.d;
	});

	for(int i = cand.size() - 2; i >= 0; i--){
		cand[i].t = std::min(cand[i].t, cand[i+1].t);
	}
	for(int s = 0;  s < 1<<n2; s++){
		long sum_d = 0;
		long sum_t = 0;
		for(int i = 0;  i < n2; i++){
			if(s & 1<<i){
				sum_d += m2[i].d + bonus;
				sum_t += m2[i].t;
				if(sum_t >= T) break;
			}
		}

		if(sum_t >= T) continue;
		if(sum_d >= D) return true;

		int min = 0;
		int max = cand.size();
		while(min < max){
			int p = min + (max-min)/2;
			if(sum_d + cand[p].d >= D && sum_t + cand[p].t < T) return true;
			if(sum_d + cand[p].d >=D){
				max = p;
			}else{
				min = p+1;
			}
		}
	}

	return false;
}

void testcase() {
	int m;
	std::cin >> n >> m >> D >> T;
	moves = std::vector<move>(n);
	std::vector<long> gulp(m+1);
	gulp[0] = 0;
	for(int i = 0; i < n; i++){
		long d, t;
		std::cin >> d >> t;
		moves[i] = {d,t};
	}

	for(int i = 1; i <=m; i++){
		std::cin >> gulp[i];
	}

	int min = 0;
	int max = m+1;
	while(min < max){
		int p = min + (max-min)/2;
		if(reachable(gulp[p])){
			max = p;
		}else{
			min = p+1;
		}
	}
	if(min <= m) std::cout << min << std::endl;
	else std::cout << "Panoramix captured" << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
