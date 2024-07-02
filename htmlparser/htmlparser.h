#ifndef _HTMLPARSER_H
#define _HTMLPARSER_H

#include <ostream>
#include <vector>

using namespace std;

class HTMLParser {
public:
        HTMLParser();
        HTMLParser(const HTMLParser &hp);
        HTMLParser(const char *content);
        HTMLParser(string content);
        void setContent(const char *content);
        void setContentFromFile(const char *filename);
        vector<HTMLParser> xpath(const char *xpath_expr);
        friend ostream& operator<<(ostream& os, const HTMLParser &hp);
        ~HTMLParser();
        string getRootName();
        string getRootContent();
        string getRootAttr(const char *attr);
private:
        void* _doc;
};

ostream& operator<<(ostream& os, const HTMLParser &hp);



#endif // _HTMLPARSER_H
