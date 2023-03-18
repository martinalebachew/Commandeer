// Browser.cpp
// (C) Martin Alebachew, 2023

#include "pch.h"
#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <json/json.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "Browser.h"

using json = nlohmann::json;
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

Browser::Browser(std::string& execName, std::string& execPath, std::string& flags, OS* os) :
	_execName(execName), _execPath(execPath), _flags(flags), _os(os) { }

Browser::Browser(std::string execName, std::string execPath, std::string flags, OS* os) :
	_execName(execName), _execPath(execPath), _flags(flags), _os(os) { }

bool Browser::Kill() const {
	return _os->KillProcessByExecName(_execName);
}

bool Browser::LaunchWithFlags() const {
	return _os->LaunchBrowserExec(_execPath, _flags);
}

static size_t WritePageToStringCallback(void* contents, size_t size, size_t nmemb, std::string* string) {
	size_t realSize = size * nmemb;
	string->append((char*)contents, realSize);
	return realSize;
}

std::string Browser::ParseDebugEndpoint() const {
	std::string debugEndpoint = "";
	CURL* curl = curl_easy_init();

	if (curl) {
		std::string jsonBuffer;
		curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:9222/json");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WritePageToStringCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonBuffer);
		// curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		if (!curl_easy_perform(curl)) {
			json data = json::parse(jsonBuffer);
			debugEndpoint = data[0]["webSocketDebuggerUrl"];
		}
		curl_easy_cleanup(curl);
	}

	return debugEndpoint;
}

void Browser::WaitUntilEndpointAccessible() const {
	_os->Wait(7);
	return;
}

std::string Browser::GetAllCookies(std::string endpoint) const {
	try {
		beast::flat_buffer cookiesBuffer;

		net::io_context io_context;
		tcp::resolver resolver { io_context };
		websocket::stream<tcp::socket> ws { io_context };

		std::cout << "Fetching cookies via WebSocket" << std::endl;
		auto const results = resolver.resolve("127.0.0.1", "9222");
		auto ep = net::connect(ws.next_layer(), results);

		std::string endpoint_path = endpoint.substr(endpoint.find("9222") + std::string("9222").size());
		ws.handshake("localhost", endpoint_path);

		ws.write(net::buffer(std::string(R"({"id": 1, "method": "Network.getAllCookies"})")));
		ws.read(cookiesBuffer);
		// ws.close(websocket::close_code::normal); FAILS for unknown reason
		
		return beast::buffers_to_string(cookiesBuffer.data());
	}
	catch(const std::exception& e) {
		std::cerr << "Failed to get cookies: " << e.what() << std::endl;
	}

	return "";
}

bool Browser::DumpJSONIntoFile(std::string cookies) const {
	try {
		std::ofstream cookiesFile("cookies.cmdr");
		cookiesFile << json::parse(cookies)["result"]["cookies"].dump(4);
		cookiesFile.close();
	}
	catch (const std::exception& e) {
		std::cerr << "Failed to write cookies file: " << e.what() << std::endl;
		return false;
	}

	std::cout << "Cookies dumped into cookies.cmdr on working directory." << std::endl;
	return true;
}