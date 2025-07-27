# Mabble
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](./LICENSE)

Mabble is a cross-platform GPU backend library designed to unify graphics and compute APIs under a single, modern, and flexible interface.
It actually has been tested on Windows(x64) only. But a Linux distribution is coming soon

![Alt](https://repobeats.axiom.co/api/embed/67945efeeddbb5188cd0171507e1313e97c18dd8.svg "Repobeats analytics image")

## Features
### Graphics APIs
Currently, Mabble is only supporting modern OpenGL (4.6). But here's the other APIs that has to come:
- Vulkan
- DirectX11
- DirectX12
- Metal

### Compute APIs
Currently, Mabble is mainly focusing on the Graphics API abstraction. But here's the future APIs that has to come:
- OpenCL
- CUDA

### core features
- [ ] built-in shader language for generic structure
- [ ] Easy to add more GAPIs out of the gate
- [ ] Built-in graphics profiler to keep track of memory usage and buffers datas and safe resources destruction
- [ ] sustainable debug tools

## Building Mabble
### Requirements
- Operating system: Windows
- Graphics API versions: Vulkan 1.3 and OpenGL 4.6
- CMake 3.22
- A C++ 23 compiler (Visual Studio 2022, GCC 11 or Clang 13)

Once you respected the requirements, you should just run everything perfectly by either use Visual Studio (it will use Ninja to build a binary)
or just build it with CMake commands or cmake-gui (which is not much recommended)

The project in his current state only supports static linking. But in the future, we should be adding a dynamic linking.

Inside your CMake file, you can modify the value of different variable to build the Graphics/Compute API you really want to use.
- ``MABBLE_BUILD_OPENGL`` to build the mabble-opengl
- ``MABBLE_BUILD_VULKAN`` to build the mabble-vulkan
- ``MABBLE_BUILD_DX11`` to build the mabble-dx11
- ``MABBLE_BUILD_DX12`` to build the mabble-dx12
- ``MABBLE_BUILD_METAL`` to build the mabble-metal

You can turn on and off the variables at your will. The default Mabble CMake make sure to turn them ON and OFF automatically depending on your OS
(if you have a Mac, then you should just compile Metal and if you have a Linux, it is no use to build Directx on the top of Metal)

## License
Mabble is licensed under the [MIT License](LICENSE).
