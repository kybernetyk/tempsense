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

FLAGS_HID := $(shell pkg-config --libs --cflags ${CONFIG_PACKAGE})

all: tempsense
tempsense: main.cpp
	$(CXX) -o $@ -std=c++11 ${FLAGS_HID} ${FLAGS_USB} $<

clean:
	rm -f tempsense
