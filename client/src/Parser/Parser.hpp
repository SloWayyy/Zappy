/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Parser
*/

#ifndef PARSER_HPP_
    #define PARSER_HPP_

    #include <string>
    #include <vector>
    #include <sstream>

class Parser {
    public:
        class ParserException : public std::exception {
            public:
                ParserException(std::string const &message);
                ~ParserException() = default;
                const char *what() const noexcept;
            private:
                std::string _message;
        };
        Parser(int ac, char **av);
        size_t getPort(void) const;
        std::string getMachine(void) const;
        void handleArgs(void);
        void setHelp(void);
        template<typename T>
        T parseArgs(const std::string &str) {
            std::stringstream stream(str);
            T value;

            stream >> value;
            if (stream.fail() || !stream.eof()) {
                throw ParserException("Invalid argument\n" + this->_usage);
            }
            return value;
        }
        ~Parser() = default;
    private:
        std::vector<std::string> _av;
        size_t _port;
        std::string machine;
        std::string _usage;
};

#endif /* !PARSER_HPP_ */
