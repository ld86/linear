#pragma once

#include <vector>
#include <sstream>

namespace NML {

struct TLabeledExample {
    TLabeledExample(const std::vector<float>& x, float y)
    : X(x)
    , Y(y)
    , HasY(true)
    {}

    TLabeledExample(std::vector<float>&& x, float y)
    : X(std::move(x))
    , Y(y)
    , HasY(true)
    {}

    TLabeledExample(const std::vector<float>& x)
    : X(x)
    , Y(0)
    , HasY(false)
    {}

    TLabeledExample(std::vector<float>&& x)
    : X(std::move(x))
    , Y(0)
    , HasY(false)
    {}

    std::string ToString() {
        std::stringstream ss;
        for (const float& x : X) {
            ss << x << "\t";
        }

        if (HasY) {
            ss << Y;
        } else {
            ss << "_";
        }

        return ss.str();
    }

    std::vector<float> X;
    float Y;
    bool HasY;
};

using TLabeledBatch = std::vector<TLabeledExample>;

} // namespace NML
