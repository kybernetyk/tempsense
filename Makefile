ifeq (,${CONFIG_PACKAGE})
CONFIG_PACKAGE := $(shell pkg-config --exists hidapi-libusb 2>&1 >/dev/null && echo hidapi-libusb)
endif

ifeq (,${CONFIG_PACKAGE})
CONFIG_PACKAGE := $(shell pkg-config --exists hidapi 2>&1 >/dev/null && echo hidapi)
endif

ifeq (Darwin,$(shell uname -s))
FLAGS_USB:=
else
FLAGS_USB := -lusb
endif

FLAGS_HID_LIB := $(shell pkg-config --libs ${CONFIG_PACKAGE})
FLAGS_HID_INCLUDE := $(shell pkg-config --cflags ${CONFIG_PACKAGE})

all: tempsense
tempsense.o: main.cpp
	$(CXX) -c -o $@ -std=c++11 ${FLAGS_HID_INCLUDE} $<
tempsense: tempsense.o
	$(CXX) $< -std=c++11 ${FLAGS_HID_LIB} ${FLAGS_USB} -o $@

clean:
	rm -f tempsense tempsense.o
