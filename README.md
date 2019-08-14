# RIC tracing helper library

The library includes a function for creating a tracer instance.

ToDo: tracer configuration options

## Usage

Create a global tracer

```c
    #include <opentracing/tracer.h>
    #include <tracelibcpp/tracelibcpp.hpp>

    opentracing::Tracer::InitGlobal(tracelibcpp::createTracer("my-service-name"));
```
Span context propagation between different software components in RIC is using a
TextMap carrier and JSON format serialization.
The [opentracing C++](https://github.com/opentracing/opentracing-cpp) Readme gives examples
how span context **inject** and **extract** with textmap can be done.
Serialization to JSON can be done with any JSON library.

## Requires

cmake
gcc/c++

## Build
mkdir build
cd build
cmake ..
make

## Unit testing
To run unit tests the project needs to be configured with testing option
cmake -DWITH_TESTING=ON ..
make check
Or with output
CTEST_OUTPUT_ON_FAILURE=1 make check

## License

See [LICENSES.txt](LICENSES.txt) file.
