FROM mcr.microsoft.com/dotnet/sdk:5.0-focal

RUN apt update \
    && apt install -y \
        gnupg \
        dirmngr \
    && curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | gpg --dearmor -o /usr/share/keyrings/githubcli-archive-keyring.gpg \
    && echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | tee /etc/apt/sources.list.d/github-cli.list > /dev/null \
    && apt update \
    && apt install -y \
        clang \
        cmake \
        doxygen \
        graphviz \
        g++ \
        libgl-dev \
        xorg-dev \
        libx11-xcb-dev \
        libxcb-render0-dev \
        libxcb-render-util0-dev \
        libxcb-xkb-dev \
        libxcb-icccm4-dev \
        libxcb-image0-dev \
        libxcb-keysyms1-dev \
        libxcb-randr0-dev \
        libxcb-shape0-dev \
        libxcb-sync-dev \
        libxcb-xfixes0-dev \
        libxcb-xinerama0-dev \
        xkb-data \
        libxcb-dri3-dev \
        libxcb-util-dev \
        python3-pip \
        gh \
	&& rm -rf /var/lib/apt/lists/*

RUN pip3 install conan

