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

using namespace std;

namespace seneca {

Movie::Movie(const string& title,
    unsigned short year,
    const string& summary)
    : MediaItem(title, summary, year) {
}

void Movie::display(ostream& out) const {

    if (g_settings.m_tableView) {

        out << "M | ";

        out << left;
        out << setfill('.');
        out << setw(50) << getTitle();
        out << " | ";

        out << right;
        out << setfill(' ');
        out << setw(9) << getYear();
        out << " | ";

        out << left;

        string summary = getSummary();

        if (g_settings.m_maxSummaryWidth > -1) {

            if ((int)summary.size() <= g_settings.m_maxSummaryWidth) {
                out << summary;
            } else {
                out << summary.substr(0, g_settings.m_maxSummaryWidth - 3);
                out << "...";
            }
        } else {
            out << summary;
        }

        out << endl;
    }
    else {

        out << getTitle() << " [" << getYear() << "]\n";

        out << setw(getTitle().size() + 7);
        out << setfill('-');
        out << "";
        out << '\n';

        string summary = getSummary();
        size_t pos = 0;

        while (pos < summary.size()) {
            out << "    ";
            out << summary.substr(pos, g_settings.m_maxSummaryWidth);
            out << '\n';
            pos = pos + g_settings.m_maxSummaryWidth;
        }

        out << setw(getTitle().size() + 7);
        out << setfill('-');
        out << "";
        out << '\n';

        out << setfill(' ');
    }
}

Movie* Movie::createItem(const string& strMovie) {

    if (strMovie.size() == 0 || strMovie[0] == '#')
        throw "Not a valid movie.";

    stringstream ss(strMovie);

    string title;
    string yearStr;
    string summary;

    getline(ss, title, ',');
    getline(ss, yearStr, ',');
    getline(ss, summary);

    MediaItem::trim(title);
    MediaItem::trim(yearStr);
    MediaItem::trim(summary);

    unsigned short year = 0;

    try {
        year = (unsigned short)stoi(yearStr);
    }
    catch (...) {
        throw "Not a valid movie.";
    }

    Movie* m = new Movie(title, year, summary);
    return m;
}

}



  
