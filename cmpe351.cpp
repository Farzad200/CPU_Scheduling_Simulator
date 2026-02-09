/* This is code developed by <Farzad Rahmani> */

#include "cmpe351.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstdio>


using namespace std;




struct Process
{
    int id;
    int burst;
    int priority;
    int arrival;
    int queueid;
    int waiting_time;
};

struct Node
{
    Process data;
    Node* next;
};

Node* read_processes(const char* filpath);
Node* createNode(Process p);
void insertEnd(Node*& head, Process p);
int getLength(Node* head);
void swapNodes(Node* a, Node* b);
void S_b_arrival(Node* head);
void S_b_burst(Node* head);
void S_b_priority(Node* head);
void compute_fcfs(Node* head);
void compute_sjf(Node* head);
void compute_priority(Node* head);
void reset_waiting_time(Node* head);



Node* createNode(Process p)
{
    Node* n = new Node();
    n->data = p;
    n->next = NULL;
    return n;
}

void insertEnd(Node*& head, Process p)
{
    Node* n = createNode(p);

    if (head == NULL)
    {
        head = n;
        return;
    }

    Node* cur = head;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = n;
}

int getLength(Node* head)
{
    int len = 0;
    Node* cur = head;

    while (cur != NULL)
    {
        len++;
        cur = cur->next;
    }

    return len;
}

void swapNodes(Node* a, Node* b)
{
    Process temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void S_b_arrival(Node* head)
{
    if (head == NULL) return;

    bool changed;
    do
    {
        changed = false;
        Node* cur = head;

        while (cur->next != NULL)
        {
            if (cur->data.arrival > cur->next->data.arrival)
            {
                swapNodes(cur, cur->next);
                changed = true;
            }
            cur = cur->next;
        }
    } while (changed);
}

void S_b_burst(Node* head)
{
    if (head == NULL) return;

    bool changed;
    do
    {
        changed = false;
        Node* cur = head;

        while (cur->next != NULL)
        {
            if (cur->data.burst > cur->next->data.burst)
            {
                swapNodes(cur, cur->next);
                changed = true;
            }
            cur = cur->next;
        }
    } while (changed);
}

void S_b_priority(Node* head)
{
    if (head == NULL) return;

    bool changed;
    do
    {
        changed = false;
        Node* cur = head;

        while (cur->next != NULL)
        {
            if (cur->data.priority > cur->next->data.priority)
            {
                swapNodes(cur, cur->next);
                changed = true;
            }
            cur = cur->next;
        }
    } while (changed);
}

void compute_sjf(Node* head)
{
    if (head == NULL)
        return;

    int time = 0;
    int finished = 0;
    int total = getLength(head);

    while (finished < total)
    {
        Node* cur = head;
        Node* best = NULL;

        while (cur != NULL)
        {
            if (cur->data.waiting_time == -1 &&
                cur->data.arrival <= time)
            {
                if (best == NULL ||
                    cur->data.burst < best->data.burst)
                {
                    best = cur;
                }
            }
            cur = cur->next;
        }

        if (best == NULL)
        {
            time++;
            continue;
        }

        best->data.waiting_time = time - best->data.arrival;
        time += best->data.burst;
        finished++;
    }
}

void run_priority_scheduler(Node* list)
{
    if (list == NULL)
        return;

    int clock = 0;
    int doneCount = 0;
    int processCount = getLength(list);

    while (doneCount < processCount)
    {
        Node* walker = list;
        Node* chosen = NULL;

        while (walker != NULL)
        {
            bool notDone = (walker->data.waiting_time == -1);
            bool arrived = (walker->data.arrival <= clock);

            if (notDone && arrived)
            {
                if (chosen == NULL ||
                    walker->data.priority < chosen->data.priority)
                {
                    chosen = walker;
                }
            }

            walker = walker->next;
        }

        if (chosen == NULL)
        {
            clock++;
            continue;
        }

        chosen->data.waiting_time = clock - chosen->data.arrival;
        clock += chosen->data.burst;
        doneCount++;
    }
}



Node* read_processes(const char* filepath)
{
    ifstream in(filepath);
    if (!in)
        return NULL;

    Node* head = NULL;
    string line;
    int idCounter = 0;

    while (getline(in, line))
    {
        int burst, priority, arrival, queue;

        int ok = sscanf(line.c_str(), "%d:%d:%d:%d",
                        &burst, &priority, &arrival, &queue);

        if (ok != 4)
            continue;

        Process p;
        p.id = idCounter;
        p.burst = burst;
        p.priority = priority;
        p.arrival = arrival;
        p.queueid = queue;
        p.waiting_time = -1;

        insertEnd(head, p);
        idCounter++;
    }

    in.close();
    return head;
}

void reset_waiting_time(Node* head)
{
    Node* current = head;

    while (current != NULL)
    {
        current->data.waiting_time = -1;
        current = current->next;
    }
}

void write_waiting_times(ofstream& out, Node* head)
{
    Node* cur = head;
    while (cur)
    {
        out << cur->data.waiting_time << " ";
        cur = cur->next;
    }
    out << endl;
}


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return -1;
    }

    const char* inFile = argv[1];
    const char* outFile = argv[2];

    Node* processList = read_processes(inFile);

    Node* queue0 = NULL;
    Node* queue1 = NULL;

    cout << "Queue 0 FCFS:" << endl;
compute_fcfs(queue0);

Node* cur = queue0;
while (cur)
{
    cout << cur->data.waiting_time << " ";
    cur = cur->next;
}
cout << endl;

reset_waiting_time(queue0);

cout << "Queue 0 SJF:" << endl;
compute_sjf(queue0);

cur = queue0;
while (cur)
{
    cout << cur->data.waiting_time << " ";
    cur = cur->next;
}
cout << endl;

reset_waiting_time(queue0);

cout << "Queue 0 Priority:" << endl;
compute_priority(queue0);

cur = queue0;
while (cur)
{
    cout << cur->data.waiting_time << " ";
    cur = cur->next;
}
cout << endl;


    Node* ptr = processList;
    while (ptr != NULL)
    {
        if (ptr->data.queueid == 0)
        {
            insertEnd(queue0, ptr->data);
        }
        else if (ptr->data.queueid == 1)
        {
            insertEnd(queue1, ptr->data);
        }
        ptr = ptr->next;
    }

    ofstream out(outFile);
if (!out.is_open())
{
    cout << "Error opening output file" << endl;
    return -1;
}

 out << "Queue 0 FCFS:" << endl;
compute_fcfs(queue0);
write_waiting_times(out, queue0);

reset_waiting_time(queue0);

out << "Queue 0 SJF:" << endl;
compute_sjf(queue0);
write_waiting_times(out, queue0);

reset_waiting_time(queue0);

out << "Queue 0 Priority:" << endl;
compute_priority(queue0);
write_waiting_times(out, queue0);

 out << "Queue 1 FCFS:" << endl;
compute_fcfs(queue1);
write_waiting_times(out, queue1);

reset_waiting_time(queue1);

out << "Queue 1 SJF:" << endl;
compute_sjf(queue1);
write_waiting_times(out, queue1);

reset_waiting_time(queue1);

out << "Queue 1 Priority:" << endl;
compute_priority(queue1);
write_waiting_times(out, queue1);

out.close();

    return 0;
}
