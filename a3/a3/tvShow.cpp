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
    : MediaItem(title, summary, year) {
    m_id = id;
}

TvShow* TvShow::createItem(const string& str) {
    if (str.size() == 0 || str[0] == '#')
        throw "Not a valid show.";

    stringstream ss(str);

    string id;
    string title;
    string yearStr;
    string summary;

    getline(ss, id, ',');
    getline(ss, title, ',');
    getline(ss, yearStr, ',');
    getline(ss, summary);

    MediaItem::trim(id);
    MediaItem::trim(title);
    MediaItem::trim(yearStr);
    MediaItem::trim(summary);

    unsigned short year = (unsigned short)stoi(yearStr);

    TvShow* show = new TvShow(id, title, summary, year);
    return show;
}

void TvShow::display(ostream& out) const {
    if (g_settings.m_tableView) {

        out << "S | ";
        out << left;
        out << setfill('.');
        out << setw(50) << getTitle();
        out << " | ";

        out << right;
        out << setfill(' ');
        out << setw(2) << m_episodes.size();
        out << " | ";

        out << setw(4) << getYear();
        out << " | ";

        out << left;

        if (g_settings.m_maxSummaryWidth > -1) {
            if ((int)getSummary().size() <= g_settings.m_maxSummaryWidth) {
                out << getSummary();
            } else {
                out << getSummary().substr(0, g_settings.m_maxSummaryWidth - 3);
                out << "...";
            }
        } else {
            out << getSummary();
        }

        out << endl;
    }
    else {

        out << getTitle() << " [" << getYear() << "]\n";

        out << setw(getTitle().size() + 7);
        out << setfill('-');
        out << "";
        out << '\n';

        size_t pos = 0;

        while (pos < getSummary().size()) {
            out << "    ";
            out << getSummary().substr(pos, g_settings.m_maxSummaryWidth);
            out << '\n';
            pos = pos + g_settings.m_maxSummaryWidth;
        }

        for (size_t i = 0; i < m_episodes.size(); i++) {

            out << "    S";
            out << right;
            out << setw(2);
            out << setfill('0');
            out << m_episodes[i].m_season;

            out << "E";
            out << setw(2);
            out << m_episodes[i].m_numberInSeason;

            out << setfill(' ');
            out << left;

            if (m_episodes[i].m_title.size() > 0) {
                out << " " << m_episodes[i].m_title << '\n';
            } else {
                out << " Episode " << m_episodes[i].m_numberOverall << '\n';
            }

            size_t pos2 = 0;
            size_t width = g_settings.m_maxSummaryWidth - 8;

            while (pos2 < m_episodes[i].m_summary.size()) {
                out << "            ";
                out << m_episodes[i].m_summary.substr(pos2, width);
                out << '\n';
                pos2 = pos2 + width;
            }
        }

        out << setw(getTitle().size() + 7);
        out << setfill('-');
        out << "";
        out << setfill(' ');
        out << '\n';
    }
}

double TvShow::getEpisodeAverageLength() const {
    if (m_episodes.size() == 0)
        return 0;

    double total = 0;

    for (size_t i = 0; i < m_episodes.size(); i++) {
        total = total + m_episodes[i].m_length;
    }

    double avg = total / m_episodes.size();
    return avg;
}

list<string> TvShow::getLongEpisodes() const {
    list<string> result;

    for (size_t i = 0; i < m_episodes.size(); i++) {
        if (m_episodes[i].m_length >= 3600) {
            result.push_back(m_episodes[i].m_title);
        }
    }

    return result;
}

}
