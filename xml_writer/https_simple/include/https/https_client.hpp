#ifndef __HTTPS_CLIENT_H__
#define __HTTPS_CLIENT_H__

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>

#include <string>
#include <memory>
#include <iostream>

// Singleton Design Pattern
class HttpsClient
{
public:
    HttpsClient (const std::string &host,const std::string &port);
    ~HttpsClient ();

    boost::beast::http::response <boost::beast::http::dynamic_body> Get
    (
        const std::string& target, const std::string& query = ""
    );

    boost::beast::http::response <boost::beast::http::dynamic_body> Post
    (
        const std::string& target, const std::string& resource = ""
    );

    boost::beast::http::response <boost::beast::http::dynamic_body> Put
    (
        const std::string& target, const std::string& resource
    );

    boost::beast::http::response <boost::beast::http::dynamic_body> Delete
    (
        const std::string& target
    );

private:
    void Connect ();
    boost::beast::http::response <boost::beast::http::dynamic_body> Send
    (
        boost::beast::http::request <boost::beast::http::string_body>& req
    );
    bool verify_certificate(bool pverified_ok, boost::asio::ssl::verify_context& ctx)
    {
        char subject_name[256];
        X509 *cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
        X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
        std::cout << "Verifying " << subject_name << std::endl;

        return pverified_ok;
    }

private:
    std::string host_;
    std::string port_;

    // required for all boost beast I/O
    boost::asio::io_context io_context_;
    boost::asio::ssl::context ctx_;
    boost::asio::ip::tcp::resolver resolver_;
    boost::beast::ssl_stream<boost::beast::tcp_stream> stream_;
};

#endif // __HTTPS_CLIENT_H__