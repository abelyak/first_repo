#ifndef RESULTHANDLER_H
#define RESULTHANDLER_H

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Util/Application.h"
#include "../ServiceManager.h"

class ResultHandler: public Poco::Net::HTTPRequestHandler
{
public:
    ResultHandler(ServiceManager& serviceManager);
	
	virtual ~ResultHandler();

    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

private:
	ServiceManager& _serviceManager;
	Poco::Logger& _logger;
};

#endif /*RESULTHANDLER_H*/