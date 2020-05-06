//
// Created by Alex Preston on 5/5/20.
//

#ifndef PLAGERISMDETECTOR_TRIVIALMATCHING_H
#define PLAGERISMDETECTOR_TRIVIALMATCHING_H
using namespace std;

#include <vector>
#include "string"

class trivialMatching {
public:
    trivialMatching();
    void readTargetFile();
    void readDatabaseFiles();
    void tokenizeString(string ID, string text);
    void createUnionList();
    void createIntersectionList();
    int tokenSimilarity();

private:
    vector<pair<vector<string>, string>>database;
    vector<string> targetWords;
    vector<string> unionVector;
    vector<string> intersectionVector;
    vector<pair<string, int>>unionNumbers;
    vector<pair<string, int>>intersectionNumbers;
    vector<pair<float, string>> similarities;
};


#endif //PLAGERISMDETECTOR_TRIVIALMATCHING_H
