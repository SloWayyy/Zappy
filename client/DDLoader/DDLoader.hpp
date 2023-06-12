/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** DDLLOADER.hpp
*/

#ifndef DDLLOADER_HPP_
    #define DDLLOADER_HPP_

    #include <string>
    #include <dlfcn.h>
    #include <iostream>
    #include <memory>

template<typename T>
class DDLoader {
    public:
        class DDLException : std::exception {
            public:
                DDLException(std::string message)
                {
                    this->_message = std::move(message);
                }

                const char *what() const noexcept override
                {
                    return this->_message.c_str();
                }

            private:
                std::string _message;
        };
        DDLoader(const std::string &path)
        {
            this->_handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!this->_handle)
                throw DDLException(dlerror());
        }
        ~DDLoader()
        {   
            if (this->_handle)
                dlclose(this->_handle);
            printf("DDLoader destructor\n");
        }
        T *getInstance(const std::string &name)
        {
            T *(*entryPoint)();

            entryPoint = (T *(*)())dlsym(this->_handle, name.c_str());
            if (!entryPoint)
                throw DDLException(dlerror());
            return entryPoint();
        }
    private:
        void *_handle;
};

#endif /* !DDLOADER_HPP_ */