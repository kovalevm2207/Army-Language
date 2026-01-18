#include "ArmyFrontEnd.h"

int main(const int argc, const char* const argv[])
{
    char* buffer = ReadFile(argc, argv);

    stack_s lexical_analysis = MakeLexicalAnalysis(buffer);
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
