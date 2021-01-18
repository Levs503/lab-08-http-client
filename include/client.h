//
// Created by Лев on 17.01.2021.
//

#ifndef TEMPLATE_CLIENT_H
#define TEMPLATE_CLIENT_H
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>
#include <boost/thread/thread.hpp>
#include <chrono>
#include <header.hpp>
#include <iostream>

using boost::asio::io_service;
using boost::asio::ip::tcp;

static io_service service;

class client {
 public:
  tcp::endpoint ep;
  tcp::socket socket;
  bool connection;

  client(tcp::endpoint edp) : ep(edp), socket(service){};
  client()
      : ep(boost::asio::ip::address::from_string("127.0.0.1"), 8001),
        socket(service){};
  void connect() {
    socket.connect(ep);
    connection = true;
  }

  void write(std::string msg) {
    msg += '\n';
    socket.write_some(boost::asio::buffer(msg));
  }

  std::string read_answer() {
    while (!socket.available()) {
    }
    std::string com;
    boost::asio::streambuf buffer;
    boost::asio::read_until(socket, buffer, '\n');
    std::istream input(&buffer);
    std::getline(input, com);
    return com;
  }

  void Check_connection() {
    while (true) {
      if (connection) {
        boost::this_thread::sleep(
            boost::posix_time::millisec((rand() % 6000) + 1000));
        write("Ping");
        std::cout << read_answer() << std::endl;
      }
    }
  }
};

#endif  // TEMPLATE_CLIENT_H
