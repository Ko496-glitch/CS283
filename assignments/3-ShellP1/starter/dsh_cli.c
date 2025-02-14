#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dshlib.h"

int main(void)
{

    char cmd_buff[SH_CMD_MAX + 1];
    command_list_t clist;
    int ret;

    while (1)
    {
        
        printf("%s", SH_PROMPT);

    
        if (fgets(cmd_buff, sizeof(cmd_buff), stdin) == NULL)
        {
            printf("\n");
            break;
        }

    
        cmd_buff[strcspn(cmd_buff, "\n")] = '\0';


        if (strcmp(cmd_buff, EXIT_CMD) == 0)
        {
            break;
        }


        ret = build_cmd_list(cmd_buff, &clist);

        if (ret == OK)
        {
        
            printf(CMD_OK_HEADER, clist.num);
            for (int i = 0; i < clist.num; i++)
            {
                printf("<%d>%s", i + 1, clist.commands[i].exe);
                if (strlen(clist.commands[i].args) > 0)
                {
                
                    printf("[%s]", clist.commands[i].args);
                }
                printf("\n");
            }
        }
        else if (ret == WARN_NO_CMDS)
        {
            printf("%s", CMD_WARN_NO_CMD);
        }
        else if (ret == ERR_TOO_MANY_COMMANDS)
        {
            printf(CMD_ERR_PIPE_LIMIT, CMD_MAX);
        }
        else if (ret == ERR_CMD_OR_ARGS_TOO_BIG)
        {
            printf("error: command or arguments too big\n");
        }
    }

    return 0;
}
