//
// Created by edish on 1/15/23.
//
#include "Process.h"
#include <json/reader.h>
#include <json/value.h>

Process::Process(unsigned int processName, unsigned int priority, unsigned int arrivalTime, unsigned int burstTime) :
        processName(processName), priority(priority), arrivalTime(arrivalTime), burstTime(burstTime),
        initBurstTime(burstTime) {}

[[nodiscard]] bool Process::isFinished() const {
    return !burstTime;
}

void Process::decrementBurstTime() {
    burstTime--;
}

[[nodiscard]] unsigned int Process::getProcessName() const {
    return processName;
}


[[nodiscard]] unsigned int Process::getArrivalTime() const {
    return arrivalTime;
}


[[nodiscard]] unsigned int Process::getBurstTime() const {
    return initBurstTime;
}

bool Process::operator<(const Process &r) const {
    return this->priority > r.priority;
}

bool Process::operator>(const Process &r) const {
    return this->priority < r.priority;
}

void Process::recordStartingTime(unsigned int time) {
    this->recordedStartingTime = recordedStartingTime ? recordedStartingTime : time;
}

void Process::recordFinishTime(unsigned int time) {
    this->recordedFinishingTime = recordedFinishingTime ? recordedFinishingTime : time;
}

unsigned int Process::getFinishingTime() const {
    return recordedFinishingTime;
}

unsigned int Process::getStartingTime() const {
    return recordedStartingTime;
}

unsigned int Process::getTurnaroundTime() const {
    return getFinishingTime() - getArrivalTime();
}

unsigned int Process::getWaitingTime() const {
    return getTurnaroundTime() - getBurstTime();
}

bool Process::operator==(const Process &r) const {
    return this->burstTime == r.burstTime && this->priority == r.priority
           && this->arrivalTime == r.arrivalTime && this->processName == r.processName;
}

Process Process::fromJson(const std::string &JSON) {
    Json::Reader reader;
    Json::Value process;

    reader.parse(JSON, process, false);

    return {process["processName"].asUInt(), process["priority"].asUInt(),
            process["arrivalTime"].asUInt(), process["burstTime"].asUInt()};
}

std::string Process::toString() const {
    return "| PID: " + std::to_string(processName) + " | Arrival Time:" + std::to_string(arrivalTime)
           + " | Burst Time: " + std::to_string(initBurstTime) + " | Priority: " + std::to_string(priority)
           + " | Start time: " + std::to_string(getStartingTime())
           + " | Finish time: " + std::to_string(getFinishingTime()) + " |";
}

unsigned int Process::getPriority() const {
    return priority;
}
