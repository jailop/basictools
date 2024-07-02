CXXFLAGS = -Wall
TEST_LIB = -lboost_unit_test_framework 
TESTS = purity_test

all: $(TESTS)

purity_test: purity_test.cpp purity.h
	$(CXX) $(CXXFLAGS) $? -lm $(TEST_LIB) -o $@

install:
	cp purity.h /usr/local/include

clean:
	rm -f $(OBJS)
	rm -f $(TESTS)
