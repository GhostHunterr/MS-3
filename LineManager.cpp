// Name: Farhan Sarang
// Seneca Student ID: 172963217
// Seneca email: fsarang2@myseneca.ca
// Date of completion: 1 / 12 / 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

using namespace std;
using namespace sdds;

namespace sdds
{
    LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations) : m_cntCustomerOrder(0), m_firstStation(nullptr)
    {
        std::ifstream file_(file);
        if (!file_)
        {
            throw "Failed to open the file";
        }
        else
        {
            Utilities utils;
            std::string fileLine;

            while (std::getline(file_, fileLine))
            {
                size_t npos = 0;
                bool more = true;

                std::string currWSname = utils.extractToken(fileLine, npos, more);
                Workstation *currWS = *std::find_if(stations.begin(), stations.end(), [&](Workstation *ws)
                                                    { return ws->getItemName() == currWSname; });

                m_activeLine.push_back(currWS);

                if (more)
                {
                    std::string nxtWSname = utils.extractToken(fileLine, npos, more);
                    Workstation *nxtWS = *std::find_if(stations.begin(), stations.end(), [&](Workstation *ws)
                                                       { return ws->getItemName() == nxtWSname; });

                    currWS->setNextStation(nxtWS);
                }
            }

            // Finding the first station in the assembly line
            m_firstStation = *std::find_if(stations.begin(), stations.end(), [&](Workstation *tmp)
                                           { return std::none_of(stations.begin(), stations.end(), [&](Workstation *station)
                                                                 { return station->getNextStation() == tmp; }); });

            m_cntCustomerOrder = g_pending.size();
        }

        file_.close();
    }

    void LineManager::reorderStations()
    {
        std::vector<Workstation *> reordered;
        Workstation *current = m_firstStation;

        while (current)
        {
            reordered.push_back(current);
            current = current->getNextStation();
        }

        m_activeLine = reordered;
    }

    bool LineManager::run(std::ostream &os)
    {
        static size_t iterations = 0;
        os << "Line Manager Iteration: " << ++iterations << std::endl;

        if (!g_pending.empty())
        {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation *ws)
                      { ws->fill(os); });
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation *ws)
                      { ws->attemptToMoveOrder(); });

        return m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
    }

    void LineManager::display(std::ostream &os) const
    {
        if (!m_activeLine.empty())
        {

            for (auto station : m_activeLine)
            {
                station->display(os);
            }
        }
    }

} // namespace sdds
