#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Task {
    char title[50];
    char description[100];
    char category[30];
    char dueDate[20];
    int priority; // 1 = High, 2 = Medium, 3 = Low
    bool completed;

public:
    void setData(const char t[], const char d[], const char c[], const char date[], int p, bool comp = false) {
        strcpy(title, t);
        strcpy(description, d);
        strcpy(category, c);
        strcpy(dueDate, date);
        priority = p;
        completed = comp;
    }

    void display() const {
        cout << "-----------------------------\n";
        cout << "Title      : " << title << endl;
        cout << "Description: " << description << endl;
        cout << "Category   : " << category << endl;
        cout << "Due Date   : " << dueDate << endl;
        cout << "Priority   : " << (priority == 1 ? "High" : priority == 2 ? "Medium" : "Low") << endl;
        cout << "Status     : " << (completed ? "Completed" : "Pending") << endl;
        cout << "-----------------------------\n";
    }

    const char* getTitle() const {
        return title;
    }

    void markCompleted() {
        completed = true;
    }

    void editDescription(const char newDesc[]) {
        strcpy(description, newDesc);
    }
};

int main() {
    int choice;
    bool running = true;

    while (running) {
        cout << "\n--- To-Do List Menu ---\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Delete Task\n";
        cout << "5. Edit Task\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        cin.ignore(); // clear newline

        switch (choice) {
            case 1: {
                ofstream fout("tasks.dat", ios::binary | ios::app);
                Task t;
                char title[50], desc[100], category[30], dueDate[20];
                int priority;

                cout << "Enter title: ";
                cin.getline(title, 50);

                cout << "Enter description: ";
                cin.getline(desc, 100);

                cout << "Enter category (Work/School/Personal/Chores): ";
                cin.getline(category, 30);

                cout << "Enter due date (YYYY-MM-DD): ";
                cin.getline(dueDate, 20);

                cout << "Enter priority (1 = High, 2 = Medium, 3 = Low): ";
                cin >> priority;
                cin.ignore();

                t.setData(title, desc, category, dueDate, priority);
                fout.write((char*)&t, sizeof(t));
                fout.close();

                cout << "Task added successfully!\n";
                break;
            }

            case 2: {
                ifstream fin("tasks.dat", ios::binary);
                Task t;
                bool empty = true;
                cout << "\nAll Tasks:\n";
                while (fin.read((char*)&t, sizeof(t))) {
                    t.display();
                    empty = false;
                }
                if (empty) {
                    cout << "No tasks found.\n";
                }
                fin.close();
                break;
            }

            case 3: {
                fstream file("tasks.dat", ios::in | ios::out | ios::binary);
                Task t;
                char searchTitle[50];
                bool found = false;

                cout << "Enter task title to mark as completed: ";
                cin.getline(searchTitle, 50);

                while (file.read((char*)&t, sizeof(t))) {
                    if (strcmp(t.getTitle(), searchTitle) == 0) {
                        t.markCompleted();
                        file.seekp(-sizeof(t), ios::cur);
                        file.write((char*)&t, sizeof(t));
                        cout << "Task marked as completed.\n";
                        found = true;
                        break;
                    }
                }

                file.close();
                if (!found) {
                    cout << "Task with title \"" << searchTitle << "\" not found.\n";
                }
                break;
            }

            case 4: {
                ifstream fin("tasks.dat", ios::binary);
                ofstream temp("temp.dat", ios::binary);
                Task t;
                char searchTitle[50];
                bool deleted = false;

                cout << "Enter task title to delete: ";
                cin.getline(searchTitle, 50);

                while (fin.read((char*)&t, sizeof(t))) {
                    if (strcmp(t.getTitle(), searchTitle) == 0) {
                        cout << "Deleting task:\n";
                        t.display();
                        deleted = true;
                        continue;
                    }
                    temp.write((char*)&t, sizeof(t));
                }

                fin.close();
                temp.close();

                remove("tasks.dat");
                rename("temp.dat", "tasks.dat");

                if (!deleted) {
                    cout << "Task with title \"" << searchTitle << "\" not found.\n";
                } else {
                    cout << "Task deleted successfully.\n";
                }
                break;
            }

            case 5: {
                fstream file("tasks.dat", ios::in | ios::out | ios::binary);
                Task t;
                char searchTitle[50];
                bool found = false;

                cout << "Enter task title to edit: ";
                cin.getline(searchTitle, 50);

                while (file.read((char*)&t, sizeof(t))) {
                    if (strcmp(t.getTitle(), searchTitle) == 0) {
                        cout << "Current Task:\n";
                        t.display();

                        char newDesc[100];
                        cout << "Enter new description: ";
                        cin.getline(newDesc, 100);

                        t.editDescription(newDesc);
                        file.seekp(-sizeof(t), ios::cur);
                        file.write((char*)&t, sizeof(t));
                        cout << "Task updated successfully.\n";
                        found = true;
                        break;
                    }
                }

                file.close();
                if (!found) {
                    cout << "Task with title \"" << searchTitle << "\" not found.\n";
                }
                break;
            }

            case 6: {
                cout << "Exiting program.\n";
                running = false;
                break;
            }

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

