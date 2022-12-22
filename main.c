#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ticket
{
    int trainNumber;//����� ������
    char station[50];//�������� ��������� ������
    char date[20];//����
    int H1, M1,//����� �������
        H2, M2;//����� ��������
    int cost;//��������� ������ � ��������
    int ticketsSold;//���-�� ��������� �������
    int ticketsAvailable;//���-��������� �����
};
char * logIn(char login[], char password[])//������� ����� � �������
{
    char* role;//����
    strcpy(&role, "");//��������� ����
    FILE *f1;//���� ��� ������ ���������
    if ((f1 = fopen("acc.txt", "r+")) == NULL)//�������� �����
    {
        printf("Cannot open file.\n");
        exit(1);
    }
    while (!feof(f1))//���� ��� ������ �� ����� �����
    {
        char constr[80];//��������� ���������� ��� ������
        char *p = constr;//��������� ���������� ��� ������
        fgets(p, 80, f1);//������ ������
        if (p[strlen(p) - 1] == '\n')//�������� ������� �������� �� ����� ������
            p[strlen(p) - 1] = '\0';
        char *str[80];
        strcpy(str, constr);
        char *token = strtok(str, ";");//���������� ������ �� ������� ";"
        char *l[80];//���������� ��� ������
        strcpy(l, token);//������ ������ �� �����
        token = strtok(NULL, ";");//������ � ������ �� ���������� ������� ";"
        char *pa[80];//���������� ��� ������
        strcpy(pa, token);//������ ������ �� �����
        if (strcmp(login, l) == 0 && strcmp(password, pa) == 0)//�������� ������ � ������
        {
            token = strtok(NULL, ";");
            strcpy(&role, token);
            printf("Role: %s\n", &role);//����� ���� �� �����
        }
    }
    fclose(f1);//�������� �����
    return role;//������� ����
}
int loadTickets(struct Ticket *t)//������ ������� �� �����
{
    FILE *f1;//����
    if ((f1 = fopen("tickets.txt", "r+")) == NULL)//�������� �����
    {
        printf("Cannot open file.\n");
        exit(1);
    }
    int i = 0;//��������� ��� �������� ���������� �������
    while (!feof(f1))//���� ������ �� ����� �����
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
    fclose(f1);//�������� �����
    return i;//���������� ���-�� �������
}
int printTicket(struct Ticket t)//����� ������� �� �����
{
    printf("Train number: %d, ", t.trainNumber);
    printf("station: %s, ", t.station);
    printf("time: %s, %d:%d, time2: %d:%d\n", t.date, t.H1, t.M1, t.H2, t.M2);
    printf("Cost: %.2f BYN, ", t.cost/100.0);
    printf("sold: %d/%d\n", t.ticketsSold, t.ticketsAvailable);
    return 0;
}
int save(int count, struct Ticket t[])//���������� ������� � ����
{
    FILE *f2;//��������� �����
    f2 = fopen("tickets.txt", "w+");//�������� �����
    for (int i = 0; i < count; i++)//���� �� ��� ������
    {
        char buf[80];//��������� ����������
        sprintf(buf, "%d;%s;%s;%d;%d;%d;%d;%d;%d;%d", t[i].trainNumber, t[i].station, t[i].date,
                t[i].H1, t[i].M1, t[i].H2, t[i].M2,
                t[i].cost, t[i].ticketsSold, t[i].ticketsAvailable);//������������ ������ � ������� � ������ � ���������� buf
        fputs(buf, f2);//���������� ������ buf � ����
        if (i + 1 < count)//��������� �������� �� ����� ������
            fputs("\n", f2);
    }
    fclose(f2);//�������� �����
}
int bye(int count, struct Ticket tickets[])//������� ������
{
    printf("What city do you want to go to?\n");//���� ������������ ��������� ������
    char city[50];
    scanf("%s", &city);
    printf("From what hour ticket do you need?\n");//���� � ������ ���� ��������� �����
    int hour1;
    scanf("%d", &hour1);
    printf("Before what hour ticket do you need?\n");//���� �� ������ ���� ��������� �����
    int hour2;
    scanf("%d", &hour2);
    for (int i = 0; i < count; i++)//���� �� ��� ������
    {
        if (strcmp(tickets[i].station, city) == 0 &&
            tickets[i].H1 >= hour1 &&
            tickets[i].H2 < hour2)//�������� ������
        {
            printf("%3d|", i);//����� ����������� ������
            printTicket(tickets[i]);
        }
    }
    printf("Which ticket do you want to bye?\n");//������ �� ������� ������
    int ticketNumber;
    scanf("%d", &ticketNumber);
    if (ticketNumber < 0 || ticketNumber >= count)//�������� ������������ ��������� ������
    {
        printf("Error");//����� ������
        exit(1);
    }
    if (tickets[ticketNumber].ticketsSold < tickets[ticketNumber].ticketsAvailable)//��������: �������� �� ������
    {
        tickets[ticketNumber].ticketsSold++;//�������
        printf("Sold!");
    }
    else
    {
        printf("Unfortunately, tickets ran out");//����� ������ � ���, ��� ������ �����������
    }
}
int main()
{
    printf("Vvedite login:\n");//������ ������
    char login[10];
    scanf("%s", login);
    printf("Vvedite parol:\n");//������ ������
    char password[10];
    scanf("%s", password);
    char *role;//���������� ����
    strcpy(&role, "");
    role = logIn(login, password);//������� �����
    if (strcmp(&role, "") == 0)//�������� ������������ ����� �� ���� (��� ���������� ����� ���� ����� ������� �� ������ ������)
    {
        printf("Error. Account not found.");
        exit(0);
    }
    struct Ticket tickets[100];//������ �������
    int count;//���������� ���������� �������
    count = loadTickets(tickets);//�������� �������
    int act = 0;//���������� ��� ����
    while (1)
    {
        printf("0-exit, 1-buy, 2-print all tickets\n");//������ ��������
        scanf("%d", &act);
        switch (act)
        {
            case 0://�����
            {
                save(count, tickets);
                exit(0);
            }
            break;
            case 1://�������
            {
                bye(count, tickets);
            }
            break;
            case 2://����� ���� �������
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
