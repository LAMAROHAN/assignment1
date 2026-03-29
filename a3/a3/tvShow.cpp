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
            } else {
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

            out << setw(getTitle().size() + 7) << setfill('-') << "" << setfill(' ') << '\n';
        }
    }

    template<typename Collection_t>
    void TvShow::addEpisode(Collection_t& col, const string& str) {
        if (str.empty() || str[0] == '#')
            throw "Not a valid episode.";

        stringstream ss(str);
        string showID, numOverall, season, numInSeason, airDate, length, title, summary;

        getline(ss, showID, ',');
        getline(ss, numOverall, ',');
        getline(ss, season, ',');
        getline(ss, numInSeason, ',');
        getline(ss, airDate, ',');
        getline(ss, length, ',');
        getline(ss, title, ',');
        getline(ss, summary);

        MediaItem::trim(showID);
        MediaItem::trim(numOverall);
        MediaItem::trim(season);
        MediaItem::trim(numInSeason);
        MediaItem::trim(airDate);
        MediaItem::trim(length);
        MediaItem::trim(title);
        MediaItem::trim(summary);

        if (showID.empty() || numOverall.empty() || numInSeason.empty() || length.empty())
            throw "Not a valid episode.";

        TvEpisode ep{};
        ep.m_numberOverall = stoi(numOverall);
        ep.m_season = season.empty() ? 1 : stoi(season);
        ep.m_numberInSeason = stoi(numInSeason);
        ep.m_airDate = airDate;
        ep.m_length = stoi(length);
        ep.m_title = title;
        ep.m_summary = summary;

        for (size_t i = 0; i < col.size(); i++) {
            TvShow* show = dynamic_cast<TvShow*>(col[i]);

            if (show != nullptr) {
                string id1 = show->m_id;
                string id2 = showID;

                MediaItem::trim(id1);
                MediaItem::trim(id2);

                if (id1 == id2) {
                    ep.m_show = show;
                    show->m_episodes.push_back(ep);
                    break;
                }
            }
        }
    }

    double TvShow::getEpisodeAverageLength() const {
        if (m_episodes.empty())
            return 0;

        double total = 0;

        for (size_t i = 0; i < m_episodes.size(); i++)
            total += m_episodes[i].m_length;

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

}
