/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: Feb 1, 2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/


#include "dictionary.h"
#include "settings.h"

#include <fstream>
#include <iostream>
#include <cctype>

namespace seneca {

    namespace {

       
        std::string trim(const std::string& s) {
            std::size_t b = 0;
            while (b < s.size() && std::isspace(static_cast<unsigned char>(s[b]))) {
                ++b;
            }

            std::size_t e = s.size();
            while (e > b && std::isspace(static_cast<unsigned char>(s[e - 1]))) {
                --e;
            }

            return s.substr(b, e - b);
        }

     
        std::string readCsvFieldKeepQuotes(const std::string& line, std::size_t& i) {
            std::string field;
            bool quoted = false;

      
            if (i < line.size() && line[i] == '"') {
                quoted = true;
                field += '"';
                ++i;
            }

            while (i < line.size()) {
                char ch = line[i];

                if (quoted) {
                    if (ch == '"') {
                        
                        if (i + 1 < line.size() && line[i + 1] == '"') {
                            field += '"';
                            i += 2;
                            continue;
                        }

                        // Closing quote
                        field += '"';
                        ++i;

                        while (i < line.size() && line[i] != ',') {
                            ++i;
                        }
                        break;
                    }

                   
                    field += ch;
                    ++i;
                }
                else {
                   
                    if (ch == ',') break;

                    field += ch;
                    ++i;
                }
            }

            if (i < line.size() && line[i] == ',') {
                ++i;
            }

            return trim(field);
        }

      
        void splitCsv3KeepQuotes(const std::string& line, std::string& w, std::string& pos, std::string& def) {
            std::size_t i = 0;
            w = readCsvFieldKeepQuotes(line, i);
            pos = readCsvFieldKeepQuotes(line, i);
            def = readCsvFieldKeepQuotes(line, i);
        }

        PartOfSpeech parsePOS(const std::string& posRaw) {
            const std::string v = trim(posRaw);

            if (v == "n." || v == "n. pl.") return PartOfSpeech::Noun;
            if (v == "adv.")               return PartOfSpeech::Adverb;
            if (v == "a.")                 return PartOfSpeech::Adjective;
            if (v == "v." || v == "v. i." || v == "v. t." || v == "v. t. & i.") return PartOfSpeech::Verb;
            if (v == "prep.")              return PartOfSpeech::Preposition;
            if (v == "pron.")              return PartOfSpeech::Pronoun;
            if (v == "conj.")              return PartOfSpeech::Conjunction;
            if (v == "interj.")            return PartOfSpeech::Interjection;

            return PartOfSpeech::Unknown;
        }

        const char* posLabel(PartOfSpeech p) {
            switch (p) {
            case PartOfSpeech::Noun:         return "noun";
            case PartOfSpeech::Pronoun:      return "pronoun";
            case PartOfSpeech::Adjective:    return "adjective";
            case PartOfSpeech::Adverb:       return "adverb";
            case PartOfSpeech::Verb:         return "verb";
            case PartOfSpeech::Preposition:  return "preposition";
            case PartOfSpeech::Conjunction:  return "conjunction";
            case PartOfSpeech::Interjection: return "interjection";
            default:                         return nullptr;
            }
        }

    } 


    void Dictionary::setEmpty() {
        delete[] m_words;
        m_words = nullptr;
        m_size = 0;
    }

    Dictionary::~Dictionary() {
        setEmpty();
    }

    Dictionary::Dictionary(const char* filename) {
        setEmpty(); // start in a clean state

        if (!filename) return;

        std::ifstream fin(filename);
        if (!fin) return;

        
        std::size_t count = 0;
        std::string line;
        while (std::getline(fin, line)) {
            if (!line.empty()) ++count;
        }

        if (count == 0) return;

        
        m_words = new Word[count];
        m_size = count;

        // Load the records
        fin.clear();
        fin.seekg(0);

        std::size_t idx = 0;
        while (idx < count && std::getline(fin, line)) {
            if (line.empty()) continue;

            std::string w, pos, def;
            splitCsv3KeepQuotes(line, w, pos, def);

            m_words[idx].m_word = w;
            m_words[idx].m_pos = parsePOS(pos);
            m_words[idx].m_definition = def;
            ++idx;
        }

        
        if (idx != count) {
            Word* exact = (idx > 0) ? new Word[idx] : nullptr;
            for (std::size_t i = 0; i < idx; ++i) {
                exact[i] = m_words[i];
            }
            delete[] m_words;
            m_words = exact;
        }
        m_size = idx;
    }

    Dictionary::Dictionary(const Dictionary& other) {
        setEmpty();

        if (other.m_size == 0 || other.m_words == nullptr) return;

        m_words = new Word[other.m_size];
        m_size = other.m_size;

        for (std::size_t i = 0; i < m_size; ++i) {
            m_words[i] = other.m_words[i];
        }
    }

    Dictionary& Dictionary::operator=(const Dictionary& other) {
        if (this != &other) {
            Word* temp = nullptr;

            if (other.m_size > 0 && other.m_words != nullptr) {
                temp = new Word[other.m_size];
                for (std::size_t i = 0; i < other.m_size; ++i) {
                    temp[i] = other.m_words[i];
                }
            }

            delete[] m_words;
            m_words = temp;
            m_size = other.m_size;
        }
        return *this;
    }

    Dictionary::Dictionary(Dictionary&& other) noexcept {
        setEmpty();
        *this = std::move(other);
    }

    Dictionary& Dictionary::operator=(Dictionary&& other) noexcept {
        if (this != &other) {
            delete[] m_words;

            m_words = other.m_words;
            m_size = other.m_size;

            other.m_words = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    void Dictionary::searchWord(const char* word) const {
       
        if (!word || !*word || m_words == nullptr || m_size == 0) {
            std::cout << "Word '" << (word ? word : "") << "' was not found in the dictionary.\n";
            return;
        }

        const std::string target(word);
        const std::string indent(target.size(), ' ');

        bool found = false;

        for (std::size_t i = 0; i < m_size; ++i) {
            if (m_words[i].m_word == target) {
              
                if (!found) std::cout << target;
                else        std::cout << indent;

                std::cout << " - ";

               
                const char* label = posLabel(m_words[i].m_pos);
                if (g_settings.m_verbose && label != nullptr) {
                    std::cout << "(" << label << ") ";
                }

                std::cout << m_words[i].m_definition << '\n';

                found = true;

              
                if (!g_settings.m_show_all) break;
            }
        }

        if (!found) {
            std::cout << "Word '" << target << "' was not found in the dictionary.\n";
        }
    }

} 

