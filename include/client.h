//
// Created by Лев on 17.01.2021.
//

#ifndef TEMPLATE_CLIENT_H
#define TEMPLATE_CLIENT_H
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

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
  std::string username;

  client(std::string a, tcp::enpoint ep): username(a), socket(service), ep(ep){};
  client();
  void connect(){
    socket.connect(ep, 8001);
  }

  void write(std::string msg){
    socket.write(buffer(msg));
  }

  std::string read_answer(){
    std::string com;
    boost::asio::streambuf buffer;
    boost::asio::read_until(socket, buffer, '\n');
    std::istream input(&buffer);
    std::getline(input, com);
    return com;
  }

  void Check_connection(){

  }

};

#endif  // TEMPLATE_CLIENT_H
