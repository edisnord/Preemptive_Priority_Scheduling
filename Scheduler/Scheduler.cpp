//
// Created by edish on 1/15/23.
//

#include <fstream>
#include <json/reader.h>
#include "Scheduler.h"

#define INIT_PROCESS Process(0,0,0,0)

Scheduler::Scheduler(): timeCounter(0) {}

Scheduler::Scheduler(const std::string& fileName) {
    std::ifstream ifs(fileName);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()    ) );

    Json::Reader reader;
    Json::Value root;

    reader.parse(content, root, false);

    for(auto process: root["processes"]){
        addProcess(Process(process["processName"].asInt(), process["priority"].asInt(),
                           process["arrivalTime"].asInt(), process["burstTime"].asInt()));
    }
}

Scheduler::Scheduler(std::vector<Process> processes): timeCounter(0) {
    std::sort(processes.begin(), processes.end(), [](Process a, Process b){return a.getArrivalTime() < b.getArrivalTime();});
    this->currProcess = processes.at(0);
    processes.erase(processes.begin());
    this->processes = processes;
}

void Scheduler::addProcess(Process process) {
    processes.push_back(process);
}

void Scheduler::startScheduling() {
    if (this->processes.empty()) {
        std::cout << "No processes available";
        return;
    }
    mainLoop();
}

void Scheduler::mainLoop() {
    //!processes.empty() || !processesWaiting.empty() || currProcess.isFinished()
    while(true){
        //Avoid performance cost if there are no processes that can arrive
        if(!processes.empty())
            checkArrivalTimes();

        //Case when you have processes in the waiting queue and current one is finished
        if(currProcess.isFinished() && !processesWaiting.empty() ){
            finishAndGetNext();
        //Case when our process is the last one
        } else if (currProcess.isFinished() && processes.empty() && processesWaiting.empty()){
            currProcess.recordFinishTime(timeCounter);
            finishedProcesses.push_back(currProcess);
            break;
        }
        processHistory.push_back(std::to_string(currProcess.getProcessName()));
        currProcess.decrementBurstTime();
        timeCounter++;
    }
    getFinalStats();
}

void Scheduler::checkArrivalTimes() {
    auto arrived = copyArrivals();
    if (!(*arrived).empty()) {
        removeArrived();
        shouldReplace(*arrived);
    }
    delete arrived;
}

std::vector<Process>* Scheduler::copyArrivals(){
    auto* arrived = new std::vector<Process>();
    std::copy_if(this->processes.begin(), this->processes.end(), std::back_inserter(*arrived),
                 [this](Process process) {return process.getArrivalTime() == this->timeCounter;});
    return arrived;
}

void Scheduler::removeArrived(){
    std::vector<Process> leftProcesses;
    std::copy_if(this->processes.begin(), this->processes.end(), std::back_inserter(leftProcesses),
                 [this](Process process) { return process.getArrivalTime() != this->timeCounter; });
    processes.swap(leftProcesses);
}

void Scheduler::shouldReplace(std::vector<Process> arrivedProcesses){
    if(arrivedProcesses.size() > 1)
        std::sort(arrivedProcesses.begin(), arrivedProcesses.end());

    if(currProcess == INIT_PROCESS){
        currProcess = arrivedProcesses.at(0);
        arrivedProcesses.erase(arrivedProcesses.begin());
    } else if (arrivedProcesses.at(0) > currProcess) {
        replaceCurrentProcess(arrivedProcesses.at(0));
        arrivedProcesses.erase(arrivedProcesses.begin());
    }
    addProcessesToWaiting(arrivedProcesses);
}

void Scheduler::replaceCurrentProcess(Process process){
    if(!currProcess.isFinished())
        this->processesWaiting.push(this->currProcess);
    else {
        currProcess.recordFinishTime(timeCounter);
        this->finishedProcesses.push_back(this->currProcess);
    }

    process.recordStartingTime(timeCounter);
    this->currProcess = process;
}

void Scheduler::addProcessesToWaiting(const std::vector<Process>& processesToAdd) {
    for(auto process : processesToAdd){
        processesWaiting.push(process);
    }
}

void Scheduler::finishAndGetNext() {
    currProcess.recordFinishTime(timeCounter);
    finishedProcesses.push_back(currProcess);
    nextProcess();
}

void Scheduler::nextProcess() {
    currProcess = processesWaiting.top();
    currProcess.recordStartingTime(timeCounter);
    processesWaiting.pop();
}

void Scheduler::getFinalStats(){
    double totalWaitingTime = 0;
    std::sort(finishedProcesses.begin(),
              finishedProcesses.end(),
              [](Process a, Process b){return a.getProcessName() < b.getProcessName();});

    for(auto process: finishedProcesses){
        std::cout   << process.toString() <<
                    " TAT = " << process.getTurnaroundTime() <<
                    " | WT: " << process.getWaitingTime() <<
                    " |\n";
        totalWaitingTime += process.getWaitingTime();
    }
    std::cout << "AWT: " << totalWaitingTime / (double)finishedProcesses.size() << "\n";
}

const std::vector<Process> &Scheduler::getFinishedProcesses() const {
    return finishedProcesses;
}

const std::vector<std::string> &Scheduler::getProcessHistory() const {
    return processHistory;
}
