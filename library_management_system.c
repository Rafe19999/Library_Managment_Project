#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct books
{
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
} b;

struct student
{
    int id;
    char sName[50];
    char sClass[50];
    int sRoll;
    char bookName[50];
    char date[12];
} s;

FILE *fp;

int main()
{

    int ch;

    while(1)
    {
        system("cls");
        printf("<==== Library Management System ====>\n");
        printf("1.Add Book\n");
        printf("2.Available Books List\n");
        printf("3.Remove Book\n");
        printf("4.Register Book\n");
        printf("5.Registered Book List\n");
        printf("6.Delete registered Book List\n");
        printf("0.Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch(ch)
        {
        case 0:
            exit(0);

        case 1:
            addBook();
            break;

        case 2:
            booksList();
            break;

        case 3:
            del();
            break;

        case 4:
            issueBook();
            break;

        case 5:
            issueList();
            break;
        case 6:
            delList();
            break;

        default:
            printf("Invalid Choice...\n\n");

        }
        printf("Press Any Key To Continue...");
        getch();
    }

    return 0;
}


void addBook()
{
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(b.date, myDate);

    fp = fopen("books.txt", "ab");

    printf("Enter book id: ");
    scanf("%d", &b.id);

    printf("Enter book name: ");
    fflush(stdin);
    gets(b.bookName);

    printf("Enter author name: ");
    fflush(stdin);
    gets(b.authorName);

    printf("Book Added Successfully\n");

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}


void booksList()
{

    system("cls");
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date");

    fp = fopen("books.txt", "rb");
    while(fread(&b, sizeof(b), 1, fp) == 1)
    {
        printf("%-10d %-30s %-20s %s\n", b.id, b.bookName, b.authorName, b.date);
    }

    fclose(fp);
}

void del()
{
    int id, f=0;
    system("cls");
    printf("<== Remove Books ==>\n\n");
    printf("Enter Book id to remove: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("books.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while(fread(&b, sizeof(b), 1, fp) == 1)
    {
        if(id == b.id)
        {
            f=1;
        }
        else
        {
            fwrite(&b, sizeof(b), 1, ft);
        }
    }

    if(f==1)
    {
        printf("\n\nDeleted Successfully.");
    }
    else
    {
        printf("\n\nRecord Not Found !");
    }

    fclose(fp);
    fclose(ft);

    remove("books.txt");
    rename("temp.txt", "books.txt");

}


void issueBook()
{

    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(s.date, myDate);

    int f=0;

    system("cls");
    printf("<== Registered Books ==>\n\n");

    printf("Enter Book id to Register: ");
    scanf("%d", &s.id);


    fp = fopen("books.txt", "rb");

    while(fread(&b, sizeof(b), 1, fp) == 1)
    {
        if(b.id == s.id)
        {
            strcpy(s.bookName, b.bookName);
            f=1;
            break;
        }
    }

    if(f==0)
    {
        printf("No book found with this id\n");
        printf("Please try again...\n\n");
        return;
    }

    fp = fopen("issue.txt", "ab");

    printf("Enter Student Name: ");
    fflush(stdin);
    gets(s.sName);

    printf("Enter Student Class: ");
    fflush(stdin);
    gets(s.sClass);

    printf("Enter Student Roll: ");
    scanf("%d", &s.sRoll);

    printf("Book Registered Successfully\n\n");

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}

void issueList()
{
    system("cls");
    printf("<== Book registered List ==>\n\n");

    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n", "S.id", "Name", "Class", "Roll", "Book Name", "Date");

    fp = fopen("issue.txt", "rb");
    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        printf("%-10d %-30s %-20s %-10d %-30s %s\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName, s.date);
    }

    fclose(fp);
}


void delList()
{
    int roll, f=0;
    system("cls");
    printf("<== Remove student from issued List ==>\n\n");
    printf("Enter the roll of that student: ");
    scanf("%d", &roll);

    FILE *ftt;

    fp = fopen("issue.txt", "rb");
    ftt = fopen("tempt.txt", "wb");

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        if(roll == s.sRoll)
        {
            f=1;
        }
        else
        {
            fwrite(&s, sizeof(s), 1, ftt);
        }
    }



    fclose(fp);
    fclose(ftt);

    remove("issue.txt");
    rename("tempt.txt", "issue.txt");
    if(f==1)
    {
        printf("\n\nDeleted Successfully.");
    }
    else
    {
        printf("\n\nRecord Not Found !");
    }
}


