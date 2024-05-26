#ifndef BLOGLIST_HPP
#define BLOGLIST_HPP

#include <iostream>
#include <fstream>
#include "BlogPost.hpp"

using namespace std;

class BlogListNode
{
public:
    BlogPost post;      // Member to store the blog post
    BlogListNode *next; // Pointer to the next node in the list

    BlogListNode()
    {
        next = nullptr; // Initialize the next pointer to null
    }
};

class BlogList
{
public:
    BlogListNode *head; // Pointer to the first node in the list
    BlogListNode *tail; // Pointer to the last node in the list

    BlogList()
    {
        head = nullptr; // Initialize the head pointer to null
        tail = nullptr; // Initialize the tail pointer to null
    }

    int getLength()
    {
        BlogListNode *currentNode = head; // Start with the head of the list
        int count = 0;                    // Initialize count to zero
        while (currentNode != nullptr)    // Traverse the list until the end
        {
            count++;                         // Increment count for each node
            currentNode = currentNode->next; // Move to the next node
        }
        return count; // Return the total count of nodes
    }

    void addPost(BlogPost newPost)
    {
        BlogListNode *newNode = new BlogListNode; // Create a new node
        newNode->post = newPost;                  // Set the post in the new node
        if (tail != nullptr)
        {
            tail->next = newNode; // Link the current tail to the new node
        }
        tail = newNode; // Update the tail to the new node

        if (head == nullptr) // If the list was empty
        {
            head = newNode; // Set the head to the new node
        }
    }

    void deletePost(int postIndex)
    {
        if (postIndex < 0 || postIndex >= getLength()) // Check if index is valid
        {
            cout << "Invalid index!" << endl
                 << endl; // Print error message if invalid
            return;       // Exit the function
        }
        BlogListNode *nodeToDelete;
        BlogListNode *previousNode;

        if (postIndex == 0)
        {
            previousNode = nullptr;
            nodeToDelete = head;
            head = nodeToDelete->next; // Update the head pointer
        }
        else
        {
            previousNode = head;                    // Start searching with the head of the list
            for (int i = 0; i < postIndex - 1; i++) // Traverse to the node before the one to delete
            {
                previousNode = previousNode->next; // Move to the next node
            }
            nodeToDelete = previousNode->next;       // The node to delete
            previousNode->next = nodeToDelete->next; // Link previous node to the node after the one to delete
        }

        if (tail == nodeToDelete) // If the tail is the node to delete
        {
            tail = previousNode; // Update the tail
        }

        delete nodeToDelete; // Delete the node
        cout << "Successfully deleted post number " << postIndex << "." << endl
             << endl;
    }

    void printPosts()
    {
        BlogListNode *currentNode = head; // Start with the head of the list
        int printIndex = 0;
        while (currentNode != nullptr) // Traverse the list until the end
        {
            BlogPost currentPost = currentNode->post;                                                                             // Get the current post
            cout << printIndex << "." << "Post by " << currentPost.userName << " at time " << currentPost.getPrintTime() << endl; // Print post details
            cout << endl
                 << currentPost.text << endl
                 << endl; // Print post text
            currentNode = currentNode->next;
            printIndex++;
        }
    }

    void savePostsFile()
    {
        fstream outputFile;                    // File stream for output
        outputFile.open("blog.txt", ios::out); // Open the file for writing

        outputFile << getLength() << endl; // Write the number of posts

        BlogListNode *currentNode = head; // Start with the head of the list
        while (currentNode != nullptr)    // Traverse the list until the end
        {
            BlogPost currentPost = currentNode->post; // Get the current post

            outputFile << currentPost.text << endl;      // Write the post text
            outputFile << currentPost.userName << endl;  // Write the user name
            outputFile << currentPost.timeStamp << endl; // Write the timestamp
            currentNode = currentNode->next;
        }

        outputFile.close(); // Close the file
        cout << "Successfully saved!" << endl;
    }
};

#endif