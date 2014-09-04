ArduinoDuePolarSSLClient
========================

This is a sample Arduino Due sketch connecting to a PolarSSL server using PSK authentication. It uses a stripped-down version of the PolarSSL library, so that it can fit in the Due.

This sketch should be built from the command-line, not the Arduino IDE. It includes a Makefile based on Paul Dreik's [Arduino Due Makefile](https://github.com/pauldreik/arduino-due-makefile).

In the Makefile, change the paths to point to your Arduino installation.

Do `make compile` to compile, `make upload` to upload the sketch to the Due. Check the comments to see how the upload works (differs on Linux and Windows).

To build on Windows, you will need some Unix tools like GNU make, ls, etc. An easy way to get them all is via [msysgit](https://github.com/msysgit/msysgit). The build should be launched from a Windows command prompt, not Cygwin.

For your convenience, the repo includes a pre-compiled version of the PolarSSL library (`libpolarssl.a`). If you want to rebuild from scratch, you should look at my [PolarSSL fork](https://github.com/tomconte/polarssl) that is configured for a stripped-down PSK configuration and includes a modifile CMake configuration to cross-compile for the Arduino Due.
