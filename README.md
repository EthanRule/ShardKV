# ShardKV  
Modern C++ 23 Sharded KV Store for 64-bit systems.


### Dependancies
OS: ```Linux (WSL)```  
Ready: ```sudo apt update```  
Compiler: ```sudo apt install clang```  
Essential Build Tools: ```sudo apt install build-essential```  
Build Tool: ```sudo apt install cmake```  
Enable Build Script: ```chmod +x rebuild_run.sh && chmod +x rebuild_test```  
Abseil Hash Libs: ```cd src && git clone https://github.com/abseil/abseil-cpp.git```  

#### Rebuild & Run
```./rebuild_run.sh```  
  

#### Inspirations

- https://github.com/redis/redis  

#### Additional Resources
- Hashing
    - https://en.wikipedia.org/wiki/Quadratic_probing
    - https://youtu.be/BoZbu1cR0no?si=8CYHemZJGFsiZYoU
    - https://en.wikipedia.org/wiki/Triangular_number
    - https://severalnines.com/blog/hash-slot-vs-consistent-hashing-redis/
    - https://abseil.io/about/design/swisstables  
- Design Patterns
    - https://refactoring.guru/design-patterns/observer/cpp/example
- Testing
    - https://google.github.io/googletest/primer.html  
- C/C++, Rust
    - https://embeddedartistry.com/blog/2017/05/05/header-guards/
    - https://www.geeksforgeeks.org/c/tcp-server-client-implementation-in-c/
- 
