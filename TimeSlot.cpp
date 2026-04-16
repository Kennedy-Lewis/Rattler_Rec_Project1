/**
 * TimeSlot.cpp
 * Implements the TimeSlot class, including validation, formatting, 
 * duration calculation, and overlap detection.
 * Author: Kennedy Lewis
 * Date:   2026-04-12
*/

#include "TimeSlot.h"
#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>

// Returns true if the provided string matches a valid day of the week
bool TimeSlot::isValidDay(const std::string& day) const {
  static const std::string validDays[] = {
    "Monday", "Tuesday", "Wednesday", "Thursday", 
    "Friday", "Saturday", "Sunday"
  };
  for(const auto& d : validDays) {
      if (day == d) return true;
  }
  return false;
}

// Returns true if the hour and minute values fall within valid ranges
bool TimeSlot::isValidTime(int hour, int min) const {
    return (hour >= 0 && hour <= 23 && min >= 0 && min <= 59);
}

// Constructor: Initializes a TimeSlot and validates all inputs.
// Throws std::invalid_argument if day or time values are invalid. 
TimeSlot::TimeSlot(std::string day, int startHour, int startMin, int endHour, int endMin)
    : m_dayOfWeek(day), m_startHour(startHour), m_startMin(startMin), 
      m_endHour(endHour), m_endMin(endMin)
{
  // Validate day of the week
  if(!isValidDay(day)) {
    throw std::invalid_argument("Invalid day of week");
  }
  
  // Validate time values (hours and minutes must be within proper range)
  if(!isValidTime(startHour, startMin) || !isValidTime(endHour, endMin)) {
    throw std::invalid_argument("Invalid time values");
  }

  // Convert time to total minutes to compare easily
  int startTotal = startHour * 60 + startMin;
  int endTotal = endHour * 60 + endMin;

  // Ensure end time occurs strictly after start time
  if(endTotal <= startTotal) {
    throw std::invalid_argument("End time must be after start time");
  }
}

// Returns a formatted string representation of the TimeSlot
std::string TimeSlot::toString() const {
    std::ostringstream oss;
    oss << m_dayOfWeek << " "
        << std::setw(2) << std::setfill('0') << m_startHour << ":"
        << std::setw(2) << std::setfill('0') << m_startMin << "-"
        << std::setw(2) << std::setfill('0') << m_endHour << ":"
        << std::setw(2) << std::setfill('0') << m_endMin;
    
    return oss.str(); 
}

// Returns the duration of the TimeSlot in minutes
int TimeSlot::getDurationMins() const {
    int startTotal = m_startHour * 60 + m_startMin;
    int endTotal = m_endHour * 60 + m_endMin;
    return endTotal - startTotal;
}

// Returns truw if TimeSlot  overlaps with another TimeSlot
bool TimeSlot::overlaps(const TimeSlot& other) const {
    if(m_dayOfWeek != other.m_dayOfWeek) {
       return false;
    }

    // Converts both time ranges into minutes 
    int start1 = m_startHour * 60 + m_startMin;
    int end1 = m_endHour * 60 + m_endMin;

    int start2 = other.m_startHour * 60 + other.m_startMin;
    int end2 = other.m_endHour * 60 + other.m_endMin;

    // Overlap occurs if one starts before the other ends
    return (start1 < end2 && start2 < end1);
}

// Returns the day of the week 
std::string TimeSlot::getDayOfWeek() const {
  return m_dayOfWeek;
}

// Returns the start hour
int TimeSlot::getStartHour() const {
  return m_startHour;
}

// Returns the start minute
int TimeSlot::getStartMin() const {
  return m_startMin;
}

// Returns the end hour
int TimeSlot::getEndHour() const {
  return m_endHour;
}

// Returns the end minute
int TimeSlot::getEndMin() const {
  return m_endMin;
}