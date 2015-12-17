#include "ResultHandler.h"
#include "Poco/URI.h"
#include "Poco/Dynamic/Var.h"

ResultHandler::ResultHandler(ServiceManager& serviceManager)
	: _serviceManager(serviceManager)
	, _logger(Poco::Util::Application::instance().logger())
{
}

ResultHandler::~ResultHandler()
{
}

void ResultHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
    _logger.information("Request from " + request.clientAddress().toString());
	response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

	Poco::URI uri(request.getURI());
	Poco::URI::QueryParameters qp = uri.getQueryParameters();
	auto jsonpIt = std::find_if(qp.begin(), qp.end(), [] (const Poco::URI::QueryParameters::value_type& i) { return i.first == "jsonp";});
	auto idIt = std::find_if(qp.begin(), qp.end(), [] (const Poco::URI::QueryParameters::value_type& i) { return i.first == "id";});

	int id = 0;
	if (idIt != qp.end())
	{		
		Poco::Dynamic::Var var(idIt->second);
		id = var.convert<int>();
		_logger.information("ResultHandler: Id: " + idIt->second);
	}

	std::string calculationResult = _serviceManager.GetCalculationResult(id);
	_logger.information("Calculation result: " + calculationResult);
		
	std::ostream& ostr = response.send();
	if (jsonpIt != qp.end())
	{	
		const std::string& jsonpFunc = jsonpIt->second;
		ostr << jsonpFunc << "([\"" << calculationResult << "\"]);\n\n";
	}
	else
	{
		ostr << calculationResult;
	}
}
