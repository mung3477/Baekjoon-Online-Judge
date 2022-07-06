#include <stdio.h>

typedef struct  s_date
{
    int year;
    int month;
    int day;
}               Date;


int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int is_leap_year(int year) 
{
    if (year % 400 == 0)
        return (1);
    else if (year % 100 == 0)
        return (0);
    else if (year % 4 == 0)
        return (1);
    else
        return (0);
}

int date_diff(Date today, Date d_day)
{
    int left;
    if (today.month == d_day.month)
        left = d_day.day - today.day;
    else
    {
        left = days[today.month] - today.day + (today.month == 2 && is_leap_year(today.year));
        for (int i = today.month + 1; i < d_day.month; i++) {
            left += days[i];
            if (i == 2 && is_leap_year(today.year))
                left += 1;
        }
        left += d_day.day;
    }
    return (left);
}

int this_year_left(Date today)
{
    int this_year = (is_leap_year(today.year) ? 366 : 365);
    int passed = 0;

    for (int i = 1; i < today.month; i++) {
        passed += days[i];
        if (i == 2 && is_leap_year(today.year))
            passed += 1;
    }
    passed += today.day;

    return (this_year - passed);
}

int d_day_year_left(Date d_day)
{
    int left = 0;
    for (int i = 1; i < d_day.month; i++)
    {
        left += days[i];
        if (i == 2 && is_leap_year(d_day.year))
            left += 1;
    }
    left += d_day.day;
    return (left);
}

int between(Date today, Date d_day)
{
    int ret = 0;
    for (int i = today.year + 1; i < d_day.year; i++)
        ret += (is_leap_year(i) ? 366 : 365);
    return (ret);
}

int main(void)
{
    Date today, d_day;

    scanf("%d %d %d", &today.year, &today.month, &today.day);
    scanf(" %d %d %d", &d_day.year, &d_day.month, &d_day.day);

    if ((today.year + 1000 < d_day.year) || \
            ((today.year + 1000 == d_day.year) && \
                (today.month * 100 + today.day) <= (d_day.month * 100 + d_day.day))
        )
            printf("gg");
    else if (today.year == d_day.year)
        printf("D-%d", date_diff(today, d_day));
    else
        printf("D-%d", this_year_left(today) + d_day_year_left(d_day) + between(today, d_day));
    return (0);
}