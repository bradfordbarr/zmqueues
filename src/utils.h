// vim: et:sts=2:sw=2:ai:sta:cc=80
#ifndef _ZMQUEUES_UTILS_
#define _ZMQUEUES_UTILS_

#include <chrono>
#include <string>

#include <zmqpp/zmqpp.hpp>

void parse_args(
  int argc, char *argv[], double &freq_hz,
  std::string &ipc, int &sndhwm, int &rcvhwm
);

void print_header(std::string name, double freq_hz, int sndhwm, int rcvhwm);

std::chrono::microseconds hz2sec(double frequency);

void set_socket_water_mark(zmqpp::socket &sock, int &sndhwm, int &rcvhwm);

#endif /* _ZMQUEUES_UTILS_ */
