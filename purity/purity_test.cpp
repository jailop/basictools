#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE purity
#include <boost/test/unit_test.hpp>

#include <vector>
#include <math.h>
#include "purity.h"

using namespace std;

BOOST_AUTO_TEST_CASE(entropy_test) {
        vector<int> a({0, 0, 1, 1, 0, 0});
        BOOST_CHECK(abs(entropy(a) - 0.636514) < 1e-6);
}

BOOST_AUTO_TEST_CASE(gini_test) {
        vector<int> a({0, 0, 1, 1, 0, 0});
        BOOST_CHECK(abs(gini_index(a) - 0.444444) < 1e-6);
        vector<char> b({'a', 'a', 'b', 'b', 'a', 'a'});
        BOOST_CHECK(abs(gini_index(b) - 0.444444) < 1e-6);
}
