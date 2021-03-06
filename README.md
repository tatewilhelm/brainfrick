# Brain Frick

Brain Frick is an interpreter for the esoteric programming language, brainfuck.

Brain Frick is designed for linux, and unix systems. (Try msys2 if your using Windows.)

---

# Install

To install brainfrick, you must have `gcc`, `make`, `cmake`, and `git` installed.

Run the following command to install brainfrick to your system.

```
curl -ss https://raw.githubusercontent.com/tatewilhelm/brainfrick/master/install.sh | sudo bash
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
| `--interpret`               | `-i`                  | Interpret files (default)                                 |      
| `--transpile python`           | `-t python`                  | Converts the file into a Python 3 file |
| `--transpile c`           | `-t c`                 | Converts the file into a C99 file |
| `--compile`           | `-c`                  | Compiles the file into a executable using `gcc` (The C compiler can be changed in constants.h) |
| `--help`                    | `-h`                  | Shows help menu                                          |
| `--return-ending-cell`        | NONE                  | Returns the ending cells value instead of the ERRNO      |
| `--infinite-cells`           | NONE                  | Infinite amount of cells compared to the standard 30,000 |
