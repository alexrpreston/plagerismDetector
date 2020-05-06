//
// Created by Alex Preston on 5/5/20.
//

#include "trivialMatching.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <algorithm>
namespace fs = std::__fs::filesystem;

trivialMatching::trivialMatching() {
    readTargetFile();
    readDatabaseFiles();
    createUnionList();
    createIntersectionList();
    tokenSimilarity();
}

void trivialMatching::readTargetFile() {
    string line;
    ifstream targetInfile ("../target/target.txt");
    if (targetInfile.is_open())
    {
        while ( getline (targetInfile,line) )
        {
            tokenizeString("T", line);
        }
        targetInfile.close();
    }

}

void trivialMatching::readDatabaseFiles() {
    std::string path = "../database";
    for (const auto & entry : fs::directory_iterator(path)){
        string dataBaseFileName = entry.path().string();
        vector<string> words;
        pair<vector<string>, string> fileLine;
        fileLine = make_pair(words, dataBaseFileName.substr(path.length()+1));
        database.push_back(fileLine);
        string line;
        ifstream targetInfile (dataBaseFileName);
        if (targetInfile.is_open())
        {
            while ( getline (targetInfile,line) )
            {
                tokenizeString(dataBaseFileName.substr(path.length()+1), line);
            }
            targetInfile.close();
        }
    }


}

void trivialMatching::tokenizeString(string ID, string text) {
    char *cstr = &text[0];
    char * token = strtok(cstr, " ");
    while(token != NULL) {
        string buffer = "";
        for (int i = 0; i < strlen(token); i++) {
            if (isalpha(tolower(token[i]))) buffer += char(tolower(token[i]));
        }
        if(buffer.size() != 0){
            if(ID == "T"){
                targetWords.push_back(buffer);
            }
            else{
                for(int i = 0; i < database.size(); i++){
                    if(database[i].second == ID){
                        database[i].first.push_back(buffer);
                    }
                }

            }
        }
        token = strtok(NULL, " ");
    }
}

void trivialMatching::createUnionList() {
    cout << "union" << endl;
    sort( targetWords.begin(), targetWords.end() );
    targetWords.erase( unique( targetWords.begin(), targetWords.end() ), targetWords.end());
    for(int i = 0; i < database.size(); i++){
        sort( database[i].first.begin(), database[i].first.end() );
        database[i].first.erase( unique( database[i].first.begin(), database[i].first.end() ), database[i].first.end());
    }

    for(int i = 0; i < database.size(); i++){

        int total = 0;
        //Adds all Database words to the same vector as the target words
        for(int j = 0; j < database[i].first.size(); j++){
            unionVector.push_back(database[i].first[j]);
        }
        for(int j = 0; j < targetWords.size(); j++){
            unionVector.push_back(targetWords[j]);
        }
        sort( unionVector.begin(), unionVector.end() );
        unionVector.erase( unique( unionVector.begin(), unionVector.end() ), unionVector.end());
        total = unionVector.size();
        unionVector.clear();
        cout << total << " " << database[i].second << endl;
        pair<string, int>unionTotal;
        unionTotal = make_pair(database[i].second, total);
        unionNumbers.push_back(unionTotal);
    }
}

void trivialMatching::createIntersectionList() {
    cout << "intersetion" << endl;
    for(int i = 0; i < database.size(); i++){
        int total = 0;
        for(int j = 0; j < database[i].first.size(); j++) {
            for (int a = 0; a < targetWords.size(); a++) {
                if (targetWords[a] == database[i].first[j]) {
                    intersectionVector.push_back(targetWords[a]);

                }
            }
        }
        pair<string, int>intersectionTotal;
        total = intersectionVector.size();
        cout << total << " " << database[i].second << endl;
        intersectionVector.clear();
        intersectionTotal = make_pair(database[i].second, total);
        intersectionNumbers.push_back(intersectionTotal);



    }

}

int trivialMatching::tokenSimilarity() {
    cout << "Similar" << endl;
    pair<float, string> similarity;
    for(int i = 0; i < unionNumbers.size(); i++){
        float similarPercent = ((float)intersectionNumbers[i].second / (float)unionNumbers[i].second) * 100;
        similarity = make_pair(similarPercent, unionNumbers[i].first);
        cout << similarPercent << " " << unionNumbers[i].first << endl;
        similarities.push_back(similarity);
    }

    return 0;
}
