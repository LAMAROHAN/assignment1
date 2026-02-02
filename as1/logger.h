/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: Feb 1, 2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/


#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include <cstddef>
#include <iostream>
#include "event.h"

namespace seneca {

    class Logger {
        Event* m_events{ nullptr };   // dynamic array of Event
        std::size_t m_size{ 0 };      

        void clear();                 
    public:
        Logger() = default;
        ~Logger();

       
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        Logger(Logger&& other) noexcept;
        Logger& operator=(Logger&& other) noexcept;

        void addEvent(const Event& event);

        friend std::ostream& operator<<(std::ostream& os, const Logger& log);
    };

} 

#endif
