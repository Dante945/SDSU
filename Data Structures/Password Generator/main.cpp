// Author: Dante Viscuso
// San Diego State University
// CS210/CS496: Data Structures
//
// File: main.cpp
//
// Demonstrates Reading from a given file, using arg's in order to utilize command line execution
// Filtering and manipulation of strings and using helper function with data structures as return values

#include <iostream>
#include <set>
#include <fstream> //Reading file
#include <string>
#include <sstream> //Separating words from lines
#include <algorithm> //toLower for entire string
#include <vector> //Vector to hold tokens
#include <cctype>
#include <regex> //Filter
using namespace std;


string removeNumbersAndPunctuation(string baseString) {
    int position = 0;
    for (int i = 0; i < baseString.length(); i++) {
        if (!isdigit(baseString[i])) {
            baseString[position] = baseString[i];
            position++;
        }
    }
    //The case where the token is only number
    if (position == 0)
        return " ";
    int i = 0;
    string newString = baseString.substr(0, position);
    int numOftrailingPunc = 0;

    do {
        if (ispunct(newString[newString.length() - 1 - i])) {
            numOftrailingPunc++;
        }
        i++;
    } while (!isalpha(newString[newString.length() - i]) && i < newString.length());

    //Returns String with no trailing punctuations or numbers in it
    return newString.substr(0, position - numOftrailingPunc);
}

//Generates a given number of passwords by using a unique set of tokens and returns them as a pointer
string * generatePasswords(int numPasswords, set<string> tokens) {
    string* passwords = new string[numPasswords];
    vector<string> tokenVector;
    for (const auto e: tokens) {
        tokenVector.push_back(e);
    }
    for (int j = 0; j < numPasswords; j++) {
        string password = "";
        string token = "";

        //Inner for loop creates the password with 4 unique tokens, spaces in-between, first letter uppercase and ends with a 1
        for (int i = 0; i < 4; i++) {
            if (i == 3) {
                token = tokenVector[rand() % tokens.size()];
                transform(token.begin(), token.end(), token.begin(), ::tolower);
                token[0] = toupper(token[0]);
                password = password + token;
                password = password + "1";
            } else {
                token = tokenVector[rand() % tokens.size()];
                transform(token.begin(), token.end(), token.begin(), ::tolower);
                token[0] = toupper(token[0]);
                password = password + token + " ";
            }
        }
        passwords[j] = password;
    }
    return passwords;
}

set<string> getTokens(int minLen, int maxLen, string fileName) {
    ifstream textReader;
    string line;
    set<string> tokens;
    regex test("[!-~]+");
    textReader.open(fileName);

    if (textReader.is_open()) {
        while (getline(textReader, line)) {
            istringstream iss(line);
            do {
                string token;
                iss >> token;
                //Filters Odd linux/mac characters
                if (!regex_match(token, test))
                    token = "";
                token = removeNumbersAndPunctuation(token);
                if (token != "" && token.length() >= minLen && token.length() <= maxLen)
                    tokens.insert(token);
            } while (iss);
        }
    } else
        cout << "unable to open file";
    textReader.close();
    return tokens;
}

void printPasswords(int numOfPasswords, string *arr){
    for(int i = 0; i < numOfPasswords; i++){
        cout << "Password #" << i + 1 << ": " << arr[i] << endl;
    }
}

int main(int argc, char **argv) {
    //Creates Unique passwords Everytime
    srand(time(0));

    int minLength = 3;
    int maxLength = 6;
    int numOfPasswords = 20;
    string *passwords;
    string fileName = "input.txt";

    set<string> uniqueTokens = getTokens(minLength, maxLength, fileName);
    passwords = generatePasswords(numOfPasswords, uniqueTokens);
    printPasswords(numOfPasswords, passwords);
}
