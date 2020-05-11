#include "processor.h"

#include "linux/linux_processor.h"

std::shared_ptr<Processor> Processor::makeProcessor() {
#ifdef __linux__
    LinuxProcessor processor = LinuxProcessor::createFromFile();
    return std::move(std::make_unique<LinuxProcessor>(processor));
#elif _WIN32
#endif
}