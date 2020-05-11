#include "processor.h"

#include "linux/processor.h"

std::shared_ptr<Processor> Processor::makeProcessor() {
#ifdef __linux__
    Linux::Processor processor = Linux::Processor::createFromFile();
    return std::move(std::make_unique<Linux::Processor>(processor));
#elif _WIN32
#endif
}