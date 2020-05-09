#include "processor.h"

#include "parser.h"

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() {
    float totalTime = Parser::Jiffies();
    float activeTime = Parser::ActiveJiffies();
    return activeTime / totalTime;
}