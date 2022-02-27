# TBF

Tate's Brain F\*ck is a compiler (or TBF for short), interpreter, and transpiler for the Brain F\*ck.

To use TBF, use the following arguments:

## Arguments

| Argument                    | Shortened Argument    | Description                                            |
| --------------------------- | --------------------- | ------------------------------------------------------ |
| `/pathto/file.txt`          | NONE                  | The file opened and intepreted, compiled or transpiled |
| `--interpret`               | `-i`                  | Interpret via the CLI (default)                                 |
| `--8bit`                    | `-1`                  | Cells are 8 bit (default)                              |
| `--16bit`                   | `-2`                  | Cells are 16 bit                                       |
| `--32bit`                   | `-4`                  | Cells are 32 bit                                       |
| `--compile`                 | `-c`                  | Compile to ELF                                         |
| `--transpile python`        | `-t python`           | Transpile to python                                    |
| `--transpile c`             | `-t c`                | Transpile to C                                         |
| `--output /output/file.txt` | `-o /output/file.txt` | File that compiled/transpiled code goes to             |
| `--help`                    | `-h`                  | Shows help menu                                        |
