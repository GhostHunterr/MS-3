// Name: Farhan Sarang
// Seneca Student ID: 172963217
// Seneca email: fsarang2@myseneca.ca
// Date of completion: 1 / 12 / 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <iomanip>
#include "Utilities.h"
#include "Station.h"

using namespace std;
using namespace sdds;

namespace sdds
{
    size_t Station::m_widthField{};
    size_t Station::id_generator = 1; // Should be 1 not 0

    Station::Station(const std::string &record)
    {
        try
        {
            m_id = id_generator++;

            Utilities utility;
            size_t npos = 0;
            bool more;

            m_name = utility.extractToken(record, npos, more);
            m_serialNumber = std::stoi(utility.extractToken(record, npos, more));
            m_inStock_items = std::stoi(utility.extractToken(record, npos, more));

            m_widthField = std::max(utility.getFieldWidth(), m_widthField);

            m_description = utility.extractToken(record, npos, more);
        }
        catch (const std::string &err)
        {
            std::cout << err;
        }
    }

    const std::string &Station::getItemName() const
    {
        return m_name;
    }

    size_t Station::getNextSerialNumber()
    {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const
    {
        return m_inStock_items;
    }

    void Station::updateQuantity()
    {
        if (m_inStock_items > 0)
        {
            m_inStock_items--;
        }
        else
        {
            m_inStock_items = 0;
        }
    }

    void Station::display(std::ostream &os, bool full) const
    {
        os << std::setfill('0') << std::setw(3) << std::right << m_id;
        os << " | " << std::setw(m_widthField) << std::setfill(' ') << std::left << m_name;
        os << " | " << std::setfill('0') << std::setw(6) << std::right << m_serialNumber << " | ";

        if (full)
        {
            os << std::setfill(' ') << setw(4) << std::right << m_inStock_items
               << " | " << std::left << m_description << std::endl;
        }
        else
        {
            os << std::endl;
        }
    }

} // namespace sdds
