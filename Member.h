/**
 * Member.h
 * Represents a Rattler Rec member including student ID, name, membership type,
 * and attendance tracking. Uses a static member to track total members.
 * Author: Kennedy Lewis
 * Date:   2026-04-12
*/

#pragma once
#include <string>

class Member {
private: 
  std::string m_studentId;
  std::string m_name; 
  std::string m_membershipType;
  int m_sessionsAttended;
  static int s_memberCount;

public:
  Member(std::string id, std::string name, std::string membershipType);
  
  ~Member();

  std::string getStudentId() const;
  std::string getName() const;
  std::string getMembershipType() const;
  int getSessionsAttended() const;

  // Sets membership type. Rejects values other than "Student", "Faculty", or "Staff"
  // Prints an error message without modifying the data member.
  void setMembershipType(const std::string& type);
 
  // Incremenets sessions attended by 1
  void recordAttendance();

  static int getMemberCount();

  void display() const;
};