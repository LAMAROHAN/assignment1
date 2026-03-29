/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: 03-28-2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/
#include "tvShow.h"
#include "settings.h"
#include <iomanip>
#include <sstream>

using namespace std;

namespace seneca {

    TvShow::TvShow(const string& id, const string& title,
        const string& summary, unsigned short year)
        : MediaItem(title, summary, year), m_id(id) {
    }

    TvShow* TvShow::createItem(const string& str) {
        if (str.empty() || str[0] == '#')
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

        return new TvShow(id, title, summary, (unsigned short)stoi(yearStr));
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
            else
                out << getSummary();

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

                out << "    S"
                    << right
                    << setw(2) << setfill('0') << m_episodes[i].m_season
                    << "E"
                    << setw(2) << setfill('0') << m_episodes[i].m_numberInSeason
                    << setfill(' ')
                    << left
                    << " " << m_episodes[i].m_title << '\n';

                size_t pos2 = 0;
                while (pos2 < m_episodes[i].m_summary.size()) {
                    out << "            "
                        << m_episodes[i].m_summary.substr(pos2, g_settings.m_maxSummaryWidth)
                        << '\n';
                    pos2 += g_settings.m_maxSummaryWidth;
                }
            }

            out << setw(getTitle().size() + 7) << setfill('-') << "" << setfill(' ') << '\n';
        }
    }

    double TvShow::getEpisodeAverageLength() const {
        if (m_episodes.empty()) return 0;

        double total = 0;
        for (size_t i = 0; i < m_episodes.size(); i++) {
            total += m_episodes[i].m_length;
        }

        return total / m_episodes.size();
    }

    std::list<std::string> TvShow::getLongEpisodes() const {
        std::list<std::string> result;

        for (size_t i = 0; i < m_episodes.size(); i++) {
            if (m_episodes[i].m_length >= 3600) {
                result.push_back(m_episodes[i].m_title);
            }
        }

        return result;
    }
}
