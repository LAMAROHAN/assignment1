/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: 03-28-2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#ifndef SENECA_MEDIAITEM_H
#define SENECA_MEDIAITEM_H

#include <string>
#include <iostream>

namespace seneca {

    class MediaItem {
        std::string m_title;
        std::string m_summary;
        unsigned short m_year;

    protected:
        static void trim(std::string& str) {

            while (!str.empty() && str[0] == ' ')
                str.erase(0, 1);

            while (!str.empty() && str[str.length() - 1] == ' ')
                str.erase(str.length() - 1, 1);
        }

    public:
        MediaItem(const std::string& title,
            const std::string& summary,
            unsigned short year) {
            m_title = title;
            m_summary = summary;
            m_year = year;
        }

        virtual ~MediaItem() {}

        std::string getTitle() const {
            return m_title;
        }

        void setTitle(const std::string& title) {
            m_title = title;
        }

        std::string getSummary() const {
            return m_summary;
        }

        void setSummary(const std::string& summary) {
            m_summary = summary;
        }

        unsigned short getYear() const {
            return m_year;
        }

        virtual void display(std::ostream& out = std::cout) const = 0;

        template<typename Functor_t>
        void fixSpelling(Functor_t& spellChecker) {
            spellChecker(m_title);
            spellChecker(m_summary);
        }
    };

    inline std::ostream& operator<<(std::ostream& out, const MediaItem& item) {
        item.display(out);
        return out;
    }

}

#endif