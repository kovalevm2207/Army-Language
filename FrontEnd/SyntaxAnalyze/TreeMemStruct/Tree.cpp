#include "Tree.h"

Tree_t* TreeCtor(Node_t* root)
{
    assert(root);
    Tree_t* tree = (Tree_t*) calloc(1, sizeof(Tree_t));

    Var_t* vars = (Var_t*) calloc(START_VARS_NUM, sizeof(Var_t));
    assert(vars);
    tree->vars_num = 0;
    tree->max_vars_num = START_VARS_NUM;
    // GetTreeVars(&vars, root, &tree->vars_num, &tree->max_vars_num);
    assert(vars);

    tree->vars = vars;
    tree->root  = root;
    tree->size  = CountTreeSize(root);
    tree->depth = GetTreeDepth(root);

    return tree;
}
size_t GetTreeDepth(const Node_t* const node)
{
    if (node == NULL) {
        return 0;
    }

    size_t left_depth  = GetTreeDepth(node->left);
    size_t right_depth = 0;
    if (node->right) right_depth = GetTreeDepth(node->right);

    return 1 + (left_depth > right_depth ? left_depth : right_depth);
}
size_t CountTreeSize(const Node_t* const node)
{
    assert(node);

    size_t size = 1;
    if(node->left)  size += CountTreeSize(node->left);
    if(node->right) size += CountTreeSize(node->right);

    return size;
}
TreeErr_t MakePrevNode(Node_t* node)
{
    if(!node) return TREE_OK;
    if(node->left)
    {
        node->left->prev_node = &node->left;
        MakePrevNode(node->left);
    }
    if(node->right)
    {
        node->right->prev_node = &node->right;
        MakePrevNode(node->right);
    }

    return TREE_OK;
}
/*size_t GetTreeVars(Var_t** vars, const Node_t* const node, size_t* cur_vars_num, size_t* max_vars_num)
{
    assert(vars);
    assert(*vars);
    assert(node);
    assert(max_vars_num);

    if(node->type == VAR)
    {
        if(!FindVar(node->data.var, *vars, *cur_vars_num))
        {
            if(*cur_vars_num == *max_vars_num)
            {
                Var_t* new_vars = (Var_t*) realloc(*vars, (*max_vars_num * 2) * sizeof(Var_t));
                assert(new_vars);
                memset(new_vars + *max_vars_num, 0, *max_vars_num * sizeof(Var_t));
                *vars = new_vars;
                *max_vars_num *= 2;
            }
            (*vars)[(*cur_vars_num)++].name = node->data.var;
        }
    }
    if(node->left)  GetTreeVars(vars, node->left,  cur_vars_num, max_vars_num);
    if(node->right) GetTreeVars(vars, node->right, cur_vars_num, max_vars_num);

    return *cur_vars_num;
}*/
bool FindVar(const char* const var, const Var_t* const vars, const size_t vars_num)
{
    assert(var);
    assert(vars);

    for (size_t i = 0; i < vars_num; i++)
    {
        if(strcmp(var, vars[i].name) == 0) return true;
    }
    return false;
}
TreeErr_t TreeDtor(Tree_t** tree)
{
    assert(tree);
    assert(*tree);

    (*tree)->max_vars_num = 0;
    (*tree)->size = 0;
    (*tree)->depth = 0;

    free((*tree)->vars);
    (*tree)->vars = NULL;

    DeleteTreeNode(&(*tree)->root);

    free((*tree));
    *tree = NULL;

    return TREE_OK;
}
TreeErr_t TreeStructDumpF(FILE* stream, Tree_t* tree)
{
    assert(stream);
    assert(tree);

    fprintf(stream, "TreeDump:\n"
                    "struct\n"
                    "{\n"
                    "\troot         = %p\n",  tree->root);
    fprintf(stream, "\tsize         = %zu\n", tree->size);
    fprintf(stream, "\tdepth        = %zu\n", tree->depth);
    fprintf(stream, "\tmax_vars_num = %zu\n", tree->max_vars_num);
    fprintf(stream, "\tvars_num     = %zu\n", tree->vars_num);
    fprintf(stream, "\tvars\n"
                    "\t{\n");

    for(size_t i = 0; i < tree->max_vars_num; i++)
    {
        if(tree->vars[i].name)
            fprintf(stream, ORANGE_COLOR "\t [%zu]*\t%s = %lg\n", i + 1, tree->vars[i].name, tree->vars[i].data);
        else
            fprintf(stream, CYAN_COLOR   "\t [%zu] \t%p = %lg\n", i + 1, tree->vars[i].name, tree->vars[i].data);
        fprintf(stream, RESET);
    }
    fprintf(stream, "\t}\n"
                    "}\n"
                    "\n");

    return TREE_OK;
}

Node_t* TreeNodeCtor(NodeType_t type, TokenData_t value, Node_t* left_som, Node_t* right_som)
{
    Node_t* node = (Node_t*) calloc(1, sizeof(Node_t));
    if(node == NULL) return NULL;

    node->type = type;
    node->data = value;
    node->prev_node = NULL;
    node->left = left_som;
    node->right = right_som;

    if (left_som)  left_som->prev_node  = &node->left;
    if (right_som) right_som->prev_node = &node->right;

    return node;
}
Node_t* DeepNodeCopy(Node_t* node)
{
     return  (node) ? TreeNodeCtor(node->type, node->data, DeepNodeCopy(node->left), DeepNodeCopy(node->right)) : NULL;
}
TreeErr_t TreeInsertLeft(Node_t* base_node, Node_t* inserting_node)
{
    assert(base_node != NULL);
    if (base_node->left != NULL)  return TREE_ERR_NODE_NOT_EMPTY;

    base_node->left = inserting_node;
    if (inserting_node) inserting_node->prev_node = &base_node->left;

    return TREE_OK;
}
TreeErr_t TreeInsertRight(Node_t* base_node, Node_t* inserting_node)
{
    assert(base_node != NULL);
    if (base_node->right != NULL) return TREE_ERR_NODE_NOT_EMPTY;

    base_node->right = inserting_node;
    if (inserting_node) inserting_node->prev_node = &base_node->right;

    return TREE_OK;
}
TreeErr_t DeleteTreeNode(Node_t** node)
{
    assert(node != NULL);
    if (*node == NULL) return NULL_NODE;

    Node_t* cur_node = *node;

    if (cur_node->left)  DeleteTreeNode(&cur_node->left);
    if (cur_node->right) DeleteTreeNode(&cur_node->right);

    switch(cur_node->type)
    {
        case NUM:
            cur_node->data.num = 0;
            break;
        case VAR:
            cur_node->data.name = 0;
            break;
        case OP:
            cur_node->data.word = UNKNOWN;
            break;
        case FUNC:
            cur_node->data.name = 0;
            break;
        default:
            return INCORRECT_TYPE;
    }

    cur_node->prev_node = NULL;

    free(cur_node);
    *node = NULL;

    return TREE_OK;
}
TreeErr_t PrintTreeNode(FILE* stream, const Node_t* node, TraverseMode_t mode)
{
    assert(mode == PREORDER || mode == INORDER || mode == POSTORDER);
    if (!node)
    {
        fprintf(stream, " nil ");
        return TREE_OK;
    }

    fprintf(stream, "(");
    switch(mode)
    {
        case PREORDER:
            PrintTreeData(stream, node);
            PrintTreeNode(stream, node->left,  mode);
            PrintTreeNode(stream, node->right, mode);
            break;
        case INORDER:
            PrintTreeNode(stream, node->left,  mode);
            PrintTreeData(stream, node);
            PrintTreeNode(stream, node->right, mode);
            break;
        case POSTORDER:
            PrintTreeNode(stream, node->left,  mode);
            PrintTreeNode(stream, node->right, mode);
            PrintTreeData(stream, node);
            break;
        default:
            return INVALID_MODE;
    }
    fprintf(stream, ")");

    return TREE_OK;
}
TreeErr_t PrintTreeData(FILE* stream, const Node_t* node)
{
    assert(stream != NULL);
    assert(node != NULL);

    switch(node->type)
    {
        case NUM:  fprintf(stream, " %d ", node->data.num                  ); break;
        case OP:   fprintf(stream, " %s ", WordsTypesNames[node->data.word]); break;
        case VAR:  fprintf(stream, " %s ", Vars[node->data.name]            ); break;
        case FUNC: fprintf(stream, " %s ", Functions[node->data.name]      ); break;
        default:
            return INCORRECT_TYPE;
    }

    return TREE_OK;
}
TreeErr_t TreeDump_(const Node_t* node, int count_img, const char* func, const char* file, int line)
{
    ON_DEBUG(printf("node ptr = %p\n", node));
    if (node == NULL) return NULL_NODE;

    CreateDotFile(node);
    char command[MAX_FILE_NAME] = {};
    sprintf(command, "dot -Tsvg TreeMemStruct/svg_dot/dump.dot -o TreeMemStruct/svg_dot/%ddump.svg", count_img);
    system(command);
    sprintf(command, "dot -Tpdf TreeMemStruct/svg_dot/dump.dot -o TreeMemStruct/pdf_dot/%ddump.pdf", count_img);
    system(command);

    WriteInHtmlFile(node, count_img, func, file, line);

    return TREE_OK;
}
