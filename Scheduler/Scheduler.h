//
// Created by edish on 1/15/23.
//

#ifndef PREEMPTIVE_SCHEDULER_H
#define PREEMPTIVE_SCHEDULER_H

#include "Process.h"
#include "vector"
#include "queue"
#include "iostream"
#include <ranges>

#include <algorithm>

class Scheduler {
public:
    Scheduler(const std::string& fileName);

    void addProcess(Process process);

    void addProcessesToWaiting(const std::vector<Process>& processesToAdd);

    void startScheduling();

    Scheduler(std::vector<Process> processes);

    Scheduler();

    const std::vector<Process> &getFinishedProcesses() const;

private:
    std::vector<Process> processes;
    std::vector<Process> finishedProcesses;
    std::priority_queue<Process> processesWaiting;
    std::vector<std::string> processHistory;

    Process currProcess = Process(0,0,0,0);

    int timeCounter{};

    void checkArrivalTimes();

    void shouldReplace(std::vector<Process> arrivedProcesses);

    void replaceCurrentProcess(Process process);

    void mainLoop();

    void getFinalStats();

public:
    const std::vector<std::string> &getProcessHistory() const;

private:

    void finishAndGetNext();

    void nextProcess();

    std::vector<Process> * copyArrivals();

    void removeArrived();
};

#endif //PREEMPTIVE_SCHEDULER_H
