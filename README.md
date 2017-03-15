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
3. Connect the Temp Sensor and run
   - MacOS X: `./tempsense`
   - Linux: `sudo ./tempsense`
   - Linux (with udev-rule): `./tempsense`

## rootless access on Linux

Create a new group specific for all users, allowed to access the temperature sensor.

```
$ sudo groupadd --system tempsensor
$ sudo usermod -aG tempsensor $USER
```

Logout from your current session and login again, to gain the new group privileges.

Create a new udev rule in `/etc/udev/rules.d/99-tempsensor.rules` with the following content:

```
SUBSYSTEM=="usb", ATTRS{idVendor}=="16c0", ATTRS{idProduct}=="0480", GROUP="tempsensor"
```

After writing the file and replugging your temperature sensor, your account should have permissions to access the sensor.

## Copyright & License

This code is licensed under the Affero GPL3 License!
(c) J. Szpilewski in 2014, js@suborbital.io
