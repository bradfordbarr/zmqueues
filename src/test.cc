// vim: et:sts=2:sw=2:ai:sta:cc=80
#include <cstdlib>
#include <getopt.h>

#include <iostream>

#include <zmqpp/zmqpp.hpp>

static char short_opts[] = ":n:";
static struct option long_opts[] = {
  {"name", required_argument, 0, 'n'},
  {0,      0,                 0,  0 }
};

int main(int argc, char *argv[]) {
  int c;
  int optind = 0;

  std::string name {"world"};

  while ((c = getopt_long(argc, argv, short_opts, long_opts, &optind)) > 0) {
    switch (c) {
    case 'n':
      name = optarg;
      break;
    default:
      break;
    }
  }

  std::cout << "Hello " << name << "!" << std::endl;

  return EXIT_SUCCESS;
}
