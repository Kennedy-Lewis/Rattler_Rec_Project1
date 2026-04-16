[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/j5Td71SE)
# Integration Project 1: Rattler Rec
### Campus Recreation Center Management System

**Course:** COP 3330 — Introduction to Object-Oriented Programming  
**Institution:** Florida A&M University — College of Science & Technology  
**Chapters:** 9 (Custom Classes) · 10 (Inheritance & Runtime Polymorphism)  
**Language:** C++20  
**Submission:** Individual — via GitHub Classroom

---

## Table of Contents

1. [Project Overview](#project-overview)
2. [Learning Objectives](#learning-objectives)
3. [Domain Scenario](#domain-scenario)
4. [System Architecture](#system-architecture)
5. [Part 1 — Custom Support Classes](#part-1-custom-support-classes-chapter-9)
6. [Part 2 — The FitnessSession Hierarchy](#part-2-the-fitnesssession-hierarchy-chapter-10)
7. [Part 3 — Polymorphic Operations](#part-3-polymorphic-operations-chapter-10)
8. [Part 4 — Interactive Dashboard](#part-4-the-interactive-dashboard-integration)
9. [Technical Requirements](#technical-requirements)
10. [Test Case Documentation](#test-case-documentation)
11. [Mastery Rubric](#mastery-rubric)
12. [Submission](#submission)

---

## Project Overview

Florida A&M University's campus recreation center — Rattler Rec — offers group fitness classes, personal training sessions, and open gym time to students, faculty, and staff. Managing this facility means tracking instructors and members, scheduling sessions, and calculating drop-in fees. Your task is to build the software system behind Rattler Rec using the two chapters at the heart of this course.

Chapter 9 introduced custom class design: protecting data with private members, validating input through set functions, sharing class-wide information with static members, and building objects from smaller objects through composition. In this project those skills produce three standalone support classes — `TimeSlot`, `Instructor`, and `Member` — that model the real-world entities any scheduling system depends on.

Chapter 10 showed how inheritance allows a family of related types to share a common interface while varying their behavior. Here those skills produce a `FitnessSession` hierarchy: an abstract base class that defines what every session must do, and three concrete derived classes that each do it differently. The Chapter 9 support classes do not disappear — they become data members inside the Chapter 10 hierarchy through composition, so the two chapters integrate naturally rather than sitting side by side.

> **Learning Goal:** Design and implement clean, encapsulated support classes using Chapter 9 techniques, then build a polymorphic inheritance hierarchy using Chapter 10 techniques that depends on those support classes — integrating both chapters into a single, working system.

---

## Learning Objectives

### Chapter 9 — Custom Classes

- Design classes with **private data members** and enforce encapsulation through public get and set functions that validate all input before assigning it.
- Implement **constructors with default arguments** and understand how they initialize object state without requiring every value from the caller.
- **Separate a class's interface** (`.h` header file) from its implementation (`.cpp` source file) to support reuse and compilation efficiency.
- Use **static data members and static member functions** to track class-wide state — specifically, the total number of active instructors and members currently registered.
- Build objects through **composition** — storing `Instructor` and `TimeSlot` objects as data members inside `FitnessSession` — and understand how the base-class initializer list initializes composed objects.

### Chapter 10 — Inheritance & Runtime Polymorphism

- Design an **abstract base class** with pure virtual functions that declare a required interface without providing an implementation.
- Implement **concrete derived classes** that override pure virtual functions with type-specific behavior, using the `override` keyword to catch signature mismatches at compile time.
- Declare a **virtual destructor** in the base class and explain why it is required for safe deletion of derived-class objects through a base-class pointer.
- Store heterogeneous derived-class objects in a **collection of base-class pointers** and process them polymorphically without knowing their specific types at runtime.
- Apply **programming to an interface** — writing utility functions that operate on the abstract `FitnessSession` type rather than on any derived type directly.

---

## Domain Scenario

Rattler Rec offers three types of fitness sessions each week:

**Group Fitness Class** — An instructor-led session open to multiple participants. Each class has a name (e.g., "HBCU Zumba", "Rattler Yoga"), a difficulty level from 1 to 5, a maximum capacity, and an assigned instructor. The drop-in fee is **$3.00 × difficulty level**, so a Level 3 class costs $9.00.

**Personal Training Session** — A one-on-one appointment between a certified trainer and a registered member. The session fee is **$15.00 base plus $5.00 for each year of the trainer's experience**. More experienced trainers command a higher rate.

**Open Gym Session** — Unstructured time in a specific equipment area (Cardio, Weights, or Courts). Monitored sessions where a certified instructor is present on the floor are **free**. Unmonitored sessions carry a **$2.00 drop-in fee**.

All three types share common data — a session ID, a `TimeSlot`, and a maximum capacity — and all three must support the same core operations: displaying full session details, calculating the drop-in fee, and reporting the session type as a string. These shared properties and operations belong in the abstract base class. Everything specific to each format belongs in the derived class.

The support classes (`TimeSlot`, `Instructor`, `Member`) are designed and implemented first using pure Chapter 9 techniques. They have no knowledge of inheritance or polymorphism. Once working, they are incorporated into the Chapter 10 hierarchy through composition.

---

## System Architecture

```
  ┌───────────────┐   ┌────────────────────┐   ┌─────────────────────┐
  │  TimeSlot     │   │   Instructor       │   │    Member           │
  │───────────────│   │────────────────────│   │─────────────────────│
  │ m_dayOfWeek   │   │ m_instructorId     │   │ m_studentId         │
  │ m_startHour   │   │ m_name             │   │ m_name              │
  │ m_startMin    │   │ m_certification    │   │ m_membershipType    │
  │ m_endHour     │   │ m_yearsExp         │   │ m_sessionsAttended  │
  │ m_endMin      │   │ ── static ──       │   │ ── static ──        │
  │───────────────│   │ s_instructorCount  │   │ s_memberCount       │
  │ toString()    │   │────────────────────│   │─────────────────────│
  │ getDuration() │   │ get / set funcs    │   │ get / set funcs     │
  │ overlaps()    │   │ getCount() static  │   │ getCount() static   │
  └───────┬───────┘   └────────┬───────────┘   └─────────┬───────────┘
          │ composed into      │ composed into            │ composed into
          ▼                    ▼                          ▼
  ┌──────────────────────────────────────────────────────────────────┐
  │            FitnessSession   (abstract base class)                │
  │──────────────────────────────────────────────────────────────────│
  │  # m_sessionId : string                                          │
  │  # m_slot      : TimeSlot         ← composition                 │
  │  # m_maxCap    : int                                             │
  │  # m_enrolled  : int                                             │
  │──────────────────────────────────────────────────────────────────│
  │  + virtual ~FitnessSession()                                     │
  │  + pure virtual display() const = 0                             │
  │  + pure virtual calcFee() const = 0                             │
  │  + pure virtual getSessionType() const = 0                      │
  │  + enroll() / drop() / isFull() / accessors                     │
  └────────────────────────┬─────────────────────────────────────────┘
        ┌──────────────────┼──────────────────┐
        ▼                  ▼                  ▼
  ┌──────────────┐  ┌──────────────────┐  ┌──────────────────┐
  │ GroupFitness │  │ PersonalTraining │  │ OpenGymSession   │
  │   Class      │  │──────────────────│  │──────────────────│
  │──────────────│  │ m_trainer:       │  │ m_areaName       │
  │ m_className  │  │   Instructor     │  │ m_isMonitored    │
  │ m_instructor:│  │   (composed)     │  │──────────────────│
  │   Instructor │  │ m_client:        │  │ display()        │
  │   (composed) │  │   Member         │  │ calcFee()        │
  │ m_difficulty │  │   (composed)     │  │ getSessionType() │
  │──────────────│  │──────────────────│  └──────────────────┘
  │ display()    │  │ display()        │
  │ calcFee()    │  │ calcFee()        │
  │ getType()    │  │ getSessionType() │
  └──────────────┘  └──────────────────┘
```

---

## Part 1: Custom Support Classes (Chapter 9)

> **Concepts covered:** Encapsulation · private data members · validated get/set functions · constructors with default arguments · static data members and functions · interface/implementation separation

Build all three support classes **before** writing any part of the inheritance hierarchy. Each class must have its interface in a `.h` header file and its implementation in a separate `.cpp` source file — this separation is a graded requirement, not a style suggestion.

**Comment requirement:** Every class must have a file-level block comment in both the `.h` and `.cpp` files (class name, description, author, date). Every member function must have an inline comment directly above it describing what it does. Every set function must have a comment explaining what values it rejects and why.

---

### 1.1 — TimeSlot

A `TimeSlot` represents a single scheduled block of time. It is immutable once constructed and will later be stored by value inside `FitnessSession` as the `m_slot` data member.

**Data members (private):**

| Member | Type | Constraints |
|---|---|---|
| `m_dayOfWeek` | `std::string` | Must be a valid day name ("Monday"–"Sunday"); throw `std::invalid_argument` on construction if invalid |
| `m_startHour` | `int` | 0–23 |
| `m_startMin` | `int` | 0–59 |
| `m_endHour` | `int` | 0–23 |
| `m_endMin` | `int` | 0–59; end time must be strictly after start time |

**Constructor:**
```cpp
TimeSlot(std::string day, int startHour, int startMin, int endHour, int endMin);
```

**Required member functions:**

| Function | Description |
|---|---|
| `std::string toString() const` | Returns a formatted string, e.g. `"Monday 10:00–11:30"` |
| `int getDurationMins() const` | Returns total minutes from start to end, e.g. `90` |
| `bool overlaps(const TimeSlot& other) const` | Returns `true` if both slots share the same day and any overlapping minutes |
| Accessors for all fields | No setters — `TimeSlot` is immutable once constructed |

> **Why immutable?** A `TimeSlot` is a fact about when something happens. Allowing it to change after construction could silently create scheduling conflicts. Immutability makes the object safe to pass around and store in multiple places without defensive copying.

---

### 1.2 — Instructor

An `Instructor` represents a fitness professional registered with Rattler Rec. Use a static data member to track how many `Instructor` objects currently exist.

**Data members (private):**

| Member | Type | Constraints |
|---|---|---|
| `m_instructorId` | `std::string` | e.g. `"INS-001"`; must not be empty |
| `m_name` | `std::string` | Must not be empty |
| `m_certification` | `std::string` | Must be `"Group"`, `"Personal"`, or `"Both"` |
| `m_yearsExp` | `int` | Must be >= 0 |
| `s_instructorCount` | `static int` | Incremented in every constructor body; decremented in destructor |

**Constructor:**
```cpp
Instructor(std::string id, std::string name, std::string certification, int yearsExp = 0);
```

**Required member functions:**

| Function | Description |
|---|---|
| Getters for all data members | No public setters for `m_instructorId` or `m_name` |
| `void setCertification(const std::string& cert)` | Validates against the three allowed values before assigning; prints an error message and does not assign if invalid |
| `void setYearsExp(int years)` | Rejects negative values with an error message; does not throw |
| `static int getInstructorCount()` | Returns the current value of `s_instructorCount` |
| `void display() const` | Prints all instructor data in a clean, labeled format |

> **Static member reminder:** Declare `s_instructorCount` with the `static` keyword in the header. Define it in the `.cpp` with `int Instructor::s_instructorCount = 0;` — this line must appear exactly once, in the `.cpp`, never in the header. Increment it at the end of every constructor body; decrement it in the destructor.

---

### 1.3 — Member

A `Member` is a Rattler Rec registrant — a student, faculty member, or staff employee. Use the same static counter pattern as `Instructor`.

**Data members (private):**

| Member | Type | Constraints |
|---|---|---|
| `m_studentId` | `std::string` | e.g. `"N01234567"`; must not be empty |
| `m_name` | `std::string` | Must not be empty |
| `m_membershipType` | `std::string` | Must be `"Student"`, `"Faculty"`, or `"Staff"` |
| `m_sessionsAttended` | `int` | Starts at 0; incremented by `recordAttendance()` |
| `s_memberCount` | `static int` | Same increment/decrement pattern as `Instructor` |

**Constructor:**
```cpp
Member(std::string id, std::string name, std::string membershipType);
```

**Required member functions:**

| Function | Description |
|---|---|
| Getters for all data members | |
| `void setMembershipType(const std::string& type)` | Validates against the three allowed values before assigning |
| `void recordAttendance()` | Increments `m_sessionsAttended` by 1 |
| `static int getMemberCount()` | Returns `s_memberCount` |
| `void display() const` | Prints all member data in a labeled format |

---

## Part 2: The FitnessSession Hierarchy (Chapter 10)

> **Concepts covered:** Abstract base class · pure virtual functions · virtual destructor · `override` keyword · constructor chaining with composed objects · runtime polymorphism via base-class pointers

**Comment requirement:** The base class header must include a block comment explaining why `FitnessSession` is abstract and what the three pure virtual functions represent. Each overridden function in every derived class must have an inline comment explaining the specific fee formula or display format that class uses.

---

### 2.1 — FitnessSession (Abstract Base Class)

`FitnessSession` cannot be instantiated directly — you can never create a plain `FitnessSession` object, only one of its three concrete subtypes. It defines the contract every session must fulfill.

**Data members (protected):**

| Member | Type | Constraints |
|---|---|---|
| `m_sessionId` | `std::string` | e.g. `"RR-GFC-001"` |
| `m_slot` | `TimeSlot` | Stored by value (composition); passed to base constructor |
| `m_maxCap` | `int` | Must be >= 1 |
| `m_enrolled` | `int` | Starts at 0 |

**Constructor:**
```cpp
FitnessSession(std::string sessionId, TimeSlot slot, int maxCapacity);
```

The `TimeSlot` is passed by value and stored by value. The session owns its time slot and that slot should not change if the caller's `TimeSlot` object is later modified.

**Pure virtual functions (must be overridden in every derived class):**
```cpp
virtual void display() const = 0;          // Print all session details
virtual double calcFee() const = 0;        // Return the drop-in fee
virtual std::string getSessionType() const = 0;  // Return the type label
```

**Non-virtual member functions (implemented in base, inherited by all):**

| Function | Description |
|---|---|
| `bool enroll()` | Increments `m_enrolled` if not full; returns `true` on success, `false` if full |
| `bool drop()` | Decrements `m_enrolled` if > 0; returns `true` on success |
| `bool isFull() const` | Returns `true` if `m_enrolled >= m_maxCap` |
| `std::string getSessionId() const` | |
| `int getMaxCap() const` | |
| `int getEnrolled() const` | |
| `const TimeSlot& getSlot() const` | Returns a `const` reference to the composed `TimeSlot` |

**Virtual destructor:**
```cpp
virtual ~FitnessSession();
```

Declare it in the header and define it (even if the body is empty) in the `.cpp`. Without a virtual destructor, deleting a derived-class object through a `FitnessSession*` will only call the base destructor — the derived class's destructor is silently skipped, which can leak resources. Add a comment in your code explaining this.

---

### 2.2 — GroupFitnessClass (Derived Class)

A group fitness class is instructor-led and open to multiple participants. `GroupFitnessClass` uses composition at two levels: it inherits a `TimeSlot` from the base and additionally owns an `Instructor` as a private data member.

**Additional data members (private):**

| Member | Type | Constraints |
|---|---|---|
| `m_className` | `std::string` | e.g. `"HBCU Zumba"`, `"Rattler Yoga"` |
| `m_instructor` | `Instructor` | Stored by value (composition) |
| `m_difficulty` | `int` | 1–5; validated in constructor |

**Constructor:**
```cpp
GroupFitnessClass(std::string sessionId, TimeSlot slot, int maxCap,
                  std::string className, Instructor instructor, int difficulty);
```

**Fee formula — comment required:**
```cpp
// Drop-in fee = $3.00 per difficulty level
// Level 1 = $3.00, Level 3 = $9.00, Level 5 = $15.00
double calcFee() const override { return m_difficulty * 3.0; }
```

**`display()` output format:**
```
[ GROUP FITNESS ] RR-GFC-001
  Time       : Monday 10:00-11:30  (90 min)
  Class      : HBCU Zumba
  Difficulty : 3 / 5
  Instructor : Dr. Maya Rivers  (Group, 8 yrs)
  Capacity   : 12 / 20 enrolled
  Drop-in Fee: $9.00
```

---

### 2.3 — PersonalTraining (Derived Class)

A personal training session pairs one `Member` with one `Instructor`. `PersonalTraining` has the deepest composition in the hierarchy: it inherits a `TimeSlot` from the base and additionally owns both an `Instructor` and a `Member` as private data members.

**Additional data members (private):**

| Member | Type | Notes |
|---|---|---|
| `m_trainer` | `Instructor` | Stored by value |
| `m_client` | `Member` | Stored by value |

**Constructor:**
```cpp
PersonalTraining(std::string sessionId, TimeSlot slot,
                 Instructor trainer, Member client);
```

> Max capacity is always 1 for a personal training session. Pass `1` to the base-class constructor and add a comment explaining why.

**Fee formula — comment required:**
```cpp
// Fee = $15.00 base + $5.00 per year of trainer experience
// Example: 6 years experience → $15 + $30 = $45.00
double calcFee() const override {
    return 15.0 + (m_trainer.getYearsExp() * 5.0);
}
```

**`display()` output format:**
```
[ PERSONAL TRAINING ] RR-PT-004
  Time    : Wednesday 14:00-15:00  (60 min)
  Trainer : Coach Darius Webb  (Personal, 6 yrs)
  Client  : Tiara Simmons  [Student]
  Fee     : $45.00
```

---

### 2.4 — OpenGymSession (Derived Class)

An open gym session reserves an equipment area for drop-in use. The fee depends entirely on whether a certified instructor is monitoring the floor.

**Additional data members (private):**

| Member | Type | Constraints |
|---|---|---|
| `m_areaName` | `std::string` | Must be `"Cardio"`, `"Weights"`, or `"Courts"` |
| `m_isMonitored` | `bool` | `true` = instructor present; `false` = unsupervised |

**Constructor:**
```cpp
OpenGymSession(std::string sessionId, TimeSlot slot, int maxCap,
               std::string areaName, bool isMonitored);
```

**Fee formula — comment required:**
```cpp
// Monitored sessions are free (included in membership)
// Unmonitored sessions carry a $2.00 drop-in charge
double calcFee() const override {
    return m_isMonitored ? 0.0 : 2.0;
}
```

**`display()` output format:**
```
[ OPEN GYM ] RR-OG-007
  Time      : Friday 06:00-08:00  (120 min)
  Area      : Weights
  Monitored : No
  Capacity  : 5 / 30 enrolled
  Drop-in Fee: $2.00
```

---

## Part 3: Polymorphic Operations (Chapter 10)

> **Concepts covered:** Runtime polymorphism · virtual dispatch · programming to an interface · heterogeneous collections

Write the following free functions in `utilities.h` and `utilities.cpp`. Every function receives a `const std::vector<FitnessSession*>&` and processes it exclusively through the `FitnessSession` interface. **Never cast to a derived type inside these functions.** Each function must have a block comment above it explaining what it does and what it returns.

---

### 3.1 — `printSchedule`

```cpp
void printSchedule(const std::vector<FitnessSession*>& sessions);
```

Iterates the collection and calls `display()` on each session. Although the vector holds `FitnessSession*` pointers, the correct overridden `display()` for each derived type is called at runtime — this is virtual dispatch in action.

---

### 3.2 — `totalRevenue`

```cpp
double totalRevenue(const std::vector<FitnessSession*>& sessions);
```

Sums `calcFee()` across all sessions and returns the total. Each session automatically computes its own type-specific fee through virtual dispatch — the function does not know or care which type each session is.

```
Total potential revenue: $56.00
```

---

### 3.3 — `filterByType`

```cpp
std::vector<FitnessSession*> filterByType(const std::vector<FitnessSession*>& sessions,
                                          const std::string& type);
```

Returns a new vector containing only sessions whose `getSessionType()` matches `type`. The returned vector still holds base-class pointers — no casts required or permitted.

---

### 3.4 — `findById`

```cpp
FitnessSession* findById(const std::vector<FitnessSession*>& sessions,
                         const std::string& id);
```

Returns the pointer to the session whose `getSessionId()` matches `id`, or `nullptr` if not found. The dashboard uses this function to support enroll and drop by session ID.

---

### 3.5 — `mostPopular`

```cpp
FitnessSession* mostPopular(const std::vector<FitnessSession*>& sessions);
```

Returns a pointer to the session with the highest current enrollment. If multiple sessions are tied, return the first one encountered. Throws `std::runtime_error` with a descriptive message if the vector is empty. Calling `display()` on the returned pointer will print the correct type-specific layout through virtual dispatch.

---

## Part 4: The Interactive Dashboard (Integration)

> **Concepts covered:** Integrating all Chapter 9 and Chapter 10 features into a cohesive, menu-driven application that demonstrates runtime polymorphism in a realistic workflow.

Write `main()` to implement the Rattler Rec front desk terminal. Store all sessions in a `std::vector<FitnessSession*>`. Loop until the user selects Exit. Allocate all session objects with `new` and `delete` every pointer before the program exits. Add a comment at the cleanup site explaining why this is necessary.

**Comment requirement:** The `main()` function must have a file-level block comment explaining the program's purpose and the data structure used to store sessions. Each menu option handler must have an inline comment describing what it does.

```
╔═══════════════════════════════════════════════════════╗
║         RATTLER REC — FRONT DESK TERMINAL            ║
╠═══════════════════════════════════════════════════════╣
║  1.  Add Group Fitness Class                         ║
║  2.  Add Personal Training Session                   ║
║  3.  Add Open Gym Session                            ║
║  4.  View Full Schedule                              ║
║  5.  View Total Potential Revenue                    ║
║  6.  Filter Schedule by Session Type                 ║
║  7.  Enroll in a Session (by ID)                     ║
║  8.  Drop from a Session (by ID)                     ║
║  9.  View Most Popular Session                       ║
║  10. View Instructor Count  (static member)          ║
║  11. View Member Count      (static member)          ║
║  0.  Exit                                            ║
╚═══════════════════════════════════════════════════════╝
```

**Requirements:**

1. **Options 1–3** prompt for all required fields (including `TimeSlot` day, start time, and end time), construct the appropriate derived-class object with `new`, and push the pointer onto the schedule vector.
2. **Option 4** calls `printSchedule()`, which triggers polymorphic `display()` on every object in the collection.
3. **Options 7 and 8** use `findById()` to locate the session by ID, then call `enroll()` or `drop()` on the returned base-class pointer.
4. **Options 10 and 11** call `Instructor::getInstructorCount()` and `Member::getMemberCount()` and print the current values. These calls must work correctly regardless of how many sessions have been added — the counts reflect the total number of `Instructor` and `Member` objects in existence, not the number of sessions.
5. **All user input must be validated.** Empty strings, invalid day names, out-of-range hours and minutes, difficulty values outside 1–5, unrecognized area names, and session IDs that don't exist in the vector must each produce a clear, specific error message followed by a re-prompt. The program must never crash on bad input.
6. **Before program exit**, `delete` every `FitnessSession*` in the vector and add a comment explaining why this cleanup is necessary.

---

## Technical Requirements

### File Organization

```
rattler_rec/
├── TimeSlot.h
├── TimeSlot.cpp
├── Instructor.h
├── Instructor.cpp
├── Member.h
├── Member.cpp
├── FitnessSession.h
├── FitnessSession.cpp
├── GroupFitnessClass.h
├── GroupFitnessClass.cpp
├── PersonalTraining.h
├── PersonalTraining.cpp
├── OpenGymSession.h
├── OpenGymSession.cpp
├── utilities.h
├── utilities.cpp
├── main.cpp
└── README.md          ← this file, completed with your submission artifacts
```

### Compilation

```bash
g++ -std=c++20 -Wall -Wextra -o rattler_rec *.cpp
```

Your project must compile with **no errors and no warnings** under these flags before you submit.

### Comment Requirements

Every source file must include:

- **File-level block comment** at the top of both `.h` and `.cpp` files:
  ```cpp
  /**
   * ClassName.h
   * Brief description of what this class represents and its role in the system.
   * Author: Your Name
   * Date:   YYYY-MM-DD
   */
  ```
- **Function-level comment** directly above every member function definition in the `.cpp`:
  ```cpp
  // Sets the difficulty level. Rejects values outside [1, 5] and prints
  // an error message without modifying the data member.
  void GroupFitnessClass::setDifficulty(int level) { ... }
  ```
- **Inline comments** on any non-obvious logic — fee formulas, validation conditions, the virtual destructor, the static member definition, and the memory cleanup loop in `main()`.

### Additional Requirements

- All non-modifying member functions must be declared `const`.
- Static data members must be **defined in the `.cpp` file**, never in the header.
- No global variables.
- No raw owning pointers outside of `main()` — all `new` calls are in `main()` and all matching `delete` calls are in `main()` before exit.

---

## Test Case Documentation

Run all 20 test cases below and record your results before submitting. All tests must pass. Submit the completed table as a PDF (see [Submission](#submission)).

> **Instructions:** Run tests top to bottom. Tests with a prerequisite depend on earlier tests — complete those first. Record the key identifying lines of your actual terminal output. Mark each test **P** (Pass) or **F** (Fail).

### Functional Test Cases

| TC # | Feature / Option | Input / Steps | Expected Output | Actual Output | P/F |
|:---:|---|---|---|---|:---:|
| TC-01 | Add Group Fitness (Opt. 1) | ID: RR-GFC-001, Monday 10:00–11:30, Class: HBCU Zumba, Instructor: INS-001 / Dr. Maya Rivers / Group / 8 yrs, Difficulty: 3, Cap: 20 | "Session added successfully!" · Option 4 shows `[ GROUP FITNESS ] RR-GFC-001` with all correct fields | | |
| TC-02 | Add Personal Training (Opt. 2) | ID: RR-PT-002, Wednesday 14:00–15:00, Trainer: INS-002 / Coach Darius Webb / Personal / 6 yrs, Client: N01234567 / Tiara Simmons / Student | "Session added successfully!" · `[ PERSONAL TRAINING ] RR-PT-002` · Fee: $45.00 (= 15 + 6×5) | | |
| TC-03 | Add Open Gym (Opt. 3) | ID: RR-OG-003, Friday 06:00–08:00, Area: Weights, Monitored: No, Cap: 30 | "Session added successfully!" · `[ OPEN GYM ] RR-OG-003` · Drop-in Fee: $2.00 | | |
| TC-04 | View Full Schedule (Opt. 4) | After TC-01, TC-02, TC-03 | All three sessions display in order with correct type tags `[ GROUP FITNESS ]`, `[ PERSONAL TRAINING ]`, `[ OPEN GYM ]` | | |
| TC-05 | Total Revenue (Opt. 5) | Schedule: TC-01 ($9.00) + TC-02 ($45.00) + TC-03 ($2.00) | "Total potential revenue: $56.00" | | |
| TC-06 | Filter — Group Fitness (Opt. 6) | Type: `Group Fitness` | Only TC-01 displayed | | |
| TC-07 | Filter — Open Gym (Opt. 6) | Type: `Open Gym` | Only TC-03 displayed | | |
| TC-08 | Enroll in Session (Opt. 7) | Session ID: `RR-GFC-001` | "Enrolled successfully. (1/20)" · Option 4 confirms Capacity: 1 / 20 | | |
| TC-09 | Drop from Session (Opt. 8) | Prereq: TC-08 (1 enrolled) · Session ID: `RR-GFC-001` | "Dropped successfully. (0/20)" | | |
| TC-10 | Most Popular (Opt. 9) | Enroll 3 in RR-GFC-001, 1 in RR-OG-003, then select opt. 9 | Displays RR-GFC-001 (highest enrollment = 3) with all correct fields | | |
| TC-11 | Instructor Count (Opt. 10) | After adding TC-01 and TC-02 (2 instructors created) | "Active instructors on record: 2" | | |
| TC-12 | Member Count (Opt. 11) | After adding TC-02 (1 member created) | "Active members on record: 1" | | |
| TC-13 | TimeSlot format in display | Select opt. 4 after TC-01 is added | Time line shows `Monday 10:00-11:30  (90 min)` — correct day, `HH:MM-HH:MM`, and duration | | |

### Edge Case & Error Handling Tests

| TC # | Feature / Option | Input / Steps | Expected Output | Actual Output | P/F |
|:---:|---|---|---|---|:---:|
| TC-14 | Invalid day name (Opt. 1 or 3) | Enter day: `Funday` · then re-enter: `Monday` | Error message rejecting "Funday" · re-prompt shown · session added on second valid input | | |
| TC-15 | End time before start (Opt. 1 or 3) | Start: 14:00 · End: 13:00 · then re-enter valid end | Error: end must be after start · re-prompt · session added after correction | | |
| TC-16 | Difficulty out of range (Opt. 1) | Try: `0` · then `-1` · then `6` · then valid: `4` | Error message for each invalid value · session added only on valid input | | |
| TC-17 | Enroll — unknown ID (Opt. 7) | Session ID: `RR-FAKE-999` | "Session not found." · program does not crash · returns to menu | | |
| TC-18 | Enroll past capacity (Opt. 7) | Add Open Gym with cap 2 · enroll twice (success) · enroll a third time | First two: "Enrolled successfully." · Third: "Session is full." · program does not crash | | |
| TC-19 | Drop with zero enrollment (Opt. 8) | New session with 0 enrolled · select opt. 8 on that session | "No enrollments to drop." · enrollment stays 0 · program does not crash | | |
| TC-20 | Most popular — empty schedule (Opt. 9) | No sessions added · select opt. 9 | `std::runtime_error` caught · descriptive message printed · program continues running | | |

---

## Mastery Rubric

| Category | ✅ Mastered | ❌ Not Yet Mastered |
|---|---|---|
| **Custom Classes (Ch. 9)** | `TimeSlot`, `Instructor`, and `Member` have private data members with public get/set functions that validate all input; static member correctly defined in `.cpp`; `Instructor` default argument `yearsExp = 0` present; interface/implementation separated into `.h` and `.cpp` for every class | Data members are public or exposed without validation; static member defined in header causing linker errors; all code in a single file |
| **Composition (Ch. 9 → 10)** | `TimeSlot` stored by value in `FitnessSession`; `Instructor` stored by value in `GroupFitnessClass` and `PersonalTraining`; `Member` stored by value in `PersonalTraining`; all composed objects initialized via the base-class initializer list | Composition replaced by global variables or raw pointers; composed objects not initialized through the initializer list; `TimeSlot` or `Instructor` accessed globally |
| **Inheritance Hierarchy (Ch. 10)** | `FitnessSession` is abstract with three pure virtual functions; all three derived classes override every pure virtual function using the `override` keyword; virtual destructor declared in header and defined in `.cpp`; derived constructors chain correctly to the base | No abstract base class; `override` keyword absent; no virtual destructor; derived constructors duplicate base-class data initialization |
| **Runtime Polymorphism (Ch. 10)** | Sessions stored as `FitnessSession*` in a single vector; `display()`, `calcFee()`, and `getSessionType()` called correctly through the base pointer; all five utility functions work without any cast to a derived type; correct derived function called at runtime for each session type | Sessions stored by derived type in separate vectors; `if`/`else` chains or `dynamic_cast` used to select behavior instead of virtual dispatch |
| **Dashboard & Integration** | All 11 menu options function correctly; options 10 and 11 call static member functions and report correct counts; `findById()` used in options 7 and 8; all pointers deleted before exit; all user input validated with re-prompting | One or more menu options crash or produce wrong output; static counts always show 0; no memory cleanup; bad input crashes the program |
| **Comments** | File-level block comment in every `.h` and `.cpp`; function-level comment above every member function definition; inline comments on fee formulas, virtual destructor explanation, static member definition, and memory cleanup loop | Missing file-level comments; member functions undocumented; no explanation of virtual destructor, static member, or memory cleanup |
| **Test Cases & Video** | All 20 test cases documented with actual output; all 20 marked Pass; PDF submitted in repo; video link in README is accessible, shows compilation with no warnings, all 11 options demonstrated with narration, at least 4 TC numbers called out including 2 edge cases, single continuous recording 8–12 min | Failing tests submitted; PDF missing; video link broken or private; options skipped; no narration; recording is edited or shows a different program than what was submitted |
| **Code Quality** | Compiles with `g++ -std=c++20 -Wall -Wextra` and no warnings; files organized as specified; no global variables; all `new` allocations matched with `delete` in `main()`; class diagram committed to repo | Compilation errors or warnings; files missing or misnamed; global variables used; memory not freed |

---

## Submission

Complete this section before your final push to GitHub. Your repository must contain all source files, the completed README (this file), the test cases PDF, and the class diagram image.

---

### Class Diagram

> Replace the placeholder below with your actual class diagram image. Commit the image file to your repository and update the path accordingly.

```
![Class Diagram](diagram.png)
```

Your diagram must show:
- All three support classes (`TimeSlot`, `Instructor`, `Member`) with data members and member function signatures
- `FitnessSession` as the abstract base class with pure virtual functions marked
- All three derived classes with their additional data members and overriding functions
- Composition relationships (arrows or labels) connecting support classes to the sessions that contain them
- Inheritance arrows from each derived class to `FitnessSession`

---

### Program Demonstration Video

> Paste your video link below. Make sure it is publicly accessible (YouTube unlisted, Google Drive with link sharing on, or OneDrive).

**Video Link:** <!-- paste URL here -->

Your video must be a **single, uncut screen recording** approximately 8–12 minutes long covering the following in order:

1. State your name and project title aloud.
2. Run the compilation command and show that it produces no errors or warnings:
   ```bash
   g++ -std=c++20 -Wall -Wextra -o rattler_rec *.cpp
   ```
3. Walk through all 11 menu options with at least one full operation each. Narrate what each option does and what the output shows.
4. Call out and demonstrate at least **four test cases by number** from the table above, including **at least two edge cases** (TC-14 through TC-20).
5. After adding sessions that include instructors and members, demonstrate **options 10 and 11** showing the live static counts.
6. Exit via option 0 and show the memory-release confirmation output.

| Requirement | Details |
|---|---|
| Format | MP4, MOV, or WebM |
| Audio | Narration required throughout |
| Continuity | Single unbroken session — no pausing, cutting, or restarting |
| Terminal | Full terminal window visible at all times; font size ≥ 14pt |
| Duration | 8–12 minutes |

---

### Test Cases PDF

> Commit your completed test case document to the repository and update the path below.

**Test Cases:** [View Test Cases PDF](test_cases.pdf)

The PDF must show the completed table with **Actual Output** and **P/F** columns filled in for all 20 test cases (TC-01 through TC-20). Every test must be marked **P** before you submit.

---

### Statement of Independent Effort

> Replace this block with your own statement. Minimum 3–5 sentences.

*Write a brief paragraph that:*
1. *Confirms that the submitted code is your own work.*
2. *Describes the most challenging aspect of the project and how you worked through it.*
3. *Explains one design decision you made — for example, why you structured a particular class a certain way, how you handled a specific validation case, or what you considered when deciding what belongs in the base class versus a derived class.*
