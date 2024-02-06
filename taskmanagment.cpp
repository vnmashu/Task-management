#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string name;
    string category;
};

class TaskManager {
private:
    vector<Task> tasks;

public:
    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    void displayTasks() {
        if (tasks.empty()) {
            cout << "No tasks available.\n";
            return;
        }
        cout << "Tasks:\n";
        for (const auto& task : tasks) {
            cout << "- " << task.name << " (" << task.category << ")\n";
        }
    }

    void modifyTask(const string& oldName, const string& newName, const string& newCategory) {
        bool found = false;
        for (auto& task : tasks) {
            if (task.name == oldName) {
                task.name = newName;
                task.category = newCategory;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Task not found.\n";
        }
    }

    void deleteTask(const string& taskName) {
        bool found = false;
        for (auto it = tasks.begin(); it != tasks.end(); ++it) {
            if (it->name == taskName) {
                it = tasks.erase(it);
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Task not found.\n";
        }
    }

    void saveTasksToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file for writing.\n";
            return;
        }
        
        for (const auto& task : tasks) {
            file << task.name << "," << task.category << "\n";
        }
        
        file.close();
        cout << "Tasks saved to file: " << filename << endl;
    }

    void loadTasksFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "File does not exist. Creating new file.\n";
            ofstream newFile(filename); // Create a new file
            newFile.close();
            cout << "New file created: " << filename << endl;
            return;
        }
        
        tasks.clear(); // Clear existing tasks before loading from file
        
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(",");
            if (pos != string::npos) {
                string name = line.substr(0, pos);
                string category = line.substr(pos + 1);
                tasks.push_back({name, category});
            }
        }
        
        file.close();
        cout << "Tasks loaded from file: " << filename << endl;
    }
};

int main() {
    TaskManager taskManager;

    // Load tasks from a file (if it exists, otherwise create it)
    taskManager.loadTasksFromFile("tasks.txt");

    int choice;
    do {
        cout << "\nTask Management Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. Display Tasks\n";
        cout << "3. Modify Task\n";
        cout << "4. Delete Task\n";
        cout << "5. Save Tasks to File\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, category;
                cout << "Enter task name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter task category: ";
                getline(cin, category);
                taskManager.addTask({name, category});
                break;
            }
            case 2:
                taskManager.displayTasks();
                break;
            case 3: {
                string oldName, newName, newCategory;
                cout << "Enter the name of the task to modify: ";
                cin.ignore();
                getline(cin, oldName);
                cout << "Enter new task name: ";
                getline(cin, newName);
                cout << "Enter new task category: ";
                getline(cin, newCategory);
                taskManager.modifyTask(oldName, newName, newCategory);
                break;
            }
            case 4: {
                string taskName;
                cout << "Enter the name of the task to delete: ";
                cin.ignore();
                getline(cin, taskName);
                taskManager.deleteTask(taskName);
                break;
            }
            case 5:
                taskManager.saveTasksToFile("tasks.txt");
                break;
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}
