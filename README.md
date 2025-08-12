# SlowType
A vintage computing console buffer emulator.<br>
Character-by-character output delayed in milliseconds (1-5000, default: 500)


# Project Info
This only uses the C Standard Library, specifically:
- `stdio.h` - print (pretty self explanitory)
- `unistd.h` - usleep (µs converted to ms)
- `stdlib.h` - atoi (type conversion for ms)
- `string.h` - input, buffer and CLI Args
- `ctype.h` - isdigit (for optional delay arg)

# Build Instructions
I've provided a Makefile, so to build you can just use:
```sh
git clone https://github.com/RileyMeta/SlowType.git
cd SlowType
make
```
<details>
  <summary>Fallback</summary>
Seriously, it's a very simple app.

```sh
gcc main.c -o slowtype
```
</details>
