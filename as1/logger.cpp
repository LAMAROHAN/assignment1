/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: Feb 1, 2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/


#include "logger.h"

namespace seneca {

    void Logger::clear() {
        delete[] m_events;
        m_events = nullptr;
        m_size = 0;
    }

    Logger::~Logger() {
        clear();
    }

    Logger::Logger(Logger&& other) noexcept
        : m_events(other.m_events), m_size(other.m_size) {
      
        other.m_events = nullptr;
        other.m_size = 0;
    }

    Logger& Logger::operator=(Logger&& other) noexcept {
        if (this != &other) {
            clear();

            m_events = other.m_events;
            m_size = other.m_size;

            other.m_events = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    void Logger::addEvent(const Event& event) {
      
        Event* bigger = new Event[m_size + 1];

        
        for (std::size_t i = 0; i < m_size; ++i) {
            bigger[i] = m_events[i];
        }

        bigger[m_size] = event;

        
        delete[] m_events;
        m_events = bigger;
        ++m_size;
    }

    std::ostream& operator<<(std::ostream& os, const Logger& log) {
        for (std::size_t i = 0; i < log.m_size; ++i) {
            os << log.m_events[i] << '\n';
        }
        return os;
    }

} 
