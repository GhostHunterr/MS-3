// Name: Farhan Sarang
// Seneca Student ID: 172963217
// Seneca email: fsarang2@myseneca.ca
// Date of completion: 1 / 12 / 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <algorithm>
#include <vector>
#include <iomanip>
#include <iostream>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds
{

    size_t CustomerOrder::m_widthField = {};

    CustomerOrder::CustomerOrder()
    {
        m_name = {};
        m_product = {};
        m_cntItem = {};
        m_lstItem = {};
    }

    CustomerOrder::CustomerOrder(const std::string &record) : CustomerOrder()
    {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        m_name = util.extractToken(record, next_pos, more);
        m_product = util.extractToken(record, next_pos, more);

        m_cntItem = std::count(record.begin(), record.end(), util.getDelimiter()) - 1;
        m_lstItem = new Item *[m_cntItem];

        for (size_t i = 0; i < m_cntItem; ++i)
        {
            m_lstItem[i] = new Item(util.extractToken(record, next_pos, more));
        }

        if (m_widthField < util.getFieldWidth())
        {
            m_widthField = util.getFieldWidth();
        }
    }

    CustomerOrder::CustomerOrder(CustomerOrder &&src) noexcept : CustomerOrder()
    {
        *this = std::move(src);
    }

    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&src) noexcept
    {
        if (this != &src)
        {

            for (size_t i = 0; i < m_cntItem; i++)
            {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;

            // Moving
            m_lstItem = src.m_lstItem;
            m_name = src.m_name;
            m_product = src.m_product;
            m_cntItem = src.m_cntItem;

            // Emptying the source
            src.m_lstItem = nullptr;
            src.m_name = "";
            src.m_product = "";
            src.m_cntItem = 0;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder()
    {
        for (unsigned i = 0; i < m_cntItem; i++)
        {
            delete m_lstItem[i];
            m_lstItem[i] = nullptr;
        }

        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const
    {
        for (size_t i = 0; i < m_cntItem; ++i)
        {
            if (!m_lstItem[i]->m_isFilled)
            {
                return false;
            }
        }
        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string &itemName) const
    {
        for (size_t i = 0; i < m_cntItem; ++i)
        {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
            {
                return false;
            }
        }
        return true;
    }

    void CustomerOrder::fillItem(Station &station, std::ostream &os)
    {
        bool itemFilled = false;
        for (size_t i = 0; i < m_cntItem && !itemFilled; ++i)
        {
            if (m_lstItem[i]->m_itemName == station.getItemName() && (!m_lstItem[i]->m_isFilled))
            {
                if (station.getQuantity() > 0)
                {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;

                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    itemFilled = true;
                }
                else
                {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream &os) const
    {
        os << m_name << " - " << m_product << std::endl;
        std::for_each(m_lstItem, m_lstItem + m_cntItem, [&](Item *item)
                      {
            os << "[" << std::setw(6) << std::setfill('0') << std::right << item->m_serialNumber << "] ";
            os << std::setw(m_widthField) << std::setfill(' ') << std::left << item->m_itemName << " - ";
            os << (item->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl; });
    }
}