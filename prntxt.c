#include <getopt.h> /* getopt_long */
#include <stdio.h>  /* IO */
#include <string.h> /* strcmp */
#include <unistd.h> /* sleep */

/*
 * There's not much comments in this program, 
 * text in IO functions explains what's happening well
 */

int main(int argc, char *argv[]) {
    int n = -1;         /* Repeat */
    int t = 1;          /* Timeout */
    int res;
    int argntext = -1;
    int textn = -1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--") == 0 && i < argc - 1) {
            argntext = i + 1;
            textn = argc - argntext;
        }
    }
    if (argntext == -1 || textn < 0) {
        puts("No text given");
        puts("(usage: prntxt -n|--number <N> [-t|--timeout [<T>]] -- <TEXT>)");
        return 1;
    }

    struct option longopts[] = {
        {
            .name = "number",
            .has_arg = required_argument,
            .flag = NULL,
            .val = 'n'
        },
        {
            .name = "timeout",
            .has_arg = required_argument,
            .flag = NULL,
            .val = 't'
        },
        {
        }
    };
    while(1) {
        res = getopt_long(argc, argv, "n:t:", longopts, NULL);
        if (res == -1) {
            break;
        }
        switch (res) {
            case '?':
                /* getopt_long already printed an error message. */
                puts("(usage: prntxt -n|--number <N> [-t|--timeout [<T>]] -- <TEXT>)");
                return 1;
                break;
            case 'n':
                if (optarg == NULL) {
                    puts("No value passed to '--number|-n' argument");
                    puts("(usage: prntxt -n|--number <N> [-t|--timeout [<T>]] -- <TEXT>)");
                    return 1;
                }
                res = sscanf(optarg, "%d", &n);
                if (res != 1 || n < 0) {
                    puts("Wrong value passed to '--number|-n' argument");
                    puts("(usage: prntxt -n|--number <N> [-t|--timeout [<T>]] -- <TEXT>)");
                    return 1;
                }
                break;
            case 't':
                if (optarg == NULL) {
                    puts("No value passed to '--timeout|-t' argument");
                    puts("(usage: prntxt -n|--number <N> [-t|--timeout [<T>]] -- <TEXT>)");
                    return 1;
                }
                res = sscanf(optarg, "%d", &t);
                if (res != 1 || t < 0) {
                    puts("Wrong value passed to '--timeout|-t' argument");
                    puts("(usage: prntxt -n|--number <N> [-t|--timeout [<T>]] -- <TEXT>)");
                    return 1;
                }
                break;
        }
    }
    if (n == -1) {
        puts("No value passed to '--number|-n' argument");
        puts("(usage: prntxt -n|--number <N> [-t|--timeout [<T>]] -- <TEXT>)");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < textn; j++) {
            fputs(argv[argntext + j], stdout);
            putchar(' ');
        }
        putchar('\n');
        if (i != n - 1) sleep(t);
    }

    return 0;
}


