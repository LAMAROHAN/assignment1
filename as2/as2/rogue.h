/*
Student Name: Rohan Shyntan Tamang
Student ID: 173438235
Student e-mail: rshyntan-tamang@myseneca.ca
Course: OOP345NCC
Prof Name: Asam Gulaid
*/


#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include <iostream>
#include "characterTpl.h"
#include "weapons.h"

namespace seneca {

    template <class T, class FirstAbility_t, class SecondAbility_t>
    class Rogue : public CharacterTpl<T> {
        int m_def;
        int m_atk;
        FirstAbility_t m_a1;
        SecondAbility_t m_a2;
        seneca::Dagger m_dagger;

    public:
        Rogue(const char* name, int hpMax, int atk, int def)
            : CharacterTpl<T>(name, hpMax) {
            m_atk = atk;
            m_def = def;
        }

        int getAttackAmnt() const override {
            double blade = (double)m_dagger;
            return (int)(m_atk + (2.0 * blade));
        }

        int getDefenseAmnt() const override {
            return m_def;
        }

        Character* clone() const override {
            Rogue* copy = new Rogue(*this);
            return copy;
        }

        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";

            m_a1.useAbility(this);
            m_a2.useAbility(this);

            int dmg = getAttackAmnt();
            m_a1.transformDamageDealt(dmg);
            m_a2.transformDamageDealt(dmg);

            std::cout << "    Rogue deals " << dmg << " melee damage!\n";
            enemy->takeDamage(dmg);
        }

        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
            std::cout << "    Rogue has a defense of " << m_def
                << ". Reducing damage received.\n";

            int finalDmg = dmg - m_def;
            if (finalDmg < 0) finalDmg = 0;

            m_a1.transformDamageReceived(finalDmg);
            m_a2.transformDamageReceived(finalDmg);

            CharacterTpl<T>::takeDamage(finalDmg);
        }
    };

}

#endif
