#include<iostream>
#include<iomanip>


void testCase(){
	int n;
	std::cin >> n;
	int max = 1;
	int count = 0;
	int i;
	for(i = 0; i < n; i++){
		int h;
		std::cin >> h;
		if( i  < max){
			count++;
			max = std::max(max, i+h);
		}else break;
	}
	i++;
	for(;i< n;i++){
		int h;
		std::cin >> h;
	}

	std::cout << count << std::endl;

}


int main(){
	std::ios_base::sync_with_stdio(false);
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

	int t;
	std::cin >> t;

	while(t--){
		testCase();

	}

	return 0;
}
