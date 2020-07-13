# NOTE: DO NOT RUN THIS ON DEVELOPMENT MACHINES!
# This is intended for setting up CI machines with the correct dependencies.

wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc | sudo apt-key add -

sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ xenial main'
sudo apt-add-repository 'deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-8 main'

sudo apt-get update
sudo apt-get install clang-8 cmake g++-8 libglu1-mesa-dev libxcursor-dev libxinerama-dev xorg-dev yasm python3 -y
sudo apt-get install libfreetype6-dev libglfw3-dev libglm-dev libgtest-dev liblua5.3-dev libopenal-dev libspdlog-dev -y

python3 -m pip install setuptools
python3 -m pip install glad

sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-8 255
sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-8 255

sudo update-alternatives --install /usr/bin/cc cc /usr/bin/clang 255
sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 255

export DOTNET_CLI_TELEMETRY_OPTOUT=1
export DOTNET_MULTILEVEL_LOOKUP=0
export DOTNET_SKIP_FIRST_TIME_EXPERIENCE=1

DotNetInstallScript="$(mktemp dotnet-install_XXXXXX.sh)"
wget -O "$DotNetInstallScript" "https://dot.net/v1/dotnet-install.sh"

DotNetInstallDirectory="~/dotnet"
CreateDirectory "$DotNetInstallDirectory"

. "$DotNetInstallScript" --channel 3.1 --version latest --install-dir "$DotNetInstallDirectory"
. "$DotNetInstallScript" --channel 2.1 --version latest --install-dir "$DotNetInstallDirectory" --runtime dotnet
