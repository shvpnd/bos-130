# BOS-130
A simple operating system built for the Raspberry Pi Pico (RP2040), implementing a shell, file system, and system utilities.

### Features

- **Basic Shell:**  Commands like `ls`, `mkdir`, `cd`, `touch`
- **Crude File System:**  In-memory file system supporting directories and files
- **Neofetch-style System Info:** `fetch` to display uptime, RAM usage, and file stats.
 
### How to Build

1. Clone this repository:
    ```bash
    git clone https://github.com/yourusername/bos-130.git
    cd bos-130
    ```

2. Create a build directory and compile:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```
3. Flash the generated `.uf2` file to your Raspberry Pi Pico.

### References
- https://github.com/asynts/pico-os
- https://github.com/oltdaniel/picos
- https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf
- https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf



