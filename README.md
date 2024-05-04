## Directory Structure

```
.
├── docs
├── external
│   ├── libmcu
│   └── STM32CubeG4
├── include
├── ports
│   ├── freertos
│   └── stm32
├── src
└── tests
    ├── fakes
    ├── mocks
    ├── runners
    ├── src
    └── stubs
```

| Directory | Desc.                                                               |
| --------- | ------------------------------------------------------------------- |
| docs      | Documentation                                                       |
| external  | Third-party libraries or SDK. e.g. STM32 SDK                        |
| include   | The project header files                                            |
| ports     | Wrappers or glue code to bring third-party drivers into the project |
| src       | Application code. No hardware or platform-specific code             |
| tests     | Test codes                                                          |
