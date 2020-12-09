# Hashing Text Files

This is the final project in my data structures class at Seattle University. We were tasked to create a class that implemented a Hash
Table to analyze a natural language text and generate a table of distinct words with the occurrences of each word. This hash table uses separate chaining
to handle collisions.

The Hash table also resizes itself when the load factor gets too high or too low. 

When the load factor (uniqueWordCount / bucketCount) > 0.75, the Hash Table
increases its size to the prime number nearest to double the current size. 

When the load factor (uniqueWordCount / bucketCount) <  0.3, the Hash Table 
decreases its size to the prime number nearest to half the current size.

## Definition of a Distinct Word

* A word is defined as a series of alphanumeric numbers
* Punctuation and spaces can both delineate a word
* Counting words is not case sensitive.
* Plural possessives and contractions are counted as one word (e.g. can't or widows')
* For words that have a hyphen in between them, count it as one word (ten-year-old)
* Words that are broken across line endings using hyphens, combine the two and remove the hyphen

## Class Methods

* Constructor: Initializes the hashtable with a prime capacity of closest to what the user specifies (default is size of 11)
* Big 4: Copy Constructor, Assignment Overload Operator, Destructor included
* addWord: Adds a new word to the hashTable. If the word already exists, then it will increment the count of that word. if the load factor goes above 0.7 then the table resizes.
* removeWord: Removes a user specified word from the hashTable. If the load factor goes below 0.3 then the table resizes.
* getWordCount: Returns the number of occurrences for a specific word
* getLoadFactor: Returns the current load factor (uniqueWordCount / capacity) rounded to three decimal places
* getUniqueWordCount: Returns the number of unique words encountered. Excludes any removed words
* getTotalWordCount: Returns the total number of words encountered, including duplicates. Excludes any removed words.
* empty: Returns true if no words have been added to the hash table.

## Hash Function
I used C++ Standard Library's hash to calculate a new word's bucket location. The index would be calculated as such:
``` 
hash<string> h;
return h(word) % capacity;
```

## Test Driver




