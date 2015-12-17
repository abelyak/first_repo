#include "SolveHandler.h"

SolveHandler::SolveHandler(ServiceManager& serviceManager)
	: _serviceManager(serviceManager)
	, _logger(Poco::Util::Application::instance().logger())
{
}

SolveHandler::~SolveHandler()
{
}

void SolveHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
    _logger.information("Request from " + request.clientAddress().toString());
	response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

	Poco::URI uri(request.getURI());
	Poco::URI::QueryParameters qp = uri.getQueryParameters();
	auto jsonpIt = std::find_if(qp.begin(), qp.end(), [] (const Poco::URI::QueryParameters::value_type& i) { return i.first == "jsonp";});

	std::string solveUrl = _serviceManager.GetSolveUrl(qp);
	_logger.information("Solve Url: " + solveUrl);
		
	std::ostream& ostr = response.send();
	if (jsonpIt != qp.end())
	{	
		const std::string& jsonpFunc = jsonpIt->second;
		ostr << jsonpFunc << "([\"" << solveUrl << "\"]);\n\n";
	}
	else
	{
		ostr << solveUrl;
	}
}