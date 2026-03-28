/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: 03-28-2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/
#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include "mediaItem.h"
#include <string>
#include <vector>
#include <list>

namespace seneca {

    class Collection;

    class TvShow : public MediaItem {

        struct Episode {
            std::string m_showID{};
            std::string m_title{};
            unsigned short m_season{};
            unsigned short m_numberInSeason{};
            std::string m_airDate{};
            unsigned short m_length{};
            std::string m_summary{};
        };

        std::string m_id{};
        std::vector<Episode> m_episodes;

    public:
        TvShow(const std::string& id, const std::string& title,
               const std::string& summary, unsigned short year);

        static TvShow* createItem(const std::string& str);

        static void addEpisode(Collection& col, const std::string& str);

        double getEpisodeAverageLength() const;

        std::list<std::string> getLongEpisodes() const;

        void display(std::ostream& out) const override;
    };

}

#endif
