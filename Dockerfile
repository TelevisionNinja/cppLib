FROM gcc:latest
WORKDIR /cppLib
COPY ./ ./
RUN make
CMD ["./test.exe"]
