#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <memory>
#include <vector>

namespace Sysmon {

class Processor {
   public:
    virtual ~Processor() = default;
    virtual double Utilization() const = 0;
    virtual std::vector<double> CoreUtilizations() const = 0;
    virtual int CountOfCores() const = 0;

    static std::shared_ptr<Processor> makeProcessor();
};

}  // namespace Sysmon

#endif