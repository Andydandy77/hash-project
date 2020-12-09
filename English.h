//
// Created by Kevin Lundeen on 11/2/20.
// For Seattle University, CPSC 5005, P5.Hashing-Hobbit.
//

#pragma once

#include <string>
#include <vector>

/**
 * Utilities for dealing with English text.
 */
class English {
public:
    /**
     * Take out all nonconforming characters from given string.
     * Also turns all uppercase letters into lowercase.
     * Conforming characters are:
     * - alphabetic and numeric characters (according to std::isalnum)
     * - apostrophes
     * - hyphens
     * (Note that trailing hyphens are left intact so line-break hyphenations
     * can be reconstructed by the caller by concatenating the first word of
     * the following line onto the result.)
     * @param dirtyWord to clean
     * @return          clean version of dirtyWord
     */
    static std::string cleanWord(std::string dirtyWord);

    /**
     * Get a list of common English words.
     * @return common English words
     */
    static std::vector<std::string> commonWords();

private:
    /**
     * special characters used by cleanWord
     */
    static const char APOSTROPHE_CHAR = '\'', HYPHEN_CHAR = '-';

};
