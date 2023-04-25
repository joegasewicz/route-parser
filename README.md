# Route Parser
URL path matcher

### Quick Start
```c
char routes[3][256] = {"/", "/hell", "/hello"};

RP_Path *path = RP_Path_new("/hello", NULL);
RP_Path_compare(path, 3, routes);

printf("Result: %s", path->result); // "/hello"
```

### Tests
Tests are written in C++ with [Google Test](https://google.github.io/googletest/) 

### Bindings
- Python (TODO)
