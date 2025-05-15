FROM mcr.microsoft.com/dotnet/sdk:6.0-focal

RUN apt update \
    && apt install -y \
        gnupg \
        dirmngr \
    && curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | gpg --dearmor -o /usr/share/keyrings/githubcli-archive-keyring.gpg \
    && curl -fsSL https://apt.kitware.com/keys/kitware-archive-latest.asc | gpg --dearmor -o /usr/share/keyrings/kitware-archive-keyring.gpg \
    && wget -q -O - https://packages.lunarg.com/lunarg-signing-key-pub.asc | apt-key add - \
    && echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | tee /etc/apt/sources.list.d/github-cli.list > /dev/null \
    && echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ focal main" | tee /etc/apt/sources.list.d/kitware.list > /dev/null \
    && wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.3.236-focal.list https://packages.lunarg.com/vulkan/1.3.236/lunarg-vulkan-1.3.236-focal.list \
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
        gh \
        vulkan-sdk \
        libxkbcommon-dev \
        wayland-protocols \
        libwayland-dev \
        extra-cmake-modules \
    && rm -rf /var/lib/apt/lists/*
