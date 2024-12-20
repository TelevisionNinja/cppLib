FROM ubuntu:rolling
WORKDIR /cppLib
COPY ./ ./
RUN apt-get -y update && apt-get -y install g++
WORKDIR /cppLib/tests
RUN g++ -std=c++23 -Wall ./*.cpp ../src/*.cpp -o test.exe
CMD ["./test.exe"]
