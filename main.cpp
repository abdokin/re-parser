#include "./regex.hpp"


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <regular_expression>" << std::endl;
        return 1;
    }

    std::string regexString = argv[1]; // Get the regular expression from command line argument
    RegExParser parser(regexString);

    try
    {
        RegEx *result = parser.parse();
        std::cout << *result << '\n'; 
        delete result;                // Clean up memory
    }
    catch (const std::exception &e)
    {
        std::cerr << "Parser error: " << e.what() << std::endl;
    }

    return 0;
}
