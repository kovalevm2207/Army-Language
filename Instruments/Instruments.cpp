#include "Instruments.h"

char* ReadFile(const int argc, const char* const argv[])
{
    assert(argv != NULL && "NULL ARGV");

    const char* name = NULL;
    if(argc != 2)
    {
        HelpUser();
        name = "по_порядку_расчитайсь.army";
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
char* SkipSpaces(char* ptr, size_t* line_counter, char** line_begining)
{
    assert(ptr != NULL && "NUUL ptr for SkipSpaces func");
    assert(line_counter);
    assert(line_begining);

    while(*ptr && isspace((unsigned char) *ptr))
    {
        if(*ptr == '\n')
        {
            *line_begining = ptr + 1;
            ++*line_counter;
        }
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
                    "Где 'My_file.txt' название файла, содержащего ваши данные с указанием полного пути до текущей директории\n"
                    "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
}
size_t CheckLen(char** word, size_t word_len, const size_t letter)
{
    assert(word);
    assert(*word);
    assert(letter <= word_len);

    if(letter == word_len)
    {
        char* new_word = (char*) realloc(*word, (word_len * 2) * sizeof(char));
        assert(new_word);
        *word = new_word;
        memset(*word + word_len, 0, word_len);
        word_len *= 2;
    }

    return word_len;
}
bool is_cyrillic_symbol(const char* s)
{
    assert(s);

    unsigned char c1 = (unsigned char)s[0];
    unsigned char c2 = (unsigned char)s[1];

    if (s[1] == '\0') return false;

    if (c1 == 0xD0)      return (c2 >= 0x90 && c2 <= 0xBF);
    else if (c1 == 0xD1) return (c2 >= 0x80 && c2 <= 0x8F);

    return false;
}
void PrintCyrillicString(char* string)
{
    assert(string);

    while(*string != '\0' && *string != '\n')
    {
        if(is_cyrillic_symbol(string))
        {
            printf("%c%c", string[0], string[1]);
            string += 2;
        }
        else
        {
            printf("%c", *string);
            string++;
        }
    }
    return;
}
