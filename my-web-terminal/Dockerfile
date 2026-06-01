FROM ubuntu:22.04

# Prevent timezone prompts during installations
ENV DEBIAN_FRONTEND=noninteractive

# 1. Install system toolchains (GCC, G++, NASM, Node.js)
RUN apt-get update && apt-get install -y \
    gcc \
    g++ \
    nasm \
    curl \
    && curl -fsSL https://deb.nodesource.com/setup_20.x | bash - \
    && apt-get install -y nodejs \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# 2. Copy code configurations and source files
COPY package.json server.js ./
COPY public/ ./public/
COPY terminal.c sysinfo.asm squarer.cpp ./

# 3. Cleanly build our low-level application binaries
RUN gcc terminal.c -o mini-term
RUN nasm -f elf64 sysinfo.asm -o sysinfo.o && ld sysinfo.o -o sysinfo
RUN g++ squarer.cpp -o squarer

# 4. Install server dependencies
RUN npm install

EXPOSE 3000

# 5. Ignite the backend server engine
CMD ["node", "server.js"]
