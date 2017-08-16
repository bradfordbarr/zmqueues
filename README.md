# ZMQueues

This repository has some small utilities for testing the queuing mechanisms in
ZMQ. The cases covered are: push and pull, push and pull reactor, pub and sub.

Each utility has a frequency with which it sends or processes (sleeps)
messages. Each utility also has a configurable send high water mark and receive
high water mark.

More information on water marks in ZMQ can be found [here][1]. More information
on the different ZMQ socket types and their error modes can be found [here][2].

[1]: http://api.zeromq.org/4-2:zmq-getsockopt
[2]: http://api.zeromq.org/4-2:zmq-socket
