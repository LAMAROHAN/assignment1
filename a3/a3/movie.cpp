/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: 03-28-2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#include "movie.h"
#include "settings.h"
#include <iomanip>
#include <sstream>

namespace seneca {

    Movie::Movie(const std::string& title,
        unsigned short year,
        const std::string& summary)
        : MediaItem(title, summary, year) {
    }

    void Movie::display(std::ostream& out) const {

        if (g_settings.m_tableView) {

            out << "M | ";

            out << std::left << std::setfill('.');
            out << std::setw(50) << getTitle() << " | ";

            out << std::right << std::setfill(' ');
            out << std::setw(9) << getYear() << " | ";

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

            out << getTitle() << " [" << getYear() << "]\n";

            out << std::setw(getTitle().length() + 7) << std::setfill('-') << "" << '\n';

            std::string summary = getSummary();
            size_t pos = 0;

            while (pos < summary.length()) {
                out << "    " << summary.substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }

            out << std::setw(getTitle().length() + 7) << std::setfill('-') << "" << '\n';
            out << std::setfill(' ');
        }
    }

    Movie* Movie::createItem(const std::string& strMovie) {

        if (strMovie.size() == 0 || strMovie[0] == '#')
            throw "Not a valid movie.";

        std::stringstream ss(strMovie);

        std::string title;
        std::string yearStr;
        std::string summary;

        std::getline(ss, title, ',');
        std::getline(ss, yearStr, ',');
        std::getline(ss, summary);

        MediaItem::trim(title);
        MediaItem::trim(yearStr);
        MediaItem::trim(summary);

        unsigned short year;

        try {
            year = (unsigned short)std::stoi(yearStr);
        }
        catch (...) {
            throw "Not a valid movie.";
        }

        return new Movie(title, year, summary);
    }

}