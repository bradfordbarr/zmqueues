// vim: et:sts=2:sw=2:ai:sta:cc=80
#include <cstdlib>

#include <getopt.h>
#include <iostream>

#include "utils.h"

static void usage(std::string name) {
  auto frequency = "[-f|--frequency 30.0]";
  auto ipc = "[-i|--ipc ipc://transport]";
  auto sndhwm = "[-s|--sndhwm 1000]";
  auto rcvhwm = "[-r|--rcvhwm 1000]";

  std::cout << "Usage: " << name;
  std::cout << " " << frequency;
  std::cout << " " << ipc;
  std::cout << " " << sndhwm;
  std::cout << " " << rcvhwm;
  std::cout << std::endl;

  std::cout << "  -f,--frequency\tFrequency to process messages." << std::endl;
  std::cout << "  -i,--ipc\t\tLocation of Unix domain socket." << std::endl;
  std::cout << "  -s,--sndhwm\t\tSend high water mark." << std::endl;
  std::cout << "  -r,--rcvhwm\t\tReceive high water mark." << std::endl;
}

void parse_args(
  int argc, char *argv[], double &freq_hz,
  std::string &ipc, int &sndhwm, int &rcvhwm
) {
  static char short_opts[] = ":hf:s:i:r:";
  static struct option long_opts[] = {
    {"help",      optional_argument, 0, 'h'},
    {"frequency", required_argument, 0, 'f'},
    {"ipc",       required_argument, 0, 'i'},
    {"sndhwm",    optional_argument, 0, 's'},
    {"rcvhwm",    optional_argument, 0, 'r'},
    {0,           0,                 0,  0 }
  };

  int c;
  int opt_ind = 0;

  while ((c = getopt_long(argc, argv, short_opts, long_opts, &opt_ind)) > 0) {
    switch (c) {
    case 'h':
      usage(argv[0]);
      exit(EXIT_SUCCESS);
    case 'f':
      freq_hz = std::stod(optarg);
      break;
    case 'i':
      ipc = optarg;
    case 's':
      sndhwm = std::stoi(optarg);
      break;
    case 'r':
      rcvhwm = std::stoi(optarg);
      break;
    default:
      break;
    }
  }
}

void print_header(std::string name, double freq_hz, int sndhwm, int rcvhwm) {
  std::cout << "--------------------------------" << std::endl;
  std::cout << " " << name << std::endl;
  std::cout << "    frequency: " << freq_hz << std::endl;
  std::cout << "    send high water:    " << sndhwm << std::endl;
  std::cout << "    receive high water: " << rcvhwm << std::endl;
  std::cout << "--------------------------------" << std::endl;
}

std::chrono::microseconds hz2sec(double frequency_hz) {
  std::chrono::microseconds duration((int)(1000000 * (1/frequency_hz)));
  return duration;
}

void set_socket_water_mark(zmqpp::socket &sock, int &sndhwm, int &rcvhwm) {
  if (sndhwm != -1) {
    sock.set(zmqpp::socket_option::send_high_water_mark, sndhwm);
  } else {
    sock.get(zmqpp::socket_option::send_high_water_mark, sndhwm);
  }

  if (rcvhwm != -1) {
    sock.set(zmqpp::socket_option::receive_high_water_mark, rcvhwm);
  } else {
    sock.get(zmqpp::socket_option::receive_high_water_mark, rcvhwm);
  }

}
