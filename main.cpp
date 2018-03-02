#include <cli.h>
#include <mc.h>
#include <io.h>

std::vector<float> IrisOHE(float y) {
	std::vector<float> result(3, 0.);
	result[static_cast<int>(y)] = 1;
	return result;
}

int Train(const NCli::TArguments& arguments) {
    std::string filename = arguments.GetParameter("i");
    NIO::TStreaming<NIO::TTSVParser> stream(filename);

    NML::TSequential model;
    model.AddLayer(std::make_unique<NML::TDense>(4, 4));
    model.AddLayer(std::make_unique<NML::TRelu>());
    model.AddLayer(std::make_unique<NML::TDense>(4, 3));
    model.AddLayer(std::make_unique<NML::TSoftmax>());

    while (stream.HasNext()) {
        NML::TLabeledExample example = stream.Next();
		std::vector<float> yHat = model.Forward(example.X);
		std::vector<float> y = IrisOHE(example.Y);

		for (size_t i = 0; i < y.size(); ++i) {
			std::cout << y[i] - yHat[i] << " ";
		}
		std::cout << std::endl;
	}

    return 0;
}

int main(int argc, char **argv) {
	NCli::TArguments arguments{argc, argv};
    NUtils::TModeChooser mc{arguments};

    mc.Add("train", Train);

    return mc.Run();
}
