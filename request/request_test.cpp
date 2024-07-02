#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE purity
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <cstring>
#include "request.h"

using namespace std;

BOOST_AUTO_TEST_CASE(string_constructor) {
    Request req("http://localhost:8000/request.cpp");
    cout << req.getContent() << endl;
    BOOST_CHECK(true);
}
