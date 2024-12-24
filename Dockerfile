FROM gcc:latest
WORKDIR /cppLib
COPY ./ ./
WORKDIR /cppLib/tests
RUN g++ -std=c++23 -Wall ./*.cpp ../src/*.cpp -o test.exe
CMD ["./test.exe"]
