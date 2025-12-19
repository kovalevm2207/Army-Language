#include "Instruments.h"

char* ReadFile(const int argc, const char* const argv[])
{
    assert(argv != NULL && "NULL ARGV");

    const char* name = NULL;
    if(argc != 2)
    {
        HelpUser();
        name = "лови шпиона.army";
    }else name = argv[1];


    FILE* file = fopen(name, "r");
    if(file == NULL) return NULL;

    struct stat file_info = {};
    stat(name, &file_info);
    size_t file_size = (size_t) file_info.st_size;

    char* buffer = (char*) calloc(file_size + 1, sizeof(char));
    if (buffer == NULL) {fclose(file); file = NULL; return NULL;}

    size_t ret = fread(buffer, sizeof(char), file_size, file);
    if (ret != file_size)
    {
        fclose(file);
        free(buffer);
        file = NULL;
        buffer = NULL;
        return NULL;
    }

    fclose(file);
    file = NULL;

    return buffer;
}
char* SkipSpaces(char* ptr)
{
    assert(ptr != NULL && "NUUL ptr for SkipSpaces func");

    while(*ptr && isspace((unsigned char) *ptr))
    {
        ptr++;
    }
    return ptr;
}
void HelpUser(void)
{
    fprintf(stderr, "Вы не ввели название файла, содержащего ваши данные, поэтому был запущен\n"
                    "встроенный файл. Чтобы остановить работу программы можете использовать сочетание:\n\n"
                    "                               Ctrl + C\n\n"
                    "Если хотите, чтобы программа запустилась с использованием вашего файла на вход командной строки\n"
                    "Подайте следующее выражение:\n\n"
                    "                        ./math++ My_file.txt\n\n"
                    "Где 'My_file.txt' название файла, содержащего ваши данные с указанием полного пути до текущей директории\n\n");
}
