/*  Name: Rohan Shyntan Tamang
    Seneca Email: rshyntan-tamang@myseneca.ca
    Seneca Student ID: 173438235
    Date: Feb 1, 2026
    I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#include "timeMonitor.h"

namespace seneca {

    void TimeMonitor::startEvent(const char* name) {
        
        m_eventName = (name ? name : "");

      
        m_startTime = std::chrono::steady_clock::now();
    }

    Event TimeMonitor::stopEvent() {
       
        auto endTime = std::chrono::steady_clock::now();
        auto durationNs =
            std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - m_startTime);

        return Event(m_eventName.c_str(), durationNs);
    }

}
