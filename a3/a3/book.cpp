/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: 03-28-2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#include "book.h"
#include "settings.h"
#include <iomanip>
#include <sstream>

namespace seneca {

    Book::Book(const std::string& author, const std::string& title,
        const std::string& country, double price,
        unsigned short year, const std::string& summary)
        : MediaItem(title, summary, year) {
        m_author = author;
        m_country = country;
        m_price = price;
    }

    void Book::display(std::ostream& out) const {

        if (g_settings.m_tableView) {

            out << "B | ";

            out << std::left << std::setfill('.');
            out << std::setw(50) << getTitle() << " | ";

            out << std::right << std::setfill(' ');
            out << std::setw(2) << m_country << " | ";
            out << std::setw(4) << getYear() << " | ";

            out << std::left;

            std::string summary = getSummary();

            if (g_settings.m_maxSummaryWidth > -1) {
                if (summary.length() <= (size_t)g_settings.m_maxSummaryWidth)
                    out << summary;
                else
                    out << summary.substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else {
                out << summary;
            }

            out << std::endl;
        }
        else {

            out << getTitle() << " [" << getYear() << "] ["
                << m_author << "] [" << m_country << "] [" << m_price << "]\n";

            out << std::setw(getTitle().length() + 7) << std::setfill('-') << "" << '\n';

            size_t pos = 0;
            std::string summary = getSummary();

            while (pos < summary.length()) {
                out << "    " << summary.substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }

            out << std::setw(getTitle().length() + 7) << std::setfill('-') << "" << '\n';
            out << std::setfill(' ');
        }
    }

    Book* Book::createItem(const std::string& strBook) {

        if (strBook.size() == 0 || strBook[0] == '#')
            throw "Not a valid book.";

        std::stringstream ss(strBook);

        std::string author, title, country;
        std::string priceStr, yearStr, summary;

        std::getline(ss, author, ',');
        std::getline(ss, title, ',');
        std::getline(ss, country, ',');
        std::getline(ss, priceStr, ',');
        std::getline(ss, yearStr, ',');
        std::getline(ss, summary);

        MediaItem::trim(author);
        MediaItem::trim(title);
        MediaItem::trim(country);
        MediaItem::trim(priceStr);
        MediaItem::trim(yearStr);
        MediaItem::trim(summary);

        double price;
        unsigned short year;

        try {
            price = std::stod(priceStr);
            year = (unsigned short)std::stoi(yearStr);
        }
        catch (...) {
            throw "Not a valid book.";
        }

        return new Book(author, title, country, price, year, summary);
    }

}