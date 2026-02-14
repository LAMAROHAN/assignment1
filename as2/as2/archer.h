/*
Student Name: Rohan Shyntan Tamang
Student ID: 173438235
Student e-mail: rshyntan-tamang@myseneca.ca
Course: OOP345NCC
Prof Name: Asam Gulaid
*/

#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include <iostream>
#include "characterTpl.h"
#include "health.h"

namespace seneca {

    template <class Weapon_t>
    class Archer : public CharacterTpl<seneca::SuperHealth> {
        int m_def;
        int m_atk;
        Weapon_t m_bow;

    public:
        Archer(const char* name, int hpMax, int atk, int def, Weapon_t weapon)
            : CharacterTpl<seneca::SuperHealth>(name, hpMax) {
            m_atk = atk;
            m_def = def;
            m_bow = weapon;
        }

        int getAttackAmnt() const override {
            return (int)(m_atk * 1.3);
        }

        int getDefenseAmnt() const override {
            return (int)(m_def * 1.2);
        }

        Character* clone() const override {
            Archer* copy = new Archer(*this);
            return copy;
        }

        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";

            int dmg = getAttackAmnt();
            std::cout << "    Archer deals " << dmg << " ranged damage!\n";

            enemy->takeDamage(dmg);
        }

        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
            std::cout << "    Archer has a defense of " << getDefenseAmnt()
                << ". Reducing damage received.\n";

            int finalDmg = dmg - getDefenseAmnt();
            if (finalDmg < 0) finalDmg = 0;

            CharacterTpl<seneca::SuperHealth>::takeDamage(finalDmg);
        }
    };

}

#endif
