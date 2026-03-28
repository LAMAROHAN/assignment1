/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: 03-28-2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

namespace seneca {

    struct Settings {
        short m_maxSummaryWidth;
        bool m_tableView;

        Settings() {
            m_maxSummaryWidth = 80;
            m_tableView = false;
        }
    };

    extern Settings g_settings;

}

#endif