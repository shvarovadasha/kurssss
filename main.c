#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ticket
{
    int trainNumber;//Номер поезда
    char station[50];//Название конечного пункта
    char date[20];//Дата
    int H1, M1,//Время отбытия
        H2, M2;//Время прибытия
    int cost;//Стоимость билета в копейках
    int ticketsSold;//Кол-во проданных билетов
    int ticketsAvailable;//Кол-вобилетов всего
};
char * logIn(char login[], char password[])//Функция входа в аккаунт
{
    char* role;//Роль
    strcpy(&role, "");//Обнуление роли
    FILE *f1;//Файл для чтения аккаунтов
    if ((f1 = fopen("acc.txt", "r+")) == NULL)//Открытие файла
    {
        printf("Cannot open file.\n");
        exit(1);
    }
    while (!feof(f1))//Цикл для чтения до конца файла
    {
        char constr[80];//Временная переменная для чтения
        char *p = constr;//Временная переменная для чтения
        fgets(p, 80, f1);//Чтение строки
        if (p[strlen(p) - 1] == '\n')//Удаление символа перехода на новую строку
            p[strlen(p) - 1] = '\0';
        char *str[80];
        strcpy(str, constr);
        char *token = strtok(str, ";");//Разделение строки по символу ";"
        char *l[80];//Переменная для логина
        strcpy(l, token);//Чтение логина из файла
        token = strtok(NULL, ";");//Чтение в строке до следующего символа ";"
        char *pa[80];//Переменная для пароля
        strcpy(pa, token);//Чтение пароля из файла
        if (strcmp(login, l) == 0 && strcmp(password, pa) == 0)//Проверка логина и пароля
        {
            token = strtok(NULL, ";");
            strcpy(&role, token);
            printf("Role: %s\n", &role);//Вывод роли на экран
        }
    }
    fclose(f1);//Закрытие файла
    return role;//Возврат роли
}
int loadTickets(struct Ticket *t)//Чтение билетов из файла
{
    FILE *f1;//Файл
    if ((f1 = fopen("tickets.txt", "r+")) == NULL)//Открытие файла
    {
        printf("Cannot open file.\n");
        exit(1);
    }
    int i = 0;//Перемнная для подсчёта количества билетов
    while (!feof(f1))//Цикл чтения до конца файла
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
    fclose(f1);//Закрытие файла
    return i;//Возвращаем кол-во билетов
}
int printTicket(struct Ticket t)//Вывод билетов на экран
{
    printf("Train number: %d, ", t.trainNumber);
    printf("station: %s, ", t.station);
    printf("time: %s, %d:%d, time2: %d:%d\n", t.date, t.H1, t.M1, t.H2, t.M2);
    printf("Cost: %.2f BYN, ", t.cost/100.0);
    printf("sold: %d/%d\n", t.ticketsSold, t.ticketsAvailable);
    return 0;
}
int save(int count, struct Ticket t[])//Сохранение билетов в файл
{
    FILE *f2;//Переменая файла
    f2 = fopen("tickets.txt", "w+");//Открытие файла
    for (int i = 0; i < count; i++)//Цикл на все билеты
    {
        char buf[80];//Временная переменная
        sprintf(buf, "%d;%s;%s;%d;%d;%d;%d;%d;%d;%d", t[i].trainNumber, t[i].station, t[i].date,
                t[i].H1, t[i].M1, t[i].H2, t[i].M2,
                t[i].cost, t[i].ticketsSold, t[i].ticketsAvailable);//Формирование строки с данными о билете в переменную buf
        fputs(buf, f2);//Сохренение строки buf в файл
        if (i + 1 < count)//Добаление перехода на новую строку
            fputs("\n", f2);
    }
    fclose(f2);//Закрытие файла
}
int bye(int count, struct Ticket tickets[])//Покупка билета
{
    printf("What city do you want to go to?\n");//Ввод необходимого конечного пункта
    char city[50];
    scanf("%s", &city);
    printf("From what hour ticket do you need?\n");//Ввод с какого часа необходим билет
    int hour1;
    scanf("%d", &hour1);
    printf("Before what hour ticket do you need?\n");//Ввод до какого часа необходим билет
    int hour2;
    scanf("%d", &hour2);
    for (int i = 0; i < count; i++)//Цикл на все билеты
    {
        if (strcmp(tickets[i].station, city) == 0 &&
            tickets[i].H1 >= hour1 &&
            tickets[i].H2 < hour2)//Проверка билета
        {
            printf("%3d|", i);//Вывод подходящего билета
            printTicket(tickets[i]);
        }
    }
    printf("Which ticket do you want to bye?\n");//Запрос на покупку билета
    int ticketNumber;
    scanf("%d", &ticketNumber);
    if (ticketNumber < 0 || ticketNumber >= count)//Проверка корректности введённого номера
    {
        printf("Error");//Вывод ошибки
        exit(1);
    }
    if (tickets[ticketNumber].ticketsSold < tickets[ticketNumber].ticketsAvailable)//Проверка: остались ли билеты
    {
        tickets[ticketNumber].ticketsSold++;//Продажа
        printf("Sold!");
    }
    else
    {
        printf("Unfortunately, tickets ran out");//Вывод ошибки о том, что билеты закончились
    }
}
int main()
{
    printf("Vvedite login:\n");//Запрос логина
    char login[10];
    scanf("%s", login);
    printf("Vvedite parol:\n");//Запрос пароля
    char password[10];
    scanf("%s", password);
    char *role;//Переменная роли
    strcpy(&role, "");
    role = logIn(login, password);//Попытка входа
    if (strcmp(&role, "") == 0)//Проверка корректности входа по роли (при корректном входе роль будет отлична от псутой строки)
    {
        printf("Error. Account not found.");
        exit(0);
    }
    struct Ticket tickets[100];//Массив билетов
    int count;//Переменная количества билетов
    count = loadTickets(tickets);//Загрузка билетов
    int act = 0;//Переменная для меню
    while (1)
    {
        printf("0-exit, 1-buy, 2-print all tickets\n");//Запрос действия
        scanf("%d", &act);
        switch (act)
        {
            case 0://Выход
            {
                save(count, tickets);
                exit(0);
            }
            break;
            case 1://Покупка
            {
                bye(count, tickets);
            }
            break;
            case 2://Вывод всех билетов
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
