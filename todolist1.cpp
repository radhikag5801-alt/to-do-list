#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Task
{
public:
    string name;
    bool completed;

    Task(string n = "", bool c = false)
    {
        name = n;
        completed = c;
    }
};

vector<Task> tasks;

// Function to Add Task
void addTask()
{
    string taskName;

    cin.ignore();
    cout << "\nEnter Task Name: ";
    getline(cin, taskName);

    Task t(taskName, false);
    tasks.push_back(t);

    cout << "Task Added Successfully!\n";
}

// Function to View Tasks
void viewTasks()
{
    if (tasks.empty())
    {
        cout << "\nNo Tasks Available!\n";
        return;
    }

    cout << "\n------ TASK LIST ------\n";

    for (int i = 0; i < tasks.size(); i++)
    {
        cout << i + 1 << ". " << tasks[i].name;

        if (tasks[i].completed)
            cout << " [Completed]";
        else
            cout << " [Pending]";

        cout << endl;
    }
}

// Function to Mark Task as Completed
void markCompleted()
{
    if (tasks.empty())
    {
        cout << "\nNo Tasks Available!\n";
        return;
    }

    viewTasks();

    int choice;
    cout << "\nEnter Task Number to Mark Completed: ";
    cin >> choice;

    if (choice >= 1 && choice <= tasks.size())
    {
        tasks[choice - 1].completed = true;
        cout << "Task Marked as Completed!\n";
    }
    else
    {
        cout << "Invalid Task Number!\n";
    }
}

// Function to Save Tasks
void saveTasks()
{
    ofstream file("tasks.txt");

    for (int i = 0; i < tasks.size(); i++)
    {
        file << tasks[i].name << "|" << tasks[i].completed << endl;
    }

    file.close();

    cout << "Tasks Saved Successfully!\n";
}

// Function to Load Tasks
void loadTasks()
{
    ifstream file("tasks.txt");

    if (!file)
        return;

    tasks.clear();

    string line;

    while (getline(file, line))
    {
        int pos = line.find('|');

        if (pos != string::npos)
        {
            string name = line.substr(0, pos);
            bool status = (line.substr(pos + 1) == "1");

            tasks.push_back(Task(name, status));
        }
    }

    file.close();
}

int main()
{
    loadTasks();

    int choice;

    do
    {
        cout << "\n==============================";
        cout << "\n      TO-DO LIST MENU";
        cout << "\n==============================";
        cout << "\n1. Add Task";
        cout << "\n2. View Tasks";
        cout << "\n3. Mark Task as Completed";
        cout << "\n4. Save Tasks";
        cout << "\n5. Load Tasks";
        cout << "\n6. Exit";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addTask();
            break;

        case 2:
            viewTasks();
            break;

        case 3:
            markCompleted();
            break;

        case 4:
            saveTasks();
            break;

        case 5:
            loadTasks();
            cout << "Tasks Loaded Successfully!\n";
            break;

        case 6:
            saveTasks();
            cout << "\nThank You!\n";
            cout << "Exiting Program...\n";
            break;

        default:
            cout << "Invalid Choice! Try Again.\n";
        }

    } while (choice != 6);

    return 0;
}