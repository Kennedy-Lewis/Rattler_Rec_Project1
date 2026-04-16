/**
 * GroupFitnessClass.cpp
 * Implements GroupFitnessClass inclduing fee calculations and formatted display.
 * Author: Kennedy Lewis
 * Date:   2026-04-12
*/

#include "GroupFitnessClass.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

// Constructor: Initializes group fitness class and validates difficulty range
GroupFitnessClass::GroupFitnessClass(std::string sessionId, TimeSlot slot, int maxCap,
                                     std::string className, Instructor instructor, int difficulty)
  : FitnessSession(sessionId, slot, maxCap),
    m_className(className),
    m_instructor(instructor),
    m_difficulty(difficulty)
{
  // Validate difficulty range (1-5)
  if(difficulty < 1 || difficulty > 5) {
    throw std::invalid_argument("Difficulty must be between 1 and 5.");
  }
}

// Drop-in fee = $3.00 per difficulty level
// Level 1 = $3.00, Level 3 = $9.00, Level 5 = $15.00
double GroupFitnessClass::calcFee() const {
  return m_difficulty * 3.0;
}

// Displays full group class information in formatted layout
void GroupFitnessClass::display() const {
  std::cout << "[ GROUP FITNESS ] " << m_sessionId << "\n"
            << "  Time       : " << m_slot.toString()
            << "  (" << m_slot.getDurationMins() << " min)\n"
            << "  Class      : " << m_className << "\n"
            << "  Difficulty : " << m_difficulty << " / 5\n"
            << "  Instructor : " << m_instructor.getName() << "\n"
            << "  Capacity   : " << m_enrolled << " / " << m_maxCap << " enrolled\n"
            << "  Drop-in Fee: " << std::fixed << std::setprecision(2) << calcFee() << "\n";
}

// Returns session type label
std::string GroupFitnessClass::getSessionType() const {
  return "GROUP FITNESS";
}