cmake_minimum_required(VERSION 3.24)
project(Preemptive)

set(CMAKE_CXX_STANDARD 17)

add_executable(Preemptive main.cpp Scheduler/Process.cpp Scheduler/Process.h Scheduler/Scheduler.cpp Scheduler/Scheduler.h UI/SchedulerApplication.cpp UI/SchedulerApplication.h)
target_link_libraries(Preemptive jsoncpp wt wthttp)