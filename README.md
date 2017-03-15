# tempsense

Command line utilty to read out data from the AVR Temp Sensor made by Diamex GmbH. 

As seen here: http://www.led-genial.de/USB-Temperatur-Sensor-Tester-fuer-DS18B20

## Dependencies
- clang (or gcc) in some newer incarnation 
- [hidapi](https://github.com/signal11/hidapi)

## Build & Run
1. download, build and install [hidapi](https://github.com/signal11/hidapi) (or 'apt-get install libhidapi-dev' on ubuntu/debian)
2. build with:
   - MacOS X: `./build_osx.sh`
   - Linux with clang: `./build_pi.sh`
   - Linux with GCC: `./build_gcc.sh`
3. Connect the Temp Sensor and run `./tempsense` (on the pi you need to sudo)
	
## Copyright & License

This code is licensed under the Affero GPL3 License!
(c) J. Szpilewski in 2014, js@suborbital.io
