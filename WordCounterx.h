// Dave Anderson
// WordCounterx.h
// CPSC5910 - 03
// November 17, 2020

#pragma once

#include <string>

/**
 * This class stores words in a hash table using hash indexing and chaining for collision resolution
 * It stores how many unique words, and total words there are and it has the capability to calculate how many
 * occurrences a particular word has. It has a default capacity size and it resizes when the load factor goes
 * above 0.75 or below 0.3
 */
class WordCounterx {

public:

    /**
     *
     * This constructs a WordCounter object and initializes the
     * hashtable with a prime capacity of closest to what the user specifies
     * or the prime closest to the default capacity
     *
     */
    WordCounterx(int userCapacity = 10);

    /**
     * Destructor
     */
    ~WordCounterx();

    /**
     * Copy constructor creates a copy of another WordCounter
     * @param other another WordCounter to copy
     */
    WordCounterx(const WordCounterx &other);

    /**
     * Assignment operator.
     * Destroys current WordCounter and copies the rhs
     * WordCounter into this
     * @param rhs another WordCounter to copy (right-hand side of = expression)
     * @return *this
     */
    WordCounterx &operator=(const WordCounterx &rhs);

    /**
     * This adds a new word to the hashTable. If the word already
     * exists, then it will increment the count of that word.
     * if the load factor goes above 0.7 then the table resizes
     * @param newWord string word to add to the hashTable
     * @return count of the word
     */
    int addWord(std::string newWord);

    /**
     * This removes a user specified word from the hashTable.
     * If the load factor goes below 0.3 then the table resizes
     * @param remove user specified word to remove
     */
    void removeWord(std::string remove);

    /**
     * This returns the number of occurrences for a specified word
     * @param countWord word to be counted in the hashTable
     * @return int number of occurences of the word
     */
    int getWordCount(std::string countWord) const;

    /**
     * This calculates the load factor (uniqueWordCount / capacity)
     * @return a double of the load factor rounded to the nearest thousandth
     */
    double getLoadFactor() const;

    /**
     * This determines the number of unique words in the hashTable
     * @return an int of the number of unique words
     */
    int getUniqueWordCount() const;

    /**
     * This determines the number of total words in the hashTable
     * @return an int of the number of total words
     */
    int getTotalWordCount() const;

    /**
     * This returns the current capacity
     * @return int of the current capacity
     */
    int getCapacity() const;

    /**
     * Determines if the hashTable has no words in it
     * @return true if the hashTable has no words, false otherwise
     */
    bool empty() const;

    /**
     * This prints each word and its occurence in the hashTable.
     * Used for debugging
     */
    void printHashTable() const;


private:

    struct BucketElem {
        std::string word;
        int count;
        BucketElem *next;

        BucketElem(std::string w, BucketElem *n, int c = 1) {
            word = w;
            count = c;
            next = n;
        }
    };

    BucketElem **hashTable;
    int capacity;
    int totalWordCount;
    int uniqueWordCount;

    // primes to choose capacity from when resizing
    static const int NUMBER_OF_PRIMES = 122;
    const int primes[NUMBER_OF_PRIMES] = {11, 13, 17, 19, 23, 29, 31, 37, 43, 53, 67, 79, 97, 107, 131, 157, 191,
                                          223, 269, 331, 389, 461, 557, 673, 797, 967, 1151, 1381, 1657, 1979,
                                          2377, 2851, 3433, 4111, 4931, 5923, 7103, 8513, 10211, 12251, 14699,
                                          17657, 21169, 25409, 30491, 36583, 43889, 52667, 63199, 75853, 91009,
                                          109211, 131059, 157259, 188707, 226451, 271753, 326087, 391331, 469583,
                                          563489, 676171, 811411, 973691, 1168451, 1402123, 1682531, 2019037,
                                          2422873, 2907419, 3488897, 4186673, 5024009, 6028807, 7234589, 8681483,
                                          10417769, 12501331, 15001603, 18001909, 21602311, 25922749, 31107317,
                                          37328761, 44794513, 53753431, 64504081, 77404907, 92885893, 111463049,
                                          133755659, 160506817, 192608173, 231129781, 277355759, 332826869,
                                          399392243, 479270713, 575124829, 690149821, 828179753, 993815743

    };

    /**
      * helper function to calculate the index of a given word using hashing
      * @param word a string to be added to the hashTable
      * @return the hashed index of the specified word
      */
    int getHashIndex(std::string word) const;

    /**
     * Helper function to delete the hashTable
     */
    void clear(int capacity);

    /**
     * helper function to copy linkedLists
     * @param headToCopy a pointer to the other BucketElem head to copy
     * @return the head pointer to the copied BucketElem
     */
    BucketElem *copy(BucketElem *headToCopy);

    /**
     * static function to help round the loadFactor
     * @param toRound a reference to the unrounded loadFactor
     */
    static void roundToThreeDecimal(double &toRound);

    /**
     * sets a new capacity that is the prime number closest to the input
     * @param userCapacity user input capacity that will turn into a prime
     */
    void setPrimeCapacity(int userCapacity);

    /**
     * This resizes the hashTables (increases if increase is true
     * decreases if increase is false
     * @param increase if true then the hashTable will double,
     * if false then the hashTable will half in size
     */
    void resize(bool increase);

    /**
     * Resize's helper function that adds the word to the resized hashTable
     * with a given count
     * @param newWord word to insert into resized hashTable
     * @param hashTable pointer to the new resized hashTable
     * @param count word occurrence of the word to add
     */
    void addToNewHash(std::string newWord, BucketElem **hashTable, int count);

    /**
     * Initializes the pointers at each index to nullptr
     * @param newTable pointer to the new hash table
     */
    void initializeNewHashTable(BucketElem **newTable);
};



