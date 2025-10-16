/*#include <iostream>
#include <string>

using namespace std;

const int MAX_TASKS = 100;

struct Task {
    int id;
    string title;
    bool completed;
};

class ToDoList {
private:
    Task tasks[MAX_TASKS];
    int taskCount = 0;
    int nextId = 1;

public:
    void addTask(const string& title) {
        if (taskCount >= MAX_TASKS) {
            cout << "Task list is full!\n";
            return;
        }
        tasks[taskCount] = { nextId++, title, false };
        taskCount++;
        cout << "Task added successfully.\n";
    }

    void viewTasks() const {
        if (taskCount == 0) {
            cout << "No tasks available.\n";
            return;
        }
        for (int i = 0; i < taskCount; ++i) {
            cout << "ID: " << tasks[i].id
                 << " | Title: " << tasks[i].title
                 << " | Status: " << (tasks[i].completed ? "Completed" : "Pending") << "\n";
        }
    }

    void completeTask(int id) {
        for (int i = 0; i < taskCount; ++i) {
            if (tasks[i].id == id) {
                tasks[i].completed = true;
                cout << "Task marked as completed.\n";
                return;
            }
        }
        cout << "Task not found.\n";
    }

    void deleteTask(int id) {
        for (int i = 0; i < taskCount; ++i) {
            if (tasks[i].id == id) {
                // Shift remaining tasks to fill the gap
                for (int j = i; j < taskCount - 1; ++j) {
                    tasks[j] = tasks[j + 1];
                }
                taskCount--;
                cout << "Task deleted successfully.\n";
                return;
            }
        }
        cout << "Task not found.\n";
    }
};

// Main menu
int main() {
    ToDoList todo;
    int choice;

    do {
        cout << "\n====== To-Do List Menu ======\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Complete Task\n";
        cout << "4. Delete Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // clear input buffer

        if (choice == 1) {
            string title;
            cout << "Enter task title: ";
            getline(cin, title);
            todo.addTask(title);
        } else if (choice == 2) {
            todo.viewTasks();
        } else if (choice == 3) {
            int id;
            cout << "Enter task ID to mark as completed: ";
            cin >> id;
            todo.completeTask(id);
        } else if (choice == 4) {
            int id;
            cout << "Enter task ID to delete: ";
            cin >> id;
            todo.deleteTask(id);
        } else if (choice == 5) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}*/
/*#include <iostream>               //222222222222222222222
#include <fstream>
#include <string>

using namespace std;

const int MAX_TASKS = 100;
const string FILENAME = "tasks.txt";

struct Task {
    int id;
    string title;
    bool completed;
};

class ToDoList {
private:
    Task tasks[MAX_TASKS];
    int taskCount = 0;
    int nextId = 1;

public:
    ToDoList() {
        loadFromFile();
    }

    void loadFromFile() {
        fstream file;
        if (!file) {
            cout << "No saved tasks found. Starting fresh.\n";
            return;
        }

        string line;
        while (getline(file, line) && taskCount < MAX_TASKS) {
            int sep1 = line.find('|');
            int sep2 = line.rfind('|');

            if (sep1 == string::npos || sep2 == string::npos || sep1 == sep2)
                continue;

            Task t;
            t.id = stoi(line.substr(0, sep1));
            t.title = line.substr(sep1 + 1, sep2 - sep1 - 1);
            t.completed = (line.substr(sep2 + 1) == "1");

            tasks[taskCount++] = t;
            if (t.id >= nextId)
                nextId = t.id + 1;
        }

        file.close();
    }

    void saveToFile() const {
        ofstream file(FILENAME);
        for (int i = 0; i < taskCount; ++i) {
            file << tasks[i].id << "|" << tasks[i].title << "|" << tasks[i].completed << "\n";
        }
        file.close();
    }

    void addTask(const string& title) {
        if (taskCount >= MAX_TASKS) {
            cout << "Task list is full!\n";
            return;
        }
        tasks[taskCount] = { nextId++, title, false };
        taskCount++;
        cout << "Task added successfully.\n";
        saveToFile();
    }

    void viewTasks() const {
        if (taskCount == 0) {
            cout << "No tasks available.\n";
            return;
        }
        for (int i = 0; i < taskCount; ++i) {
            cout << "ID: " << tasks[i].id
                 << " | Title: " << tasks[i].title
                 << " | Status: " << (tasks[i].completed ? "Completed" : "Pending") << "\n";
        }
    }

    void completeTask(int id) {
        for (int i = 0; i < taskCount; ++i) {
            if (tasks[i].id == id) {
                tasks[i].completed = true;
                cout << "Task marked as completed.\n";
                saveToFile();
                return;
            }
        }
        cout << "Task not found.\n";
    }

    void deleteTask(int id) {
        for (int i = 0; i < taskCount; ++i) {
            if (tasks[i].id == id) {
                // Shift tasks
                for (int j = i; j < taskCount - 1; ++j) {
                    tasks[j] = tasks[j + 1];
                }
                taskCount--;
                cout << "Task deleted successfully.\n";
                saveToFile();
                return;
            }
        }
        cout << "Task not found.\n";
    }
};

// ---------- Main Function ----------
int main() {
    ToDoList todo;
    int choice;

    do {
        cout << "\n====== To-Do List Menu ======\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Complete Task\n";
        cout << "4. Delete Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // clear newline

        if (choice == 1) {
            string title;
            cout << "Enter task title: ";
            getline(cin, title);
            todo.addTask(title);
        } else if (choice == 2) {
            todo.viewTasks();
        } else if (choice == 3) {
            int id;
            cout << "Enter task ID to mark as completed: ";
            cin >> id;
            todo.completeTask(id);
        } else if (choice == 4) {
            int id;
            cout << "Enter task ID to delete: ";
            cin >> id;
            todo.deleteTask(id);
        } else if (choice == 5) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;*/



//NEWNEWNEW
#include <iostream>
#include <string>
using namespace std;

const int MAX_TASKS = 100;

struct Task {
    string description;
    bool completed;
};

void displayMenu() {
    cout << "\n--- To-Do List Menu ---\n";
    cout << "1. Add Task\n";
    cout << "2. Display Tasks\n";
    cout << "3. Remove Task\n";
    cout << "4. Mark Task as Completed\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

void addTask(Task tasks[], int &taskCount) {
    if (taskCount >= MAX_TASKS) {
        cout << "Task list is full!\n";
        return;
    }

    cout << "Enter task description: ";
    cin.ignore(); // To clear newline from previous input
    getline(cin, tasks[taskCount].description);
    tasks[taskCount].completed = false;
    taskCount++;
    cout << "Task added successfully.\n";
}

void displayTasks(Task tasks[], int taskCount) {
    if (taskCount == 0) {
        cout << "No tasks to show.\n";
        return;
    }

    cout << "\n--- Task List ---\n";
    for (int i = 0; i < taskCount; i++) {
        cout << i + 1 << ". " << tasks[i].description;
        cout << " [" << (tasks[i].completed ? "Completed" : "Not Completed") << "]\n";
    }
}

void removeTask(Task tasks[], int &taskCount) {
    int index;
    cout << "Enter task number to remove: ";
    cin >> index;

    if (index < 1 || index > taskCount) {
        cout << "Invalid task number.\n";
        return;
    }

    for (int i = index - 1; i < taskCount - 1; i++) {
        tasks[i] = tasks[i + 1]; // Shift left
    }

    taskCount--;
    cout << "Task removed successfully.\n";
}

void markTaskCompleted(Task tasks[], int taskCount) {
    int index;
    cout << "Enter task number to mark as completed: ";
    cin >> index;

    if (index < 1 || index > taskCount) {
        cout << "Invalid task number.\n";
        return;
    }

    tasks[index - 1].completed = true;
    cout << "Task marked as completed.\n";
}

int main() {
    Task tasks[MAX_TASKS];
    int taskCount = 0;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks, taskCount);
                break;
            case 2:
                displayTasks(tasks, taskCount);
                break;
            case 3:
                removeTask(tasks, taskCount);
                break;
            case 4:
                markTaskCompleted(tasks, taskCount);
                break;
            case 5:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
