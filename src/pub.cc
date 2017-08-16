// vim: et:sts=2:sw=2:ai:sta:cc=80
#include <cstdlib>

#include <iostream>
#include <thread>
#include <chrono>

#include <zmqpp/zmqpp.hpp>

#include "utils.h"

int main(int argc, char *argv[]) {
  int sequence_number = 0;
  int sndhwm = -1;
  int rcvhwm = -1;
  double frequency_hz = 30.0;
  std::string ipc_path("ipc://transport");

  parse_args(argc, argv, frequency_hz, ipc_path, sndhwm, rcvhwm);

  zmqpp::context context;
  zmqpp::socket pub(context, zmqpp::socket_type::pub);
  pub.bind(ipc_path);

  set_socket_water_mark(pub, sndhwm, rcvhwm);

  auto duration = hz2sec(frequency_hz);

  print_header(argv[0], frequency_hz, sndhwm, rcvhwm);
  
  while (true) {
    std::cout << "Sending packet " << sequence_number++ << std::endl;

    zmqpp::message request;
    request << std::to_string(sequence_number);
    pub.send(request);

    std::this_thread::sleep_for(duration);
  }

  return EXIT_SUCCESS;
}
