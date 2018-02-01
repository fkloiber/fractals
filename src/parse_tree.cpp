#include "parse_tree.hpp"
#include <cstdio>

template <typename... T>
void printIndented(int Indent, const char * Format, T... Args)
{
    printf("%*s", 4*Indent, "");
    printf(Format, Args...);
}

size_t length(const std::list<parse_tree_ptr> & L)
{
    return std::distance(begin(L), end(L));
}

void printArgs(int Indent, const std::list<parse_tree_ptr> & L)
{
    int i = 1;
    for (auto P : L)
    {
        printIndented(Indent, "--- Argument #%d:\n", i++);
        print(P, Indent + 1);
    }
}

void print(parse_tree_ptr P, int Indent)
{
    switch (P->Type)
    {
        case expression_type::Invalid:
        {
            printIndented(Indent, "ERROR Invalid node\n");
            return;
        } break;

        case expression_type::Addition:
        {
            printIndented(Indent, "Addition with %d operators:\n", length(P->Params));
            printArgs(Indent, P->Params);
        } break;

        case expression_type::Multiplication:
        {
            printIndented(Indent, "Multiplication with %d operators:\n", length(P->Params));
            printArgs(Indent, P->Params);
        } break;

        case expression_type::Exponentiation:
        {
            printIndented(Indent, "Exponentiation with %d operators:\n", length(P->Params));
            printArgs(Indent, P->Params);
        } break;

        case expression_type::Negation:
        {
            printIndented(Indent, "Negation:\n");
            printArgs(Indent, P->Params);
        } break;

        case expression_type::Inversion:
        {
            printIndented(Indent, "Inversion:\n");
            printArgs(Indent, P->Params);
        } break;

        case expression_type::Function:
        {
            printIndented(Indent, "Function \"%s\" with %d arguments:\n", P->Name.c_str(), length(P->Params));
            printArgs(Indent, P->Params);
        } break;

        case expression_type::Literal:
        {
            printIndented(Indent, "Literal of type %s with value ", P->IsInteger ? "int" : "double");
            if (P->IsInteger)
            {
                printf("%lld.\n", P->IntVal);
            } else
            {
                printf("%f.\n", P->DblVal);
            }
        } break;

        case expression_type::Identifier:
        {
            printIndented(Indent, "Identifier \"%s\"\n", P->Name.c_str());
        } break;
    }
}
