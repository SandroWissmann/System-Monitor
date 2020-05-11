#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <memory>
#include <vector>

class Processor {
   public:
    virtual ~Processor() = default;
    virtual float Utilization() const = 0;
    virtual std::vector<float> CoreUtilizations() const = 0;
    virtual int CountOfCores() const = 0;

    static std::shared_ptr<Processor> makeProcessor();
};

#endif