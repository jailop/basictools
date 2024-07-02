#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE purity
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <cstring>
#include "htmlparser.h"

using namespace std;

BOOST_AUTO_TEST_CASE(string_constructor) {
    char content[] = "<html><body><h1>Hola munod</h1><body></html>";
    HTMLParser hp(content);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(xpath_test) {
    char content[] = "<ul><li>1</li><li>2</li><li>3</li></ul>";
    HTMLParser hp(content);
    auto vec = hp.xpath("//li");
    BOOST_CHECK(vec.size() == 3);
    BOOST_CHECK(vec[0].getRootName() == "li");
}
