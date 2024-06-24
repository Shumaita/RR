//Round Robin Algorithm
//Implemented by myself
//Got some help from chatgpt
//It includes arrival time

#include <bits/stdc++.h>
using namespace std;

struct process { //structure nilam
    int pid;//process id
    int arrival_time;
    int burst_time;
    int start_time;
    int ct; //ct bolte computation time k bujhacchi
    int turnaround_time;
    int waiting_time;
};

bool compare1(process p1, process p2)
{
    return p1.arrival_time < p2.arrival_time; //arrival time onushare compare korbo
}

bool compare2(process p1, process p2)
{
    return p1.pid < p2.pid; //process id onushare compare
}

int main() { //main function er kaj shuru

    int n;
    int tq;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int burst_remaining[100];
    int idx;

    cout << setprecision(2) << fixed; //doshomik r por dui ghor jabe

    cout<<"Enter the number of processes: ";
    cin>>n;
    cout<<"Enter time quantum: ";
    cin>>tq;

    for(int i = 0; i < n; i++) {
        cout<<"Enter arrival time of process "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter burst time of process "<<i+1<<": ";
        cin>>p[i].burst_time;
        burst_remaining[i] = p[i].burst_time;
        p[i].pid = i+1;
        cout<<endl;
    }

    sort(p,p+n,compare1);
//The compare1 function is defined earlier in the code. It compares two processes based on their arrival times.
//After calling std::sort() with the array of processes (p), the array will be rearranged such that
//the processes are sorted in ascending order based on their arrival times.
//Once sorted, the processes will be arranged in such a way that the process with
//the earliest arrival time will be at the beginning of the array (p[0]), and the process with the latest arrival time will be at the end of the array (p[n-1]).

    queue<int> q;// process gulor index queue te store korbe, current execution er
    int current_time = 0;
    q.push(0);//prothom process howar por ber hobe
    int completed = 0;
    int mark[100];//mark whether a process has been added to the queue or not
    memset(mark,0,sizeof(mark));//It ensures that all elements are initially marked as not added to the queue.
    mark[0] = 1;

    while(completed != n) {
        idx = q.front();//the index of the next process to be executed by accessing the front element of the queue q.
        q.pop();//it removes the front element from the queue q

        if(burst_remaining[idx] == p[idx].burst_time) {
            p[idx].start_time = max(current_time,p[idx].arrival_time);
            current_time = p[idx].start_time;;// jodi remaining burst time current burst time er shoman hoy tar mane sheta matro start hocche
        }

        if(burst_remaining[idx]-tq > 0) { // if executing the current time quantum (tq) for the process indexed by idx would leave some burst time remaining
            burst_remaining[idx] -= tq;//burst time kome update hobe
            current_time += tq;//current time update hbe
        }
        else {
            current_time += burst_remaining[idx];
            burst_remaining[idx] = 0;;//the process has completed its execution within the current time quantum
            completed++;

            p[idx].ct = current_time;
            p[idx].turnaround_time = p[idx].ct - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
        }

        for(int i = 1; i < n; i++) {//prothom process chara
            if(burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0) {//only processes that have not yet completed their execution, have already arrived,
                //and have not been marked as added to the queue are eligible to be added
                q.push(i);
                mark[i] = 1;
            }
        }
        if(burst_remaining[idx] > 0) {
            q.push(idx);
        }

        if(q.empty()) {
            for(int i = 1; i < n; i++) {
                if(burst_remaining[i] > 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }

    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;

    sort(p,p+n,compare2);
//This line ensures that after the execution of the Round Robin algorithm and calculation
//of various metrics, the array of processes is sorted based on their process IDs in ascending order.
    cout<<endl;
    cout<<"#P\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {
        cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].start_time<<"\t"<<p[i].ct<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<"\n"<<endl;
    }
    cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
    cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
}
//RoundRobin
