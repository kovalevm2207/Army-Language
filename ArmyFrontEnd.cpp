#include "ArmyFrontEnd.h"

int main(const int argc, const char* const argv[])
{
    char* buffer = ReadFile(argc, argv);

    stack_s lexical_analysis = MakeLexicalAnalysis(buffer, (argc == 2) ? argv[1] : "по_порядку_расчитайсь.army");
    FREE(buffer)

    /*
    Node_t* root = GetProgram(lexical_analysis);
    StartHTMLfile();
    TreeDump(root, 0);
    DeleteTreeNode(&root);
    EndHTMLfile();
    */
    StackDtor(&lexical_analysis);
}
