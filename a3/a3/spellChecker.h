/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: 03-28-2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>
#include <iostream>

namespace seneca {

class SpellChecker {

    std::string m_badWords[6];
    std::string m_goodWords[6];
    size_t m_counts[6];

public:

    SpellChecker(const char* filename);

    void operator()(std::string& text);

    void showStatistics(std::ostream& out) const;
};

}

#endif
