
#include <bits/stdc++.h>
using namespace std;

struct Process {
    string id;
    int burstTime;
    int priority;
};

vector<Process> processes;
vector<string> history;

// Input validation
bool validInput(int &value) {
    cin >> value;

    if (cin.fail() || value <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    return true;
}

// Find process using ID
int searchIndex(string id) {
    for (int i = 0; i < processes.size(); i++) {
        if (processes[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Display processes
void display() {
    if (processes.empty()) {
        cout << "\nNo processes available.\n";
        return;
    }

    cout << "\nID\tBurst Time\tPriority\n";

    for (int i = 0; i < processes.size(); i++) {
        cout << processes[i].id << "\t"
             << processes[i].burstTime << "\t\t"
             << processes[i].priority << endl;
    }
}

// Load sample data
void loadData() {
    processes.clear();

    for (int i = 1; i <= 15; i++) {
        Process p;
        p.id = "P" + to_string(i);
        p.burstTime = (i * 3) % 10 + 2;
        p.priority = (i * 2) % 5 + 1;

        processes.push_back(p);
    }

    history.push_back("Loaded 15 sample processes.");
    cout << "\n15 sample processes loaded successfully!\n";
}

// Add process
void addProcess() {
    Process p;

    cout << "\nEnter Process ID: ";
    cin >> p.id;

    if (searchIndex(p.id) != -1) {
        cout << "Process ID already exists!\n";
        return;
    }

    cout << "Enter Burst Time: ";

    if (!validInput(p.burstTime)) {
        cout << "Invalid Burst Time!\n";
        return;
    }

    cout << "Enter Priority: ";

    if (!validInput(p.priority)) {
        cout << "Invalid Priority!\n";
        return;
    }

    processes.push_back(p);
    history.push_back("Added process " + p.id);

    cout << "Process added successfully!\n";
}

// Delete process
void deleteProcess() {
    string id;

    cout << "\nEnter Process ID to delete: ";
    cin >> id;

    int index = searchIndex(id);

    if (index == -1) {
        cout << "Process not found!\n";
        return;
    }

    processes.erase(processes.begin() + index);
    history.push_back("Deleted process " + id);

    cout << "Process deleted successfully!\n";
}

// Update process
void updateProcess() {
    string id;

    cout << "\nEnter Process ID to update: ";
    cin >> id;

    int index = searchIndex(id);

    if (index == -1) {
        cout << "Process not found!\n";
        return;
    }

    int bt, pr;

    cout << "Enter New Burst Time: ";

    if (!validInput(bt)) {
        cout << "Invalid Burst Time!\n";
        return;
    }

    cout << "Enter New Priority: ";

    if (!validInput(pr)) {
        cout << "Invalid Priority!\n";
        return;
    }

    processes[index].burstTime = bt;
    processes[index].priority = pr;

    history.push_back("Updated process " + id);

    cout << "Process updated successfully!\n";
}

// Priority queue comparator
struct Compare {
    bool operator()(Process a, Process b) {
        if (a.priority != b.priority) {
            return a.priority > b.priority;
        }

        if (a.burstTime != b.burstTime) {
            return a.burstTime > b.burstTime;
        }

        return a.id > b.id;
    }
};

// Heap visualization
void showHeap() {
    priority_queue<Process, vector<Process>, Compare> pq;

    cout << "\nHEAP INSERTION OPERATIONS\n";

    for (int i = 0; i < processes.size(); i++) {
        pq.push(processes[i]);

        cout << "Inserted: " << processes[i].id
             << " | Priority: " << processes[i].priority
             << " | Current highest priority: "
             << pq.top().id << endl;
    }

    cout << "\nHEAP DELETION OPERATIONS\n";

    while (!pq.empty()) {
        Process p = pq.top();

        cout << "Removed: " << p.id
             << " | Priority: " << p.priority << endl;

        pq.pop();

        if (!pq.empty()) {
            cout << "Next highest priority: "
                 << pq.top().id << endl;
        }
    }

    history.push_back("Displayed heap insertion and deletion operations.");
}

// Scheduling calculations
void calculate(vector<Process> order, string name) {
    int n = order.size();

    if (n == 0) {
        cout << "\nNo processes available!\n";
        return;
    }

    vector<int> prefix(n);
    vector<int> suffix(n);

    prefix[0] = order[0].burstTime;

    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1] + order[i].burstTime;
    }

    suffix[n - 1] = 0;

    for (int i = n - 2; i >= 0; i--) {
        suffix[i] = suffix[i + 1] + order[i + 1].burstTime;
    }

    double totalWT = 0;
    double totalTAT = 0;

    cout << "\n" << name << " Scheduling\n";
    cout << "\nID\tBT\tPriority\tCT\tTAT\tWT\tRemaining BT\n";

    for (int i = 0; i < n; i++) {
        int ct = prefix[i];
        int tat = ct;
        int wt = tat - order[i].burstTime;

        totalWT += wt;
        totalTAT += tat;

        cout << order[i].id << "\t"
             << order[i].burstTime << "\t"
             << order[i].priority << "\t\t"
             << ct << "\t"
             << tat << "\t"
             << wt << "\t"
             << suffix[i] << endl;
    }

    cout << fixed << setprecision(2);

    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;

    history.push_back(name + " scheduling executed.");
}

// FCFS using Queue
void FCFS() {
    queue<Process> q;

    for (int i = 0; i < processes.size(); i++) {
        q.push(processes[i]);
    }

    vector<Process> order;

    while (!q.empty()) {
        order.push_back(q.front());
        q.pop();
    }

    calculate(order, "FCFS");
}

// SJF using Sorting
void SJF() {
    vector<Process> order = processes;

    sort(order.begin(), order.end(),
         [](Process a, Process b) {
             return a.burstTime < b.burstTime;
         });

    calculate(order, "SJF");
}

// Priority Scheduling using Heap
void priorityScheduling() {
    priority_queue<Process, vector<Process>, Compare> pq;

    for (int i = 0; i < processes.size(); i++) {
        pq.push(processes[i]);
    }

    vector<Process> order;

    while (!pq.empty()) {
        order.push_back(pq.top());
        pq.pop();
    }

    calculate(order, "Priority");
}

// Search process
void searchProcess() {
    string id;

    cout << "\nEnter Process ID: ";
    cin >> id;

    int index = searchIndex(id);

    if (index == -1) {
        cout << "Process not found!\n";
        return;
    }

    cout << "\nProcess Found!\n";
    cout << "ID: " << processes[index].id << endl;
    cout << "Burst Time: " << processes[index].burstTime << endl;
    cout << "Priority: " << processes[index].priority << endl;
}

// Sort processes
void sortProcesses() {
    sort(processes.begin(), processes.end(),
         [](Process a, Process b) {
             return a.burstTime < b.burstTime;
         });

    cout << "\nProcesses sorted by Burst Time:\n";
    display();

    history.push_back("Sorted processes by burst time.");
}

// Filter processes
void filterProcesses() {
    int pr;

    cout << "\nEnter priority to filter: ";

    if (!validInput(pr)) {
        cout << "Invalid Priority!\n";
        return;
    }

    cout << "\nMatching Processes:\n";

    bool found = false;

    for (int i = 0; i < processes.size(); i++) {
        if (processes[i].priority == pr) {
            cout << processes[i].id
                 << " | Burst Time: "
                 << processes[i].burstTime
                 << " | Priority: "
                 << processes[i].priority << endl;

            found = true;
        }
    }

    if (!found) {
        cout << "No matching processes found.\n";
    }
}

// Operation history
void showHistory() {
    cout << "\nOperation History:\n";

    if (history.empty()) {
        cout << "No operations performed yet.\n";
        return;
    }

    for (int i = 0; i < history.size(); i++) {
        cout << i + 1 << ". " << history[i] << endl;
    }
}

// Complexity summary
void complexity() {
    cout << "\nTIME COMPLEXITY SUMMARY\n";

    cout << "\nOperation\t\tTime Complexity\n";
    cout << "Display\t\t\tO(n)\n";
    cout << "Search\t\t\tO(n)\n";
    cout << "Add Process\t\tO(n)\n";
    cout << "Delete Process\t\tO(n)\n";
    cout << "Update Process\t\tO(n)\n";
    cout << "FCFS Scheduling\t\tO(n)\n";
    cout << "SJF Scheduling\t\tO(n log n)\n";
    cout << "Priority Scheduling\tO(n log n)\n";
    cout << "Heap Insertion\t\tO(log n)\n";
    cout << "Heap Deletion\t\tO(log n)\n";
    cout << "Sorting\t\t\tO(n log n)\n";
    cout << "Filtering\t\tO(n)\n";

    cout << "\nSpace Complexity: O(n)\n";
}

// Main function
int main() {
    loadData();

    int choice;

    do {
        cout << "\n========== CPU PROCESS SCHEDULER ==========\n";

        cout << "1. Display Processes\n";
        cout << "2. Add Process\n";
        cout << "3. Delete Process\n";
        cout << "4. Update Process\n";
        cout << "5. FCFS Scheduling\n";
        cout << "6. SJF Scheduling\n";
        cout << "7. Priority Scheduling\n";
        cout << "8. Search Process\n";
        cout << "9. Sort Processes\n";
        cout << "10. Filter Processes\n";
        cout << "11. Display Heap\n";
        cout << "12. Operation History\n";
        cout << "13. Complexity Summary\n";
        cout << "14. Reload Sample Data\n";
        cout << "0. Exit\n";

        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid menu input!\n";
            continue;
        }

        switch (choice) {
            case 1:
                display();
                break;

            case 2:
                addProcess();
                break;

            case 3:
                deleteProcess();
                break;

            case 4:
                updateProcess();
                break;

            case 5:
                FCFS();
                break;

            case 6:
                SJF();
                break;

            case 7:
                priorityScheduling();
                break;

            case 8:
                searchProcess();
                break;

            case 9:
                sortProcesses();
                break;

            case 10:
                filterProcesses();
                break;

            case 11:
                showHeap();
                break;

            case 12:
                showHistory();
                break;

            case 13:
                complexity();
                break;

            case 14:
                loadData();
                break;

            case 0:
                cout << "\nThank you for using CPU Process Scheduler!\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
