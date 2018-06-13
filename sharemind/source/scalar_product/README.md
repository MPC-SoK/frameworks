# Stand alone Sharemind client application demo

## Build instructions

### Build on the command line

To build and install the binaries into the `prefix/` directory, run:

```
mkdir build
cd build
cmake ..
make install
```

To compile and install the SecreC files, run:

```
sm_compile.sh secrec/*.sc
```

### Build in Qt Creator

* Load the project by opening the `CMakeLists.txt` file in Qt Creator and going through the CMake wizard.
* Build.
* Compile and install the SecreC files by opening them selecting 'Tools'->'External'->'Sharemind SDK'->'Compile SecreC' or Ctrl+F1.
* Before running, configure the 'Working directory' under the 'Projects'->'Build & Run'->'Run' tab to point to the `debugfiles` directory of the demo. Otherwise Qt Creator will not find the client configuration.


## Run instructions

Before running the application, start the Sharemind servers either in Qt Creator or by running `sm_start_servers.sh` on the command line.
Then run the executable `prefix/bin/ScalarProduct` from the command line or run the project from Qt Creator.
