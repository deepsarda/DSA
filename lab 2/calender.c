#include <stdio.h>

char days[][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
char months[][10] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
int months_length[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int get_first_day_of_month(int year, int month)
{
    int d = 1; // First day of the month
    int m = month;
    int y = year;

    if (m < 3)
    {
        m += 12;
        y -= 1;
    }

    int k = y % 100;
    int j = y / 100;

    // Source: Zeller's Congruence
    int f = d + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 + 5 * j;
    return f % 7;
}

int main()
{
    int year;
    int month;

    printf("Enter year: ");
    scanf("%d", &year);

    printf("Enter month (1-12): ");
    scanf("%d", &month);

    if (month < 1 || month > 12)
    {
        printf("Invalid month!\n");
        return 1;
    }

    printf("Calendar for %s %d:\n", months[month - 1], year);
    printf("Mon Tue Wed Thu Fri Sat Sun\n");

    int first_day = get_first_day_of_month(year, month);
    int days_in_month = months_length[month - 1];

    // Check for leap year
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
    {
        days_in_month = 29;
    }

    int day_counter = 1;
    int week_day;

    for (week_day = 0; week_day < first_day; week_day++)
    {
        printf("    ");
    }

    for (; day_counter <= days_in_month; week_day++)
    {
        printf("%3d ", day_counter);
        if (week_day % 7 == 6)
        {
            printf("\n");
        }

        day_counter++;
    }
    printf("\n");

    return 0;
}