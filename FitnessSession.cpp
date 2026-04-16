/**
 * FitnessSession.cpp
 * Implements the FitnessSession abstract base class, including shared 
 * functionality such as enrollement tracking and validation.
 * Author: Kennedy Lewis
 * Date:   2026-04-12
*/

#include "FitnessSession.h"
#include <stdexcept>

// Constructor: Initializes session and validates input values
FitnessSession::FitnessSession(std::string sessionId, TimeSlot slot, int maxCapacity)
  : m_sessionId(sessionId), m_slot(slot), m_maxCap(maxCapacity), m_enrolled(0)
{
  // Validate session ID
  if(m_sessionId.empty()) {
    throw std::invalid_argument("Session ID cannot be empty.");
  }
  
  // Validate capacity is at least 1
  if(m_maxCap < 1) {
    throw std::invalid_argument("Max capacity must be at least 1.");
  }
}

// Attempts to enroll a participant. Returns false if session is full.
bool FitnessSession::enroll() {
  // Prevent enrollement if session has reached capacity
  if(isFull()) {
    return false;
  }
  ++m_enrolled;
  return true;
}

// Attemps to drop a participant. returns false if no one is enrolled.
bool FitnessSession::drop() {
  // Cannot drop if no participants are enrolled
  if(m_enrolled <= 0) {
    return false;
  }
  --m_enrolled;
  return true;
}

// Returns true if session is at maximun capacity
bool FitnessSession::isFull() const {
  return m_enrolled >= m_maxCap;
}
  
// Returns session ID
std::string FitnessSession::getSessionId() const {
  return m_sessionId;
}

// Returns maximun capacity
int FitnessSession::getMaxCap() const {
  return m_maxCap;
}

// Returns current enrollment
int FitnessSession::getEnrolled() const {
  return m_enrolled;
}

// Returns reference to the TimeSlot 
const TimeSlot& FitnessSession::getSlot() const {
  return m_slot;
}

// Virtual Destructor ensures derived destructors are called properly
FitnessSession::~FitnessSession() {}