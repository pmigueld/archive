#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>

#define T_RETURN      	 'r'
#define T_BORROW      	 'b'
#define T_QUIT      	 'q'
#define MAX      		 10
#define loop      		 while(1)
#define MAX_ALLOTED_TIME 604800

typedef unsigned short bool;

typedef struct Transaction {
    char borrower[64];
    char date_borrowed[64];
    char date_returned[64];
} Transaction;

typedef struct Book {
    char          title[64];   // book title
    char          author[64];  // book author
    bool          status;      // available or borrowed?
    Transaction   transaction; // record of latest transaction
} Book;

void _borrow(Book *b, char *name);
void _return(Book *b, char *name);

int main(void) {
    FILE *db;
    char choice;
    char name[64];

    db = fopen("db.dat", "r+b");

    Book *books = (Book *)malloc(sizeof(Book) * MAX);
    fread(books, sizeof(Book), MAX, db);
    
    printf("\nPlease enter your name: ");
    scanf("%[^\n]", name); getchar();
    printf("\nWelcome, %s!\n\n", name);

    loop {
        system("cls");
        printf("    %-25s %-10s %-15s %-15s\n", 
               "Title/Author", "Status", "Date Borrowed", "Date Returned");

        for(int i = 0; i < MAX; i++) {
            Book book = books[i];

            printf("%2d) %-25s %-10s %-15s %-15s\n    by %-22s\n\n", i + 1, book.title,
                book.status == 0 ? "AVAILABLE" : "BORROWED",
                book.transaction.date_borrowed,
                book.transaction.date_returned,
                book.author);
        }

select:
        printf("\nWhat would you like to do:\n(R)eturn a book\n(B)orrow a book\n(Q)uit\n\n> ");
        choice = tolower(getchar());
        switch(choice) {
            case T_BORROW: _borrow(books, name); break;
            case T_RETURN: _return(books, name); break;
            case T_QUIT:
                goto quit;
            default:
                goto select;
        }

        rewind(db);
        fwrite(books, sizeof(Book), MAX, db);
    }

quit:
    fclose(db);
    free(books);
    return 0;
}


void _borrow(Book *b, char *name) {
    int index;
    time_t now;
    struct tm *date;
a:
    printf("Which book would you like to borrow? ");
    scanf("%d", &index); getchar();
    if(index > MAX) {
        printf("That book does not exist.\n");
        getch();
        goto a;
    }

    index--;
    // Get local time
    now = time(NULL);
    date = localtime(&now);
    
    if(b[index].status == 0) {
        printf("You are allowed 1 week to keep the book, %s. (penalty is 20php/day)\n", 
               b[index].title);
        b[index].status = 1;
        // Save the borrower's name in the 'database'
        strcpy(b[index].transaction.borrower, name);
        // Clear the date it was last returned
        strcpy(b[index].transaction.date_returned, "");
        // Save the date it was borrowed as a string in the format: MM/DD/YYYY
        strftime(b[index].transaction.date_borrowed, 
                 sizeof(b[index].transaction.date_borrowed), 
                 "%m/%d/%Y", date);
    } else {
        printf("Sorry, that book has already been borrowed by, %s.\n", 
               b[index].transaction.borrower);
    }
    getch();
}

void _return(Book *b, char *name) {
    int index;
    time_t date_returned;
    time_t date_borrowed;
    struct tm *date;
    int penalty;
b:
    printf("Which book are you returning? ");
    scanf("%d", &index); getchar();
    if(index > MAX) {
        printf("Such a book does not exist.\n");
        goto b;
    }

    index--;
    // Get local time
    date_returned = time(NULL);
    date = localtime(&date_returned);

    if(strcmp(b[index].transaction.borrower, name) == 0) {
        b[index].status = 0;
        // Clear the name of the borrower
        strcpy(b[index].transaction.borrower, "");
        // Save the date it was returned as a string in the format: MM/DD/YYYY
        strftime(b[index].transaction.date_returned, 
                 sizeof(b[index].transaction.date_returned), 
                 "%m/%d/%Y", date);
        // Get the internal representation of a date string (string -> time structure)
        sscanf(b[index].transaction.date_borrowed, "%d/%d/%d", 
               &date->tm_mon, &date->tm_mday, &date->tm_year);
        date->tm_mon--; date->tm_isdst = -1;
        date_borrowed = mktime(date);
        // Calculate penalty (date passed since it was borrowed minus the 7 day alloted time)
        // difftime() returns the time difference in seconds so we convert it to days
		
        penalty = (difftime(date_returned, date_borrowed) - MAX_ALLOTED_TIME) / (24 * 60 * 60);
        if(penalty > 0) {
            printf("This book was due %d day(s) ago. Please pay %dphp to the librarian "
                   "upon retrieving your library card.\n", penalty, penalty * 20);
        } else {
            printf("Thank you for returning the book within the given time.\n");
        }
        // Clear the date it was borrowed
        strcpy(b[index].transaction.date_borrowed, "");
    } else if(b[index].status == 0) {
        printf("This book has not been borrowed.\n");
    } else {
        printf("You are not the one who borrowed this book.\nPlease have the person "
               "who borrowed this book return it himself.\n");
    }
    getch();
}
