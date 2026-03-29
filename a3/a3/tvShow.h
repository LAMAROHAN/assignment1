/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: 03-28-2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/
#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include <string>
#include <vector>
#include <list>
#include <sstream>
#include "mediaItem.h"

namespace seneca {

    struct TvEpisode {
        const class TvShow* m_show{};
        unsigned short m_numberOverall{};
        unsigned short m_season{};
        unsigned short m_numberInSeason{};
        std::string m_airDate{};
        unsigned int m_length{};
        std::string m_title{};
        std::string m_summary{};
    };

    class TvShow : public MediaItem {
        std::string m_id{};
        std::vector<TvEpisode> m_episodes{};

    public:
        TvShow(const std::string& id, const std::string& title,
               const std::string& summary, unsigned short year);

        static TvShow* createItem(const std::string& str);

        void display(std::ostream& out = std::cout) const override;

        template<typename Collection_t>
        static void addEpisode(Collection_t& col, const std::string& str)
        {
            if (str.empty() || str[0] == '#')
                throw "Not a valid episode.";

            std::stringstream ss(str);

            std::string showID, overall, season, inSeason, airDate, length, title, summary;

            getline(ss, showID, ',');
            getline(ss, overall, ',');
            getline(ss, season, ',');
            getline(ss, inSeason, ',');
            getline(ss, airDate, ',');
            getline(ss, length, ',');
            getline(ss, title, ',');
            getline(ss, summary);

            MediaItem::trim(showID);
            MediaItem::trim(overall);
            MediaItem::trim(season);
            MediaItem::trim(inSeason);
            MediaItem::trim(airDate);
            MediaItem::trim(length);
            MediaItem::trim(title);
            MediaItem::trim(summary);

            if (showID.empty() || overall.empty() || inSeason.empty() || length.empty())
                throw "Not a valid episode.";

            TvEpisode ep{};

            ep.m_numberOverall = (unsigned short)std::stoi(overall);
            ep.m_season = season.empty() ? 1 : (unsigned short)std::stoi(season);
            ep.m_numberInSeason = (unsigned short)std::stoi(inSeason);

            ep.m_airDate = airDate;

            int h = 0, m = 0, s = 0;
            char c;
            std::stringstream time(length);
            time >> h >> c >> m >> c >> s;
            ep.m_length = h * 3600 + m * 60 + s;

            ep.m_title = title;
            ep.m_summary = summary;

            for (size_t i = 0; i < col.size(); i++) {
                TvShow* show = dynamic_cast<TvShow*>(col[i]);
                if (show != nullptr && show->m_id == showID) {
                    ep.m_show = show;
                    show->m_episodes.push_back(ep);
                    break;
                }
            }
        }

        double getEpisodeAverageLength() const;
        std::list<std::string> getLongEpisodes() const;
    };

}

#endif
