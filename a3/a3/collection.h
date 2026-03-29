/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: 03-28-2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <string>
#include <vector>
#include <iostream>
#include "mediaItem.h"

namespace seneca {

class Collection {

    std::string m_name;
    std::vector<MediaItem*> m_items;
    void (*m_observer)(const Collection&, const MediaItem&);

public:

    Collection(const std::string& name);

    Collection(const Collection&) = delete;
    Collection& operator=(const Collection&) = delete;

    ~Collection();

    const std::string& name() const;

    size_t size() const;

    void setObserver(void (*observer)(const Collection&, const MediaItem&));

    Collection& operator+=(MediaItem* item);

    MediaItem* operator[](size_t idx) const;

    MediaItem* operator[](const std::string& title) const;

    void removeQuotes();

    void sort(const std::string& field);
};

std::ostream& operator<<(std::ostream& out, const Collection& col);

}

#endif
