#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BANK_NAME "INDIAN BANK"

struct Register
{
    char using_name[50];
    char dob[15];
    char gender[10];
    char account_number[20];
    char mail_id[50];
    long long phone_number;
    char user_name[25];
    char password[20];
};

int count_chars(char *str)
{
    int i = 0;
    while (str[i] != '\0') i++;
    return i;
}

int validate_name(char *name)
{
    return (count_chars(name) > 0);
}

int validate_dob(char *dob)
{
    if (count_chars(dob) != 8) return 0;
    for (int i = 0; i < 8; i++)
        if (dob[i] < '0' || dob[i] > '9') return 0;
    return 1;
}

int validate_gender(char *g)
{
    return (!strcmp(g, "male") || !strcmp(g, "female"));
}

int validate_account(char *acc)
{
    if (count_chars(acc) != 11) return 0;
    for (int i = 0; i < 11; i++)
        if (acc[i] < '0' || acc[i] > '9') return 0;
    return 1;
}

int validate_mail(char *mail)
{
    int at = -1, dot = -1, len = count_chars(mail);
    for (int i = 0; i < len; i++)
    {
        if (mail[i] == '@') at = i;
        if (mail[i] == '.') dot = i;
    }
    return (at > 0 && dot > at + 1 && dot < len - 1);
}

int validate_phone(long long phone)
{
    int digits = 0;
    while (phone > 0) { phone /= 10; digits++; }
    return digits == 10;
}

int validate_password(char *pass)
{
    return count_chars(pass) == 6;
}

int is_user_registered(char *account, long long phone)
{
    FILE *fp = fopen("database.txt", "r");
    if (!fp) return 0;

    char name[50], dob[15], gender[10], acc[20];
    char mail[50], user[30], pass[20];
    long long ph;

    while (fscanf(fp, "%s %s %s %s %s %lld %s %s",name, dob, gender, acc, mail, &ph, user, pass) != EOF)
    {
        if (!strcmp(account, acc) || phone == ph)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void save_data(struct Register *p)
{
    FILE *fp = fopen("database.txt", "a");
    fprintf(fp, "%s %s %s %s %s %lld %s %s\n",
            p->using_name, p->dob, p->gender, p->account_number,
            p->mail_id, p->phone_number, p->user_name, p->password);

    fclose(fp);
}
void MemberInformation()
{
    FILE *fp = fopen("database.txt", "r");
    char line[200];

    if (fp == NULL)
    {
        printf("Error: No saved records found.\n");
        return;
    }

    printf("Saved User Information\n");

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }

    fclose(fp);
}

int login()
{
int amount,balance;
    char mail[50], pass[20];

    printf("\nEnter Mail ID: ");
    scanf("%49s", mail);

    printf("Enter Password: ");
    scanf("%19s", pass);

    FILE *fp = fopen("database.txt", "r");
    if (!fp) return 0;

    char name[50], dob[15], gender[10], acc[20];
    char file_mail[50], user[30], file_pass[20];
    long long ph;

    while (fscanf(fp, "%s %s %s %s %s %lld %s %s",name, dob, gender, acc, file_mail, &ph, user, file_pass) != EOF)
    {
        if (!strcmp(mail, file_mail) && !strcmp(pass, file_pass))
        {
            fclose(fp);
            printf("\nLogin Successful! Welcome %s\n", user);

            int choice;
            while (1)
            {
                printf("\n1. View Information \n2.withdraw amount: \n3.deposite amount \n4. Logout\nEnter choice:");
                scanf("%d", &choice);

                if (choice == 1)
                    MemberInformation();
                else if(choice == 2)
                {
                   printf("enter the Amount : ");
				   scanf("%d",&amount);
			       printf("collect the Amount : ");
			       balance=1000 - amount;
			       printf("%d",balance);
                   balance == 1000;
                   printf("%d",balance);
                }
                else if(choice == 3)
                {
                    printf("enter the Amount : ");
				    scanf("%d",&amount);
				    printf("deposited  the Amount : ");
				    balance = 1000 + amount;
                    printf("%d",balance);
                }
                else if (choice == 4)
                    return 1;
                else
                    printf("Invalid Option\n");
            }
        }
    }

    fclose(fp);
    printf("\nInvalid Mail or Password!\n");
    return 0;
}

void registration()
{
    struct Register reg;
    printf("\nRegistration\n");

    do {
        printf("Using Name: ");
        scanf("%49s", reg.using_name);
    } while (!validate_name(reg.using_name));

    do {
        printf("DOB (DDMMYYYY): ");
        scanf("%8s", reg.dob);
    } while (!validate_dob(reg.dob));

    do {
        printf("Gender (male/female): ");
        scanf("%9s", reg.gender);
    } while (!validate_gender(reg.gender));

    do {
        printf("Account Number: ");
        scanf("%19s", reg.account_number);
    } while (!validate_account(reg.account_number));

    do {
        printf("Mail ID: ");
        scanf("%49s", reg.mail_id);
    } while (!validate_mail(reg.mail_id));

    do {
        printf("Phone Number: ");
        scanf("%lld", &reg.phone_number);
    } while (!validate_phone(reg.phone_number));

    if (is_user_registered(reg.account_number, reg.phone_number))
    {
        printf("\nData already registered!\n");
        return;
    }


    do {
        printf("User Name: ");
        scanf("%24s", reg.user_name);
    } while (count_chars(reg.user_name) == 0);

    do {
        printf("Password (6 characters): ");
        scanf("%6s", reg.password);
    } while (!validate_password(reg.password));

    save_data(&reg);

    printf("\nRegistration Successful!\n");
}

int main()
{
    int choice;

    printf("Selected Bank: %s\n", BANK_NAME);

    while (1)
    {
        printf("\n1. Login\n2. Register\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice)
        {
         if(choice == 1 )
            {
            login();
           }
         else if(choice == 2)
            {
                registration();
            }

         else if(choice == 3)
            {
            printf("\nThank you!\n");
            exit(0);
          }
    else
            {
            printf("Invalid Option!\n");
           }
        }

    }
}
