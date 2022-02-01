# Creator:    VPR
# Created:    January 27, 2022
# Updated:    February 1, 2022

FROM ubuntu:20.04

# Set env to avoid user input interruption during installation
ENV TZ=America/Chicago
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install normal goodies
RUN apt-get update -y
RUN apt-get install -y --no-install-recommends ssh \
                                               sudo \
                                               zsh \
                                               zsh-autosuggestions \
                                               git \
                                               curl \
                                               wget \
                                               vim \
                                               tree \
                                               zip \
                                               unzip \
                                               pkg-config \
                                               libtool \
                                               m4 \
                                               automake \
                                               libmicrohttpd-dev \
                                               make \
                                               cmake \
                                               build-essential \
                                               clang \
                                               gdb \
                                               cscope \
                                               python3-dev \
                                               htop \
                                               iftop \
                                               iotop

# Change login shell to zsh
RUN chsh -s /bin/zsh $(whoami)

# Copy profile
COPY misc/.profile /root/.profile
COPY misc/.vimrc /root/.vimrc
COPY misc/.zshrc /root/.zshrc
