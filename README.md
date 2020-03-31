This repository contains a collection of sample programs for a variety of multi-party computation (MPC) frameworks. For ease of examination, we have set up each framework in a Docker container. This minimizes the effort required to test framework functionality. 

The goal of this project is to make it easier for researchers (and other users) to experiment with MPC software frameworks. These software tools are suitable for prototyping applications, testing current capabilities, measuring rough benchmark performances, and other similar tasks. Many of these frameworks are not suitable for use in production environments! 

There are two main contributions of this repository. One is the code above. The other is extended documentation, including READMEs, comments in the code, and extended notes in the [wiki](https://github.com/mpc-sok/frameworks/wiki) pages. 
We welcome contributions in any of these areas: if you have used a framework, optimized the compilation scripts, or made observations about its usability or quirks, please consider writing a note about your experiences and submitting it as a pull request (or an email).

This repository accompanies the paper <a href="http://marcellahastings.com/static/mpcsok.pdf">SoK: General-Purpose Compilers for Secure Multi-party Computation</a>, which includes a thorough evaluation of each framework across usability and architectural criteria. For a gentler introduction to secure computation and this project, please read the [layperson's guide](https://github.com/MPC-SoK/frameworks/wiki/A-Layperson%27s-Guide).

## Frameworks 
We include a complete build environment and three sample programs for each framework. Additional documentation of some framework can be found in the [wiki](https://github.com/mpc-sok/frameworks/wiki) pages). 
Each framework directory includes a `Dockerfile` and one or more `install.sh` scripts. There is a `README` that describes some relevant architecture along with instructions to compile, run, and modify examples. The `source` directory holds the sample programs and any additional code (including patches, vim syntax highlighting, and input generation scripts).

For more information about using Docker, see the [Docker documentation](https://github.com/MPC-SoK/frameworks/wiki/Docker).

## About Sample Programs
We implemented three sample programs for each framework. These are small unit tests and are not intended to exhaustively test framework functionality. We used them to learn about the architecture and set-up requirements of each framework. They illustrate a variety of common functionality requirements.

`mult3`: This multiplies three numbers together. It either takes input from three different parties (if supported) or takes three _secret shared_ inputs from two parties. Some frameworks provide built-in tools for secret-sharing input; others required us to manually share inputs to two parties. It tests basic numeric capabilities, integer I/O, and basic computation. 

`innerprod`: This computes an inner product (aka scalar product, aka dot product) on two integer vectors. It takes two vectors as input and computes the pairwise product of their elements. It requires support for input, access, and iteration over secret-valued arrays. 

`xtabs`: This computes a crosstabulation, a database operation that computes averages (or sums) by category. The category table and value table share a primary key but are owned by different parties. This tests output and modification of arrays and requires conditionals on secret data. We used a brute-force algorithm to solve this problem, and return a list of sums by category (rather than averages).

## Contributions and Citations
This software is offered as-is. It may not be up-to-date with the latest versions of each framework. **We welcome pull requests** for compatibility with new software versions, corrections to sample programs, and new frameworks.

If you maintain a software tool that belongs here, please contact us. New frameworks are first added as branches then merged with the main repository. 

Questions and commentary should be raised publicly in the [Issue Tracker](https://github.com/MPC-SoK/frameworks/issues). 

If you use this work for an academic project, please cite:
```latex
    @inproceedings{mpc-sok,
       author = {Marcella Hastings and Brett Hemenway and Daniel Noble and Steve Zdancewic},
       title = {{SoK:} General-Purpose Compilers for Secure Multi-Party Computation},
       booktitle = {2019 IEEE Symposium on Security and Privacy (SP)},
       year = {2019},
    }
```

