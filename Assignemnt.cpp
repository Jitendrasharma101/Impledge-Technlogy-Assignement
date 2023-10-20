#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>
#include <vector>
#include <string>
#include <unordered_set>
#include <chrono>


using namespace std;
using namespace chrono;

// Define kisi ek node ko Trie mei
class TrieNode {
public:
    char val;               // Is node ke character ko store karta hai.
    unordered_map<char, TrieNode*> children; // Child nodes ki mapping.
    bool isWord;            // Is node se word ka end point hai ya nahi.

    TrieNode(char value) : val(value), isWord(false) {}

    // Naya child node add kare is node ke liye.
    void addChild(char child) {
        children[child] = new TrieNode(child);
    }

    // Diya gaya character ke corresponding child node ko de.
    TrieNode* getChild(char child) {
        return children[child];
    }

    // Diya gaya character ke child node ka existence check kare.
    bool containsChild(char child) {
        return children.find(child) != children.end();
    }
};

class Trie {
private:
    TrieNode* root; // Trie ka root node.
    TrieNode* curr; // Traverse karne ke liye pointer.

public:
    Trie() : root(new TrieNode(' ')), curr(root) {}

    // Word ko Trie mei insert kare.
    void insert(const string& s) {
        char letter;
        curr = root;

        for (size_t i = 0; i < s.length(); i++) {
            letter = s[i];

            // Agar current node ke pass letter ke corresponding child node nahi hai, toh naya child node create kare.
            if (!curr->containsChild(letter)) {
                curr->addChild(letter);
            }

            curr = curr->getChild(letter); // Child node par move kare.
        }

        curr->isWord = true; // Last node ko word ka end point mark kare.
    }

    // Suffixes ke starting indices ko Trie se nikale.
    vector<int> getSuffixesStartIndices(const string& s) {
        vector<int> indices;
        char letter;
        curr = root;

        for (size_t i = 0; i <= s.length(); i++) {
            letter = s[i];

            // Agar current node ke pass letter ke corresponding child node nahi hai, toh ab tak ke indices ko return kare.
            if (!curr->containsChild(letter)) {
                return indices;
            }

            curr = curr->getChild(letter);

            if (curr->isWord) {
                indices.push_back(i + 1); // Complete word mile to index add kare.
            }
        }

        return indices;
    }
};

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();

    // Trie create kare, words store kare aur operations perform kare.
    Trie trie;
    list<pair<string, string>> queue; // Pairs of words process karne ke liye list.
    unordered_set<string> compoundWords;

    ifstream inputFile("Input_02.txt");

    if (!inputFile.is_open()) {
        cerr << "File open karne mei error." << endl;
        return 1;
    }

    string word;
    vector<int> sufIndices;

    // Input file se words read kare aur process kare.
    while (inputFile >> word) {
        sufIndices = trie.getSuffixesStartIndices(word);

        for (int i : sufIndices) {
            if (i >= static_cast<int>(word.length())) {
                break;
            }
            queue.push_back(make_pair(word, word.substr(i))); // Word aur uske suffix ko queue mei add kare.
        }

        trie.insert(word); // Word ko Trie mei insert kare.
    }

    inputFile.close();

    pair<string, string> p;
    int maxLength = 0;
    string longest = "";
    string sec_longest = "";

    // Queue ko process kare aur compound words nikale.
    while (!queue.empty()) {
        p = queue.front();
        word = p.second;
        queue.pop_front();
        sufIndices = trie.getSuffixesStartIndices(word);

        if (sufIndices.empty()) {
            continue;
        }

        for (int i : sufIndices) {
            if (i > static_cast<int>(word.length())) {
                break;
            }

            if (i == static_cast<int>(word.length())) {
                if (static_cast<int>(p.first.length()) > maxLength) {
                    sec_longest = longest;
                    maxLength = static_cast<int>(p.first.length());
                    longest = p.first;
                }

                compoundWords.insert(p.first);
            } else {
                queue.push_back(make_pair(p.first, word.substr(i))); // Next segment ko queue mei add kare.
            }
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    // Results aur processing time print kare.
    cout << "Longest Compound Word: " << longest << endl;
    cout << "Second Longest Compound Word: " << sec_longest << endl;
    cout << "Time Taken to process the Code: " << elapsed_time.count() << " milliseconds" << endl;

    return 0;
}
