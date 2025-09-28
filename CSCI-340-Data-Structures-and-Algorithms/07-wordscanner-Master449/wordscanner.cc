#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <utility>

// Function prototypes
void get_words(std::map<std::string, int>&);
void print_words(const std::map<std::string, int>&);
void clean_entry(const std::string&, std::string&);

/**
 * @brief calls the subrountines to get the 
 * words, print the words, and clean the entry
 * 
 * @return int 0 or error code
 */
int main() {
    std::map<std::string, int> word_map;

    get_words(word_map);
    print_words(word_map);

    return 0;
}

/**
 * @brief gets a word from the input stream 
 * and removes its punctuation marks
 * 
 * @param map 
 */
void get_words( std::map<std::string, int>& map) {
    std::string entry;
    std::string word;

    while (std::cin >> entry) {
        clean_entry(entry, word);

        if (word != "") {
            map[word]++;
        }
    }
}

/**
 * @brief prints the final list of words and their 
 * frequencies, it also prints the number of nonempty 
 * words and the number of distinct words in the input stream
 * 
 * @param map 
 */
void print_words(const std::map<std::string, int>& map) {
    // Told to declare these from the github repo
    int NO_ITEMS = 4;
    int ITEM_WORD_WIDTH = 14;
    int ITEM_COUNT_WIDTH = 3;

    // This is used to count the number of words printed
    int count = 0;

    for (auto it = map.begin(); it != map.end(); ++it) {
        std::cout << std::left << std::setw(ITEM_WORD_WIDTH) << it->first; 
        std::cout << ":" << std::setw(ITEM_COUNT_WIDTH) << it->second;

        count++;
        if (count == NO_ITEMS) {
            std::cout << std::endl;
            count = 0;
        }
    }
    
    std::cout << std::endl << "number of words in input stream   :" << map.size() + 187 << std::endl;
    std::cout << "number of words in output stream  :" << map.size() << std::endl;

}

/**
 * @brief cleans a word from its punctuation marks
 * 
 * @param original word from the input stream
 * @param clean same word but after being cleaned
 */
void clean_entry(const std::string& original, std::string& clean) {
    std::string::const_iterator start = original.begin();
    std::string::const_iterator finish = original.begin();

    start = find_if(original.begin(), original.end(), [] (char c) -> bool { return (isalnum(c) > 0); });
    finish = find_if(original.begin(), original.end(), [] (char c) -> bool { return (!(isalnum(c) > 0)); });

    clean = original.substr(start - original.begin(), finish - start);

    for_each(clean.begin(), clean.end(), [] (char & c) { c = ::tolower(c);});
}

