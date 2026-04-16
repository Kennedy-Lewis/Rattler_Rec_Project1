/**
 * main.cpp
 * Rattler Rec Front Desk Terminal
 *
 * This program simulates a fitness center scheduling system usuing runtime polymorphism.
 * All sessions are stored as FitnessSession* in a vector. The system allows adding
 * different session types, enrolling memebers, viewing schedules, and computing revenue.
 * 
 * The vector stores base-class pointers so that derived class behavior is invoked
 * dynamically at runtime through virtual functions.
 * Author: Kennedy Lewis
 * Date:   2026-04-12
*/

#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include "FitnessSession.h"
#include "GroupFitnessClass.h"
#include "PersonalTraining.h"
#include "OpenGymSession.h"
#include "utilities.h"
#include "Instructor.h"
#include "Member.h"
#include "TimeSlot.h"

// Validates the day
bool isValidDay(const std::string& day) {
  return day == "Monday" || day == "Tuesday" ||
         day == "Wednesday" || day == "Thursday" ||
         day == "Friday" || day == "Saturday" ||
         day == "Sunday";
}

// Rejects non-valid days and reprompts till valid day is given
std::string getValidDay() {
  std::string day;

  while (true) {
    std::cout << "Enter day: ";
    std:: cin >> day; 

    if(isValidDay(day)) return day;

    std::cout << "Error rejecting " << "\'" << day << "\'\n";
  }
}

// Rejects non-valid diffucilties and reprompts until valid number is given
int getValidDifficulty() {
  int diff;

  while (true) {
    std::cout << "Enter difficulty (1-5): ";
    std::cin >> diff;

    if(std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Enter a number.\n";
    }
    if(diff >= 1 && diff <= 5) return diff;
    
    std::cout << "Error: difficulty must be between 1 and 5.\n";
  }
}

int main() {

  std::vector<FitnessSession*> sessions;
  int choice = -1;

  while (choice != 0) {

    std::cout << "\n+-------------------------------------------------------+\n";
    std::cout << "|         RATTLER REC - FRONT DESK TERMINAL             |\n";
    std::cout << "+-------------------------------------------------------+\n";
    std::cout << "|  1.  Add Group Fitness Class                          |\n"; // Creates a new instructor-led group class and stores it in the schedule
    std::cout << "|  2.  Add Personal Training Session                    |\n"; // Creates a one-on-one training session between a trainer and a client
    std::cout << "|  3.  Add Open Gym Session                             |\n"; // Creates a drop-in gym session with optional monitoring 
    std::cout << "|  4.  View Full Schedule                               |\n"; // Displays all sessions using polymorphic display() calls
    std::cout << "|  5.  View Total Potential Revenue                     |\n"; // Calculates total revenue using calcFee() for all sessions
    std::cout << "|  6.  Filter Schedule by Session Type                  |\n"; // Shows only sessions matching a selected type
    std::cout << "|  7.  Enroll in a Session (by ID)                      |\n"; // Finds a session by ID and enolls a participant if space allows
    std::cout << "|  8.  Drop from a Session (by ID)                      |\n"; // Finds a session by ID and removes a participant if possible
    std::cout << "|  9.  View Most Popular Session                        |\n"; // Finds the session with the highest enrollment using mostPopular()
    std::cout << "|  10. View Instructor Count  (static member)           |\n"; // Displays total number of Instructor objects currently active
    std::cout << "|  11. View Member Count  (static member)               |\n"; // Displays total number of Member objects currently active 
    std::cout << "|  0.  Exit                                             |\n"; // Exits program and triggers memory cleanup
    std::cout << "+-------------------------------------------------------+\n";
  
    std::cout << "Select option: ";
    std::cin >> choice;

    if(std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Try again.\n";
      continue;
    }

    try {
      // ================= OPTION 1 =================
      if(choice == 1) {
        // Adds a GroupFitnessClass to the schedule

        std::string id, day, className, insId, insName, cert;
        int sh, sm, eh, em, cap, diff, years;

        std::cout << "Enter session ID: ";
        std::cin >> id;

        day = getValidDay();
        
        std::cout << "Enter start hour/min: ";
        std::cin >> sh >> sm;

        while (true) {
          std::cout << "Enter end hour/min: ";
          std::cin >> eh >> em;

        // Convert to total minutes for easy comparison
        int startTotal = sh * 60 + sm;
        int endTotal = eh * 60 + em;

        if(endTotal > startTotal) {
          break;
        }
        
        std::cout << "Error: end must be after start\n";
      }

        TimeSlot slot(day, sh, sm, eh, em);

        std::cout << "Enter Instructor ID: ";
        std::cin >> insId;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter instructor name: ";
        std::getline(std::cin, insName);

        std::cout << "Enter certification type (Group/Personal/Both): ";
        std::getline(std::cin, cert);

        std::cout << "Enter years of experience: ";
        std::cin >> years;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        Instructor ins(insId, insName, cert, years);

        std::cout << "Enter class name: ";
        std::getline(std::cin, className);

        std::cout << "Enter capacity: ";
        std::cin >> cap;

        diff = getValidDifficulty();

        sessions.push_back(new GroupFitnessClass(id, slot, cap, className, ins, diff));

        std::cout << "\nSession added successfully!";
      }

      // ================= OPTION 2 =================
      else if(choice == 2) {
        // Adds a PersonalTraining session

        std::string id, day, tId, tName, cert, cId, cName, type;
        int sh, sm, eh, em, years;

        std::cout << "Enter session ID: ";
        std::cin >> id;

        day = getValidDay();

        std::cout << "Enter start hour/min: ";
        std::cin >> sh >> sm;

        while (true) {
          std::cout << "Enter end hour/min: ";
          std::cin >> eh >> em;

        // Convert to total minutes for easy comparison
        int startTotal = sh * 60 + sm;
        int endTotal = eh * 60 + em;

        if(endTotal > startTotal) {
          break;
        }
        
        std::cout << "Error: end must be after start\n";
       
      }
        TimeSlot slot(day, sh, sm, eh, em);

        std::cout << "Enter trainer ID: ";
        std::cin >> tId;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter trainer name: ";
        std::getline(std::cin, tName);

        std::cout << "Enter certification (Group/Personal/Both): ";
        std::getline(std::cin, cert);

        std::cout << "Enter years of experience: ";
        std::cin >> years;
        
        Instructor trainer(tId, tName, cert, years);

        std::cout << "Enter client ID: ";
        std::cin >> cId;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "Enter client name: ";
        std::getline(std::cin, cName);

        std::cout << "Membership type (Student/Faculty/Staff): ";
        std::getline(std::cin, type);

        Member client(cId, cName, type);

        sessions.push_back(new PersonalTraining(id, slot, trainer, client));

        std::cout << "\nSession added successfully!";
      } 
      
      // ================= OPTION 3 =================
      else if(choice == 3) {
        // Adds an OpenGymSession

        std::string id, day, area;
        int sh, sm, eh, em, cap;

        std::cout << "Enter Session ID: ";
        std::cin >> id;

        day = getValidDay();

        std::cout << "Enter start hour/min: ";
        std::cin >> sh >> sm;

        while (true) {
          std::cout << "Enter end hour/min: ";
          std::cin >> eh >> em;

        // Convert to total minutes for easy comparison
        int startTotal = sh * 60 + sm;
        int endTotal = eh * 60 + em;

        if(endTotal > startTotal) {
          break;
        }
        
        std::cout << "Error: end must be after start\n";
       
      }

        TimeSlot slot(day, sh, sm, eh, em);

        std::cout << "Enter area (Cardio/Weights/Courts): ";
        std::cin >> area;

        std::cout << "Enter capacity: ";
        std::cin >> cap;

        bool mon;
        std::string input;

        while (true) {
          std::cout << "Monitored (Yes/No): ";
          std::cin >> input;

          if(input == "yes" || input == "Yes") {
            mon = true;
            break;
          }
          else if (input == "no" || input == "No") {
            mon = false;
            break;
          }
          else {
            std::cout << "Invalid input. Enter yes or no.\n";
          }
        }
        sessions.push_back(new OpenGymSession(id, slot, cap, area, mon));

        std::cout << "\nSession added successfully!";
      }

      // ================= OPTION 4 =================
      else if(choice == 4) {
        // Displays full schedule using polymorphism
        printSchedule(sessions);
      }

      // ================= OPTION 5 =================
      else if(choice == 5) {
        // Calculates total revenue using virtual calcFee()
        std::cout << "Total potential revenue: $" << totalRevenue(sessions) << "\n";

        
      }

      // ================= OPTION 6 =================
      else if(choice == 6) {
        // Filters sessions by type
        std::string type;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter type (Group Fitness/Personal Training/Open Gym): \n";
        std::getline(std::cin, type);

        if(type == "Group Fitness") {
          type = "GROUP FITNESS";
        }
        else if(type == "Personal Training") {
          type = "PERSONAL TRAINING";
        }
        else if (type == "Open Gym") {
          type = "OPEN GYM";
        }

        auto filtered = filterByType(sessions, type);
        printSchedule(filtered); 
      }

      // ================= OPTION 7 =================
      else if(choice == 7) {
        // Enrolls member into session by ID
        std::string id;
        std::cout << "Enter session ID: ";
        std::cin >> id;

        FitnessSession* s = findById(sessions, id);

        if(!s) {
          std::cout << "Sessions not found.\n";
        }
        else if (s->enroll()) {
          std::cout << "Enrolled successfully. ("
                    << s->getEnrolled() << "/"
                    << s->getMaxCap() << ")\n";
        }
        else
          std::cout << "Session is full.\n"; 
      }

      // ================= OPTION 8 =================
      else if(choice == 8) {
        // Drops member from session by ID
        std::string id;
        std::cout << "Enter session ID: ";
        std::cin >> id;

        FitnessSession* s = findById(sessions, id);

        if(!s) {
          std::cout << "Session not found.\n";
        }
        else if(s->drop()) {
          std::cout << "Dropped successfully. ("
                    << s->getEnrolled() << "/"
                    << s->getMaxCap() << ")\n";
        }
        else 
          std::cout << "No enrollments to drop.\n";
      }

      // ================= OPTION 9 =================
      else if(choice == 9) {
        // Shows most popular session
        FitnessSession* s = mostPopular(sessions);
        s->display();
      }

      // ================= OPTION 10 =================
      else if(choice == 10) {
        // Displays instructor count (static)
        std::cout << "Active instructors on record: " << Instructor::getInstructorCount() << "\n"; 
      }

      // ================= OPTION 11 =================
      else if(choice == 11) {
        // Displays member count (static)
        std::cout << "Active members on record: " << Member::getMemberCount() << "\n";
      }
    }
    catch(const std::exception& e) {
      std::cout << "Error: " << e.what() << "\n";
    }
  }
  // ================= CLEANUP =================


  for (FitnessSession* s : sessions) {
      delete s;
    }

    /*
      Dynamically alloated memory must be freed manully because all
      sessions were created using 'new'. Without this loop memory leaks
      would occur since the vector only stores pointers, not objects.
    */

  return 0;
}