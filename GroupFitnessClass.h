/**
 * GroupFitnessClass.h
 * Represents an instructor-led group fitness class with a difficulty-based pricing model.
 * Inherits from FitnessSession and demostrates polymorphism and composition.
 * Author: Kennedy Lewis
 * Date:   2026-04-12
*/

#pragma once
#include "FitnessSession.h"
#include "Instructor.h"
#include <string>

/*
  GroupFitnessClass is concrete derived class of FitnessSession.
  It represents instrucor-led group workouts where pricing depends
  on difficulty. It inherits TimeSlot through FitnessSession (composition)
  and has an Instructor object, demonstrating mutlti-level object composition.

  It overrides:
  - display(): custom formatted output for group classes
  - calcFee(): pricing based on difficulty level 
  - getSessionType(): returns class type label
*/

class GroupFitnessClass : public FitnessSession {
private:
  std::string m_className;
  Instructor m_instructor;
  int m_difficulty;

public:
  GroupFitnessClass(std::string sessionId, TimeSlot slot, int maxCap,
                    std::string className, Instructor instructor, int difficulty);
                  
  double calcFee() const override;
  void display() const override;
  std::string getSessionType() const override;
};