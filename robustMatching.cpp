//
// Created by Alex Preston on 5/5/20.
//

#include "robustMatching.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <chrono>
#include <iostream>
namespace fs = std::__fs::filesystem;
using namespace std;

robustMatching::robustMatching() {
    cout << "Gestalt Pattern Matching Algorithm (Robust):" << endl;
    auto start = std::chrono::high_resolution_clock::now();
    readTargetFile();
    readDatabaseFiles();
    gestaltPatternMatching();
    auto finish = std::chrono::high_resolution_clock::now();

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(finish-start);
    std::cout << "Robust Version completed in " << seconds.count() << " second.\n";

}

void robustMatching::readTargetFile() {
    string total = "";
    string line;
    ifstream targetInfile ("../target/target.txt");
    if (targetInfile.is_open())
    {
        while ( getline (targetInfile,line) )
        {
            total+= line;
        }
        targetInfile.close();
        targetFileLines = line;
    }

}

void robustMatching::readDatabaseFiles() {
    std::string path = "../database";
    for (const auto & entry : fs::directory_iterator(path)){
        string dataBaseFileName = entry.path().string();

        ifstream targetInfile (dataBaseFileName);
        string total = "";
        string line = "";
        if (targetInfile.is_open())
        {

            while ( getline (targetInfile,line) )
            {
                total+= line;
            }
        }
        pair<string, string>dataBaseLine;
        dataBaseLine = make_pair(line, dataBaseFileName.substr(path.length()+1));
        database.push_back(dataBaseLine);
        targetInfile.close();
    }

}

void robustMatching::gestaltPatternMatching() {
    for(int i = 0; i < database.size(); i++){
        int length = 0;
        length = database[i].first.size() + targetFileLines.size();
        float similaritiy = (2*(float)longestCSResusive(database[i].first)) / ((float)length);
        cout << "'target.txt' has a " << similaritiy*100 << "% to " << database[i].second << endl;
        totalLCS = 0;

    }
}

string robustMatching::longestCommonSubstring(string target, string database) { //Helper since we have to recurse through left and right
    int targetLength = target.size();
    int databaseLength = database.size();
    int result = 0;
    int end;
    int table[2][databaseLength];
    int currentString = 0;

    for (int i = 0; i <= targetLength; i++) {
        for (int j = 0; j <= databaseLength; j++) {
            if (i == 0 || j == 0) { //Zeroing out the top right corner of table
                table[currentString][j] = 0;
            }
            else if (target[i - 1] == database[j - 1]) { //There is a string character match
                table[currentString][j] = table[1 - currentString][j - 1] + 1;
                if (table[currentString][j] > result) {
                    result = table[currentString][j];
                    end = i - 1;
                }
            }
            else {
                table[currentString][j] = 0; //Since there is no match for an individual character we zero the table
            }
        }
        currentString = 1 - currentString; //The two strings get flipped
    }
    return target.substr(end - result + 1, result);
}

int robustMatching::longestCSResusive(string database) {
    string currentLCS = longestCommonSubstring(targetFileLines, database);
    if(currentLCS.size() > 5)totalLCS += currentLCS.size(); //This ensures we aren't counting dummy characters ex: coding --> the 'ing' in flying


    std::size_t found = database.find(currentLCS);
    if (found!=std::string::npos && found != 0){
        string leftDatabaseHalf = database.substr(0, found);
        if(leftDatabaseHalf.size() > 0){
            longestCSResusive(leftDatabaseHalf);
        }
        string rightDatabaseHalf = database.substr(found+currentLCS.size());
        if(rightDatabaseHalf.size() > 0){
            longestCSResusive(rightDatabaseHalf);
        }
    }

    return totalLCS;



}




