#pragma once

#include <vector>
#include <sstream>
#include <memory>
#include <random>
#include <cmath>
#include <algorithm>

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

class ILayer {
public:
    virtual std::vector<float> Forward(const std::vector<float>& in) const = 0;

    ~ILayer() = default;
};
using ILayerPtr = std::unique_ptr<ILayer>;

class TDense : public ILayer {
public:
    TDense(size_t in, size_t out)
    : In(in)
    , Out(out)
    , Weights(Out, std::vector<float>(In, 0.0))
    {
        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution(-1.0, 1.0);
        for (int i = 0; i < Out; ++i) {
            for (int j = 0; j < In; ++j) {
                Weights[i][j] = distribution(generator);
            }
        }
    }

    std::vector<float> Forward(const std::vector<float>& in) const {
        if (in.size() != In) {
            throw std::runtime_error("in.size() != In");
        }

        std::vector<float> out(Out, 0);

        for (int i = 0; i < Out; ++i) {
            for (int j = 0; j < In; ++j) {
                out[i] += Weights[i][j] * in[j];
            }
        }

        return out;
    }

private:
    size_t In;
    size_t Out;
    std::vector<std::vector<float>> Weights;
};

class TSoftmax : public ILayer {
    std::vector<float> Forward(const std::vector<float>& in) const {
		float max = *std::max_element(in.begin(), in.end());

		float sum = 0;
		for (const float& i : in) {
			sum += exp(i - max);
		}

		std::vector<float> result(in.size(), 0.0);
		for (size_t i = 0; i < in.size(); ++i) {
			result[i] = exp(in[i] - max) / sum;
		}

		return result;
	}
};

class TSequential {
public:
    void AddLayer(ILayerPtr&& layer) {
        Layers.push_back(std::move(layer));
    }

    std::vector<float> Forward(std::vector<float> data) {
        for (const ILayerPtr& layer : Layers) {
            data = layer->Forward(data);
        }
        return data;
    }

private:
    std::vector<ILayerPtr> Layers;
};

} // namespace NML
