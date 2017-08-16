// vim: et:sts=2:sw=2:ai:sta:cc=80
#include <cstdlib>

#include <iostream>
#include <thread>
#include <chrono>

#include <zmqpp/zmqpp.hpp>

#include "utils.h"

int main(int argc, char *argv[]) {
  int sndhwm = -1;
  int rcvhwm = -1;
  double frequency_hz = 30.0;
  std::string ipc_path("ipc://transport");

  parse_args(argc, argv, frequency_hz, ipc_path, sndhwm, rcvhwm);

  zmqpp::context context;
  zmqpp::socket pull(context, zmqpp::socket_type::pull);
  pull.bind(ipc_path);

  set_socket_water_mark(pull, sndhwm, rcvhwm);

  auto duration = hz2sec(frequency_hz);

  print_header(argv[0], frequency_hz, sndhwm, rcvhwm);

  zmqpp::reactor reactor;
  reactor.add(pull, [&]() {
    std::this_thread::sleep_for(duration);

    zmqpp::message resp;
    pull.receive(resp);

    std::cout << "Receiving packet " << resp.get(0) << std::endl;

    return true;
  });

  while (true) {
    reactor.poll();
  }

  return EXIT_SUCCESS;
}
