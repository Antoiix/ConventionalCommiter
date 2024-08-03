/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** stumper3
*/

#include "libs.h"

int main_two(int ac, char **av)
{
    if (ac == 10)
        return av[0][0];
    char *args[] = {"git", "status"};
    printf("%s, %s\n", args[0], args[1]);
    system("git status");
    return 0;
}

void set_noncanonical_mode(void)
{
    struct termios t;

    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void restore_terminal(void)
{
    struct termios t;

    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void handle_arrows(const char c)
{
    switch (c) {
        case 68:
            printf("\033[1D");
            break;
        case 67:
            printf("\033[1C");
            break;
        default:
            break;
    }
}

void exec_git(void)
{
    int status = fork();
    char* command = "git";
    char* argument_list[] = {"git", "status", NULL};

    if (status == 0) {
        int status_code = execvp(command, argument_list);

        if (status_code == -1) {
            exit(1);
        }
    }
}

void exec_push(void)
{
    int status = fork();
    char* command = "git";
    char* argument_list[] = {"git", "push", NULL};

    if (status == 0) {
        int status_code = execvp(command, argument_list);

        if (status_code == -1) {
            exit(1);
        }
    }
}

void exec_commit(char *commit_struct)
{
    int status = fork();
    char* command = "git";
    char* argument_list[] = {"git", "commit", "-m", commit_struct, NULL};

    if (status == 0) {
        int status_code = execvp(command, argument_list);

        if (status_code == -1) {
            exit(1);
        }
    }
}

void print_menu(void)
{
    printf("\033[1;37m------------------------------------------------------------------------------\n\033[0m");
    printf("\033[1;37m|\n\033[0m");
    printf("\033[1;37m|\033[0m\033[1;33m     ----- Conventionnal Commiter -----\n\033[0m");
    printf("\033[1;37m|\n\033[0m");
    printf("\033[1;37m|\033[0m\033[1;37m ------------------------------------------\n\033[0m");
    printf("\033[1;37m|\n\033[0m");
    printf("\033[1;37m|\033[0m   \033[1;34mTap 1 to see your uncommited changes (git status)\n\033[0m");
    printf("\033[1;37m|\033[0m   \033[1;35mTap 2 to create your commit\n\033[0m");
    printf("\033[1;37m|\033[0m   \033[1;36mTap 3 to push your commit\n\033[0m");
    printf("\033[1;37m|\n\033[0m");
    printf("\033[1;37m|\033[0m   \033[1;31mPress Enter key to quit the program\n\033[0m");
    printf("\033[1;37m------------------------------------------------------------------------------\n\033[0m");
}

void menu_wait(void)
{
    char c = 0;
    while (c != 114)
        c = getchar();
    print_menu();
}

char *commit_title(void)
{
    int exit_num = 0;
    char c;
    char *str = calloc(10, sizeof(char));

    printf("Please select :\n\n"
           "1 to feat\n"
           "2 to fix\n"
           "3 to chore\n"
           "4 to refactor\n"
           "5 to style\n"
           "6 to test\n"
           "7 to docs\n"
           "8 to perf\n");
    while (exit_num == 0) {
        c = getchar();
        if (c == '1') {
            str = "feat";
            exit_num = 1;
        }
        if (c == '2') {
            str = "fix";
            exit_num = 1;
        }
        if (c == '3') {
            str = "chore";
            exit_num = 1;
        }
        if (c == '4') {
            str = "refactor";
            exit_num = 1;
        }
        if (c == '5') {
            str = "style";
            exit_num = 1;
        }
        if (c == '6') {
            str = "test";
            exit_num = 1;
        }
        if (c == '7') {
            str = "docs";
            exit_num = 1;
        }
        if (c == '8') {
            str = "perf";
            exit_num = 1;
        }
    }
    return str;
}

void select_commit(void)
{
    char *commit_text = calloc(1000, sizeof(char));
    char *title = commit_title();
    char c = '\0';
    char str[] = "\0";

    printf("%s is selected\n", title);
    printf("Please enter your commit target : ");
    strcat(commit_text, title);
    strcat(commit_text, "(");
    c = getchar();
    while (c != 10) {
        printf("%c", c);
        str[0] = c;
        strcat(commit_text, str);
        c = getchar();
    }
    printf("\n");
    strcat(commit_text, "): ");
    printf("Please enter your commit comment : ");
    c = getchar();
    while (c != 10) {
        printf("%c", c);
        str[0] = c;
        strcat(commit_text, str);
        c = getchar();
    }
    printf("\n");
    exec_commit(commit_text);

}

int main(void)
{
    print_menu();

    set_noncanonical_mode();
    char c = 0;

    while (c != 10) {
        c = getchar();
        if (c == 49) {
            exec_git();
            wait(NULL);
            printf("\033[1;33m\nPress r to return to the menu\033[0m\n");
            menu_wait();
        }
        if (c == 50) {
            printf("commit\n");
            select_commit();
            printf("\033[1;33m\nPress r to return to the menu\033[0m\n");
            menu_wait();
        }
        if (c == 51) {
            exec_push();
            wait(NULL);
            printf("\033[1;33m\nPress r to return to the menu\033[0m\n");
            menu_wait();
        }
    }
    restore_terminal();
    return 0;
}