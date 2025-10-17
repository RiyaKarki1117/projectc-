//Project for C++
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Task {
    int id;
    char description[100];
    bool completed;

public:
    void setData(int i, const char d[], bool c = false) {
        id = i;
        strcpy(description, d);
        completed = c;
    }

    void display() const {
        cout << "ID: " << id
             << " | Description: " << description
             << " | Status: " << (completed ? "Completed" : "Pending") << endl;
    }

    int getID() const {
        return id;
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
                int id;
                char desc[100];

                cout << "Enter task ID: ";
                cin >> id;
                cin.ignore();

                cout << "Enter task description: ";
                cin.getline(desc, 100);
                cin.ignore();

                t.setData(id, desc, false);
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
                int searchID;
                bool found = false;

                cout << "Enter task ID to mark as completed: ";
                cin >> searchID;
                cin.ignore();

                while (file.read((char*)&t, sizeof(t))) {
                    if (t.getID() == searchID) {
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
                    cout << "Task with ID " << searchID << " not found.\n";
                }
                break;
            }

            case 4: {
                ifstream fin("tasks.dat", ios::binary);
                ofstream temp("temp.dat", ios::binary);
                Task t;
                int searchID;
                bool deleted = false;

                cout << "Enter task ID to delete: ";
                cin >> searchID;

                while (fin.read((char*)&t, sizeof(t))) {
                    if (t.getID() == searchID) {
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
                    cout << "Task with ID " << searchID << " not found.\n";
                } else {
                    cout << "Task deleted successfully.\n";
                }
                break;
            }

            case 5: {
                fstream file("tasks.dat", ios::in | ios::out | ios::binary);
                Task t;
                int searchID;
                bool found = false;

                cout << "Enter task ID to edit: ";
                cin >> searchID;
                cin.ignore();

                while (file.read((char*)&t, sizeof(t))) {
                    if (t.getID() == searchID) {
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
                    cout << "Task with ID " << searchID << " not found.\n";
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

