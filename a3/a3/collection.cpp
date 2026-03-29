
/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: 03-28-2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/
#include "collection.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

namespace seneca {

Collection::Collection(const string& name) {
    m_name = name;
    m_observer = nullptr;
}

Collection::~Collection() {
    for (size_t i = 0; i < m_items.size(); i++) {
        delete m_items[i];
    }
}

const string& Collection::name() const {
    return m_name;
}

size_t Collection::size() const {
    return m_items.size();
}

void Collection::setObserver(void (*observer)(const Collection&, const MediaItem&)) {
    m_observer = observer;
}

Collection& Collection::operator+=(MediaItem* item) {

    if (item == nullptr) {
        return *this;
    }

    bool exists = false;

    for (size_t i = 0; i < m_items.size(); i++) {
        if (m_items[i] != nullptr) {
            if (m_items[i]->getTitle() == item->getTitle()) {
                exists = true;
            }
        }
    }

    if (!exists) {
        m_items.push_back(item);

        if (m_observer != nullptr) {
            m_observer(*this, *item);
        }
    }
    else {
        delete item;
    }

    return *this;
}

MediaItem* Collection::operator[](size_t idx) const {

    if (idx >= m_items.size()) {
        throw out_of_range(
            "Bad index [" + to_string(idx) + "]. Collection has [" + to_string(m_items.size()) + "] items."
        );
    }

    return m_items[idx];
}

MediaItem* Collection::operator[](const string& title) const {

    for (size_t i = 0; i < m_items.size(); i++) {
        if (m_items[i]->getTitle() == title) {
            return m_items[i];
        }
    }

    return nullptr;
}

string dequote(const string& str) {

    string res = str;

    if (res.size() > 0 && res[0] == '"') {
        res.erase(0, 1);
    }

    if (res.size() > 0 && res[res.size() - 1] == '"') {
        res.erase(res.size() - 1, 1);
    }

    return res;
}

void Collection::removeQuotes() {

    for (size_t i = 0; i < m_items.size(); i++) {

        string title = m_items[i]->getTitle();
        string summary = m_items[i]->getSummary();

        m_items[i]->setTitle(dequote(title));
        m_items[i]->setSummary(dequote(summary));
    }
}

void Collection::sort(const string& field) {

    if (field == "title") {

        for (size_t i = 0; i < m_items.size(); i++) {
            for (size_t j = i + 1; j < m_items.size(); j++) {

                if (m_items[j]->getTitle() < m_items[i]->getTitle()) {
                    MediaItem* temp = m_items[i];
                    m_items[i] = m_items[j];
                    m_items[j] = temp;
                }
            }
        }

    }
    else if (field == "year") {

        for (size_t i = 0; i < m_items.size(); i++) {
            for (size_t j = i + 1; j < m_items.size(); j++) {

                if (m_items[j]->getYear() < m_items[i]->getYear()) {
                    MediaItem* temp = m_items[i];
                    m_items[i] = m_items[j];
                    m_items[j] = temp;
                }
            }
        }

    }
}

ostream& operator<<(ostream& out, const Collection& col) {

    for (size_t i = 0; i < col.size(); i++) {
        out << *col[i];
    }

    return out;
}

}
