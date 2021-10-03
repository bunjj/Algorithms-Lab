#include<iostream>
#include<iomanip>
#include<vector>


void testCase(){
	int n, m;
	std::cin >> n >> m;
	int r, b;
	std::cin >> r >> b;
	r--;b--;

	std::vector<std::vector<int>> edge(n,std::vector<int>());
	for(int i = 0; i < m; i++){
		int u, v;
		std::cin >> u >> v;
		u--; v--;
		edge[u].push_back(v);
	}

	std::vector<int> max (n,-1);
	std::vector<int> min (n, n);

	max[n-1] = 0;
	min[n-1] = 0;
	for(int i = n-2; i >= 0; i--){
		for(auto it = edge[i].begin(); it != edge[i].end(); it++){
			max[i] = std::max(max[i], min[*it] + 1);
		      	min[i] = std::min(min[i], max[*it] + 1);	
		}
	}


	if(min[r] % 2){
		if(min[r] <= min[b]) std::cout << 0;
		else std::cout << 1;
	}else{
		if(min[r] < min[b]) std::cout << 0;
		else std::cout << 1;
	}
	std::cout << std::endl;
}


int main(){
	std::ios_base::sync_with_stdio(false);
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

	int t;
	std::cin >> t;
	while(t--) testCase();

	return 0;
}
