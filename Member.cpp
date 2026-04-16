/**
 * Member.cpp
 * Implements the Member class including validation, static member tracking, 
 * attendance recording, and display functionality.
 * Author: Kennedy Lewis
 * Date:   2026-04-12
*/

#include "Member.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

// Static member defintion
int Member::s_memberCount = 0;

// Constructor: Intializes member and validates inputs.
// Sets sessions attended to 0 and increments static count.
Member::Member(std::string id, std::string name, std::string membershipType)
  : m_studentId(id), m_name(name), m_sessionsAttended(0) 
{
  // Validate student ID
  if(m_studentId.empty()) {
    throw std::invalid_argument("Student ID cannot be empty.");
  }
  // Validate name
  if(m_name.empty()) {
    throw std::invalid_argument("Name cannot be empty.");
  }
  // Validate membership type
  if(membershipType != "Student" && membershipType != "Faculty" && membershipType != "Staff") {
     throw std::invalid_argument("Invalid membership type. Must be Student, Faculty or Staff."); 
  }
  m_membershipType = membershipType;

  // Incremenet static counter when a new Member is created
  ++s_memberCount;
}  
  
// Destructor: Decrements static member count
Member::~Member() {}

// Returns student ID
std::string Member::getStudentId() const {
  return m_studentId;
}

// Returns member name
std::string Member::getName() const {
  return m_name;
}

// Returns membership type
std::string Member::getMembershipType() const {
  return m_membershipType;
}

// Returns number of sessions attended
int Member::getSessionsAttended() const {
  return m_sessionsAttended;
}

// Sets membership type. Rejects invalid values and does no modify if invalid
void Member::setMembershipType(const std::string& type) {
  if(type != "Student" && type != "Faculty" && type != "Staff") {
    std::cout << "Error Invalid membership type. Must be Student, Faculty, or Staff.\n";
    return;
  }
  m_membershipType = type;
}

// Incremenets the number of sessions attended
void Member::recordAttendance() {
  ++m_sessionsAttended;
}

// Returns current number of Member objects
int Member::getMemberCount() {
  return s_memberCount;
}

// Displays member information in fomatted output 
void Member::display() const {
  std::cout << "Student ID: " << m_studentId << "\n"
            << "Name: " << m_name << "\n"
            << "Membership Type: " << m_membershipType << "\n"
            << "Sessions Attended: " << m_sessionsAttended << "\n";
}

