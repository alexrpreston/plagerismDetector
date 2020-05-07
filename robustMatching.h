//
// Created by Alex Preston on 5/5/20.
//

#ifndef PLAGERISMDETECTOR_ROBUSTMATCHING_H
#define PLAGERISMDETECTOR_ROBUSTMATCHING_H

#include <vector>
#include "string"
using namespace std;

class robustMatching {
public:
    robustMatching();
    void readTargetFile();
    void readDatabaseFiles();
    void gestaltPatternMatching();
    string longestCommonSubstring(string target, string database);
    int longestCSResusive(string database);
    int totalLCS = 0;
private:
    vector<pair<string, string>>database;
    string targetFileLines;
};


#endif //PLAGERISMDETECTOR_ROBUSTMATCHING_H
