/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: Feb 1, 2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/


#include "event.h"
#include "settings.h"

#include <iomanip>

namespace seneca {

   
    namespace {

        
        int durationWidth(const std::string& units) {
            if (units == "seconds")      return 2;
            if (units == "milliseconds") return 5;
            if (units == "microseconds") return 8;
            return 11;
        }

        
        long long durationValue(std::chrono::nanoseconds ns,
            const std::string& units) {
            if (units == "seconds") {
                return std::chrono::duration_cast<std::chrono::seconds>(ns).count();
            }
            if (units == "milliseconds") {
                return std::chrono::duration_cast<std::chrono::milliseconds>(ns).count();
            }
            if (units == "microseconds") {
                return std::chrono::duration_cast<std::chrono::microseconds>(ns).count();
            }
            return ns.count(); // nanoseconds
        }

    }


    Event::Event(const char* name, const std::chrono::nanoseconds& duration)
        : m_name(name ? name : ""), m_duration(duration) {
    }

    std::ostream& operator<<(std::ostream& os, const Event& ev) {
     
        static int counter = 0;
        ++counter;

        const std::string& units = g_settings.m_time_units;
        int width = durationWidth(units);
        long long value = durationValue(ev.m_duration, units);

        os << std::setw(2) << std::right << counter << ": "
            << std::setw(40) << std::right << ev.m_name
            << " -> "
            << std::setw(width) << std::right << value
            << " " << units;

        return os;
    }

} 