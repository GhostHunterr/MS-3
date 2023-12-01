// Name: Farhan Sarang
// Seneca Student ID: 172963217
// Seneca email: fsarang2@myseneca.ca
// Date of completion: 1 / 12 / 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include "Utilities.h"

using namespace std;
using namespace sdds;

namespace sdds
{
    char Utilities::m_delimiter{};

    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more)
    {
        size_t idxOfDelimiter = str.find(getDelimiter(), next_pos);

        if (idxOfDelimiter == next_pos)
        {
            more = false;
            throw std::string("Failed to find the delimiter");
        }

        std::string extracted = str.substr(next_pos, idxOfDelimiter - next_pos);

        // Trim Spaces
        size_t first_not_space = extracted.find_first_not_of(" \t");
        size_t last_not_space = extracted.find_last_not_of(" \t");

        if (first_not_space != std::string::npos && last_not_space != std::string::npos)
        {
            extracted = extracted.substr(first_not_space, last_not_space - first_not_space + 1);
        }
        else
        {
            extracted.clear();
        }

        next_pos = idxOfDelimiter + 1;

        setFieldWidth(std::max(m_widthField, extracted.size()));

        more = idxOfDelimiter != std::string::npos;

        return extracted;
    }

    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }
} // namespace sdds
