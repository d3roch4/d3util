FROM alpine:3.17.0 AS build

RUN apk update && \
    apk add \
        build-base \
        cmake \
        boost-dev \
        libpq-dev \
        libpng-dev \
        libjpeg-turbo-dev \
        tiff-dev \
        git

WORKDIR /teleentrega 
COPY .  ./
RUN git submodule update --init --recursive

WORKDIR /teleentrega/build 
RUN  cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build . --parallel 8

FROM alpine:3.17.0

RUN apk update && \
    apk add \
    libstdc++ \
    boost1.80-program_options==1.80.0-r3 \
    boost1.80-log==1.80.0-r3 \
    boost1.80-log_setup==1.80.0-r3 \
    boost1.80-system==1.80.0-r3 \
    boost1.80-filesystem==1.80.0-r3 \
    boost1.80-program_options==1.80.0-r3 \
    boost1.80-locale==1.80.0-r3 

RUN addgroup -S shs && adduser -S shs -G shs
USER shs    

COPY --chown=shs:shs --from=build \
    ./build/teleentrega-servidor \
    ./app/

ENTRYPOINT [ "./app/teleentrega-servidor" ]


EXPOSE 4000
EXPOSE 4001