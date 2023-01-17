#include "Scheduler/Scheduler.h"
#include <Wt/WApplication.h>
#include "UI/SchedulerApplication.h"


int main(int argc, char** argv){
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return std::make_unique<SchedulerApplication>(env);
    });

}