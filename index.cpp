#include <iostream>
#include <string>
using namespace std;

struct BookRequestNode
{
    int studentID;
    string studentName;
    int bookID;
    string bookTitle;
    int priority;
    BookRequestNode* next;
};

class PriorityQueue
{
private:
    BookRequestNode* front;
    BookRequestNode* rear;
    int count;

public:
    PriorityQueue()
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    PriorityQueue(const PriorityQueue& other)
    {
        front = nullptr;
        rear = nullptr;
        count = 0;

        BookRequestNode* current = other.front;
        while (current != nullptr)
        {
            BookRequestNode* newNode = new BookRequestNode;
            newNode->studentID = current->studentID;
            newNode->studentName = current->studentName;
            newNode->bookID = current->bookID;
            newNode->bookTitle = current->bookTitle;
            newNode->priority = current->priority;
            newNode->next = nullptr;

            Add(newNode);
            current = current->next;
        }
    }

    PriorityQueue& operator=(const PriorityQueue& other)
    {
        if (this == &other)
            return *this;

        while (front != nullptr)
        {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = nullptr;
        count = 0;

        BookRequestNode* current = other.front;
        while (current != nullptr)
        {
            BookRequestNode* newNode = new BookRequestNode;
            newNode->studentID = current->studentID;
            newNode->studentName = current->studentName;
            newNode->bookID = current->bookID;
            newNode->bookTitle = current->bookTitle;
            newNode->priority = current->priority;
            newNode->next = nullptr;

            Add(newNode);
            current = current->next;
        }

        return *this;
    }

    ~PriorityQueue()
    {
        while (front != nullptr)
        {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
        count = 0;
    }

    void Add(BookRequestNode* request)
    {
        request->next = nullptr;

        if (front == nullptr)
        {
            front = request;
            rear = request;
        }
        else if (request->priority < front->priority)
        {
            request->next = front;
            front = request;
        }
        else
        {
            BookRequestNode* current = front;

            while (current->next != nullptr && current->next->priority <= request->priority)
            {
                current = current->next;
            }

            request->next = current->next;
            current->next = request;

            if (request->next == nullptr)
            {
                rear = request;
            }
        }

        count++;
    }

    BookRequestNode* Remove()
    {
        if (front == nullptr)
            return nullptr;

        BookRequestNode* request = front;
        front = front->next;

        if (front == nullptr)
            rear = nullptr;

        request->next = nullptr;
        count--;
        return request;
    }

    bool IsEmpty()
    {
        return front == nullptr;
    }

    bool IsNotEmpty()
    {
        return front != nullptr;
    }

    void PrintQueue()
    {
        if (IsEmpty())
        {
            cout << "No requests in the queue." << endl;
            return;
        }

        BookRequestNode* current = front;
        cout << "Front" << endl;
        cout << "  V" << endl;

        while (current != nullptr)
        {
            cout << current->studentName << " (P" << current->priority << ")";
            if (current->next != nullptr)
                cout << " -> ";
            current = current->next;
        }

        cout << endl;
        cout << "  ^" << endl;
        cout << "Rear" << endl;
    }

    void DisplayDetailedQueue()
    {
        if (IsEmpty())
        {
            cout << "No requests in the queue." << endl;
            return;
        }

        BookRequestNode* current = front;
        int position = 1;

        while (current != nullptr)
        {
            cout << "Request " << position << ":" << endl;
            cout << "  Student ID: " << current->studentID << endl;
            cout << "  Student Name: " << current->studentName << endl;
            cout << "  Book ID: " << current->bookID << endl;
            cout << "  Book Title: " << current->bookTitle << endl;
            cout << "  Priority: " << current->priority << endl;
            cout << "  ---------------------------" << endl;
            current = current->next;
            position++;
        }
    }

    int GetCount()
    {
        return count;
    }
};

BookRequestNode* CreateRequest(int studentID, string studentName, int bookID, string bookTitle, int priority)
{
    BookRequestNode* request = new BookRequestNode;
    request->studentID = studentID;
    request->studentName = studentName;
    request->bookID = bookID;
    request->bookTitle = bookTitle;
    request->priority = priority;
    request->next = nullptr;
    return request;
}

void DisplayRequest(BookRequestNode* request)
{
    if (request == nullptr)
        return;

    cout << "Student ID: " << request->studentID << endl;
    cout << "Student Name: " << request->studentName << endl;
    cout << "Book ID: " << request->bookID << endl;
    cout << "Book Title: " << request->bookTitle << endl;
    cout << "Priority: " << request->priority << endl;
    cout << "--------------------------------" << endl;
}

int main()
{
    PriorityQueue requests;
    int choice;

    do
    {
        cout << "\n====================================" << endl;
        cout << "Library Book Request System" << endl;
        cout << "====================================" << endl;
        cout << "1. Add Book Request" << endl;
        cout << "2. Process Highest Priority Request" << endl;
        cout << "3. Display All Requests" << endl;
        cout << "4. Check Queue Status" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            int studentID, bookID, priority;
            string studentName, bookTitle;

            cout << "\nEnter Student ID: ";
            cin >> studentID;
            cin.ignore();

            cout << "Enter Student Name: ";
            getline(cin, studentName);

            cout << "Enter Book ID: ";
            cin >> bookID;
            cin.ignore();

            cout << "Enter Book Title: ";
            getline(cin, bookTitle);

            cout << "Enter Priority (1=Urgent, 2=Assignment, 3=Normal): ";
            cin >> priority;

            if (priority < 1 || priority > 3)
            {
                cout << "Invalid priority. Please enter 1, 2, or 3." << endl;
                break;
            }

            BookRequestNode* request = CreateRequest(studentID, studentName, bookID, bookTitle, priority);
            requests.Add(request);
            cout << "Book request added successfully." << endl;
            break;
        }

        case 2:
        {
            if (requests.IsEmpty())
            {
                cout << "Queue is empty. No request to process." << endl;
            }
            else
            {
                BookRequestNode* processed = requests.Remove();
                cout << "\nProcessed Request:" << endl;
                DisplayRequest(processed);
                delete processed;
            }
            break;
        }

        case 3:
        {
            if (requests.IsEmpty())
            {
                cout << "Queue is empty." << endl;
            }
            else
            {
                cout << "\nAll Pending Requests (Highest Priority First):" << endl;
                requests.DisplayDetailedQueue();
            }
            break;
        }

        case 4:
        {
            cout << "\nQueue Status:" << endl;
            if (requests.IsEmpty())
            {
                cout << "Queue is empty (IsEmpty() returns true)." << endl;
            }
            else
            {
                cout << "Queue is not empty (IsNotEmpty() returns true)." << endl;
            }
            cout << "Total pending requests: " << requests.GetCount() << endl;
            break;
        }

        case 5:
            cout << "\nExiting the program. Thank you!" << endl;
            break;

        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
    }
    while (choice != 5);

    while (!requests.IsEmpty())
    {
        delete requests.Remove();
    }

    return 0;
}
