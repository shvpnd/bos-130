# BOS-130
A simple operating system built for the Raspberry Pi Pico (RP2040), implementing a shell, file system, and system utilities.

![Screenshot_2025-05-12_14-38-07](https://github.com/user-attachments/assets/106c3630-fbc0-4965-920e-396f4734dd5f)

### Features

- **Basic Shell:**  Commands like `ls`, `mkdir`, `cd`, `touch`
- **Crude File System:**  In-memory file system supporting directories and files
- **Neofetch-style System Info:** `fetch` to display uptime, RAM usage, and file stats.
 
### How to Build

1. Clone this repository:
    ```bash
    git clone https://github.com/shvpnd/bos-130.git
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



