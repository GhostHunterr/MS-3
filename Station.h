// Name: Farhan Sarang
// Seneca Student ID: 172963217
// Seneca email: fsarang2@myseneca.ca
// Date of completion: 1 / 12 / 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <string>

namespace sdds
{
    class Station
    {
        int m_id;
        std::string m_name;
        std::string m_description;
        unsigned m_serialNumber;
        unsigned m_inStock_items;

        static size_t m_widthField;
        static size_t id_generator;

    public:
        Station(const std::string &record);              // one-argument Constructor
        const std::string &getItemName() const;          // returns the name of the current Station object
        size_t getNextSerialNumber();                    // returns the next serial number to be used on the assembly line and increments m_serialNumber
        size_t getQuantity() const;                      // returns the remaining quantity of items in the Station object
        void updateQuantity();                           // subtracts 1 from the available quantity; should not drop below 0.
        void display(std::ostream &os, bool full) const; // inserts information about the current object into stream os.
    };

} // namespace sdds

#endif