/**
 * utilities.h
 * Declares utility functions that operates on a collection of FitnessSession pointers.
 * These functions demonstrate runtime polymorphism by using the only base class interface.
 * Author: Kennedy Lewis
 * Date:   2026-04-12
*/

#pragma once
#include <string>
#include <vector>
#include "FitnessSession.h"

/*
  Prints the full schedule of fitness sessions. Interates through the vector
  of FitnessSession pointers and calls display() on each session. Due to the 
  runtime polymorphism, the correct display() implementation for each derived 
  class is invoked automatically.
*/

void printSchedule(const std::vector<FitnessSession*>& sessions);

/*
  Calculates the total potential revenue from all sessions and returns the total 
  revenue as a double. Ireates through the vector and sums the result of calcFee() 
  for each session. Each session determines its own fee through virtal dipatch, 
  allowing the function to remain unaware of specific derived types. 
*/
double totalRevenue(const std::vector<FitnessSession*>& sessions);

/*
  Filters sessions by type and returns a vector of FitnessSession* matching the 
  given type. Creates and returns a new vector containing only the sessions whose
  getSessionType() matches the provided type string. The returned vector still 
  contains base-class pointers, preserving polymorphic behavior.
*/
std::vector<FitnessSession*> filterByType(const std::vector<FitnessSession*>& sessions,
                                          const std::string& type);
                                    
/*
  Finds a session by its unique session ID. Returns a pointer to the matching 
  session if found, or nullptr if no match exists. Searches for the vecttor for a
  session whose getSessionId() matches the given id.
*/                                          
FitnessSession* findById(const std::vector<FitnessSession*>& sessions,
                         const std::string& id);

/*
  Finds the most popular session based on enrollement. Throw std::runtime_error if 
  the sessions vector is empty. Iterates through all sessions and returns a pointer 
  to the one with the highest number of enrolled participants. If mutiple sessiosn 
  have the same highest enrollement the first one encountered is returned.
*/                         
FitnessSession* mostPopular(const std::vector<FitnessSession*>& sessions);

