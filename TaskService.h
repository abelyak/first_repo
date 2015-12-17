#ifndef TASKSERVICE_H
#define TASKSERVICE_H

#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/OptionSet.h"

class TaskService: public Poco::Util::ServerApplication
{
public:
    TaskService();

    virtual ~TaskService();

protected:
    void initialize(Poco::Util::ServerApplication& self);

    void uninitialize();

    void defineOptions(Poco::Util::OptionSet& options);

    void handleHelp(const std::string& name, const std::string& value);

    int main(const std::vector<std::string>& args);

private:
    bool _helpRequested;
};



#endif /* TASKSERVICE_H */
