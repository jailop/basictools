CXXFLAGS = -Wall -Werror -g
LDLIBS = -lrequest -lhtmlparser `xml2-config --libs` `curl-config --libs`
BINS = scraper

all: $(BINS)

scraper: scraper.cpp

clean:
	rm -f $(BINS)
