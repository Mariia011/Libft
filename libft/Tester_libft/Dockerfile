# SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
#
# SPDX-License-Identifier: GPL-3.0-or-later

FROM centos:8 as criterion-builder
WORKDIR /tmp
RUN yum install -y git gcc cmake libffi-devel python3.8
RUN python3.8 -m pip install ninja meson
RUN git clone --recursive --depth 1 https://github.com/Snaipe/Criterion
# RUN mv /usr/bin/gcc /usr/bin/cc
RUN cd Criterion && meson build
RUN cd Criterion && ninja -C build

FROM centos:8 as mimick-builder
WORKDIR /tmp
RUN yum install -y git cmake gcc make
RUN git clone --recursive --depth 1 https://github.com/Snaipe/Mimick
# RUN sed 's/ElfAddr/Elf64_Addr/g' Mimick/src/plt-elf.c | sed "s/ElfOff/Elf64_Off/g" > tmp.txt
# RUN mv tmp.txt Mimick/src/plt-elf.c
RUN mkdir Mimick/build && cd Mimick/build && cmake ..
RUN cd Mimick/build && make

FROM centos:8
COPY --from=criterion-builder /tmp/Criterion/include/ /usr/include
COPY --from=criterion-builder /tmp/Criterion/build/src/libcriterion.so /usr/lib/libcriterion.so
COPY --from=mimick-builder /tmp/Mimick/include/ /usr/include/
COPY --from=mimick-builder /tmp/Mimick/build/libmimick.a /usr/lib/libmimick.a
# Following is for libbsd-devel
RUN rpm -ivh http://mirror.centos.org/centos/8/BaseOS/x86_64/os/Packages/libpkgconf-1.4.2-1.el8.x86_64.rpm
RUN rpm -ivh http://mirror.centos.org/centos/8/BaseOS/x86_64/os/Packages/pkgconf-1.4.2-1.el8.x86_64.rpm
RUN rpm -ivh http://mirror.centos.org/centos/8/BaseOS/x86_64/os/Packages/pkgconf-m4-1.4.2-1.el8.noarch.rpm
RUN rpm -ivh http://mirror.centos.org/centos/8/BaseOS/x86_64/os/Packages/pkgconf-pkg-config-1.4.2-1.el8.x86_64.rpm
RUN rpm -ivh https://download-ib01.fedoraproject.org/pub/epel/8/Everything/x86_64/Packages/l/libbsd-0.9.1-4.el8.x86_64.rpm
RUN rpm -ivh https://download-ib01.fedoraproject.org/pub/epel/8/Everything/x86_64/Packages/l/libbsd-devel-0.9.1-4.el8.x86_64.rpm
# End of libbsd-devel
RUN yum -y install kernel-devel make libffi libasan libubsan git ruby ruby-devel redhat-rpm-config clang gcc
RUN gem install bundler bunny parseconfig json:2.3.0
RUN useradd at42-libft-test -d /home/at42-libft-test
USER at42-libft-test
WORKDIR /home/at42-libft-test
# TODO install real norminette
COPY --chown=at42-libft-test:at42-libft-test ./.norminette ./.norminette/
COPY --chown=at42-libft-test:at42-libft-test *.mk Makefile ./
COPY --chown=at42-libft-test:at42-libft-test libft_test libft_test/
ENTRYPOINT /bin/sh -c 'eval "$(ssh-agent -s)" 1>/dev/null && chmod -R 0400 .ssh/* && find .ssh | xargs ssh-add 2>/dev/null || /bin/bash'
