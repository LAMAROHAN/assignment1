/*
Student Name: Rohan Shyntan Tamang
Student ID: 173438235
Student e-mail: rshyntan-tamang@myseneca.ca
Course: OOP345NCC
Prof Name: Asam Gulaid
*/

#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <string>
#include "character.h"

namespace seneca {

    class Team {
        std::string m_teamName;
        Character** m_list;   
        size_t m_count;       

        void clear();           

    public:
        Team();
        Team(const char* name);

        ~Team();

        Team(const Team& src);
        Team& operator=(const Team& src);

        Team(Team&& src) noexcept;
        Team& operator=(Team&& src) noexcept;

        void addMember(const Character* c);
        void removeMember(const std::string& name);
        Character* operator[](size_t index) const;
        void showMembers() const;
    };

}

#endif
