/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: 03-28-2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#include "spellChecker.h"
#include <fstream>
#include <iomanip>

using namespace std;

namespace seneca {

SpellChecker::SpellChecker(const char* filename) {

    ifstream file(filename);

    if (!file) {
        throw "Bad file name!";
    }

    for (size_t i = 0; i < 6; i++) {
        file >> m_badWords[i];
        file >> m_goodWords[i];
        m_counts[i] = 0;
    }
}

void SpellChecker::operator()(string& text) {

    for (size_t i = 0; i < 6; i++) {

        size_t pos = 0;

        bool done = false;

        while (!done) {

            size_t found = text.find(m_badWords[i], pos);

            if (found == string::npos) {
                done = true;
            } else {
                text.replace(found, m_badWords[i].length(), m_goodWords[i]);
                pos = found + m_goodWords[i].length();
                m_counts[i]++;
            }
        }
    }
}

void SpellChecker::showStatistics(ostream& out) const {

    out << "Spellchecker Statistics\n";

    for (size_t i = 0; i < 6; i++) {

        out << left << setw(15) << m_badWords[i];
        out << ": ";
        out << m_counts[i];
        out << " replacements\n";
    }
}

}
