## Setup and Prerequisites

Follow guide on: https://github.com/raspberrypi/pico-sdk

1. Git clone the above Raspberry Pi Pico SDK repository.

2. Create a separate project directory for your program. 

3. Copy `pico_sdk_import.cmake` from the SDK into your project directory

4. Create a `CmakeLists.txt` file with following content (everything below `pico_sdk_init()` is project specific):

```
cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(hello_world
    hello_world.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(hello_world pico_stdlib)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hello_world)
```

5. Write code (here in a `hello_world.c` file) - this example will make the onboard LED flash:

```
#include "pico/stdlib.h"

int main() {
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    }
#endif
}
```

6. Create a build directory

```
$ mkdir build
$ cd build
$ cmake -DPICO_SDK_PATH=/path/to/pico-sdk ..
```

The last line of the output should read
```
-- Build files have been written to: /mnt/c/Users/david/Documents/GitHub/pico-examples/build
```

7. Build the project

Going forward after code changes this is all you need to run to update the program on the microcontroller. 

```
make hello_world
```

This will take a few minutes. The last lines will read
```
make[3]: warning:  Clock skew detected.  Your build may be incomplete.
[100%] Built target hello_world
```

8. Upload the program by dragging and dropping the \*.uf2 file into the Pico drive

## How to reset Pico

See: https://www.okdo.com/project/raspberry-pi-pico-reset-button/#:~:text=Push%20and%20hold%20the%20reset,Release%20the%20BOOTSEL%20button.

Connect the RUN pin (Pin 30) to GND.
Hold BOOTSEL
Disconnect RUN pin from GND
Release BOOTSEL


