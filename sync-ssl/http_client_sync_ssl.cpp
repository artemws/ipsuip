#include "root_certificates.h"
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>

#include <iostream>
#include <sstream>

enum class Variant { CONTINENT, COUNTRY, OTHER };

// Performs an HTTP GET and prints the response
std::string get(const std::string &host, const std::string &target)
{
    std::stringstream ss;

    try
    {
        // The io_context is required for all I/O
        boost::asio::io_context ioc;

        // The SSL context is required, and holds certificates
        boost::asio::ssl::context ctx(boost::asio::ssl::context::tlsv12_client);

        // This holds the root certificate used for verification
        ipsuip::load_root_certificates(ctx);

        // Verify the remote server's certificate
        ctx.set_verify_mode(boost::asio::ssl::verify_peer);

        // These objects perform our I/O
        boost::asio::ip::tcp::resolver resolver(ioc);
        boost::beast::ssl_stream<boost::beast::tcp_stream> stream(ioc, ctx);

        // Set SNI Hostname (many hosts need this to handshake successfully)
        if (!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str()))
        {
            boost::beast::error_code ec{static_cast<int>(::ERR_get_error()),
                                        boost::asio::error::get_ssl_category()};
            throw boost::beast::system_error{ec};
        }

        // Look up the domain name
        auto const results = resolver.resolve(host, "443");

        // Make the connection on the IP address we get from a lookup
        boost::beast::get_lowest_layer(stream).connect(results);

        // Perform the SSL handshake
        stream.handshake(boost::asio::ssl::stream_base::client);

        // Set up an HTTP GET request message
        boost::beast::http::request<boost::beast::http::string_body>
            req(boost::beast::http::verb::get, target, 11);
        req.set(boost::beast::http::field::host, host);
        req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // Send the HTTP request to the remote host
        boost::beast::http::write(stream, req);

        // This buffer is used for reading and must be persisted
        boost::beast::flat_buffer buffer;

        // Declare a container to hold the response
        // http::response<http::dynamic_body> res;

        boost::beast::http::response_parser<boost::beast::http::string_body> parser;

        // Allow for an unlimited body size
        parser.body_limit((std::numeric_limits<std::uint64_t>::max)());

        // Receive the HTTP response
        boost::beast::http::read(stream, buffer, parser);

        // Write the message to standard out
        // std::cout << res << std::endl;
        // std::ofstream ofs("index.html");
        // ofs << res;

        ss << parser.get().body();
        //std::cout << parser.get().base() << std::endl;

        // Gracefully close the stream
        boost::beast::error_code ec;
        stream.shutdown(ec);

        if (ec == boost::asio::error::eof) {
            // Rationale:
            // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
            ec = {};
        }
        if (ec)
            throw boost::beast::system_error{ec};

        // If we get here then the connection is closed gracefully
    }
    catch (std::exception const &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "http_client_sync_ssl" << std::endl;
    }

    return ss.str();
}
