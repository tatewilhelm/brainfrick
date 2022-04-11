# Brain Frick

Brain Frick is an interpreter for the esoteric programming language, brainfuck.

Brain Frick is designed for linux, and unix systems. (Try msys2 if your using Windows.)

---

# Install

To install brainfrick, you must have `gcc`, `make`, `cmake`, and `git` installed.

Run the following command to install brainfrick to your system.

```
curl -ss https://www.github.com/tatewilhelm/brainfrick/install.sh | sudo bash
```

Or you can manually run the compilation using the following commands:

```
# Download
git clone https://github.com/tatewilhelm/brainfrick
cd brainfrick

# Build
cmake CMakeLists.txt
make

# Install
sudo make install

# Clean up
cd ../
rm -rf brainfrick
```
---

# Arguments

| Argument                    | Shortened Argument    | Description                                              |
| --------------------------- | --------------------- | -------------------------------------------------------- |
| `/path/to/file.bf`          | NONE                  | The file opened                                          |
| `--interpret`               | `-i`                  | Interpret files (default)                                |      
| `--help`                    | `-h`                  | Shows help menu                                          |
| `--returnEndingCell`        | NONE                  | Returns the ending cells value instead of the ERRNO      |
| `--infiniteCells`           | NONE                  | Infinite amount of cells compared to the standard 30,000 |
