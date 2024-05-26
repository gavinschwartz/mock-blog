#ifndef BLOGPOST_HPP // If not defined BLOGPOST_HPP, define it
#define BLOGPOST_HPP // Define BLOGPOST_HPP

#include <ctime> // Include the ctime library for time-related functions

class BlogPost // Define a class called BlogPost
{
public:
    char text[128];    // Public member variable to store text, with a maximum length of 128 characters
    char userName[64]; // Public member variable to store the user name, with a maximum length of 64 characters
    time_t timeStamp;  // Public member variable to store the timestamp

    // Constructor - called automatically when creating the object
    BlogPost()
    {
        timeStamp = time(0); // Initialize timeStamp to the current time
    }

    // Returns a character pointer as a string
    const char *getPrintTime() const // Marked as const to indicate it doesn't modify any member variables
    {
        char *printTime = asctime(localtime(&timeStamp)); // Convert timeStamp to a string representation of local time
        // Remove the newline character added by asctime
        if (printTime[strlen(printTime) - 1] == '\n') // Check if the last character is a newline
        {
            printTime[strlen(printTime) - 1] = '\0'; // Replace the newline character with a null terminator
        }
        return printTime; // Return the formatted time string
    }
};
#endif // End of the BLOGPOST_HPP definition