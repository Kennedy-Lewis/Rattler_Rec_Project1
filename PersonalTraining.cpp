/**
 * PersonalTraining.cpp
 * Implements PersonalTraining including fee calculations and formatted display.
 * Author: Kennedy Lewis
 * Date:   2026-04-12
*/

#include "PersonalTraining.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// Constructor: Intializes a 1-on-1 training session (capacity is always 1) 
PersonalTraining::PersonalTraining(std::string sessionId, 
                                   TimeSlot slot,
                                   Instructor trainer,
                                   Member client)
  : FitnessSession(sessionId, slot, 1), 
    m_trainer(trainer), m_client(client) {}
  
// Fee = $15.00 base + $5.00 per year of trainer experience
// Example: 6 years experience -> $15 + $30 = $45.00
double PersonalTraining::calcFee() const {
  return 15.0 + (m_trainer.getYearsExp() * 5.0);
}

// Returns session type label
std::string PersonalTraining::getSessionType() const {
  return "PERSONAL TRAINING";
}

// Displays full personal training session details
void PersonalTraining::display() const {
  std:: cout << "[ " << getSessionType() << " ] " << m_sessionId << "\n"
             << "  Time   : " << m_slot.toString()
             << "  (" << m_slot.getDurationMins() << " min)\n"
             << "  Trainer : " << m_trainer.getName() << "\n"
             << "  Client  : " << m_client.getName() 
             << "  [" << m_client.getMembershipType() << "]\n"
             << "  Fee     : $" << std::fixed << std::setprecision(2) <<calcFee() << "\n";
}
