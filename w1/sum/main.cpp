#include<iostream>

void testCase(){

	int n;
	std::cin >> n ;

	int sum =0 ;
	for(int i = 0 ; i < n ; i++){
		int tmp;
		std::cin >> tmp;
		sum += tmp;
	}

	std::cout << sum << std::endl;

}


int main(){

	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;

	while(t--){
		testCase();
	}

	return 0;

}
