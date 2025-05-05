#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long int w[5] = {0, 0, 0, 0, 0};
        int len = k.length();
        int w_len = len/6;
        for (int i = 0; i < (w_len + 1); i++) {
            int end = len - (i * 6);
            int begin = std::max(0, end - 6);
            std::string s = k.substr(begin, end -  begin);
            w[4-i] = helper(s);
        }
        HASH_INDEX_T output = 0;
        for (int i = 0; i < 5; i++) {
            std::cout << "w[" << i << "] = " << w[i] << std::endl;
            output += w[i] * rValues[i];
        }
        return output;
    }

    // given the 6 digit string, helps generate the numeric values
    unsigned long long helper (const std::string& str) const {
        std::string updated_str;
        int len = str.length();
        if (len < 6) {
            for (int i = 0; i < (6 - len); i++) {
                updated_str += 'a';
            }
            for (int i = 0; i < len; i++) {
                updated_str += str[i];
            }
        }
        else {
            updated_str = str;
        }
        unsigned long long output = 0;
        for (int i = 0; i < 6; i++) {
            int digit = letterDigitToNumber(updated_str[i]);
            output = output * 36 + digit;
        }
        return output;
    }
    
    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T number = 0;
        letter = std::tolower(letter);
        if (std::isalpha(letter)) {
            number = letter - 'a';
        }
        else if (std::isdigit(letter)){
            number = 26 + (letter - '0');
        }
        return number;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
