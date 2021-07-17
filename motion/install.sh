# get MOTION
git clone --recursive --config core.autocrlf=input https://github.com/encryptogroup/MOTION.git
cd MOTION
# build MOTION
cmake -DMOTION_BUILD_TESTS=On -DMOTION_BUILD_EXE=On -DMOTION_LINK_TCMALLOC=On -B build
cmake --build build -- -j 4
