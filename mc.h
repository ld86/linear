#pragma once

#include <cli.h>

#include <iostream>
#include <map>
#include <functional>

namespace NUtils {

using TAction = std::function<int(const NCli::TArguments&)>;

class TModeChooser {
public:
    TModeChooser(const NCli::TArguments& arguments)
    : Arguments(arguments)
    {}

    void Add(const std::string& modeName, TAction action) {
        Actions.insert({modeName, action});
    }

    int Run() {
        if (!Arguments.HasParameter("mode")) {
            PrintHelp();
            return 1;
        }

        const std::string& mode = Arguments.GetParameter("mode");
        if (!Actions.count(mode)) {
            PrintHelp();
            return 1;
        }

        Actions.at(mode)(Arguments);
        
        return 0;
    }

private:
    void PrintHelp() {
        std::cerr << "Available modes:" << std::endl;
        for (const auto& kv : Actions) {
            std::cerr << kv.first << std::endl;
        }
    }


private:
    const NCli::TArguments& Arguments;
    std::map<std::string, TAction> Actions;
};

}
