#include <cstdio>

#include "driver.hpp"
#include "assembler.hpp"

render_info<double> TestInfo =
{
    nullptr,
    100, 100,
    100,
    100,
    -2.0, 2.0, -2.0, 2.0,
    2.0
};

int main(int argc, char ** argv)
{
    driver Driver;
    for (int i = 1; i < argc; ++i)
    {
        if (i != 1)
        {
            printf("\n");
        }
        printf("Trying to parse \"%s\"...\n", argv[i]);
        if (Driver.Parse(argv[i]))
        {
            printf("Parsing successful. Parse tree is:\n");
            print(Driver.Root);
            func F = Assemble(Driver.Root);
            F(&TestInfo);
            FreeFunc(F);
        } else
        {
            printf("Parsing failed.\n");
        }
    }
    return 0;
}
