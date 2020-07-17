# NOTE: DO NOT RUN THIS ON DEVELOPMENT MACHINES!
# This is intended for setting up CI machines with the correct dependencies.

sudo apt-get update
sudo apt-get install clang cmake g++ libglu1-mesa-dev libxcursor-dev libxinerama-dev xorg-dev yasm python3 -y
sudo apt-get install libfreetype-dev libglfw3-dev libglm-dev libgtest-dev libgmock-dev libsndfile1-dev liblua5.3-dev libopenal-dev -y

python3 -m pip install glad

export DOTNET_CLI_TELEMETRY_OPTOUT=1
export DOTNET_MULTILEVEL_LOOKUP=0
export DOTNET_SKIP_FIRST_TIME_EXPERIENCE=1

DotNetInstallScript="$(mktemp dotnet-install_XXXXXX.sh)"
wget -O "$DotNetInstallScript" "https://dot.net/v1/dotnet-install.sh"

DotNetInstallDirectory="~/dotnet"
if [ ! -d "$DotNetInstallDirectory" ]; then
  mkdir -p "$DotNetInstallDirectory"
fi

. "$DotNetInstallScript" --channel 3.1 --version latest --install-dir "$DotNetInstallDirectory"
. "$DotNetInstallScript" --channel 2.1 --version latest --install-dir "$DotNetInstallDirectory" --runtime dotnet

~/dotnet/dotnet --info

cmake --version
