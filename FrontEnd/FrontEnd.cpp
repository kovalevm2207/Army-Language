#include "FrontEnd.h"

int main(const int argc, const char* const argv[])
{
    char* buffer = ReadFile(argc, argv);

    stack_s lexical_analysis = MakeLexicalAnalysis(buffer, (argc == 2) ? argv[1] : "по_порядку_расчитайсь.army");
    FREE(buffer)

    Node_t* root = GetProgram(ConvertToAnalyze(lexical_analysis));

    StartHTMLfile();
    TreeDump(root, 0);
    EndHTMLfile();

    DeleteTreeNode(&root);
    StackDtor(&lexical_analysis);
}
Analyze_t ConvertToAnalyze(const stack_s lexical_analysis)
{
    return (Analyze_t){.data     = lexical_analysis.data,
                       .size     = lexical_analysis.size,
                       .capacity = lexical_analysis.capacity,
                       .STATUS   = lexical_analysis.STATUS};
}
