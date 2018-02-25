#pragma once

#include <ml.h>
#include <utils.h>

#include <experimental/optional>
#include <fstream>

namespace NIO {

class TTSVParser {
public:
    using TExample = NML::TLabeledExample;
    
    template <typename TStream>
    std::experimental::optional<TExample> Parse(TStream& stream) {
        std::string line;
        if (!std::getline(stream, line)) {
            return {};
        }

        std::vector<float> x = NUtils::SplitBy<float>(line, "\t");
        if (x.size() < 2) {
            throw std::runtime_error(line);
        }

        float y = x.back();
        x.pop_back();

        return NML::TLabeledExample(x, y);
    }
};

template <typename TParser>
class TStreaming {
public:
    TStreaming(const std::string& filename)
    : Filename(filename)
    , Stream(filename)
    {
        Example = Parser.Parse(Stream);
    }

    typename TParser::TExample Next() {
        if (!HasNext()) {
            throw std::runtime_error("HasNext()");
        }

        typename TParser::TExample example = Example.value();
        Example = Parser.Parse(Stream);

        return example;
    }

    bool HasNext() {
        if (Example) {
            return true;
        }
        return false;
    }

private:
    std::string Filename;
    std::ifstream Stream;
    TParser Parser;
    std::experimental::optional<typename TParser::TExample> Example;
};

} // namespace NIO
