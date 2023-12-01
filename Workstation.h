// Name: Farhan Sarang
// Seneca Student ID: 172963217
// Seneca email: fsarang2@myseneca.ca
// Date of completion: 1 / 12 / 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds
{
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station
    {
        std::deque<CustomerOrder> m_orders{};
        Workstation *m_pNextStation{};

    public:
        Workstation(const std::string &record);
        void fill(std::ostream &os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation *station = nullptr);
        Workstation *getNextStation() const;
        void display(std::ostream &os) const;
        Workstation &operator+=(CustomerOrder &&newOrder);

        // Copy Semantics
        Workstation(const Workstation &rOp) = delete;
        Workstation &operator=(const Workstation &rOp) = delete;

        // Move Semantics
        Workstation(Workstation &&rOp) = delete;
        Workstation &operator=(Workstation &&rOp) = delete;
    };

} // namespace sdds

#endif