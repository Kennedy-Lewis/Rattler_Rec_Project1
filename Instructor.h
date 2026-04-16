/**
 * Instrcutor.h
 * Represents a fitness instructor at Rattler Rec, including their Id, name,
 * certification type, and years of experience. Tracks total instrcutors using
 * a static member varaible.
 * Author: Kennedy Lewis
 * Date:   2026-04-12
*/

#pragma once
#include <string>

class Instructor {
private:
  std::string m_instructorId;
  std::string m_name;
  std::string m_certification;
  int m_yearsExp;
  static int s_instructorCount; // static member 

public:
  Instructor(std::string id, std::string name, std::string certification, int yearsExp = 0);
  ~Instructor();
  
  std::string getInstructorId() const;
  std::string getName() const;
  std::string getCertification() const;
  int getYearsExp() const;

  // Sets certification. Rejects values other than "Group", "Peronal", or "Both"
  // Prints an error message without modifying the data member
  void setCertification(const std::string& cert);

  // Sets years of experience. rejects negative values and prints error message.
  void setYearsExp(int years);

  static int getInstructorCount();

  void display() const;
};