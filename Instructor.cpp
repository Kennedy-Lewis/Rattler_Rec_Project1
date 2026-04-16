/**
 * Instrcutor.cpp
 * Implements the Instrcutor class, including validation, static member tracking, 
 * and display functionality
 * Author: Kennedy Lewis
 * Date:   2026-04-12
*/

#include "Instructor.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

// Static member defintion
int Instructor::s_instructorCount = 0;

// Constructor: Initializes instructor and validates all inputs. 
// Increments static instructor count upon successful creation. 
Instructor::Instructor(std::string id, std::string name, std::string certification, int yearsExp) 
    : m_instructorId(id), m_name(name), m_yearsExp(yearsExp) {

    // Validate ID is not empty
    if(m_instructorId.empty()) {
      throw std::invalid_argument("Instructor ID cannot be empty.");
    }

    // Validate name is not empty
    if(m_name.empty()) {
      throw std::invalid_argument("Instructor name cannot be empty.");
    }

    // Validate certification value 
    if(certification != "Group" && certification != "Personal" && certification != "Both") {
      throw std::invalid_argument("Invalid certification. Must be Group, Personal, or Both");
    }
    m_certification = certification;

    // Validate years of experience is non-negative
    if(m_yearsExp < 0) {
      throw std::invalid_argument("Years of experience cannot be negative.");
    }

    // Increment static counter when a new Instructor is created
    ++s_instructorCount;
}

// Destructor
Instructor::~Instructor() {}

// Returns instructor ID
std::string Instructor::getInstructorId() const {
  return m_instructorId;
}

// Returns instructor name
std::string Instructor::getName() const {
  return m_name;
}

// Returns certification type
std::string Instructor::getCertification() const {
  return m_certification;
}

// Returns years of experience
int Instructor::getYearsExp() const {
  return m_yearsExp;
}

// Sets certification. Rejects invalid values and does not modify if invalid.
void Instructor::setCertification(const std::string& cert) {
  if(cert != "Group" && cert != "Personal" && cert != "Both") {
    std::cout << "Error: invlaid certification. Must be Group, Personal, or Both.\n";
    return;
  }
    m_certification = cert;
}

// Sets years of experience. Rejects negative values and does not modify if invalid
void Instructor::setYearsExp(int years) {
  if(years < 0) {
    std::cout << "Error: Years of experience cannot be negative.\n";
    return;
  }
  m_yearsExp = years;
}

// Returns current number of Instructor objects
int Instructor::getInstructorCount() {
  return s_instructorCount;
}

// Displays instructor information in a formatted layout 
void Instructor::display() const {
  std::cout << "Instructor ID: " << m_instructorId << "\n"
            << "Name: " << m_name << "\n"
            << "Certification: " << m_certification << "\n"
            << "Years of Experience: " << m_yearsExp << "\n";
}
