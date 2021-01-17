// Copyright 2020 Your Name <your_email>

#include <boost/thread/thread.hpp>
#include <header.hpp>
#include <iostream>

#include "client.h"

static client one_client;

using boost::asio::io_service;
using boost::asio::ip::tcp;

void Check() { one_client.Check_connection(); }

void start() {
  std::cout << "введите имя пользователя" << std::endl;
  std::string username;
  std::cin >> username;
  tcp::endpoint endp(boost::asio::ip::address::from_string("127.0.0.1"), 8001);
  one_client.connect();
  one_client.write(username);
  std::cout << one_client.read_answer() << std::endl;
  while (true) {
    std::string com;
    std::cout << "enter command" << std::endl;
    std::cin >> com;
    one_client.write(com);
    std::cout << one_client.read_answer() << std::endl;
  }
}

int main() {
  boost::thread_group threads;
  // threads.create_thread(Check);
  threads.create_thread(start);
  threads.join_all();
}
