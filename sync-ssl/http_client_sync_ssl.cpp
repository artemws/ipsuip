#include "../functions.h"
#include "root_certificates.h"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/beast/ssl/ssl_stream.hpp>


// Performs an HTTP GET and prints the response
std::vector<std::string> get(const std::string &host,
                             const std::string &target) {
  using namespace boost;

  // The io_context is required for all I/O
  asio::io_context ioc;

  // The SSL context is required, and holds certificates
  asio::ssl::context ctx(asio::ssl::context::tlsv12_client);

  // This holds the root certificate used for verification
  ipsuip::load_root_certificates(ctx);

  // Verify the remote server's certificate
  ctx.set_verify_mode(asio::ssl::verify_peer);

  // These objects perform our I/O
  asio::ip::tcp::resolver resolver(ioc);
  beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

  // Set SNI Hostname (many hosts need this to handshake successfully)
  if (!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str())) {
    beast::error_code ec{static_cast<int>(::ERR_get_error()),
                         asio::error::get_ssl_category()};
    throw beast::system_error{ec};
  }

  // Look up the domain name
  auto const results = resolver.resolve(host, "443");

  // Make the connection on the IP address we get from a lookup
  beast::get_lowest_layer(stream).connect(results);

  // Perform the SSL handshake
  stream.handshake(asio::ssl::stream_base::client);

  // Set up an HTTP GET request message
  beast::http::request<beast::http::string_body> req(beast::http::verb::get,
                                                     target, 11);
  req.set(beast::http::field::host, host);
  req.set(beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

  // Send the HTTP request to the remote host
  beast::http::write(stream, req);

  // This buffer is used for reading and must be persisted
  auto buffer = std::make_unique<beast::flat_buffer>();

  // Declare a container to hold the response
  auto parser = std::make_unique<beast::http::response_parser<beast::http::string_body>>();

  // Allow for an unlimited body size
  parser->body_limit((std::numeric_limits<std::uint64_t>::max)());

  system::error_code ecr;
  std::size_t bytes = beast::http::read(stream, *buffer, *parser, ecr);

  std::cout << "bytes: " << bytes << std::endl;
  std::cout << "Download " << ipsuip::HumanReadable(bytes) << "\n";

  //if (ecr) {
  //  std::cerr << ecr.value() << " " << ecr.what() << std::endl;
  //  throw beast::system_error{ecr};
  //}

  beast::error_code ec;
  // Gracefully close the stream
  stream.shutdown(ec);

  std::vector<std::string> v;

  auto ss = std::make_unique<std::stringstream>(parser->get().body());

  for (std::string temp; std::getline(*ss, temp);) {
    v.emplace_back(temp);
  }

  if (v.empty())
    throw std::runtime_error("Vector v empty in fuction get()");
  return v;

  if (ec == asio::error::eof) {
    std::cerr << ec.value() << " " << ec.what() << std::endl;
    ec = {};
  }

  //if (ec)
  //  throw beast::system_error{ec};
  return std::vector<std::string>();
}
