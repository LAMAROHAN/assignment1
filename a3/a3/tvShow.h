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
        static inline void addEpisode(Collection_t& col, const std::string& str)
        {
            if (str.empty() || str[0] == '#')
                throw "Not a valid episode.";

            std::stringstream ss(str);
            std::string showID, numOverall, season, numInSeason, airDate, length, title, summary;

            std::getline(ss, showID, ',');
            std::getline(ss, numOverall, ',');
            std::getline(ss, season, ',');
            std::getline(ss, numInSeason, ',');
            std::getline(ss, airDate, ',');
            std::getline(ss, length, ',');
            std::getline(ss, title, ',');
            std::getline(ss, summary);

            MediaItem::trim(showID);
            MediaItem::trim(numOverall);
            MediaItem::trim(season);
            MediaItem::trim(numInSeason);
            MediaItem::trim(airDate);
            MediaItem::trim(length);
            MediaItem::trim(title);
            MediaItem::trim(summary);

            if (showID.empty() || numOverall.empty() || numInSeason.empty() || length.empty())
                return;

            TvEpisode ep{};
            ep.m_numberOverall = std::stoi(numOverall);
            ep.m_season = season.empty() ? 1 : std::stoi(season);
            ep.m_numberInSeason = std::stoi(numInSeason);
            ep.m_airDate = airDate;
            ep.m_length = std::stoi(length);
            ep.m_title = title;
            ep.m_summary = summary;

            for (size_t i = 0; i < col.size(); i++) {
                TvShow* show = dynamic_cast<TvShow*>(col[i]);

                if (show != nullptr) {
                    std::string id1 = show->m_id;
                    std::string id2 = showID;

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

        double getEpisodeAverageLength() const;
        std::list<std::string> getLongEpisodes() const;
    };

}

#endif
