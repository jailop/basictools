#include <iostream>
#include <sstream>
#include <fstream>
#include <htmlparser.h>
#include <request.h>

#define BASE_URL "https://revistas.csuca.org"
#define INDEX_PATH "/Search/Results?page="

using namespace std;

string readFile(const char* filename) {
    fstream fs;
    string content, aux;
    fs.open(filename, ios::in);
    while (getline(fs, aux)) content += aux;
    fs.close();
    return content;  
}

vector<string> getEntryPaths(string index_page) {
    char expr[] = "//*[@class=\"result-body\"]/div[1]/a";
    HTMLParser hp(index_page);
    vector<HTMLParser> entries = hp.xpath(expr);
    vector<string> paths; 
    for (HTMLParser entry : entries) 
        paths.push_back(entry.getRootAttr("href"));
    return paths; 
}

string getIndexPage(int counter) {
    ostringstream os;
    os << BASE_URL << INDEX_PATH << counter;
    Request req(os.str().c_str());
    return req.getContent();
}

string getArticlePage(string path) {
    string url(BASE_URL);
    url += path;
    Request req(url.c_str()); 
    return req.getContent();
}

int main() {
    // cout << getIndexPage(1) << endl;
    // string content = readFile("page_1.html");
    // vector<string> paths = getEntryPaths(content);
    // string art = getArticlePage(paths[0]);
    // cout << art << endl;
    string art = readFile("article.html");
    HTMLParser hp(art);
    string title = hp.xpath("/html/body/div[1]/div/div/div[1]/div[1]/div[2]/h1/text()")[0].getRootContent();
    auto res =  hp.xpath("/html/body/div[1]/div/div/div[1]/div[1]/div[2]/table/tbody/tr[1]/td/span/a");
    cout << title << endl;
    cout << res.size() << endl;
    return 0;
}
