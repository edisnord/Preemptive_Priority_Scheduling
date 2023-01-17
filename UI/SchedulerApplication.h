//
// Created by edish on 1/17/23.
//

#ifndef PREEMPTIVE_SCHEDULERAPPLICATION_H
#define PREEMPTIVE_SCHEDULERAPPLICATION_H
#include "../Scheduler/Scheduler.h"

#include "Wt/WServer.h"
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WTable.h>

using namespace Wt;

class SchedulerApplication : public Wt::WApplication
{
public:
    SchedulerApplication(const Wt::WEnvironment& env);

private:
    Wt::WLineEdit *nameEdit_;
    Wt::WText *greeting_;
};





#endif //PREEMPTIVE_SCHEDULERAPPLICATION_H
