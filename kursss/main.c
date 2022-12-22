#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ticket
{
    int trainNumber; // номер поезда
    char station[50]; // название конечного пункта
    char date[20]; // дата
    int H1, M1, // время отправления
        H2, M2; // время прибытия
    int cost; // стоимость билета в копейках
    int ticketsSold; // количество проданных билетов
    int ticketsAvailable; // количество доступных билетов 
};
char * logIn(char login[], char password[]) // функция входа в аккаунт
{
    char * role; // роль
    strcpy(&role, ""); // обнуление роли
    FILE *f1; // файл для чтения аккаунтов
    if ((f1 = fopen("acc.txt", "r+")) == NULL) // открытие файла
    {
        printf("Cannot open file.\n");
        exit(1);
    }
    while (!feof(f1)) // цикл для чтения до конца файла
    {
        char constr[80]; // временная переменная для чтения
        char *p = constr; // временная переменная для чтения
        fgets(p, 80, f1); // чтение строки
        if (p[strlen(p) - 1] == '\n') // удаление символа перехода на новую строку
            p[strlen(p) - 1] = '\0';
        char *str[80];
        strcpy(str, constr);
        char *token = strtok(str, ";"); // разделение строки по символу ";"
        char *l[80]; // переменная для логина
        strcpy(l, token); // чтение логина из файла
        token = strtok(NULL, ";"); //чтение в строке до следующего символа ";"
        char *pa[80]; // переменная для пароля
        strcpy(pa, token); // чтение пароля из файла
        if (strcmp(login, l) == 0 && strcmp(password, pa) == 0) //проверка логина и пароля
        {
            token = strtok(NULL, ";");
            strcpy(&role, token);
            printf("Role: %s\n", &role); // вывод роли на экран
        }
    }
    fclose(f1); // закрытие файла
    return role; // возврат роли
}
int loadTickets(struct Ticket *t) // чтение билетов из файла
{
    FILE *f1; // файл
    if ((f1 = fopen("tickets.txt", "r+")) == NULL) // открытие файла
    {
        printf("Cannot open file.\n");
        exit(1);
    }
    int i = 0; // перемнная для подсчёта количества билетов
    while (!feof(f1)) // цикл чтения до конца файла
    {
        char constr[80];
        char *p = constr;
        fgets(p, 80, f1);
        if (p[strlen(p) - 1] == '\n')
            p[strlen(p) - 1] = '\0';
        char *str[80];
        strcpy(str, constr);
        char *token = strtok(str, ";");
        char *pp[80];
        strcpy(pp, token);
        t[i].trainNumber = atoi(pp);
        token = strtok(NULL, ";");
        strcpy(&t[i].station, token);
        token = strtok(NULL, ";");
        strcpy(&t[i].date, token);
        token = strtok(NULL, ";");
        strcpy(pp, token);
        t[i].H1 = atoi(pp);
        token = strtok(NULL, ";");
        strcpy(pp, token);
        t[i].M1 = atoi(pp);
        token = strtok(NULL, ";");
        strcpy(pp, token);
        t[i].H2 = atoi(pp);
        token = strtok(NULL, ";");
        strcpy(pp, token);
        t[i].M2 = atoi(pp);
        token = strtok(NULL, ";");
        strcpy(pp, token);
        t[i].cost = atoi(pp);
        token = strtok(NULL, ";");
        strcpy(pp, token);
        t[i].ticketsSold = atoi(pp);
        token = strtok(NULL, ";");
        strcpy(pp, token);
        t[i].ticketsAvailable = atoi(pp);
        i++;
    }
    fclose(f1); // закрытие файла
    return i; // возврат количества билетов
}
int printTicket(struct Ticket t) // вывод билетов на экран
{
    printf("Train number: %d, ", t.trainNumber);
    printf("Station: %s, ", t.station);
    printf("Time: %s, %d:%d, Time2: %d:%d\n", t.date, t.H1, t.M1, t.H2, t.M2);
    printf("Cost: %.2f BYN, ", t.cost/100.0);
    printf("Sold: %d/%d\n", t.ticketsSold, t.ticketsAvailable);
    return 0;
}
int save(int count, struct Ticket t[]) // cохранение билетов в файл
{
    FILE *f2; // переменая файла
    f2 = fopen("tickets.txt", "w+"); // открытие файла
    for (int i = 0; i < count; i++) // цикл на все билеты
    {
        char buf[80]; // временная переменная
        sprintf(buf, "%d;%s;%s;%d;%d;%d;%d;%d;%d;%d", t[i].trainNumber, t[i].station, t[i].date,
                t[i].H1, t[i].M1, t[i].H2, t[i].M2,
                t[i].cost, t[i].ticketsSold, t[i].ticketsAvailable); // формирование строки с данными о билете в переменную buf
        fputs(buf, f2); // сохренение строки buf в файл
        if (i + 1 < count) // добаление перехода на новую строку
            fputs("\n", f2);
    }
    fclose(f2); // закрытие файла
}
int buy(int count, struct Ticket tickets[]) // покупка билета
{
    printf("Which city would you like to go to?\n"); // ввод необходимого конечного пункта
    char city[50];
    scanf("%s", &city);
    printf("What time (hour) would you like to hit the road?\n"); // ввод часа, на который нужет билет
    int hour1;
    scanf("%d", &hour1);
    printf("Until what time (hour) do you need a ticket?\n"); // ввод до какого часа необходим билет
    int hour2;
    scanf("%d", &hour2);
    for (int i = 0; i < count; i++) // цикл на все билеты
    {
        if (strcmp(tickets[i].station, city) == 0 &&
            tickets[i].H1 >= hour1 &&
            tickets[i].H2 < hour2) // проверка билета
        {
            printf("%3d|", i); // вывод подходящего билета
            printTicket(tickets[i]);
        }
    }
    printf("Which ticket do you want to bye?\n"); // запрос на покупку билета
    int ticketNumber;
    scanf("%d", &ticketNumber);
    if (ticketNumber < 0 || ticketNumber >= count) // проверка корректности введённого номера
    {
        printf("Error"); // вывод ошибки
        exit(1);
    }
    if (tickets[ticketNumber].ticketsSold < tickets[ticketNumber].ticketsAvailable) // проверка: остались ли билеты
    {
        tickets[ticketNumber].ticketsSold++; // продажа
        printf("Sold!\n");
    }
    else
    {
        printf("Unfortunately, the tickets ran out"); // вывод ошибки о том, что билеты закончились
    }
}
int main()
{
    printf("Enter login:\n"); // запрос логина
    char login[10];
    scanf("%s", login);
    printf("Enter password:\n"); // запрос пароля
    char password[10];
    scanf("%s", password);
    char *role; // переменная роли
    strcpy(&role, "");
    role = logIn(login, password); // попытка входа
    if (strcmp(&role, "") == 0) // проверка корректности входа по роли (при корректном входе роль будет отлична от пустой строки)
    {
        printf("Error. Account not found.");
        exit(0);
    }
    struct Ticket tickets[100]; // массив билетов
    int count; // переменная для количества билетов
    count = loadTickets(tickets); // загрузка билетов
    int act = 0; // переменная для меню
    while (1)
    {
        printf("0-EXIT, 1-BUY, 2-PRINT ALL TICKETS\n"); // запрос действия
        scanf("%d", &act);
        switch (act)
        {
            case 0: // выход
            {
                save(count, tickets);
                exit(0);
            }
            break;
            case 1: // покупка
            {
                buy(count, tickets);
            }
            break;
            case 2: // вывод всех билетов
            {
                for (int i = 0; i < count; i++)
                {
                    printf("%3d|", i);
                    printTicket(tickets[i]);
                }
            }
            break;
        }
    }
    return 0;
}