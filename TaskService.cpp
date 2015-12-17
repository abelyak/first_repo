#include "TaskService.h"
#include "TaskServiceFactory.h"

#include "Poco/Util/Option.h"
#include "Poco/Util/HelpFormatter.h"

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerParams.h"

#include <iostream>
#include <sstream>

TaskService::TaskService()
	: _helpRequested(false)
{
}

TaskService::~TaskService()
{
}

void TaskService::initialize(Poco::Util::ServerApplication& self)
{
    loadConfiguration();
    ServerApplication::initialize(self);
}

void TaskService::uninitialize()
{
    ServerApplication::uninitialize();
}

void TaskService::defineOptions(Poco::Util::OptionSet& options)
{
    ServerApplication::defineOptions(options);

    options.addOption(Poco::Util::Option("help", "h", "display argument help information").required(false).repeatable(false).callback(Poco::Util::OptionCallback<TaskService>(this, &TaskService::handleHelp)));
}

void TaskService::handleHelp(const std::string& name, const std::string& value)
{
	Poco::Util::HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader("A web server that serves the current date and time.");
    helpFormatter.format(std::cout);
    stopOptionsProcessing();
    _helpRequested = true;
}

int TaskService::main(const std::vector<std::string>& args)
{
    if (!_helpRequested)
    {
		std::stringstream log;
        
		std::string localHost = config().getString("TaskService.LocalHost", "10.10.210.200");
        int localPort = config().getInt("TaskService.LocalPort", 9999);

		std::string serverHost = config().getString("TaskService.ServerHost", "10.10.210.200");
        int serverPort = config().getInt("TaskService.ServerPort", 9980);

		int registrationTimeout = config().getInt("TaskService.RegistrationTimeout", 30);
		/*
		Poco::Logger& _logger(Poco::Util::Application::instance().logger());

		log << "localHost = " << localHost << std::endl;
		log << "localPort = " << localPort << std::endl;

		log << "serverHost = " << serverHost << std::endl;
		log << "serverPort = " << serverPort << std::endl;

		log << "registrationTimeout = " << registrationTimeout << std::endl;

		_logger.information(log.str());
		*/
		const Poco::Net::SocketAddress localAddress(localHost, localPort);
		const Poco::Net::SocketAddress serverAddress(serverHost, serverPort);

        Poco::Net::ServerSocket svs(localAddress);

        Poco::Net::HTTPServer srv(new TaskServiceFactory(localAddress, serverAddress, registrationTimeout), svs, new Poco::Net::HTTPServerParams);

        srv.start();

        waitForTerminationRequest();

        srv.stop();
    }
    return Application::EXIT_OK;
}