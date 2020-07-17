FROM mcr.microsoft.com/dotnet/core/sdk:3.1-focal

RUN apt-get update
RUN apt-get install -y clang cmake g++ python3
RUN apt-get install -y libfreetype-dev libglfw3-dev libglm-dev libgtest-dev \
    libgmock-dev libsndfile1-dev liblua5.3-dev libopenal-dev
RUN apt-get install -y python3-glad
RUN rm -rf /var/lib/apt/lists/*
