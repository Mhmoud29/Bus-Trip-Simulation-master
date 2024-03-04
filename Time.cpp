#include "Time.h"

// Default constructor for the Time class
Time::Time() {
    this->totalHours = 4;
    this->totalMinutes = 0;
}

// Parameterized constructor for the Time class
Time::Time(int totalHours, int totalMinutes) {
    this->totalHours = totalHours;
    this->totalMinutes = totalMinutes;
}

// Getter function to retrieve the total hours
int Time::getTotalHours() {
    return this->totalHours;
}

// Getter function to retrieve the total minutes
int Time::getTotalMinutes() {
    return this->totalMinutes;
}

// Setter function to set the total hours
void Time::setTotalHours(int totalHours) {
    this->totalHours = totalHours;
}

// Setter function to set the total minutes
void Time::setTotalMinutes(int totalMinutes) {
    this->totalMinutes = totalMinutes;
}

// Increment total hours by 1
void Time::incrementTotalHours() {
    this->totalHours++;
}

// Increment total minutes by 1, handling rollover to the next hour
void Time::incrementTotalMinutes() {
    // Check if total minutes will roll over to the next hour
    if (this->totalMinutes + 1 == 60) {
        this->totalMinutes = 0;
        this->totalHours++;
        return;
    }
    this->totalMinutes++;
}

// Convert Time object to total minutes
int Time::toTotalMinutes() {
    return this->totalHours * 60 + this->totalMinutes;
}

// Convert total minutes to Time object
void Time::fromTotalMinutes(int totalMins) {
    this->totalHours = totalMins / 60;
    this->totalMinutes = totalMins % 60;
}


// Check if total hours fall within a specified range
bool Time::isTotalHoursInRange(int rangeStart, int rangeEnd) {
    int totalMins = this->totalMinutes + this->totalHours * 60;
    return (totalMins >= rangeStart * 60 && totalMins <= rangeEnd * 60);
}

// Equality comparison operator for Time objects
bool Time::operator==(const Time& other) const {
    return (totalHours == other.totalHours && totalMinutes == other.totalMinutes);
}

bool Time::operator!=(const Time& other) const
{
    return (totalHours != other.totalHours && totalMinutes != other.totalMinutes);
}

// Addition operator to add minutes to a Time object
Time Time::operator+(int minutesToAdd) const {
    // Calculate total hours and total minutes after addition
    int totalHrs = this->totalHours;
    int totalMins = this->totalMinutes + minutesToAdd;
    // Handle rollover of minutes to the next hour
    if (totalMins >= 60) {
        totalHrs += totalMins / 60;
        totalMins = totalMins % 60;
    }
    // Create and return a new Time object
    Time result(totalHrs, totalMins);
    return result;
}

// Addition operator to add two Time objects
Time Time::operator+(const Time& otherTime) const {
    // Calculate total hours and total minutes after addition
    int totalHrs = this->totalHours + otherTime.totalHours;
    int totalMins = this->totalMinutes + otherTime.totalMinutes;
    // Handle rollover of minutes to the next hour
    if (totalMins >= 60) {
        totalHrs += totalMins / 60;
        totalMins = totalMins % 60;
    }
    // Create and return a new Time object
    Time result(totalHrs, totalMins);
    return result;
}

Time Time::operator-(const Time& otherTime) const
{
    // Calculate total hours and total minutes after subtraction
    int totalHrs = this->totalHours - otherTime.totalHours;
    int totalMins = this->totalMinutes - otherTime.totalMinutes;
    // Handle borrowing from hours if minutes are negative
    if (totalMins < 0) {
        totalHrs--;
        totalMins = totalMins + 60;
    }
    // Create and return a new Time object
    Time result(totalHrs, totalMins);
    return result;
}





// Greater-than or equal-to comparison operator with an integer threshold
bool Time::operator>=(int minutesThreshold) {
    return (toTotalMinutes() >= minutesThreshold);
}

// Greater-than comparison operator for Time objects
bool Time::operator>(const Time& otherTime) const {
    // Compare total hours and total minutes
    if (totalHours > otherTime.totalHours)
        return true;
    if (otherTime.totalHours > totalHours)
        return false;
    if (totalMinutes > otherTime.totalMinutes)
        return true;
    return false;
}

// Assignment operator for Time objects
Time Time::operator=(const Time& otherTime) const {
    // Copy total hours and total minutes
    int totalHrs = otherTime.totalHours;
    int totalMins = otherTime.totalMinutes;
    // Create and return a new Time object
    Time result(totalHrs, totalMins);
    return result;
}
