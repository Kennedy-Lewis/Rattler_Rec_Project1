/**
 * FitnessSession.h
 * Abstract base class representing a generic fitness session.
 * Define a common interface for all session types including display,
 * fee calculation, and session type identification.
 * Author: Kennedy Lewis
 * Date:   2026-04-12
*/

#pragma once
#include <string>
#include "TimeSlot.h"

/*
  FitnessSession is an abstract base class because it contains pure virtual functions.
  This means it cannot be instantiated directly, only derived classes can be created.
  
  The three virtual functions represent behaviors that vary by session type:
  - display(): Each session type may present its details differently.
  - calFee(): each session type has its own pricing model.
  - getSessionType(): Each type returns its own label 
*/

class FitnessSession {
protected:
  std::string m_sessionId;
  TimeSlot m_slot; // Composition (stored by value)
  int m_maxCap;
  int m_enrolled;

public:
  FitnessSession(std::string sessionId, TimeSlot slot, int maxCapacity);

  virtual void display() const = 0;    // Print all session details
  virtual double calcFee() const = 0;  // Return the drop-in fee
  virtual std::string getSessionType() const = 0;  // Return the type label

  bool enroll();
  bool drop();
  bool isFull() const;
  
  std::string getSessionId() const;
  int getMaxCap() const;
  int getEnrolled() const;
  const TimeSlot& getSlot() const;

  virtual ~FitnessSession();

  /*
    Virtual desctructor ensures that when deleting a derived class object
    through a FitnessSession pointer, the derived class desctructor is 
    also called. Without this, only the base descructor runs, leading to
    resource links. 
  */
};