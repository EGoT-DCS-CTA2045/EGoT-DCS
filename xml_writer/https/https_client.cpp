#include "include/https/https_client.hpp"
#include "include/https/root_certificates.hpp"

// alias to make things easier to read
namespace bb = boost::beast;
namespace net = boost::asio; 
namespace ssl = net::ssl; 

HttpsClient::HttpsClient(const std::string &host, const std::string &port) 
    : host_(host), 
    port_(port), 
    ssl_context_(ssl::context::tlsv12_client), 
    resolver_(io_context_),
    stream_(io_context_, ssl_context_)
{
    load_root_certificates(ssl_context_);

    ssl_context_.set_verify_mode(
        ssl::context::verify_peer 
        | ssl::context::verify_fail_if_no_peer_cert
    );

    // Set SNI Hostname (many hosts need this to handshake successfully)
    if(! SSL_set_tlsext_host_name(stream_.native_handle(), host_.c_str()))
    {
        bb::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
        throw bb::system_error{ec};
    }

    ssl_context_.set_default_verify_paths();

    ssl_context_.set_verify_mode(ssl::verify_peer);
}

HttpsClient::~HttpsClient ()
{
    // do nothing
}

bb::http::response <bb::http::dynamic_body>
HttpsClient::Get(const std::string& target, const std::string& query)
{
    std::string href = target + query;
    bb::http::request <bb::http::string_body> req
    {
        bb::http::verb::get, href, 11
    };
    req.set(bb::http::field::host, host_);

    req.prepare_payload();
    return HttpsClient::Send (req);
}

bb::http::response <bb::http::dynamic_body>
HttpsClient::Post(const std::string& target, const std::string& resource)
{
    bb::http::request <bb::http::string_body> req
    {
        bb::http::verb::post, target, 11
    };
    req.set(bb::http::field::host, host_);

    req.body() = resource;
    req.prepare_payload();

    return HttpsClient::Send (req);
}

bb::http::response <bb::http::dynamic_body>
HttpsClient::Put(const std::string& target, const std::string& resource)
{
    bb::http::request <bb::http::string_body> req
    {
        bb::http::verb::put, target, 11
    };
    req.set(bb::http::field::host, host_);

    req.body() = resource;
    req.prepare_payload();

    return HttpsClient::Send (req);
}

bb::http::response <bb::http::dynamic_body>
HttpsClient::Delete(const std::string& target)
{
    bb::http::request <bb::http::string_body> req
    {
        bb::http::verb::delete_, target, 11
    };
    req.set(bb::http::field::host, host_);

    req.prepare_payload();

    return HttpsClient::Send (req);
}

void HttpsClient::Connect() 
{
    // Make the connection on the IP address we get from a lookup
    bb::get_lowest_layer(stream_).connect(resolver_.resolve(host_, port_));
    
    stream_.handshake(ssl::stream_base::client);
}

bb::http::response <bb::http::dynamic_body>
HttpsClient::Send(bb::http::request<bb::http::string_body>& req)
{
    HttpsClient::Connect();

	// Send the HTTP request to the remote host
	bb::http::write(stream_, req);

	// This buffer is used for reading and must be persisted
	bb::flat_buffer buffer;

	// Declare a container to hold the response
	bb::http::response<bb::http::dynamic_body> res;

	// Receive the HTTP response
	bb::http::read(stream_, buffer, res);

    boost::system::error_code ec;
    stream_.shutdown(ec);
    if(ec == net::error::eof)
    {
        // Rationale:
        // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
        ec = {};
    }
    if(ec)
    {
        throw bb::system_error{ec};
    }

	return res;
}