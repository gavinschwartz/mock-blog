#include <iostream>     // Include the iostream library for input/output operations
#include <cstdlib>      // Include the cstdlib library for general purpose functions
#include "BlogList.hpp" // Include the BlogPost header file
#include "BlogPost.hpp" // Include the BlogPost header file (redundant include)
#include <ctime>        // Include the ctime library for time-related functions
#include <fstream>      // Include the fstream library for file operations

using namespace std; // Use the standard namespace

// Function declarations
void addNewPost(BlogList &blogList);
void printPosts(BlogList &blogList);
void deletePost(BlogList &blogList);
void savePosts(BlogList &blogList);

int main()
{
    // Allocates the memory for blogEntry
    BlogList blogList;     // Create an array to store blog posts
    int blogPostCount = 0; // Initialize the blog post count to 0

    // See if the blog file already exists, by trying to open the file
    fstream inputFile;                   // Create a file stream object
    inputFile.open("blog.txt", ios::in); // Open the blog file in input mode

    // If the file could not be opened, the file does not already exist
    if (!inputFile.is_open())
    {
        inputFile.close(); // Close the input file if it was open
        cout << "blog.txt does not exist, create the file" << endl;

        // Create the new empty output file
        fstream outputFile;                    // Create a file stream object for output
        outputFile.open("blog.txt", ios::out); // Open the blog file in output mode
        outputFile.close();                    // Close the output file

        // Reopen input file
        inputFile.open("blog.txt", ios::in); // Reopen the blog file in input mode
    }
    else
    {
        inputFile >> blogPostCount; // Read the blog post count from the file
    }

    cout << "Blog post count = " << blogPostCount << endl; // Output the blog post count
    inputFile.ignore(1, '\n');                             // Ignore the newline character after the count
    for (int i = 0; i < blogPostCount; i++)
    {
        BlogPost blogPost;
        inputFile.getline(blogPost.text, 128);    // Read the text of each blog post
        inputFile.getline(blogPost.userName, 64); // Read the username of each blog post
        inputFile >> blogPost.timeStamp;          // Read the timestamp of each blog post
        inputFile.ignore(1, '\n');                // Ignore the newline character after the timestamp
        blogList.addPost(blogPost);
    }

    bool exit = false; // Initialize the exit flag to false
    while (!exit)
    {
        cout << "What do you want to do? " << endl;
        cout << "Choose option 1, 2, 3, or 4. " << endl;
        cout << "1 = add a post" << endl
             << "2 = see all posts" << endl
             << "3 = delete a post" << endl
             << "4 = exit" << endl;
        int choice;          // Variable to store the user's choice
        cin >> choice;       // Read the user's choice
        cin.ignore(1, '\n'); // Ignore the newline character after the choice

        switch (choice)
        {
        case 1:
            addNewPost(blogList); // Add a new post
            break;
        case 2:
            printPosts(blogList); // Print all posts
            break;
        case 3:
            deletePost(blogList); // Delete a post
            break;
        case 4:
            savePosts(blogList); // Save posts to the file
            exit = true;         // Set the exit flag to true
            break;
        default:
            cout << "Invalid choice. Please choose 1, 2, 3, or 4." << endl; // Invalid choice message
            break;
        }
    }
    return 0; // End of the main function
}

void addNewPost(BlogList &blogList)
{
    BlogPost newPost; // Create a new blog post

    cout << "Type your post here: " << endl;
    cin.getline(newPost.text, 128); // Read the text of the new post

    cout << "Type your username here: " << endl;
    cin.getline(newPost.userName, 64); // Read the username of the new post

    newPost.timeStamp = time(0); // Set the current time as the timestamp

    blogList.addPost(newPost); // Add the new post to the array
}

void printPosts(BlogList &blogList)
{

    blogList.printPosts();
}

void deletePost(BlogList &blogList)
{
    int postIndex; // Variable to store the index of the post to be deleted
    cout << "Enter the index of the post you want to delete (0 to " << blogList.getLength() - 1 << "): ";
    cin >> postIndex;    // Read the index of the post to be deleted
    cin.ignore(1, '\n'); // Ignore the newline character after the index

    if (postIndex < 0 || postIndex >= blogList.getLength())
    {
        cout << "Invalid index!" << endl; // Invalid index message
        return;                           // Exit the function
    }

    blogList.deletePost(postIndex);

    cout << "Post deleted successfully." << endl
         << endl; // Deletion success message
}

void savePosts(BlogList &blogList)
{
    blogList.savePostsFile();
}
