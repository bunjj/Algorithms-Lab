//STL includes
#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>

//CGL includes
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

P intersect(R ray, S segment){
	auto o = CGAL::intersection(ray, segment);
	if(const P* op = boost::get<P>(&*o)) return *op;
	else if(const S* os = boost::get<S>(&*o)){
		return (CGAL::squared_distance(ray.source(), os->source()) < CGAL::squared_distance(ray.source(), os->target()) ? os->source() : os->target() );
	}

	return P(0,0);

}

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testCase(int n){
	long x, y ,a ,b;
	std::cin >> x >> y >> a >> b;

	P origin(x,y);
	P direction(a,b);

	R ray(origin, direction);

	std::vector<S> segments;
	segments.reserve(n);

	for(int i = 0; i < n; i++){
		std::cin >> x >> y >> a >> b;
		segments.emplace_back(P(x,y), P(a,b));
	}

	std::random_shuffle(segments.begin(), segments.end());


	int i = 0;

	S ray_segment;
	for(; i < n; i++){
		if(CGAL::do_intersect(ray, segments[i])){
				P end = intersect(ray, segments[i]);
				ray_segment = S(origin, end);
				break;
		}
	}

	if(i==n) {
		std::cout << "no" << std::endl;
		return;
	}

	for(; i < n; i++){
		if(CGAL::do_intersect(ray_segment, segments[i])){
				P end = intersect(ray, segments[i]);
				ray_segment = S(origin, end);
		}
	}

	
	std::cout << floor_to_double(ray_segment.target().x()) << " " << floor_to_double(ray_segment.target().y()) << std::endl;


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
