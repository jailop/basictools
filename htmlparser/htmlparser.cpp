#include <stdexcept>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include "htmlparser.h"

#define DOC(a) (static_cast<xmlDocPtr>(a))

ostream& operator<<(ostream& os, const HTMLParser &hp) {
    xmlNodePtr node = DOC(hp._doc)->children;
    switch (node->type) {
        case XML_TEXT_NODE:
            os << node->content;
            break;
        case XML_ATTRIBUTE_NODE:
            os << node->name;
            break;
        default:
            os << node->name;
    }
    return os;
}

string HTMLParser::getRootName() { 
    string s((const char *) DOC(_doc)->children->name); 
    return s;
}

string HTMLParser::getRootContent() {
    string s((const char *) DOC(_doc)->children->content);
    return s;
}

string HTMLParser::getRootAttr(const char *attr) {
    xmlChar *value = xmlGetProp(DOC(_doc)->children, (const xmlChar *) attr);
    string s((const char *) value);
    xmlFree(value);
    return s;
}

HTMLParser::HTMLParser() : _doc(nullptr) {
    xmlInitParser();
    LIBXML_TEST_VERSION;
}

HTMLParser::HTMLParser(const HTMLParser &hp) {
    _doc = (hp._doc != nullptr) ? xmlCopyDoc(DOC(hp._doc), 1) : nullptr;
};

HTMLParser::HTMLParser(const char *content) {
    HTMLParser();
    setContent(content);
}

HTMLParser::HTMLParser(string content) {
    HTMLParser();
    setContent(content.c_str());
}

void HTMLParser::setContentFromFile(const char *filename) {
    // TO BE FIXED
    // if (_doc != nullptr) xmlFreeDoc(_doc);
    _doc = htmlReadFile(filename, NULL,
        HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | 
        HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
    if (!_doc)
        throw invalid_argument("Error: content cannot be parsed");
}

void HTMLParser::setContent(const char *content) {
    // TO BE FIXED
    // if (_doc != nullptr) xmlFreeDoc(_doc);
    _doc = htmlReadDoc((const xmlChar *) content, NULL, NULL,
        HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | 
        HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
    if (!_doc)
        throw invalid_argument("Error: content cannot be parsed");
}

HTMLParser::~HTMLParser() {
    if (_doc != nullptr) xmlFreeDoc(DOC(_doc));
    xmlCleanupParser();
    xmlMemoryDump();
}

vector<HTMLParser> HTMLParser::xpath(const char *xpath_expr) {
    vector<HTMLParser> vec;
    xmlXPathContextPtr ctx;
    xmlXPathObjectPtr obj;
    ctx = xmlXPathNewContext(DOC(_doc));
    if (ctx == NULL)
        throw invalid_argument("Error: XPath expression is not valid");
    obj = xmlXPathEvalExpression((const xmlChar *) xpath_expr, ctx);
    if (obj == NULL) 
        throw invalid_argument("Error: XPath expression is not valid");
    if (obj->nodesetval) {
        int n = obj->nodesetval->nodeNr;
        for (int i = 0; i < n; i++) {
            HTMLParser hp;
            hp._doc = xmlNewDoc(BAD_CAST "1.0");
            xmlDocSetRootElement(DOC(hp._doc), 
                xmlCopyNode(obj->nodesetval->nodeTab[i], 1));
            vec.push_back(hp);
        }
    }
    xmlXPathFreeObject(obj);
    xmlXPathFreeContext(ctx);
    return vec;
}
