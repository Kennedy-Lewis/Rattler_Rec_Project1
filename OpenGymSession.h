/**
 * OpenGymSession.h
 * Represents a drop-in gym session fro members using a specific area.
 * Fee depends on whether the session is monitored by staff.
 * Author: Kennedy Lewis
 * Date:   2026-04-12
*/

#pragma once
#include <string>
#include "FitnessSession.h"

/*
  OpenGymSession is a concrete derived class of FitnessSession.
  It represents a general-use gym session where members can 
  access a specific equipment area. The session can be isMonitored
  or unmonitored which affects the drop-in fee. It inherits TimeSlot
  through FitnessSession and adds attributes specifc to gym usage.
  
  It overrides:
  - display(): custom formatted output for open gym sessions
  - calcFee(): pricing based on whether the session is monitored
  - getSessionType(): returns session type label
*/

class OpenGymSession : public FitnessSession{
private: 
  std::string m_areaName;
  bool m_isMonitored;

public: 
  OpenGymSession(std::string sessionId, TimeSlot slot, int maxCap,
                 std::string areaName, bool isMonitored);
               
  double calcFee() const override;
  void display() const override;  
  std::string getSessionType() const override;
};