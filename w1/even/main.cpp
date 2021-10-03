#include<iostream>
#include<iomanip>
#include<vector>

void testCase(){
	int n;
	std::cin >> n;

	int parity = 0;
	int odd = 0;
	int even = 0;

	for(int i = 0; i < n; i++){
		int x;
		std::cin >> x;
		parity = (parity+x)%2;
		if(parity) odd++;
		else even++;
	}
	
	int result = even + even*(even-1) / 2 + odd*(odd-1)/2;
	std::cout << result << std::endl;

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
