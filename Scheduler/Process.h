//
// Created by edish on 1/15/23.
//

#ifndef PREEMPTIVE_PROCESS_H
#define PREEMPTIVE_PROCESS_H

#include <string>

class Process {
public:
    Process(unsigned int processName, unsigned int priority, unsigned int arrivalTime, unsigned int burstTime);

    [[nodiscard]] bool isFinished() const;

    void decrementBurstTime();

    [[nodiscard]] unsigned int getProcessName() const;

    unsigned int getPriority() const;

    [[nodiscard]] unsigned int getArrivalTime() const;

    [[nodiscard]] unsigned int getBurstTime() const;


    void recordStartingTime(unsigned int time);

    void recordFinishTime(unsigned int time);

    [[nodiscard]] unsigned int getFinishingTime() const;

    [[nodiscard]] unsigned int getStartingTime() const;

    [[nodiscard]] unsigned int getTurnaroundTime() const;

    [[nodiscard]] unsigned int getWaitingTime() const;

    bool operator<(const Process& r) const;

    bool operator>(const Process& r) const;

    bool operator==(const Process& r) const;

    static Process fromJson(const std::string& JSON);

    [[nodiscard]] std::string toString() const;
private:
    unsigned int recordedFinishingTime = 0;
    unsigned int recordedStartingTime = 0;
    unsigned int processName;
    unsigned int priority;
    unsigned int arrivalTime;
    unsigned int burstTime;
    unsigned int initBurstTime;
};

#endif //PREEMPTIVE_PROCESS_H
