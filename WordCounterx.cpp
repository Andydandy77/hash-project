// Dave Anderson
// WordCounterx.cpp
// CPSC5910 - 03
// November 17, 2020

#include "WordCounterx.h"

#include <math.h>
#include <iostream>

using namespace std;


WordCounterx::WordCounterx(int userCapacity) {
    setPrimeCapacity(userCapacity);
    hashTable = new BucketElem *[capacity];
    totalWordCount = 0;
    uniqueWordCount = 0;
    initializeNewHashTable(hashTable);

}

WordCounterx::~WordCounterx() {
    clear(capacity);
}

WordCounterx::WordCounterx(const WordCounterx &other) {
    capacity = other.capacity;
    hashTable = new BucketElem *[capacity];
    totalWordCount = other.totalWordCount;
    uniqueWordCount = other.uniqueWordCount;
    for (int i = 0; i < capacity; i++) {
        hashTable[i] = copy(other.hashTable[i]);
    }

}

WordCounterx &WordCounterx::operator=(const WordCounterx &rhs) {
    if (this != &rhs) {
        capacity = rhs.capacity;
        totalWordCount = rhs.totalWordCount;
        uniqueWordCount = rhs.uniqueWordCount;
        clear(capacity);
        for (int i = 0; i < capacity; i++) {
            hashTable[i] = copy(rhs.hashTable[i]);
        }
    }

    return *this;
}

int WordCounterx::addWord(std::string newWord) {
    int wordCount = 0;
    int index = getHashIndex(newWord);
    bool addWord = true;
    if (hashTable[index] != nullptr) {
        BucketElem *curr = hashTable[index];
        while (curr != nullptr) { // if the word is found search for it until its found and update count
            if (curr->word == newWord) {
                curr->count++;
                wordCount = curr->count;
                addWord = false;
            }
            curr = curr->next;
        }

        if (addWord) {
            hashTable[index] = new BucketElem(newWord, hashTable[index]);
            wordCount = 1;
            uniqueWordCount++;

        }
    } else {
        hashTable[index] = new BucketElem(newWord, hashTable[index]);
        wordCount = 1;
        uniqueWordCount++;


    }
    totalWordCount++;


    if (getLoadFactor() > 0.75)
        resize(true);

    return wordCount;

}

void WordCounterx::removeWord(std::string remove) {
    int index = getHashIndex(remove);
    BucketElem *toDelete;

    if (hashTable[index] != nullptr) {
        if (hashTable[index]->word == remove) { // if the head is the word to remove
            totalWordCount -= hashTable[index]->count;
            uniqueWordCount--;
            toDelete = hashTable[index]; // delete this word and set head to the next word
            hashTable[index] = hashTable[index]->next;
            delete toDelete;
        } else {

            BucketElem *curr = hashTable[index];
            BucketElem *prev;
            while (curr != nullptr && curr->word != remove) {
                prev = curr;
                curr = curr->next;
            }
            if (curr == nullptr) {
                return;
            }
            prev->next = curr->next;
            totalWordCount -= curr->count;
            uniqueWordCount--;
            delete curr;
        }
    }

    if (getLoadFactor() < 0.3)
        resize(false);
}

int WordCounterx::getWordCount(std::string countWord) const {
    hash<string> h;
    int index = h(countWord) % capacity;
    for (BucketElem *curr = hashTable[index]; curr != nullptr; curr = curr->next) {
        if (curr->word == countWord)
            return curr->count;
    }
    return 0; // if the word wasn't found then just return 0
}

double WordCounterx::getLoadFactor() const {
    double loadFactor = 1.0 * uniqueWordCount / capacity;
    roundToThreeDecimal(loadFactor);
    return loadFactor;
}

int WordCounterx::getUniqueWordCount() const {
    return uniqueWordCount;
}

int WordCounterx::getTotalWordCount() const {
    return totalWordCount;
}

bool WordCounterx::empty() const {
    return totalWordCount == 0;
}

void WordCounterx::clear(int cap) {
    for (int i = 0; i < cap; i++) {
        BucketElem *head = hashTable[i];
        while (head != nullptr) {
            BucketElem *toDelete = head;
            head = head->next;
            delete toDelete;
        }
    }
    delete[] hashTable;

}

WordCounterx::BucketElem *WordCounterx::copy(WordCounterx::BucketElem *headToCopy) {
    BucketElem anchor("", nullptr), *source, *tail;
    tail = &anchor;
    for (source = headToCopy; source != nullptr; source = source->next) {
        tail->next = new BucketElem(source->word, source->next, source->count);
        tail = tail->next;
    }
    return anchor.next;
}

void WordCounterx::roundToThreeDecimal(double &toRound) {
    toRound = round(toRound * 1000.0) / 1000.0;
}

int WordCounterx::getCapacity() const {
    return capacity;
}

void WordCounterx::printHashTable() const {
    int total = 0;
    for (int i = 0; i < capacity; i++) {
        BucketElem *cur = hashTable[i];
        while (cur != nullptr) {
            total += cur->count;
            cout << cur->word << ": " << cur->count << endl;
            cur = cur->next;
        }
    }
    cout << "total: " << total << endl;

}

void WordCounterx::setPrimeCapacity(int userCapacity) {
    for (int i = 0; i < NUMBER_OF_PRIMES; i++) {
        if (primes[i] >= userCapacity) {
            capacity = primes[i];
            return;
        }
    }
}

void WordCounterx::resize(bool increase) {
    int oldCapacity = capacity;

    if (increase) {
        setPrimeCapacity(capacity * 2);
//        cout << "Resizing: " << oldLoadFactor  << " > 0.750 -- from " << oldCapacity << " to " << capacity << endl << endl;
    } else {
        setPrimeCapacity(capacity / 2);
//        cout << "Resizing: " << oldLoadFactor << " < 0.300 -- from " << oldCapacity << " to " << capacity << endl << endl;
    }
    auto **newHashTable = new BucketElem *[capacity];
    initializeNewHashTable(newHashTable);


    for (int i = 0; i < oldCapacity; i++) {
        BucketElem *cur = hashTable[i];
        while (cur != nullptr) {
            addToNewHash(cur->word, newHashTable, cur->count);
            cur = cur->next;
        }
    }

    clear(oldCapacity);
    hashTable = newHashTable;
}

int WordCounterx::getHashIndex(std::string word) const {
    hash<string> h;
    return h(word) % capacity;
}

void WordCounterx::addToNewHash(std::string newWord, BucketElem **hashTable, int count) {
    int index = getHashIndex(newWord);

    hashTable[index] = new BucketElem(newWord, hashTable[index], count);


}

void WordCounterx::initializeNewHashTable(WordCounterx::BucketElem **newTable) {
    for (int i = 0; i < capacity; i++) {
        newTable[i] = nullptr;
    }
}




