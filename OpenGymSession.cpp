/**
 * OpenGymSession.cpp
 * Implements OpenGymSession including fee logic and formatted display.
 * Author: Kennedy Lewis
 * Date:   2026-04-12
*/

#include "OpenGymSession.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

// Constructor: Intializes Open Gym session an dvalidates area name
OpenGymSession::OpenGymSession(std::string sessionId, TimeSlot slot, int maxCap,
                               std::string areaName, bool isMonitored) 
  : FitnessSession(sessionId, slot, maxCap),
    m_areaName(areaName), m_isMonitored(isMonitored)
{
  // Validate gym area type
  if(areaName != "Cardio" && areaName != "Weights" && areaName != "Courts") {
    throw std::invalid_argument("Area must be Cardio, Weights, or Courts.");
  }
}

// Fee = free if monitored, otherwise $2
double OpenGymSession::calcFee() const {
  return m_isMonitored ? 0.0 : 2.0;
}

// Returns session type label
std::string OpenGymSession::getSessionType() const {
  return "OPEN GYM";
}

// Displays full open gym session information
void OpenGymSession::display() const {
  std::cout << "[ " << getSessionType() << " ] " << m_sessionId << "\n"
            << "  Time      : " << m_slot.toString()
            << "  (" << m_slot.getDurationMins() << " min)\n"
            << "  Area      : " << m_areaName << "\n"
            << "  Monitored : " << (m_isMonitored ? "Yes" : "No") << "\n"
            << "  Capacity  : " << m_enrolled << " / " << m_maxCap << " enrolled\n"
            << "  Drop-in Fee: $" << std:: fixed << std::setprecision(2) << calcFee() << "\n";
} 
