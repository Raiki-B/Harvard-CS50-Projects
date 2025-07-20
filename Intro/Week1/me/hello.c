#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Requests name from user
    string name = get_string("What's your name?: \n");

    // Prints a hello message to the user by their name.
    printf("hello, %s\n", name);
}
