#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>

struct location{
	int dist;
	int parasol;
	int location;
};
void testCase(){
	int n;
	std::cin >> n;
	std::vector<int> x(n);
	for(auto it = x.begin(); it != x.end(); it++){
		std::cin >> *it;
	}

	std::sort(x.begin(), x.end());

	int max = 0;
	int min = 0;

	std::vector<location> loc;
	while(max < n){
		if(x[max] - x[min] > 200){
			min++;
			continue;
		}
		loc.push_back({ (x[max]-x[min]+1)/2, max-min+1, (x[max]+x[min])/2});
		if((x[max]-x[min])%2) loc.push_back({ (x[max]-x[min]+1)/2, max-min+1,  (x[max]+x[min])/2 + 
				(x[max]+x[min] < 0 ? -1 : 1)});

		max++;
	}
	std::sort(loc.begin(), loc.end(), [](const location l1, const location l2){
			if(l1.parasol > l2.parasol) return true;
			else if(l1.parasol == l2.parasol && l1.dist < l2.dist) return true;
			else if(l1.parasol == l2.parasol && l1.dist == l2.dist && l1.location < l2.location) return true;
			return false;
			});

	int parasol = loc[0].parasol;
	int dist = loc[0].dist;
	std::cout << parasol << " " << dist << std::endl;
	for(int i = 0; i < n; i ++){
		if(loc[i].parasol != parasol || loc[i].dist != dist) break;
		std::cout<< loc[i].location << " ";
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
