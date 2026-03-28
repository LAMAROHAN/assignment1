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

        TvShow(const std::string& id,
               const std::string& title,
               const std::string& summary,
               unsigned short year)
            : MediaItem(title, summary, year) {
            m_id = id;
        }

        static TvShow* createItem(const std::string& str);

        void display(std::ostream& out) const override;

        template<typename Collection_t>
        static void addEpisode(Collection_t& col, const std::string& str)
        {
            if (str.size() == 0 || str[0] == '#')
                throw "Not a valid episode.";

            std::stringstream ss(str);

            std::string id, overall, season, number, airDate, length, title, summary;

            std::getline(ss, id, ',');
            std::getline(ss, overall, ',');
            std::getline(ss, season, ',');
            std::getline(ss, number, ',');
            std::getline(ss, airDate, ',');
            std::getline(ss, length, ',');
            std::getline(ss, title, ',');
            std::getline(ss, summary);

            MediaItem::trim(id);
            MediaItem::trim(overall);
            MediaItem::trim(season);
            MediaItem::trim(number);
            MediaItem::trim(airDate);
            MediaItem::trim(length);
            MediaItem::trim(title);
            MediaItem::trim(summary);

            TvEpisode ep;

            ep.m_numberOverall = std::stoi(overall);

            if (season.size() == 0)
                ep.m_season = 1;
            else
                ep.m_season = std::stoi(season);

            ep.m_numberInSeason = std::stoi(number);
            ep.m_airDate = airDate;
            ep.m_length = std::stoi(length);
            ep.m_title = title;
            ep.m_summary = summary;

            for (size_t i = 0; i < col.size(); i++) {

                TvShow* show = dynamic_cast<TvShow*>(col[i]);

                if (show != nullptr && show->m_id == id) {
                    ep.m_show = show;
                    show->m_episodes.push_back(ep);
                }
            }
        }

        double getEpisodeAverageLength() const {

            if (m_episodes.size() == 0)
                return 0;

            double total = 0;

            for (size_t i = 0; i < m_episodes.size(); i++) {
                total += m_episodes[i].m_length;
            }

            return total / m_episodes.size();
        }

        std::list<std::string> getLongEpisodes() const {

            std::list<std::string> result;

            for (size_t i = 0; i < m_episodes.size(); i++) {

                if (m_episodes[i].m_length >= 3600) {
                    result.push_back(m_episodes[i].m_title);
                }
            }

            return result;
        }
    };

}

#endif
