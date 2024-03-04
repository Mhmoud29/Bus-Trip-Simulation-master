#pragma once

class Time {
private:
    int totalHours;
    int totalMinutes;

public:
    // Constructors
    Time();
    Time(int totalHours, int totalMinutes);

    // Getters
    int getTotalHours();
    int getTotalMinutes();

    // Setters
    void setTotalHours(int totalHours);
    void setTotalMinutes(int totalMinutes);

    // Member functions
    void incrementTotalHours();
    void incrementTotalMinutes();
    int toTotalMinutes();
    void fromTotalMinutes(int totalMins);
    bool isTotalHoursInRange(int rangeStart, int rangeEnd);
 
    // Operator overloading
    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;

    Time operator+(int minutesToAdd) const;
    Time operator+(const Time& otherTime) const;
    Time operator-(const Time& otherTime) const;

    bool operator>=(int minutesThreshold);
    bool operator>(const Time& otherTime) const;
    Time operator=(const Time& otherTime) const;
  
};
