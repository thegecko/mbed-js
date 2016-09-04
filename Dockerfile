# ------------------------------------------------------------------------------
# Pull base image
FROM ubuntu:trusty
MAINTAINER Rob Moran <rob.moran@arm.com>

# ------------------------------------------------------------------------------
# Install base
RUN apt-get -y update
RUN apt-get -y dist-upgrade

# ------------------------------------------------------------------------------
# Install base tools
RUN apt-get -y install curl
RUN apt-get -y install git

# ------------------------------------------------------------------------------
# Install arm gcc
RUN apt-get -y install software-properties-common
RUN add-apt-repository -y ppa:team-gcc-arm-embedded/ppa
RUN apt-get -y update
RUN apt-get -y install gcc-arm-embedded

# ------------------------------------------------------------------------------
# Install python
RUN apt-get -y install python python-setuptools python-usb
RUN apt-get -y remove python-pip
RUN easy_install pip

# ------------------------------------------------------------------------------
# Install mbed-cli
RUN pip install -U mbed-cli==0.9.1

# ------------------------------------------------------------------------------
# Set up workspace
COPY ./workspace /workspace

# ------------------------------------------------------------------------------
# Install mbed OS @5.1.3
RUN git clone https://github.com/ARMmbed/mbed-os /workspace/mbed-os
RUN cd /workspace/mbed-os && git checkout mbed-os-5.1.3

# ------------------------------------------------------------------------------
# Install mbed OS requirements
RUN pip install -r /workspace/mbed-os/requirements.txt

# ------------------------------------------------------------------------------
# Install Node.js
RUN curl -sL https://deb.nodesource.com/setup_4.x | sudo -E bash -
RUN apt-get -y install nodejs

# ------------------------------------------------------------------------------
# Install CommonJS Compiler
RUN npm install -g cjsc

# ------------------------------------------------------------------------------
# Install tools
ADD ./tools /usr/local/bin/tools
RUN chmod +x /usr/local/bin/tools/js2c.py
RUN chmod +x /usr/local/bin/tools/mbed-js.sh
RUN ln -s /usr/local/bin/tools/js2c.py /usr/local/bin/js2c
RUN ln -s /usr/local/bin/tools/mbed-js.sh /usr/local/bin/mbed-js
COPY ./tools/require.js /usr/lib/node_modules/cjsc/lib/Renderer/template/require.js
