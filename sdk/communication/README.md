# SDK - Communication

## Introduction

This is the communication module of the SDK. It is used to communicate with the server and the graphical client.

The aim of this part of the project is to provide a way to communicate with the server and the graphical client and get the data from them.

### Table of contents

- [Introduction](#introduction)

- [Table of contents](#table-of-contents)

- [How to execute the SDK](#how-to-execute-the-sdk)

- [How to use the SDK](#how-to-use-the-sdk)

- [ICommunication.hpp](#icommunicationhpp)

  - [Methods](#methods)

- [Example](#example)

- [Authors](#authors)


## How to execute the SDK

You have to compile the files using ```make``` command.

## How to use the SDK

After the compilation, the SDK is ready to be used. You can use it in your project by including the header file ```ICommunication.hpp``` and linking the library ```communication_sdk.so```.

## ICommunication.hpp

This is the header file of the SDK. It contains the interface of the SDK.

```cpp
namespace zappy::sdk {
    class CommunicationException : std::exception {
        public:
            explicit CommunicationException(std::string message) : _message(std::move(message)) {}

            [[nodiscard]] const char *what() const noexcept override {
                return this->_message.c_str();
            }

        private:
            std::string _message;
    };

    class ICommunicationModule {
        public:
            virtual ~ICommunicationModule() = default;

            virtual void connect(const std::string &host, int port) = 0;
            virtual void connectAsGraphical() = 0;
            virtual void disconnect() = 0;
            virtual bool isConnected() = 0;
            virtual std::vector<std::string> readBuffer() = 0;
            virtual void writeBuffer(const std::string &command) = 0;
            virtual void setDisconnected(bool disconnected) = 0;
            virtual bool isDisconnected() const = 0;
    };
}

extern "C" zappy::sdk::ICommunicationModule *communicationEntrypoint();
```

### Methods

- ```zappy::sdk::CommunicationException```: This class is used to handle errors in the SDK.

- ```zappy::sdk::connect``` : This method is used to connect to the server

- ```zappy::sdk::disconnect``` : This method is used to disconnect from the server

- ```zappy::sdk::isConnected``` : This method is used to know if the SDK is connected to the server and returns a boolean

- ```zappy::sdk::readBuffer``` : This method is used to read the buffer from the server's socket and returns an ```std::vector<std::string>```

- ```zappy::sdk::writeBuffer``` : This method is used to write in the server's socket

- ```zappy::sdk::setDisconnect``` : This method is used to set the disconnect flag to true

- ```zappy::sdk::isDisconnect``` : This method is used to get the disconnect flag and returns a boolean

- ```zappy::sdk::communicationEntrypoint``` : This method is used to create an instance of the SDK and returns a pointer to it (ICommunicationModule)

## Example

```cpp
#include <iostream>

#include "ICommunication.hpp"

int main()
{
    auto *handle = dlopen("communication_sdk.so", RTLD_LAZY); // Open the library
    if (!handle) { // Check if the library is opened
        std::cerr << dlerror() << std::endl;
        return 84;
    }
    auto *communication = reinterpret_cast<zappy::sdk::ICommunicationModule *(*)()>(dlsym(handle, "communicationEntrypoint"))(); // Get the instance of the SDK

    try {
        communication->connect("localhost", 4242); // Connect to the server on localhost:4242 or throw an exception if it fails
    } catch (const zappy::sdk::CommunicationException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    std::cout << "Connected to the server" << std::endl;
}
```

## Authors

| [<img src="https://github.com/EdenComp.png?size=85" width=85><br><sub>Florian Lauch</sub>](https://github.com/EdenComp) | [<img src="https://github.com/kvn703.png?size=85" width=85><br><sub>Kevin NADARAJAH</sub>](https://github.com/kvn703) |
| :---: | :---: |