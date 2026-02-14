/*
Student Name: Rohan Shyntan Tamang
Student ID: 173438235
Student e-mail: rshyntan-tamang@myseneca.ca
Course: OOP345NCC
Prof Name: Asam Gulaid
*/


#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include <iostream>
#include "characterTpl.h"

namespace seneca {

    template <class T, class Ability_t, class Weapon_t>
    class Barbarian : public CharacterTpl<T> {
        int m_def;
        int m_atk;
        Ability_t m_skill;
        Weapon_t m_wep1;
        Weapon_t m_wep2;

    public:
        Barbarian(const char* name, int hpMax, int atk, int def,
            Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
            : CharacterTpl<T>(name, hpMax) {
            m_atk = atk;
            m_def = def;
            m_wep1 = primaryWeapon;
            m_wep2 = secondaryWeapon;
        }

        int getAttackAmnt() const override {
            double part1 = (double)m_wep1 / 2.0;
            double part2 = (double)m_wep2 / 2.0;
            return (int)(m_atk + part1 + part2);
        }

        int getDefenseAmnt() const override {
            return m_def;
        }

        Character* clone() const override {
            Barbarian* copy = new Barbarian(*this);
            return copy;
        }

        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";

            m_skill.useAbility(this);

            int dmg = getAttackAmnt();
            m_skill.transformDamageDealt(dmg);

            std::cout << "    Barbarian deals " << dmg << " melee damage!\n";
            enemy->takeDamage(dmg);
        }

        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
            std::cout << "    Barbarian has a defense of " << m_def
                << ". Reducing damage received.\n";

            int finalDmg = dmg - m_def;
            if (finalDmg < 0) finalDmg = 0;

            m_skill.transformDamageReceived(finalDmg);

            CharacterTpl<T>::takeDamage(finalDmg);
        }
    };

}

#endif
