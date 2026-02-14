/*
Student Name: Rohan Shyntan Tamang
Student ID: 173438235
Student e-mail: rshyntan-tamang@myseneca.ca
Course: OOP345NCC
Prof Name: Asam Gulaid
*/

#include <iostream>
#include <utility>
#include "guild.h"

namespace seneca {

    void Guild::reset() {
        delete[] m_list;
        m_list = nullptr;
        m_count = 0;
    }

    Guild::Guild() {
        m_guildName = "";
        m_list = nullptr;
        m_count = 0;
    }

    Guild::Guild(const char* name) : Guild() {
        if (name != nullptr) {
            m_guildName = name;
        }
    }

    Guild::~Guild() {
        reset();
    }

    Guild::Guild(const Guild& src) : Guild() {
        m_guildName = src.m_guildName;

        if (src.m_count > 0) {
            m_list = new Character * [src.m_count];
            m_count = src.m_count;

            for (size_t i = 0; i < m_count; i++) {
                m_list[i] = src.m_list[i];
            }
        }
    }

    Guild& Guild::operator=(const Guild& src) {
        if (this != &src) {
            reset();
            m_guildName = src.m_guildName;

            if (src.m_count > 0) {
                m_list = new Character * [src.m_count];
                m_count = src.m_count;

                for (size_t i = 0; i < m_count; i++) {
                    m_list[i] = src.m_list[i];
                }
            }
        }
        return *this;
    }

    Guild::Guild(Guild&& src) noexcept : Guild() {
        m_guildName = std::move(src.m_guildName);
        m_list = src.m_list;
        m_count = src.m_count;

        src.m_list = nullptr;
        src.m_count = 0;
        src.m_guildName.clear();
    }

    Guild& Guild::operator=(Guild&& src) noexcept {
        if (this != &src) {
            reset();

            m_guildName = std::move(src.m_guildName);
            m_list = src.m_list;
            m_count = src.m_count;

            src.m_list = nullptr;
            src.m_count = 0;
            src.m_guildName.clear();
        }
        return *this;
    }

    void Guild::addMember(Character* c) {
        if (c == nullptr) return;

        for (size_t i = 0; i < m_count; i++) {
            if (m_list[i] == c) {
                return;
            }
        }

        Character** bigger = new Character * [m_count + 1];

        for (size_t i = 0; i < m_count; i++) {
            bigger[i] = m_list[i];
        }

        bigger[m_count] = c;

        delete[] m_list;
        m_list = bigger;
        m_count++;

        c->setHealthMax(c->getHealthMax() + 300);
    }

    void Guild::removeMember(const std::string& name) {
        if (m_list == nullptr || m_count == 0) return;

        size_t pos = m_count;
        for (size_t i = 0; i < m_count; i++) {
            if (m_list[i] != nullptr && m_list[i]->getName() == name) {
                pos = i;
                break;
            }
        }

        if (pos == m_count) return;

        m_list[pos]->setHealthMax(m_list[pos]->getHealthMax() - 300);

        for (size_t i = pos; i < m_count - 1; i++) {
            m_list[i] = m_list[i + 1];
        }

        m_count--;

        if (m_count == 0) {
            delete[] m_list;
            m_list = nullptr;
            return;
        }

        Character** smaller = new Character * [m_count];
        for (size_t i = 0; i < m_count; i++) {
            smaller[i] = m_list[i];
        }

        delete[] m_list;
        m_list = smaller;
    }

    Character* Guild::operator[](size_t index) const {
        if (index >= m_count) return nullptr;
        return m_list[index];
    }

    void Guild::showMembers() const {
        if (m_guildName.empty()) {
            std::cout << "No guild.\n";
            return;
        }

        std::cout << "[Guild] " << m_guildName << "\n";
        for (size_t i = 0; i < m_count; i++) {
            std::cout << "    " << (i + 1) << ": " << *m_list[i] << "\n";
        }
    }

}
