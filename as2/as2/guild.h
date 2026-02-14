
/*
Student Name: Rohan Shyntan Tamang
Student ID: 173438235
Student e-mail: rshyntan-tamang@myseneca.ca
Course: OOP345NCC
Prof Name: Asam Gulaid
*/

#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <string>
#include <iostream>
#include "character.h"

namespace seneca {

    class Guild {
        std::string m_guildName;
        Character** m_list;
        size_t m_count;

        void reset();

    public:
        Guild();
        Guild(const char* name);

        ~Guild();

        Guild(const Guild& src);
        Guild& operator=(const Guild& src);

        Guild(Guild&& src) noexcept;
        Guild& operator=(Guild&& src) noexcept;

        void addMember(Character* c);
        void removeMember(const std::string& name);
        Character* operator[](size_t index) const;
        void showMembers() const;
    };

}

#endif
