#pragma once
#include <boost/asio/ssl.hpp>

namespace detail
{
    void load_root_certificates(boost::asio::ssl::context &ctx, boost::system::error_code &ec);
}

void load_root_certificates(boost::asio::ssl::context &ctx, boost::system::error_code &ec);

void load_root_certificates(boost::asio::ssl::context &ctx);
