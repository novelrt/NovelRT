wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc | sudo apt-key add -

sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ xenial main'
sudo apt-add-repository 'deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-8 main'

sudo apt-get update
sudo apt-get install clang-8 cmake yasm -y

sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-8 255
sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-8 255

sudo update-alternatives --install /usr/bin/cc cc /usr/bin/clang 255
sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 255

sudo rm -f /usr/local/bin/cmake
