/*#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

struct Task {
    string title;
    string description;
    string category;
    string dueDate;
    string priority; // High / Medium / Low
    bool completed;
};

vector<Task> tasks;

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", ltm);
    return string(buf);
}

void printTask(const Task& task, int index) {
    cout << "\n[" << index << "] " << task.title << "\n";
    cout << "    Description: " << task.description << "\n";
    cout << "    Category   : " << task.category << "\n";
    cout << "    Due Date   : " << task.dueDate << "\n";
    cout << "    Priority   : " << task.priority << "\n";
    cout << "    Status     : " << (task.completed ? "Completed" : "Pending") << "\n";
}

void addTask() {
    Task task;
    cin.ignore(); // clear buffer

    cout << "\nEnter Title: ";
    getline(cin, task.title);

    cout << "Enter Description: ";
    getline(cin, task.description);

    cout << "Enter Category: ";
    getline(cin, task.category);

    cout << "Enter Due Date (YYYY-MM-DD): ";
    getline(cin, task.dueDate);

    cout << "Enter Priority (High/Medium/Low): ";
    getline(cin, task.priority);

    task.completed = false;
    tasks.push_back(task);

    cout << "Task added.\n";
}

void viewTasks() {
    if (tasks.empty()) {
        cout << "\nNo tasks available.\n";
        return;
    }

    cout << "\n===== TASK LIST =====\n";
    for (int i = 0; i < (int)tasks.size(); ++i) {
        printTask(tasks[i], i);
    }
}

void markCompleted() {
    int index;
    cout << "Enter task number to mark as completed: ";
    cin >> index;

    if (index >= 0 && index < (int)tasks.size()) {
        tasks[index].completed = true;
        cout << "Task marked as completed.\n";
    } else {
        cout << "Invalid index.\n";
    }
}

void deleteTask() {
    int index;
    cout << "Enter task number to delete: ";
    cin >> index;

    if (index >= 0 && index < (int)tasks.size()) {
        tasks.erase(tasks.begin() + index);
        cout << "Task deleted.\n";
    } else {
        cout << "Invalid index.\n";
    }
}

void saveToFile(const string& filename) {
    ofstream file(filename.c_str());
    if (!file) {
        cout << "Failed to open file.\n";
        return;
    }

    for (int i = 0; i < (int)tasks.size(); ++i) {
        file << tasks[i].title << '|'
             << tasks[i].description << '|'
             << tasks[i].category << '|'
             << tasks[i].dueDate << '|'
             << tasks[i].priority << '|'
             << tasks[i].completed << '\n';
    }

    file.close();
    cout << "Tasks saved.\n";
}

void loadFromFile(const string& filename) {
    ifstream file(filename.c_str());
    if (!file) return;

    tasks.clear();
    string line;

    while (getline(file, line)) {
        Task task;
        int start = 0;
        int pos = 0;
        int field = 0;
        string fields[6];

        for (int i = 0; i < 5; ++i) {
            pos = line.find('|', start);
            if (pos == string::npos) break;
            fields[i] = line.substr(start, pos - start);
            start = pos + 1;
        }
        fields[5] = line.substr(start);

        task.title = fields[0];
        task.description = fields[1];
        task.category = fields[2];
        task.dueDate = fields[3];
        task.priority = fields[4];
        task.completed = (fields[5] == "1");

        tasks.push_back(task);
    }

    file.close();
}

void showMenu() {
    cout << "\n===== TO-DO LIST MENU =====\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Delete Task\n";
    cout << "5. Save Tasks\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    string filename = "tasks.txt";
    loadFromFile(filename);

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markCompleted(); break;
            case 4: deleteTask(); break;
            case 5: saveToFile(filename); break;
            case 6: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 6);

    return 0;
}*/
//SECOND                    222222222222222222222222222222222222222
/*#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

const int MAX_TASKS = 100;

struct Task {
    string title;
    string description;
    string category;
    string dueDate;
    string priority; // High / Medium / Low
    bool completed;
};

Task tasks[MAX_TASKS];
int taskCount = 0;

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", ltm);
    return string(buf);
}

void printTask(const Task& task, int index) {
    cout << "\n[" << index << "] " << task.title << "\n";
    cout << "    Description: " << task.description << "\n";
    cout << "    Category   : " << task.category << "\n";
    cout << "    Due Date   : " << task.dueDate << "\n";
    cout << "    Priority   : " << task.priority << "\n";
    cout << "    Status     : " << (task.completed ? "Completed" : "Pending") << "\n";
}

void saveToFile(const string& filename) {
    ofstream file(filename.c_str());
    if (!file) {
        cout << "Failed to open file.\n";
        return;
    }

    for (int i = 0; i < taskCount; ++i) {
        file << tasks[i].title << '|'
             << tasks[i].description << '|'
             << tasks[i].category << '|'
             << tasks[i].dueDate << '|'
             << tasks[i].priority << '|'
             << tasks[i].completed << '\n';
    }

    file.close();
}

void loadFromFile(const string& filename) {
    ifstream file(filename.c_str());
    if (!file) return;

    taskCount = 0;
    string line;

    while (getline(file, line) && taskCount < MAX_TASKS) {
        Task task;
        int start = 0;
        int pos = 0;
        string fields[6];

        for (int i = 0; i < 5; ++i) {
            pos = line.find('|', start);
            if (pos == string::npos) break;
            fields[i] = line.substr(start, pos - start);
            start = pos + 1;
        }
        fields[5] = line.substr(start);

        task.title = fields[0];
        task.description = fields[1];
        task.category = fields[2];
        task.dueDate = fields[3];
        task.priority = fields[4];
        task.completed = (fields[5] == "1");

        tasks[taskCount++] = task;
    }

    file.close();
}

void addTask(const string& filename) {
    if (taskCount >= MAX_TASKS) {
        cout << "Task list is full.\n";
        return;
    }

    Task task;
    cin.ignore(); // clear buffer

    cout << "\nEnter Title: ";
    getline(cin, task.title);

    cout << "Enter Description: ";
    getline(cin, task.description);

    cout << "Enter Category: ";
    getline(cin, task.category);

    cout << "Enter Due Date (YYYY-MM-DD): ";
    getline(cin, task.dueDate);

    cout << "Enter Priority (High/Medium/Low): ";
    getline(cin, task.priority);

    task.completed = false;
    tasks[taskCount++] = task;

    saveToFile(filename);

    cout << "Task added.\n";
}

void viewTasks() {
    if (taskCount == 0) {
        cout << "\nNo tasks available.\n";
        return;
    }

    cout << "\n===== TASK LIST =====\n";
    for (int i = 0; i < taskCount; ++i) {
        printTask(tasks[i], i);
    }
}

void markCompleted(const string& filename) {
    int index;
    cout << "Enter task number to mark as completed: ";
    cin >> index;

    if (index >= 0 && index < taskCount) {
        tasks[index].completed = true;
        saveToFile(filename);
        cout << "Task marked as completed.\n";
    } else {
        cout << "Invalid index.\n";
    }
}

void deleteTask(const string& filename) {
    int index;
    cout << "Enter task number to delete: ";
    cin >> index;

    if (index >= 0 && index < taskCount) {
        for (int i = index; i < taskCount - 1; ++i) {
            tasks[i] = tasks[i + 1];
        }
        --taskCount;
        saveToFile(filename);
        cout << "Task deleted.\n";
    } else {
        cout << "Invalid index.\n";
    }
}

void showMenu() {
    cout << "\n===== TO-DO LIST MENU =====\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Delete Task\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    string filename = "tasks.txt";
    loadFromFile(filename);

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: addTask(filename); break;
            case 2: viewTasks(); break;
            case 3: markCompleted(filename); break;
            case 4: deleteTask(filename); break;
            case 5: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 5);

    return 0;
}*/
//THIRD                          3333333333333333333333333333333333333
/*#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_TASKS = 100;

struct Task {
    string title;
    string description;
    string category;
    string dueDate;
    string priority; // High / Medium / Low
    bool completed;
};

Task tasks[MAX_TASKS];
int taskCount = 0;

void printTask(const Task& task, int index) {
    cout << "\n[" << index << "] " << task.title << "\n";
    cout << "    Description: " << task.description << "\n";
    cout << "    Category   : " << task.category << "\n";
    cout << "    Due Date   : " << task.dueDate << "\n";
    cout << "    Priority   : " << task.priority << "\n";
    cout << "    Status     : " << (task.completed ? "Completed" : "Pending") << "\n";
}

void saveToFile(const string& filename) {
    ofstream file(filename.c_str());
    if (!file) {
        cout << "Failed to open file.\n";
        return;
    }

    for (int i = 0; i < taskCount; ++i) {
        file << tasks[i].title << '|'
             << tasks[i].description << '|'
             << tasks[i].category << '|'
             << tasks[i].dueDate << '|'
             << tasks[i].priority << '|'
             << tasks[i].completed << '\n';
    }

    file.close();
}

void loadFromFile(const string& filename) {
    ifstream file(filename.c_str());
    if (!file) return;

    taskCount = 0;
    string line;

    while (getline(file, line) && taskCount < MAX_TASKS) {
        Task task;
        int start = 0;
        int pos = 0;
        string fields[6];

        for (int i = 0; i < 5; ++i) {
            pos = line.find('|', start);
            if (pos == string::npos) break;
            fields[i] = line.substr(start, pos - start);
            start = pos + 1;
        }
        fields[5] = line.substr(start);

        task.title = fields[0];
        task.description = fields[1];
        task.category = fields[2];
        task.dueDate = fields[3];
        task.priority = fields[4];
        task.completed = (fields[5] == "1");

        tasks[taskCount++] = task;
    }

    file.close();
}

void addTask(const string& filename) {
    if (taskCount >= MAX_TASKS) {
        cout << "Task list is full.\n";
        return;
    }

    Task task;
    cin.ignore(); // clear buffer

    cout << "\nEnter Title: ";
    getline(cin, task.title);

    cout << "Enter Description: ";
    getline(cin, task.description);

    cout << "Enter Category: ";
    getline(cin, task.category);

    cout << "Enter Due Date (YYYY-MM-DD): ";
    getline(cin, task.dueDate);

    cout << "Enter Priority (High/Medium/Low): ";
    getline(cin, task.priority);

    task.completed = false;
    tasks[taskCount++] = task;

    saveToFile(filename);

    cout << "Task added.\n";
}

void viewTasks() {
    if (taskCount == 0) {
        cout << "\nNo tasks available.\n";
        return;
    }

    cout << "\n===== TASK LIST =====\n";
    for (int i = 0; i < taskCount; ++i) {
        printTask(tasks[i], i);
    }
}

void markCompleted(const string& filename) {
    int index;
    cout << "Enter task number to mark as completed: ";
    cin >> index;

    if (index >= 0 && index < taskCount) {
        tasks[index].completed = true;
        saveToFile(filename);
        cout << "Task marked as completed.\n";
    } else {
        cout << "Invalid index.\n";
    }
}

void deleteTask(const string& filename) {
    int index;
    cout << "Enter task number to delete: ";
    cin >> index;

    if (index >= 0 && index < taskCount) {
        for (int i = index; i < taskCount - 1; ++i) {
            tasks[i] = tasks[i + 1];
        }
        --taskCount;
        saveToFile(filename);
        cout << "Task deleted.\n";
    } else {
        cout << "Invalid index.\n";
    }
}

void showMenu() {
    cout << "\n===== TO-DO LIST MENU =====\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Delete Task\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    string filename = "tasks.txt";
    loadFromFile(filename);

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: addTask(filename); break;
            case 2: viewTasks(); break;
            case 3: markCompleted(filename); break;
            case 4: deleteTask(filename); break;
            case 5: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 5);

    return 0;
}*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_TASKS = 100;

struct Task {
    string title;
    string description;
    string category;
    string dueDate;
    string priority; // High / Medium / Low
    bool completed;
};

Task tasks[MAX_TASKS];
int taskCount = 0;

void printTask(const Task& task, int index) {
    cout << "\n[" << index << "] " << task.title << "\n";
    cout << "    Description: " << task.description << "\n";
    cout << "    Category   : " << task.category << "\n";
    cout << "    Due Date   : " << task.dueDate << "\n";
    cout << "    Priority   : " << task.priority << "\n";
    cout << "    Status     : " << (task.completed ? "Completed" : "Pending") << "\n";
}

void saveToFile(const string& filename) {
    ofstream file(filename.c_str());
    if (!file) {
        cout << "Failed to open file.\n";
        return;
    }

    for (int i = 0; i < taskCount; ++i) {
        file << tasks[i].title << '|'
             << tasks[i].description << '|'
             << tasks[i].category << '|'
             << tasks[i].dueDate << '|'
             << tasks[i].priority << '|'
             << tasks[i].completed << '\n';
    }

    file.close();
}

void loadFromFile(const string& filename) {
    ifstream file(filename.c_str());
    if (!file) return;

    taskCount = 0;
    string line;

    while (getline(file, line) && taskCount < MAX_TASKS) {
        Task task;
        int start = 0;
        int pos = 0;
        string fields[6];

        for (int i = 0; i < 5; ++i) {
            pos = line.find('|', start);
            if (pos == string::npos) break;
            fields[i] = line.substr(start, pos - start);
            start = pos + 1;
        }
        fields[5] = line.substr(start);

        task.title = fields[0];
        task.description = fields[1];
        task.category = fields[2];
        task.dueDate = fields[3];
        task.priority = fields[4];
        task.completed = (fields[5] == "1");

        tasks[taskCount++] = task;
    }

    file.close();
}

void addTask(const string& filename) {
    if (taskCount >= MAX_TASKS) {
        cout << "Task list is full.\n";
        return;
    }

    Task task;
    cin.ignore(); // clear buffer

    cout << "\nEnter Title: ";
    getline(cin, task.title);

    cout << "Enter Description: ";
    getline(cin, task.description);

    cout << "Enter Category: ";
    getline(cin, task.category);

    cout << "Enter Due Date (YYYY-MM-DD): ";
    getline(cin, task.dueDate);

    cout << "Enter Priority (High/Medium/Low): ";
    getline(cin, task.priority);

    task.completed = false;
    tasks[taskCount++] = task;

    saveToFile(filename);

    cout << "Task added.\n";
}

void viewTasks() {
    if (taskCount == 0) {
        cout << "\nNo tasks available.\n";
        return;
    }

    cout << "\n===== TASK LIST =====\n";
    for (int i = 0; i < taskCount; ++i) {
        printTask(tasks[i], i);
    }
}

void markCompleted(const string& filename) {
    int index;
    cout << "Enter task number to mark as completed: ";
    cin >> index;

    if (index >= 0 && index < taskCount) {
        tasks[index].completed = true;
        saveToFile(filename);
        cout << "Task marked as completed.\n";
    } else {
        cout << "Invalid index.\n";
    }
}

void deleteTask(const string& filename) {
    int index;
    cout << "Enter task number to delete: ";
    cin >> index;

    if (index >= 0 && index < taskCount) {
        for (int i = index; i < taskCount - 1; ++i) {
            tasks[i] = tasks[i + 1];
        }
        --taskCount;
        saveToFile(filename);
        cout << "Task deleted.\n";
    } else {
        cout << "Invalid index.\n";
    }
}

void editTask(const string& filename) {
    int index;
    cout << "Enter task number to edit: ";
    cin >> index;
    cin.ignore(); // clear buffer

    if (index >= 0 && index < taskCount) {
        Task& task = tasks[index];

        cout << "\nEditing Task [" << index << "]: " << task.title << "\n";
        cout << "Leave field empty to keep current value.\n";

        string input;

        cout << "New Title (" << task.title << "): ";
        getline(cin, input);
        if (!input.empty()) task.title = input;

        cout << "New Description (" << task.description << "): ";
        getline(cin, input);
        if (!input.empty()) task.description = input;

        cout << "New Category (" << task.category << "): ";
        getline(cin, input);
        if (!input.empty()) task.category = input;

        cout << "New Due Date (" << task.dueDate << "): ";
        getline(cin, input);
        if (!input.empty()) task.dueDate = input;

        cout << "New Priority (" << task.priority << "): ";
        getline(cin, input);
        if (!input.empty()) task.priority = input;

        saveToFile(filename);
        cout << "Task updated.\n";
    } else {
        cout << "Invalid index.\n";
    }
}

void showMenu() {
    cout << "\n===== TO-DO LIST MENU =====\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Delete Task\n";
    cout << "5. Edit Task\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    string filename = "tasks.txt";
    loadFromFile(filename);

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: addTask(filename); break;
            case 2: viewTasks(); break;
            case 3: markCompleted(filename); break;
            case 4: deleteTask(filename); break;
            case 5: editTask(filename); break;
            case 6: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 6);

    return 0;
}



