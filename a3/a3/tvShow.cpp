/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: 03-28-2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#include "tvShow.h"
#include "settings.h"
#include <sstream>
#include <iomanip>

namespace seneca {

    TvShow* TvShow::createItem(const std::string& str) {

        if (str.size() == 0 || str[0] == '#')
            throw "Not a valid show.";

        std::stringstream ss(str);

        std::string id;
        std::string title;
        std::string yearStr;
        std::string summary;

        std::getline(ss, id, ',');
        std::getline(ss, title, ',');
        std::getline(ss, yearStr, ',');
        std::getline(ss, summary);

        MediaItem::trim(id);
        MediaItem::trim(title);
        MediaItem::trim(yearStr);
        MediaItem::trim(summary);

        unsigned short year = (unsigned short)std::stoi(yearStr);

        return new TvShow(id, title, summary, year);
    }

    void TvShow::display(std::ostream& out) const {

        if (g_settings.m_tableView) {

            out << "S | ";

            out << std::left << std::setfill('.');
            out << std::setw(50) << getTitle() << " | ";

            out << std::right << std::setfill(' ');
            out << std::setw(2) << m_episodes.size() << " | ";
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

            out << getTitle() << " [" << getYear() << "]\n";

            out << std::setw(getTitle().length() + 7) << std::setfill('-') << "" << '\n';

            std::string summary = getSummary();
            size_t pos = 0;

            while (pos < summary.length()) {
                out << "    " << summary.substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }

            for (size_t i = 0; i < m_episodes.size(); i++) {

                out << std::right << std::setfill('0');

                out << "    S"
                    << std::setw(2) << m_episodes[i].m_season
                    << "E"
                    << std::setw(2) << m_episodes[i].m_numberInSeason;

                out << std::setfill(' ');

                // ✅ FIXED (NO EXTRA QUOTES)
                out << " " << m_episodes[i].m_title << "\n";

                size_t pos2 = 0;

                while (pos2 < m_episodes[i].m_summary.length()) {
                    out << "            "
                        << m_episodes[i].m_summary.substr(pos2, g_settings.m_maxSummaryWidth - 8)
                        << '\n';

                    pos2 += g_settings.m_maxSummaryWidth - 8;
                }
            }

            out << std::setw(getTitle().length() + 7) << std::setfill('-') << "" << '\n';
            out << std::setfill(' ');
        }
    }

}
