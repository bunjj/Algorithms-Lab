//STL includes
#include<iostream>
#include<iomanip>
#include<vector>


#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

typedef  CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;

typedef  CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef  CGAL::Min_circle_2_traits_2<EK>  ETraits;
typedef  CGAL::Min_circle_2<ETraits>      EMin_circle;

typedef K::Point_2 P;

double ceil_to_double(const EK::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a >= x+ 1) a -= 1;
  return a;
}

void testCase(int n){
	std::vector<P> pts;
	pts.reserve(n);
	for(int i = 0; i < n; i++){
		long x, y;
		std::cin >> x >> y;
		pts.emplace_back(x,y);
	}


	Min_circle mc(pts.begin(), pts.end(), true);

	std::vector<EK::Point_2> supp_points;

	for(auto it = mc.support_points_begin(); it != mc.support_points_end(); it++){
	       supp_points.emplace_back(it->x(), it->y());
	}	       

	EMin_circle result(supp_points.begin(), supp_points.end(), true);
	ETraits::Circle c = result.circle();
	std::cout << ceil_to_double(CGAL::sqrt(c.squared_radius())) << std::endl;

}



int main(){

	std::ios_base::sync_with_stdio(false);
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

	int n;
	std::cin >> n;

	while(n){
		testCase(n);
		std::cin >> n;
	}

	return 0;
}
