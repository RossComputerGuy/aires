FROM debian:sid

RUN apt update -y >/dev/null 2>&1 && \
	apt install -y build-essential curl cmake clang libgtest-dev libglfw3-dev pkg-config >/dev/null 2>&1 && \
	apt-get clean >/dev/null 2>&1 && rm -rf /var/lib/apt/lists/* /tmp/*

COPY ./scripts/install-shaderc.sh /opt/install-shaderc.sh
RUN bash /opt/install-shaderc.sh && rm /opt/install-shaderc.sh

RUN useradd builder -m -u 1000
RUN passwd -d builder

USER builder
WORKDIR /usr/src
