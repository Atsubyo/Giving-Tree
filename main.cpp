#include <map>
#include <set>
#include <sstream>
#include <iostream>

using namespace std;

void printExpression (map<char, set<char>> &parentChildMap, char currNode) {
    cout << '(' << currNode;
    for (auto it = parentChildMap[currNode].begin(); it != parentChildMap[currNode].end(); ++it) {
        printExpression(parentChildMap, *it);
    }
    cout << ")";
}

void checkE4Error (bool &E4, map<char, int> &childParentMap, char &rootVal) {
    int numRoots = 0;
    for (auto it = childParentMap.begin(); it != childParentMap.end(); ++it) {
        if (it->second == 0) {
            rootVal = it->first;
            ++numRoots;
        }
    }
    if (numRoots > 1) {
        E4 = true;
    }
}

void insertToMap (map<char, set<char>> &parentChildMap, map<char, int> &childParentMap, string userPairStr, bool &E2, bool &E3, bool &E5) {
    // debugging
    // cout << userPairStr[1] << ' ' << userPairStr[3] << '\n';

    // if duplicate pair
    if (!parentChildMap.empty()) {
        if (parentChildMap.find(userPairStr[1]) != parentChildMap.end()) {
            if (parentChildMap[userPairStr[1]].find(userPairStr[3]) != parentChildMap[userPairStr[1]].end()) {
                E2 = true;
            }
        }
    }
    // insert into maps
    parentChildMap[userPairStr[1]].insert(userPairStr[3]);
    childParentMap[userPairStr[1]];
    childParentMap[userPairStr[3]]++;
    
    // if parent has more than two children
    if (parentChildMap[userPairStr[1]].size() > 2) {
        E3 = true;
    }
    // if input contains cycle
    if (childParentMap[userPairStr[3]] > 1) {
        E5 = true;
    }
    
}

bool inputHandling (string userInputStr, map<char, set<char>> &parentChildMap, map<char, int> &childParentMap, bool &E2, bool &E3, bool &E5) {
    // cout << userInputStr << endl;
    if (userInputStr.find("  ") != string::npos) {
        return true;
    }
    if (userInputStr.front() != '(' || userInputStr.back() != ')') {
        return true;
    }
    
    // creating stringstream
    stringstream userInputSS(userInputStr);
    string userPairStr;
    
    while (userInputSS >> userPairStr) {
        // cout << userPairStr;
        // if length does not match the form
        if (userPairStr.length() != 5) {
            return true;
        } else {
            // if the pair opens and closes with appropriate parenthesis
            if (userPairStr[0] != '(' || userPairStr[4] != ')') {
                return true;
            }
            // if the rest follow correct formatting
            if (!isupper(userPairStr[1]) || userPairStr[2] != ',' || !isupper(userPairStr[3])) {
                return true;
            }
        }
        insertToMap(parentChildMap, childParentMap, userPairStr, E2, E3, E5);
    }
    return false;
}

void getUserInput (bool &E1, bool &E2, bool &E3, bool &E5, map<char, set<char>> &parentChildMap, map<char, int> &childParentMap) {
    // Get the user input
    string userInputStr;
    getline(cin, userInputStr);
    
    E1 = inputHandling(userInputStr, parentChildMap, childParentMap, E2, E3, E5);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    // Variables
    bool E1 = false;
    bool E2 = false;
    bool E3 = false;
    bool E4 = false;
    bool E5 = false;
    map<char, set<char>> parentChildMap;
    map<char, int> childParentMap;
    char rootVal;
    
    getUserInput(E1, E2, E3, E5, parentChildMap, childParentMap);
    
    checkE4Error(E4, childParentMap, rootVal);
    
    // debugging
    // for (auto it = parentChildMap.begin(); it != parentChildMap.end(); ++it) {
    //     cout << it->first << " => ";
    //     set<char> st = it->second;
    //     for (auto it = st.begin(); it != st.end(); ++it) {
    //         cout << (*it) << ' ';
    //     }
    //     cout << '\n';
    // }
    // cout << '\n';
    // for (auto it = childParentMap.begin(); it != childParentMap.end(); ++it) {
    //     cout << it->first << " => " << it->second << '\n';
    // }
    // cout << "Expected: (A(B(D(E(G))))(C(F)))" << '\n';
    
    if (E1) {
        cout << "E1\n";
    } else if (E2) {
        cout << "E2\n";
    } else if (E3) {
        cout << "E3\n";
    } else if (E4) {
        cout << "E4\n";
    }else if (E5) {
        cout << "E5\n";
    } else {
        cout << "Got: ";
        printExpression(parentChildMap, rootVal);
        cout << '\n';
    }

    return 0;
}