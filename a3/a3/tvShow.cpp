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

using namespace std;

namespace seneca {

    TvShow* TvShow::createItem(const string& str) {

        if (str.size() == 0 || str[0] == '#')
            throw "Not a valid show.";

        stringstream ss(str);

        string id, title, yearStr, summary;

        getline(ss, id, ',');
        getline(ss, title, ',');
        getline(ss, yearStr, ',');
        getline(ss, summary);

        MediaItem::trim(id);
        MediaItem::trim(title);
        MediaItem::trim(yearStr);
        MediaItem::trim(summary);

        return new TvShow(id, title, summary, stoi(yearStr));
    }

    void TvShow::display(ostream& out) const {

        if (g_settings.m_tableView) {

            out << "S | ";
            out << left << setfill('.');
            out << setw(50) << getTitle() << " | ";
            out << right << setfill(' ');
            out << setw(2) << m_episodes.size() << " | ";
            out << setw(4) << getYear() << " | ";
            out << left;

            if (g_settings.m_maxSummaryWidth > -1) {

                if ((short)getSummary().size() <= g_settings.m_maxSummaryWidth)
                    out << getSummary();
                else
                    out << getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else {
                out << getSummary();
            }

            out << endl;
        }
        else {

            size_t pos = 0;

            out << getTitle() << " [" << getYear() << "]\n";

            out << setw(getTitle().size() + 7) << setfill('-') << "" << '\n';

            while (pos < getSummary().size()) {
                out << "    " << getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }

            for (size_t i = 0; i < m_episodes.size(); i++) {

                out << "    S";

                if (m_episodes[i].m_season < 10)
                    out << "0";

                out << m_episodes[i].m_season;

                out << "E";

                if (m_episodes[i].m_numberInSeason < 10)
                    out << "0";

                out << m_episodes[i].m_numberInSeason;

                out << " " << m_episodes[i].m_title << '\n';
            }

            out << setw(getTitle().size() + 7) << setfill('-') << "" << setfill(' ') << '\n';
        }
    }

}
