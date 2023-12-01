// Name: Farhan Sarang
// Seneca Student ID: 172963217
// Seneca email: fsarang2@myseneca.ca
// Date of completion: 1 / 12 / 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include "Workstation.h"

using namespace std;
using namespace sdds;

namespace sdds
{
    std::deque<CustomerOrder> g_pending{};
    std::deque<CustomerOrder> g_completed{};
    std::deque<CustomerOrder> g_incomplete{};

    Workstation::Workstation(const std::string &record) : Station(record) {}

    void Workstation::fill(std::ostream &os)
    {
        if (!m_orders.empty())
        {
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder()
    {

        bool isMoved = false;
        if (!m_orders.empty())
        {
            if (m_orders.front().isItemFilled(getItemName()))
            {
                if (!m_pNextStation)
                {
                    if (m_orders.front().isOrderFilled())
                        g_completed.push_back(std::move(m_orders.front()));
                    else
                        g_incomplete.push_back(std::move(m_orders.front()));
                }
                else
                    *m_pNextStation += std::move(m_orders.front());
                m_orders.pop_front();
                isMoved = true;
            }
            else if (!getQuantity())
            {
                if (!m_pNextStation)
                    g_incomplete.push_back(std::move(m_orders.front()));
                else
                    *m_pNextStation += std::move(m_orders.front());
                m_orders.pop_front();
                isMoved = true;
            }
        }
        return isMoved;
    }

    void Workstation::setNextStation(Workstation *station)
    {
        m_pNextStation = station;
    }

    Workstation *Workstation::getNextStation() const
    {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream &os) const
    {
        os << getItemName() << " --> " << (m_pNextStation == nullptr ? "End of Line" : m_pNextStation->getItemName()) << '\n';
    }

    Workstation &Workstation::operator+=(CustomerOrder &&newOrder)
    {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }

} // namespace sdds
