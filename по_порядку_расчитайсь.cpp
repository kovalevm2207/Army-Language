// То как на Си должна выглядеть наша программа

#include <stdio.h>

int CatchSpy(int spy_pos)
{
    int people_number_in_line = 10;

    int spy_line = spy_pos / people_number_in_line;

    printf("Хватай шпиона! Он в шеренге  номер %d\n", spy_line);

    return 0;
}

int main()
{
    int spy_pos = 52;

    int people_number_in_line = 10;
    int rota = 120;
    int cur_solder = 1;

    while(cur_solder <= rota)
    {
        if(cur_solder == spy_pos)
        {
            printf(". . . .\n");
            CatchSpy(spy_pos);
        }
        if(cur_solder != spy_pos)
        {
            printf("%3d ", cur_solder);
        }
        if(cur_solder % people_number_in_line == 0)
        {
            printf("\n");
        }
        cur_solder = cur_solder + 1;
    }

    return 0;
}
