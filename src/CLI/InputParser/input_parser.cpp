#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include "input_parser.h"

Command InputParser::parseInput(std::string input) {
    std::vector<std::string> tokens = tokenize(input);

    RestAPI rest;

    // toupper first token
    std::transform(tokens[0].begin(), tokens[0].end(), tokens[0].begin(),[](unsigned char c){ return std::toupper(c); });

    if (tokens[0] == "GET") {
        rest = RestAPI::GET;
    } else if (tokens[0] == "SET")
    {
        rest = RestAPI::SET;
    }
    else if (tokens[0] == "DELETE") {
        rest = RestAPI::DELETE;
    } else {
        throw std::runtime_error("Error: command: " + tokens[0] + " does not exist, try SET, GET, or DELETE.");
    }

    std::string key = "";
    std::string value = "";
    if (rest == RestAPI::SET) {
        if (tokens.size() == 3) {
            key = tokens[1];
            value = tokens[2];
        } else {
            throw std::runtime_error("Error: expected 3 arguments, found: " + std::to_string(tokens.size()));
        }
    } else if (rest == RestAPI::GET || rest == RestAPI::DELETE) {
        if (tokens.size() == 2) {
            key = tokens[1];
        } else {
            throw std::runtime_error("Error: expected 2 arguments, found: " + std::to_string(tokens.size()));
        }
    }

    return {rest, key, value};
}

std::vector<std::string> InputParser::tokenize(std::string& input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (ss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}
