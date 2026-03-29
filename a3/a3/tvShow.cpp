/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: 03-28-2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/
#include "tvShow.h"
#include "collection.h"
#include "settings.h"
#include <sstream>
#include <iomanip>

using namespace std;

namespace seneca {

    TvShow::TvShow(const string& id, const string& title,
                   const string& summary, unsigned short year)
        : MediaItem(title, summary, year) {
        m_id = id;
    }

    TvShow* TvShow::createItem(const string& str) {

        if (str.empty() || str[0] == '#')
            throw "Not a valid show.";

        stringstream ss(str);

        string id, title, year, summary;

        getline(ss, id, ',');
        getline(ss, title, ',');
        getline(ss, year, ',');
        getline(ss, summary);

        MediaItem::trim(id);
        MediaItem::trim(title);
        MediaItem::trim(year);
        MediaItem::trim(summary);

        return new TvShow(id, title, summary, stoi(year));
    }

    void TvShow::addEpisode(Collection& col, const string& str) {

        if (str.empty() || str[0] == '#')
            throw "Not a valid episode.";

        try {

            stringstream ss(str);

            string showID, overall, season, number, airDate, length, title, summary;

            getline(ss, showID, ',');
            getline(ss, overall, ',');
            getline(ss, season, ',');
            getline(ss, number, ',');
            getline(ss, airDate, ',');
            getline(ss, length, ',');
            getline(ss, title, ',');
            getline(ss, summary);

            MediaItem::trim(showID);
            MediaItem::trim(overall);
            MediaItem::trim(season);
            MediaItem::trim(number);
            MediaItem::trim(airDate);
            MediaItem::trim(length);
            MediaItem::trim(title);
            MediaItem::trim(summary);

            if (!showID.empty() && showID.front() == '"')
                showID.erase(0, 1);
            if (!showID.empty() && showID.back() == '"')
                showID.pop_back();

            if (showID.empty() || overall.empty() || number.empty() || length.empty())
                throw "Not a valid episode.";

            Episode ep;

            ep.m_season = season.empty() ? 1 : stoi(season);
            ep.m_numberInSeason = stoi(number);
            ep.m_airDate = airDate;
            ep.m_length = stoi(length);
            ep.m_title = title;
            ep.m_summary = summary;

            bool added = false;

            for (size_t i = 0; i < col.size(); i++) {

                TvShow* show = dynamic_cast<TvShow*>(col[i]);

                if (show != nullptr && show->m_id == showID) {
                    show->m_episodes.push_back(ep);
                    added = true;
                    break;
                }
            }

            if (!added)
                throw "Not a valid episode.";

        } catch (...) {
            throw "Not a valid episode.";
        }
    }

    double TvShow::getEpisodeAverageLength() const {

        if (m_episodes.empty())
            return 0;

        double total = 0;

        for (size_t i = 0; i < m_episodes.size(); i++) {
            total += m_episodes[i].m_length;
        }

        return total / m_episodes.size();
    }

    list<string> TvShow::getLongEpisodes() const {

        list<string> result;

        for (size_t i = 0; i < m_episodes.size(); i++) {
            if (m_episodes[i].m_length >= 3600)
                result.push_back(m_episodes[i].m_title);
        }

        return result;
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

                if (m_episodes[i].m_season < 10) out << "0";
                out << m_episodes[i].m_season;

                out << "E";

                if (m_episodes[i].m_numberInSeason < 10) out << "0";
                out << m_episodes[i].m_numberInSeason;

                out << " " << m_episodes[i].m_title << '\n';

                size_t p = 0;

                while (p < m_episodes[i].m_summary.size()) {
                    out << "            "
                        << m_episodes[i].m_summary.substr(p, g_settings.m_maxSummaryWidth - 8)
                        << '\n';
                    p += g_settings.m_maxSummaryWidth - 8;
                }
            }

            out << setw(getTitle().size() + 7) << setfill('-') << "" << setfill(' ') << '\n';
        }
    }

}
