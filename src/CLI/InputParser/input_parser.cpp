#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cctype>
#include "input_parser.h"

std::pair<Result, Command> InputParser::parseInput(std::string input) {
    std::pair<Result, std::vector<std::string>> tokens = tokenize(input);
    if (tokens.first.status == Status::ERROR) return {{tokens.first.status, tokens.first.error}, {}};

    RestAPI rest;
    std::transform(tokens.second[0].begin(), tokens.second[0].end(), tokens.second[0].begin(),[](unsigned char c){ return std::toupper(c); });
    if (tokens.second[0] == "GET") {
        rest = RestAPI::GET;
    } else if (tokens.second[0] == "SET")
    {
        rest = RestAPI::SET;
    }
    else if (tokens.second[0] == "DELETE") {
        rest = RestAPI::DELETE;
    } else {
        return {{Status::ERROR, "Rest command unknown. Try GET, SET, or DELETE."}, {}};
    }

    std::string key = "";
    std::string value = "";
    if (rest == RestAPI::GET || rest == RestAPI::SET) {
        if (tokens.second.size() == 3) {
            key = tokens.second[1];
            value = tokens.second[2];
        } else {
            return {{Status::ERROR, "Invalid argument count for. Expected 3"}, {}};
        }
    } else if (rest == RestAPI::DELETE) {
        if (tokens.second.size() == 2) {
            key = tokens.second[1];
        } else {
            return {{Status::ERROR, "Invalid argument count. Expected 2"}, {}};
        }
    }

    return {{Status::SUCCESS}, {rest, key, value}};
}

std::pair<Result, std::vector<std::string>> InputParser::tokenize(std::string& input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (ss >> token) {
        tokens.push_back(token);
    }

    return {{Status::SUCCESS}, tokens};
}
