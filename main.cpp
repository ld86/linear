#include <cli.h>
#include <mc.h>

int HelloWorld(const NCli::TArguments& arguments) {
    std::cout << "Hello, world" << std::endl;
    return 0;
}

int main(int argc, char **argv) {
	NCli::TArguments arguments{argc, argv};
    NUtils::TModeChooser mc{arguments};

    mc.Add("hello", HelloWorld);

    return mc.Run();
}
