/**
 * TimeSlot.h
 * Represents an immutable scheduled blocks of time day and start/end times.
 * Provides validation, formatting, duration calculation, and overlap detection.
 * Author: Kennedy Lewis
 * Date:   2026-04-12
*/

#pragma once
#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>

class TimeSlot {
private:
  std::string m_dayOfWeek;
  int m_startHour; 
  int m_startMin; 
  int m_endHour;
  int  m_endMin;

  // Validates that the given string is valid day of the week
  bool isValidDay(const std::string& day) const;

  // Validates that hour and minute values are within accepatble ranges
  bool isValidTime(int hour, int min) const;
  
public: 
  TimeSlot(std::string day, int startHour, int startMin, int endHour, int endMin);

  std::string toString() const;
  int getDurationMins() const;
  bool overlaps(const TimeSlot& other) const;

  std::string getDayOfWeek() const;
  int getStartHour() const;
  int getStartMin()const;
  int getEndHour() const;
  int getEndMin() const;
};