//
// Created by edish on 1/17/23.
//

#include "SchedulerApplication.h"
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WTable.h>


#define schedText(str) addWidget(std::make_unique<Wt::WText>(str));
#define procText(str) schedText(std::to_string(str))

SchedulerApplication::SchedulerApplication(const Wt::WEnvironment& env)
        : Wt::WApplication(env)
{
    setTitle("Preemptive Priority Scheduling");
    useStyleSheet("stylesheet.css");

    root()->addWidget(std::make_unique<Wt::WText>("Insert process JSON file path"));
    nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    Wt::WPushButton *button = root()->addWidget(std::make_unique<Wt::WPushButton>("Run algorithm."));
    root()->addWidget(std::make_unique<Wt::WBreak>());
    Wt::WTable *table = root()->addWidget(std::make_unique<Wt::WTable>());
    auto ganttext = root()->addWidget(std::make_unique<Wt::WText>());
    Wt::WTable *gantt = root()->addWidget(std::make_unique<Wt::WTable>());
    table->setStyleClass("schedTable");

    auto greet = [this, table, gantt, ganttext]() mutable{
        Scheduler scheduler = Scheduler(nameEdit_->text().toUTF8());
        scheduler.startScheduling();
        root()->removeWidget(table);
        root()->removeWidget(ganttext);
        root()->removeWidget(gantt);
        table = root()->addWidget(std::make_unique<Wt::WTable>());
        ganttext = root()->addWidget(std::make_unique<Wt::WText>("Gantt chart:"));
        gantt = root()->addWidget(std::make_unique<Wt::WTable>());
        int index = 1;
        table->elementAt(0, 0)->schedText("PID");
        table->elementAt(0, 1)->schedText("Burst Time");
        table->elementAt(0, 2)->schedText("Arrival Time");
        table->elementAt(0, 3)->schedText("Priority");
        table->elementAt(0, 4)->schedText("Start Time");
        table->elementAt(0, 5)->schedText("Finish Time");
        table->elementAt(0, 6)->schedText("Turnaround Time");
        table->elementAt(0, 7)->schedText("Waiting Time");
        for(auto process : scheduler.getFinishedProcesses()){
            table->elementAt(index, 0)->procText(process.getProcessName());
            table->elementAt(index, 1)->procText(process.getBurstTime());
            table->elementAt(index, 2)->procText(process.getArrivalTime());
            table->elementAt(index, 3)->procText(process.getPriority());
            table->elementAt(index, 4)->procText(process.getStartingTime());
            table->elementAt(index, 5)->procText(process.getFinishingTime());
            table->elementAt(index, 6)->procText(process.getTurnaroundTime());
            table->elementAt(index, 7)->procText(process.getWaitingTime());
            index++;
        }
        int ganttIndex = 0;
        for(const auto& a : scheduler.getProcessHistory()){
            auto num = gantt->elementAt(0, ganttIndex);
            num->procText(ganttIndex+1);
            auto process = gantt->elementAt(1, ganttIndex);
            process->schedText("P" + a);
            ganttIndex++;
        }

    };
    button->clicked().connect(greet);
}