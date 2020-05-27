#include "map.hpp"
#include <iostream>
#include <cassert>
#include <string>

class Compare {
public:
	bool operator () (const int &lhs, const int &rhs) const {
		return lhs < rhs;
	}
};

int main()
{
    sjtu::map<int,int, Compare> map;

    auto result = map.insert(sjtu::pair<int, int>(14, 0));
    map.show();
auto   result1 = map.insert(sjtu::pair<int, int>(9, 0));
    map.show();
    auto result2 = map.insert(sjtu::pair<int, int>(-28, 0));
    map.show();
    auto result3 = map.insert(sjtu::pair<int, int>(5, 0));
    map.show();
    auto result4 = map.insert(sjtu::pair<int, int>(12, 0));
    map.show();
    auto result5 = map.insert(sjtu::pair<int, int>(25, 0));
    map.show();
    auto result6 = map.insert(sjtu::pair<int, int>(-50, 0));
    map.show();
    auto result7 = map.insert(sjtu::pair<int, int>(3, 0));
    map.show();
    auto result8 = map.insert(sjtu::pair<int, int>(20, 0));
    map.show();
    auto result9 = map.insert(sjtu::pair<int, int>(15, 0));
    map.show();
    auto result10 = map.insert(sjtu::pair<int, int>(50, 0));
    map.show();
    auto result11 = map.insert(sjtu::pair<int, int>(-23, 0));
    map.show();
    auto result12 = map.insert(sjtu::pair<int, int>(26, 0));
    map.show();
    auto result13= map.insert(sjtu::pair<int, int>(30, 0));
    map.show();
    auto result14 = map.insert(sjtu::pair<int, int>(60, 0));
    map.show();
    auto result15 = map.insert(sjtu::pair<int, int>(-24, 0));
    map.show();
    auto result16 = map.insert(sjtu::pair<int, int>(59, 0));
    map.show();
    auto result17 = map.insert(sjtu::pair<int, int>(102, 0));
    map.show();
    auto result18 = map.insert(sjtu::pair<int, int>(-235, 0));
    map.show();
    auto result19 = map.insert(sjtu::pair<int, int>(50, 0));
    map.show();
    auto result20 = map.insert(sjtu::pair<int, int>(31, 0));
    map.show();
    auto result21 = map.insert(sjtu::pair<int, int>(210, 0));
    map.show();
    auto result22 = map.insert(sjtu::pair<int, int>(159, 0));
    map.show();
    auto result23 = map.insert(sjtu::pair<int, int>(5, 0));
    map.show();
    auto result24 = map.insert(sjtu::pair<int, int>(-233, 0));
    map.show();
    auto result25 = map.insert(sjtu::pair<int, int>(268, 0));
    map.show();
    auto result26= map.insert(sjtu::pair<int, int>(-301, 0));
    map.show();
    auto result27 = map.insert(sjtu::pair<int, int>(670, 0));
    map.show();
    map.preshow();
    sjtu::map<int ,int,Compare>::const_iterator t;
    t=map.cbegin();
    std::cout<<std::endl<<std::endl<<std::endl;
	while (map.begin() != map.end()) {
        map.show();
		map.erase(++map.begin());
		std::cout<<map.size()<<std::endl;
		map.show();
	}

    //map.erase(t);
    map.show();
    return 0;
}
