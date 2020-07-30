FROM mcr.microsoft.com/dotnet/core/sdk:3.1-focal

RUN apt-get update \
    && apt-get install -y \
        clang \
        cmake \
        doxygen \
        graphviz \
        g++ \
        libfreetype-dev \
        libglfw3-dev \
        libglm-dev \
        libgmock-dev \
        libgtest-dev \
        liblua5.3-dev \
        libopenal-dev \
        libsndfile1-dev \
        libspdlog-dev \
        python3-glad \
	&& rm -rf /var/lib/apt/lists/*
