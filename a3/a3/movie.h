/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: 03-28-2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include <string>
#include "mediaItem.h"

namespace seneca {

    class Movie : public MediaItem {

        Movie(const std::string& title,
            unsigned short year,
            const std::string& summary);

    public:
        void display(std::ostream& out = std::cout) const override;
        static Movie* createItem(const std::string& strMovie);
    };

}

#endif