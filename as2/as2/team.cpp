/*
Student Name: Rohan Shyntan Tamang
Student ID: 173438235
Student e-mail: rshyntan-tamang@myseneca.ca
Course: OOP345NCC
Prof Name: Asam Gulaid
*/

#include <iostream>
#include <utility>   
#include "team.h"

namespace seneca {

    void Team::clear() {
        
        for (size_t i = 0; i < m_count; i++) {
            delete m_list[i];
            m_list[i] = nullptr;
        }

        delete[] m_list;
        m_list = nullptr;
        m_count = 0;
    }

    Team::Team() {
        m_teamName = "";
        m_list = nullptr;
        m_count = 0;
    }

    Team::Team(const char* name) : Team() {
        if (name != nullptr) {
            m_teamName = name;
        }
    }

    Team::~Team() {
        clear();
    }

    
    Team::Team(const Team& src) : Team() {
        m_teamName = src.m_teamName;

        if (src.m_count > 0) {
            m_list = new Character * [src.m_count];
            m_count = src.m_count;

            for (size_t i = 0; i < m_count; i++) {
                m_list[i] = src.m_list[i]->clone();
            }
        }
    }

 
    Team& Team::operator=(const Team& src) {
        if (this != &src) {
            clear();
            m_teamName = src.m_teamName;

            if (src.m_count > 0) {
                m_list = new Character * [src.m_count];
                m_count = src.m_count;

                for (size_t i = 0; i < m_count; i++) {
                    m_list[i] = src.m_list[i]->clone();
                }
            }
        }
        return *this;
    }

    
    Team::Team(Team&& src) noexcept : Team() {
        m_teamName = std::move(src.m_teamName);
        m_list = src.m_list;
        m_count = src.m_count;

      
        src.m_list = nullptr;
        src.m_count = 0;
        src.m_teamName.clear();
    }

    
    Team& Team::operator=(Team&& src) noexcept {
        if (this != &src) {
            clear();

            m_teamName = std::move(src.m_teamName);
            m_list = src.m_list;
            m_count = src.m_count;

            src.m_list = nullptr;
            src.m_count = 0;
            src.m_teamName.clear();
        }
        return *this;
    }

    void Team::addMember(const Character* c) {
        if (c == nullptr) return;

       
        for (size_t i = 0; i < m_count; i++) {
            if (m_list[i]->getName() == c->getName()) {
                return;
            }
        }

      
        Character** bigger = new Character * [m_count + 1];


        for (size_t i = 0; i < m_count; i++) {
            bigger[i] = m_list[i];
        }

        bigger[m_count] = c->clone();

        delete[] m_list;
        m_list = bigger;
        m_count++;
    }

    void Team::removeMember(const std::string& name) {
        if (m_count == 0 || m_list == nullptr) return;

        size_t foundIndex = m_count;  

        for (size_t i = 0; i < m_count; i++) {
            if (m_list[i]->getName() == name) {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex == m_count) {
            return; 
        }

        
        delete m_list[foundIndex];
        m_list[foundIndex] = nullptr;

        
        for (size_t i = foundIndex; i < m_count - 1; i++) {
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

    Character* Team::operator[](size_t index) const {
        if (index >= m_count) {
            return nullptr;
        }
        return m_list[index];
    }

    void Team::showMembers() const {
        if (m_teamName.size() == 0) {
            std::cout << "No team.\n";
            return;
        }

        std::cout << "[Team] " << m_teamName << "\n";

        for (size_t i = 0; i < m_count; i++) {
            std::cout << "    " << (i + 1) << ": " << *m_list[i] << "\n";
        }
    }

}
