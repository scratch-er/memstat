# memstat: a minimal tool to record memory usage

## Overview

`memstat.c` starts a new process and sample its memory usage at a given interval. `memreport.py` plots the recorded data.

## Usage

First, record the memory usage of a program with `memstat`, for example:

```bash
memstat 1000 wasmtime run ./pwhash_scrypy
```

It will start the command `wasmtime run ./pwhash_scrypy` and sample its memory usage at a interval of 1000 microseconds. The data will be saved in `memstat.data`.

Then run `memreport.py`, it will read the recorded data from `memstat.data` and plot the memory usage of the program over time.

## How it works

`memstat` samples the memory usage of a program by perodically read `/proc/pid/statm`. It just saves the raw output of `/proc/pid/statm` into `memtest.data`.

`memreport.py` plots the memory usage with matplotlib. 


