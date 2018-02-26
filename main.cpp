#include <cli.h>
#include <mc.h>
#include <io.h>

int Train(const NCli::TArguments& arguments) {
    std::string filename = arguments.GetParameter("i");
    NIO::TStreaming<NIO::TTSVParser> stream(filename);

    NML::TSequential model;
    model.AddLayer(std::make_unique<NML::TDense>(4, 3));
    model.AddLayer(std::make_unique<NML::TSoftmax>());

    while (stream.HasNext()) {
        NML::TLabeledExample example = stream.Next();
        for (const auto i : model.Forward(example.X)) {
            std::cout << i << " ";
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
