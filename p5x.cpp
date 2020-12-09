// David Anderson
// P5x.cpp
// CPSC5910 - 03
// November 17, 2020

#include "WordCounterx.h"
#include "English.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

/**
 * This handles if a line ends with a word that has a hypen on the end.
 * It appends it with the first word on the next line
 * @param word a reference to the word that ends with a hyphen
 * @param nextWord a string of the word to append
 */
void hyphenEndLine(string &word, string nextWord) {
    word.pop_back();
    word.append(nextWord);
}

/**
 * This reads in a file and adds all the words to the wordCount object
 * It also cleans up words, and removes common english words from wordCount
 * @param inFile a reference to the ifstream file to be read
 * @param wordCount a reference to the WordCounter
 */
void readInFile(ifstream &inFile, WordCounterx &wordCount) {
    string word = "";

    cout << "Initial capacity: " << wordCount.getCapacity() << endl;
    while (inFile >> word) {
        word = English::cleanWord(word);
        if (word.back() == '-' && word.front() != '-') {
            string wordOnNextLine;
            inFile >> wordOnNextLine;
            hyphenEndLine(word, English::cleanWord(wordOnNextLine));
        }
        if (word != "")
            wordCount.addWord(word);
    }
    for (string removeWord : English::commonWords())
        wordCount.removeWord(removeWord);

}

int main() {

    string filepath;
    ifstream inFile;
    cout << "What is the filename: ";
    cin >> filepath;
    inFile.open(filepath);
    WordCounterx wordCount;

    if (inFile) {

        readInFile(inFile, wordCount);

        cout << "Word counter statistics: " << endl;
        cout << "\tunique:       " << wordCount.getUniqueWordCount() << endl;
        cout << "\ttotal:        " << wordCount.getTotalWordCount() << endl;
        cout << "\tload:         " << wordCount.getLoadFactor() << endl;
        cout << "final capacity: " << wordCount.getCapacity() << endl << endl;

        string userInput;
        cout << "Enter words (separated by space): ";
        cin.get();
        getline(cin, userInput);
        istringstream iss(userInput);
        string word;
        cout << "Analysis of words:" << endl;
        while (iss >> word) {
            cout << "\t" << word << ": " << wordCount.getWordCount(word) << endl;
        }

    } else {
        cout << "ERROR: cannot open file.\n";
    }

    return 0;
}
