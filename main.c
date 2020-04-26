#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER ('\r')
#define MAXITEM 9

struct data_t {
char name [30] ;
char phone[15] ;
char email [30] ;
char birthdate [15] ;
char job [20] ;

};

typedef struct node_t
{
    struct data_t data ;
    struct node_t *next ;
}node ; //each node represents an employee

//functions declarations
void print_emp (node* temp); //this function prints only one employee
void print_emps (void);
void add_from_buffer (char* buffer);//Extract the data of an employeee from a string
void load_file (void) ; //pass the name of the file with its extension
void add (void) ; //this function adds and employee and take the input from the user of the program.
void del (void) ; //this function deletes an employee by providing its name
void search_emp (void) ; // searches for an employee by name.
void modify (void);
void save_file (void) ;
void sort_data (void) ;

void main_menu (void) ;

node* emps = NULL ; //pointer to the employees

int main()
{
    main_menu () ;
    return 0;
}

void main_menu (void)
{   //set fonts and clear the screen
    system("COLOR F5");
    char i ,print_flag =1 ,y = 0,ch =0   ;
    char line[MAXITEM][20] = {"ADD" , "LOAD" , "DELETE" ,"SAVE" , "SEARCH" , "MODIFY" , "SORT", "PRINT_DATA","QUIT" };

    void (* func_ptr[MAXITEM-1])(void) = { add , load_file , del , save_file ,search_emp ,modify , sort_data , print_emps} ;

    while(1)
    {
        if (print_flag == 1 ) //print screen
        {
            system("cls") ;
            printf("\n\n\n");
            for (i = 0 ; i < MAXITEM ; i ++)
            {   printf("\t\t\t");
                if (i == y) printf("-- ");

                printf("%s\n\n" ,line[i]);
            }
            print_flag = 0 ;
        }
        if (kbhit() !=0) ch = getch() ;
        switch (ch)
        {
            case KEY_UP:    if(y==0) y = MAXITEM-1 ;
                            else  y--;
                            print_flag = 1;
                            break;

            case KEY_DOWN:  if(y == (MAXITEM-1) )y=0;
                            else y++ ;
                            print_flag = 1;
                            break;
            case ENTER:     if (y == MAXITEM-1) return ;
                            else
                            {
                                func_ptr[y]() ;
                                ch = 0;
                                printf("\n\n\nPress ESC to return to the main menu\n") ;
                                while(ch != 27)
                                {
                                     ch = getch() ;

                                }
                                y = 0 ; print_flag =1 ;
                            }
                            system("COLOR F6");

                            break; // enter key

        }
        ch = 0 ;
    }
}

void add (void)
{   system("cls") ;
    system("COLOR F2");
    node *link = malloc(sizeof(node)) ;
    printf("Entering the data of a new employee\n");
    printf("Enter the name\n");
    gets(link->data.name) ;

    printf("Enter the Phone no.\n");
    gets(link->data.phone) ;

    printf("Enter the Email\n");
    gets(link->data.email) ;

    printf("Enter the Bith Date\n");
    gets(link->data.birthdate) ;

    printf("Enter the JOb Title\n");
    gets(link->data.job) ;

    //adding the node at first(temporary till implementing sorting functions)
    link->next = emps ;
    emps = link ;


}
void print_emp (node* temp)
{
    printf("Name:%s\nPhone:%s\nEmail:%s",temp->data.name,temp->data.phone,temp->data.email) ;
  //  printf("\nBirth Date:%s\nJob:%s\n",temp->data.birthdate,temp->data.job) ;
}

void print_emps (void)
{
    system("cls") ;
    system("COLOR F2");
     node* temp = emps;

  unsigned char count = 1 ;

    while (temp != NULL)
    {
    printf("\nData of employee:%d", count);
    printf("\nName:%s\nPhone:%s\nEmail:%s",temp->data.name,temp->data.phone,temp->data.email) ;
 //   printf("\nBirth Date:%s\nJob:%s\n",temp->data.birthdate,temp->data.job) ;
    temp = temp->next ;
    count ++ ;
    }

}


void del ()
{
    system("cls") ;
    char name_to_delete[30] ;
    node *temp ,*prev ;
    temp =prev = emps  ;
    char ch = 0 ;
    puts("Enter name of the employee to be deleted\n") ;
    gets(name_to_delete) ;

    while(temp != NULL)
    {
    if (strcmp(name_to_delete , temp->data.name) == 0)
    {
        printf("Are you sure to delete employee:\n");
        print_emp(temp ) ;
        printf("\nType y to confirm\n");
        scanf(" %c" , &ch) ;
        if(ch == 'y')
        {//deleting procedure
            if (prev == temp)//only one node and to be deleted
            {   emps = NULL ;
                free(temp) ;
            }
            else
            {
            prev->next = temp->next;
            free(temp);
            }
            return ;
        }else return ;
    }
    prev = temp ;
    temp=temp->next ;
    }
    printf("Employee is not found\n");
}

void search_emp (void)
{   system("COLOR F2");
    system("cls") ;
    char name_to_search[30] ;
    node *temp ;
    temp = emps ;
    puts("\nEnter name of the employee to be searched of\n") ;
    gets(name_to_search);

    while(temp != NULL)
    {
        if (strcmp(name_to_search , temp->data.name) == 0)
        {
            printf("Employee is found\n");
            print_emp(temp) ;
            return;
        }
        temp=temp->next ;
    }
    printf("Employee is not found\n");
}

void load_file (void)
{   system("cls") ;
    system("COLOR F2");
    char file_name [30] ;
    puts ("Enter the file name between two double quotes""") ;
    gets (file_name) ;
    char buffer[100] ;
    //char file_name[100] = "test.txt" ;
    char ch ;
    unsigned char i = 0 ;
    FILE *fp = NULL ;
    fp = fopen(file_name , "r") ;
    if (fp==NULL) printf("file is not opened\n") ;
    else
    {
        //printf("file is opened\n") ;
        ch = fgetc(fp);
        while(ch!=EOF)
         {
            i= 0;
            while((ch!=EOF) && (ch!=34)) ch = fgetc(fp); //loop till get to the first "(34) in ascii
            if(ch == EOF) break ;
            buffer[i] = ch ; //saving the first (")
            i++ ;
            ch = fgetc(fp);
            while((ch!=EOF) && (ch!=34)) //loop till get to the second "(34) in ascii
            {
                buffer[i] = ch ;
                i++ ;
                ch = fgetc(fp);
            }
            buffer[i] = ch; //saving the second (")
            i++ ;
            buffer[i] = 0; //adding NULL terminator of Buffer string
            ch = fgetc(fp);//getting the character immediately after the second (")
            add_from_buffer(buffer) ;
        }
    }
    fclose(fp);
}


void add_from_buffer (char* buffer)
{   node *link = malloc(sizeof(node)) ;
    char *ptrs[5] = { link->data.name ,link->data.phone , link->data.email ,link->data.birthdate  ,link->data.job  } ;
    char i , j ;

    buffer++;//skip the first "
    for (j=0 ; j<5 ; j++)
    {
    i=0 ;
    while ((*buffer != 44) && (*buffer != 34)) //34 is (") and 44 is (,)
    {
        *(*(ptrs+j)+i)= *buffer; // e.g. link->data.name[i] = *buffer;
        buffer++;
        i++ ;
    }
    *(*(ptrs+j)+i)  = 0 ;
    buffer ++ ; //skip the comma
    }
    link->next = emps ;
    emps = link ;
}


void modify (void)
{

system("cls") ;
system("COLOR F2");
char name_to_modify[30] ;
int field ;
node *temp ;
char *ptrs[5] ;
char buffer [30] ;
temp = emps ;
puts("\nEnter name of the employee to be modified\n") ;
gets(name_to_modify);

while(temp != NULL)
{
    if (strcmp(name_to_modify , temp->data.name) == 0)
    {
        printf("Employee is found\n");
        print_emp(temp) ;
        ptrs[0] = temp->data.name ;
        ptrs[1] = temp->data.phone ;
        ptrs[2] = temp->data.email ;
        ptrs[3] = temp->data.birthdate ;
        ptrs[4] = temp->data.job ;
        printf("\nwhich field to be modifed\nname:0\tphone:1\temail:2\tbirthdate:3\tJob title:4\n");
        scanf(" %d" ,&field);
        printf("Enter the new ");
        switch(field)
        {
            case  0 : printf("name\n") ; break ;
            case  1 : printf("phone no.\n") ; break ;
            case  2 : printf("email\n") ; break ;
            case  3 : printf("birthdate\n") ; break ;
            case  4 : printf("job title\n") ; break ;
        }
        scanf("\n");
        gets(buffer) ;
        strcpy (ptrs[field] , buffer) ;

        return;
    }
    temp=temp->next ;
}
printf("Employee is not found\n");
}

void save_file (void)
{

    system("cls") ;
    system("COLOR F2");
    return ;
}
void sort_data (void)
{
    system("cls") ;
    system("COLOR F2");
    return ;
}

