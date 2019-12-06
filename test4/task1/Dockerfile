FROM ubuntu:18.04

LABEL description="Base build environment with YAML-CPP"
LABEL version="1.0"
LABEL maintainer="1.dawid.bugajski@gmail.com"

# Update system, install dependencies
RUN \
    echo "Installing updates..." && \
    apt-get update && apt-get -y upgrade && \
    echo "Installing required dependencies..." && \
    apt-get install -y build-essential g++ git cmake

# Install libyaml-cpp
WORKDIR /home
RUN \
    echo "Installing yaml-cpp library from source..." && \
    git clone https://github.com/jbeder/yaml-cpp && cd yaml-cpp && \
    mkdir build && cd build && cmake .. && make && make install

# Prepare program source
WORKDIR /app
USER root

COPY Makefile .
ADD src src

RUN \
    echo "Everything done."

CMD ["bash"]