#include <stdio.h>

struct Person
{
    char name[50];
    int age;
    float height;
};

int main()
{
    int a = 10;
    float b = 20.5;
    char c = 'A';
    double d = 30.123456;

    struct Person person = {"John Doe", 25, 5.9};

    printf("Primitive Data Types:\n");
    printf("Integer: Value = %d, Address = %ld, Size = %zu bytes\n", a, &a, sizeof(a));
    printf("Float: Value = %.2f, Address = %ld, Size = %zu bytes\n", b, &b, sizeof(b));
    printf("Character: Value = %c, Address = %ld, Size = %zu bytes\n", c, &c, sizeof(c));
    printf("Double: Value = %.6f, Address = %ld, Size = %zu bytes\n", d, &d, sizeof(d));

    printf("\nNon-Primitive Data Type (Struct Person):\n");
    printf("Name: Value = %s, Address = %ld, Size = %zu bytes\n", person.name, &person.name, sizeof(person.name));
    printf("Age: Value = %d, Address = %ld, Size = %zu bytes\n", person.age, &person.age, sizeof(person.age));
    printf("Height: Value = %.2f, Address = %ld, Size = %zu bytes\n", person.height, &person.height, sizeof(person.height));

    return 0;
}