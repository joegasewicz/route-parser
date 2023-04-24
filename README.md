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
You will need [Google Test](https://google.github.io/googletest/) on your system to run the tests

### Bindings
- Python (TODO)
