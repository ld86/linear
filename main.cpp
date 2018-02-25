#include <cli.h>
#include <mc.h>
#include <io.h>

int Train(const NCli::TArguments& arguments) {
    std::string filename = arguments.GetParameter("i");
    NIO::TStreaming<NIO::TTSVParser> stream(filename);

    while (stream.HasNext()) {
        NML::TLabeledExample example = stream.Next();
        std::cout << example.ToString() << std::endl;
    }

    return 0;
}

int main(int argc, char **argv) {
	NCli::TArguments arguments{argc, argv};
    NUtils::TModeChooser mc{arguments};

    mc.Add("train", Train);

    return mc.Run();
}
