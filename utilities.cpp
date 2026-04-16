/**
 * utilities.cpp
 * Implements polymorphic operations on a collection of FitnessSession objects.
 * Demonstrates runtime polymorphism using base-class pointers without casting.
 * Author: Kennedy Lewis
 * Date:   2026-04-12
*/

#include "utilities.h"
#include "FitnessSession.h"
#include <iostream>
#include <stdexcept>
#include <vector>

// Iterates through all sessions and calls polymorphic display()
void printSchedule(const std::vector<FitnessSession*>& sessions) {
  if(sessions.empty()) {
    std::cout << "No sessions scheduled.\n";
    return;
  }
  for(const auto* s : sessions) {
    s->display(); 
    std::cout <<"\n";
  }
}

// Computes total revenue usuing polymorphic calcFee()
double totalRevenue(const std::vector<FitnessSession*>& sessions) {
  double total = 0.0;

  for(const auto& session : sessions) {
    total += session->calcFee();
  }
  return total;
}

// Returns a vector of sessions matching the given session type
std::vector<FitnessSession*> filterByType(const std::vector<FitnessSession*>& sessions,
                                          const std::string& type) 
{
  std::vector<FitnessSession*> result;

  for(const auto& session : sessions) {
    if(session->getSessionType() == type) {
      result.push_back(session);
    }
  }
  return result;
}

// Find a session by ID and returns pointer or nullptr if not found
FitnessSession* findById(const std::vector<FitnessSession*>& sessions,
                         const std::string& id) 
{
  for (const auto& session : sessions){
    if(session->getSessionId() == id) {
      return session;
    }
  }
  return nullptr;
}  

// Returns the session with the highest enrollment count
// Throws exception if no sessions exists
FitnessSession* mostPopular(const std::vector<FitnessSession*>& sessions){
  if(sessions.empty()) {
    throw std::runtime_error("No sessions available to evaluate popularity.");
  }

FitnessSession* mostPopularSession = sessions[0];

for(const auto& session : sessions) {
  if(session->getEnrolled() > mostPopularSession->getEnrolled()) {
    mostPopularSession = session;
  }
}

return mostPopularSession;
}
                      


