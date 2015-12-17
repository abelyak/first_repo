#ifndef SOLVEHANDLER_H
#define SOLVEHANDLER_H

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Util/Application.h"
#include "Poco/URI.h"
#include "../ServiceManager.h"

class SolveHandler: public Poco::Net::HTTPRequestHandler
{
public:
    SolveHandler(ServiceManager& serviceManager);
	virtual ~SolveHandler();

    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

private:
	ServiceManager& _serviceManager;
	Poco::Logger& _logger;
};

#endif /*SOLVEHANDLER_H*/