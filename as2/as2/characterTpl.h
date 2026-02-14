/*
Student Name: Rohan Shyntan Tamang
Student ID: 173438235
Student e-mail: rshyntan-tamang@myseneca.ca
Course: OOP345NCC
Prof Name: Asam Gulaid
*/


#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

#include <iostream>
#include "character.h"

namespace seneca {

    template <class T>
    class CharacterTpl : public Character {
        int m_maxHealth;
        T m_currentHealth;

    public:
        CharacterTpl(const char* name, int maxHealth)
            : Character(name) {

            m_maxHealth = maxHealth;
            m_currentHealth = maxHealth;
        }

        void takeDamage(int dmg) override {
            m_currentHealth = m_currentHealth - dmg;

            if ((int)m_currentHealth < 0) {
                m_currentHealth = 0;
            }

            if (!isAlive()) {
                std::cout << "    " << getName() << " has been defeated!\n";
            }
            else {
                std::cout << "    " << getName()
                    << " took " << dmg
                    << " damage, "
                    << getHealth()
                    << " health remaining.\n";
            }
        }

        int getHealth() const override {
            return (int)m_currentHealth;
        }

        int getHealthMax() const override {
            return m_maxHealth;
        }

        void setHealth(int value) override {
            m_currentHealth = value;
        }

        void setHealthMax(int value) override {
            m_maxHealth = value;
            m_currentHealth = value;
        }
    };

}

#endif
