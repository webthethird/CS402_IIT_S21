#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readfile.h"

/* Define constants */
#define MAX_NAME 64
#define MIN_ID 100000
#define MAX_ID 999999
#define MIN_SALARY 30000
#define MAX_SALARY 150000
#define N 1024

/* Define Employee data structure */
struct Employee
{
    int id;
    char firstName[MAX_NAME];
    char lastName[MAX_NAME];
    int salary;
};
/* Declare methods defined later in this file */
int emp_comparator(const void*, const void*);
void sort_employees(int, struct Employee*);
void print_employees(struct Employee*);
void load_employees(struct Employee*);
int add_new_employee(struct Employee*);
void main_menu(struct Employee*);
void print_menu(void);
void search_by_id(struct Employee*);
int input_id(void);
void search_by_name(struct Employee*);
int input_last_name(char*);
int input_first_name(char*);
int input_salary(void);
int input_menu_selection(void);

/*
 * Main:
 * Attempts to open the file using the filename
 * passed in as an argument, by calling the open_file
 * method in readfile.c
 *
 * If successful, the method allocates space in memory
 * for an array of up tp 1024 Employee structs, then
 * passes the pointer for this array to load_employees
 * and main_menu.
 *
 * argc - unused
 * argv - holds the filename input by the user at launch
 * returns -1 on error opening file, 0 otherwise
 */
int main(int argc, const char *argv[])
{
    if (open_file(argv[1]) == -1)
    {
        printf("%s", "Error opening file\n");
        return -1;
    }

    struct Employee *emps = malloc(N * sizeof(struct Employee));
    load_employees(emps);
    main_menu(emps);
    return 0;
}

/*
 * Main Menu:
 * Handles routing main menu selections to the appropriate
 * subroutine, then returning to the menu.
 *
 * emps - pointer to the array of Employee structs, in order
 *          to pass along to the next subroutine
 */
void main_menu(struct Employee *emps)
{
    print_menu();
    switch(input_menu_selection()) {
        case 1:
            print_employees(emps);
            break;
        case 2:
            search_by_id(emps);
            break;
        case 3:
            search_by_name(emps);
            break;
        case 4:
            add_new_employee(emps);
            break;
        case 5:
            return;
    }
    main_menu(emps);
}

/*
 * Input Menu Selection:
 * Called by main_menu() after the menu is displayed.
 * Prompts the user to enter a selection from the menu,
 * and validates the input, first to make sure that it is
 * an integer, then to check that it is between 1 and 5.
 * Prompts the user to try again if either check fails.
 *
 * returns an integer between 1 and 5
 */
int input_menu_selection()
{
    int selection;
    char ch;
    printf("%s", "Please enter your selection: ");
    while (scanf("%d", &selection) != 1)
    {
        while ((ch = getchar()) != '\n')
            putchar(ch);
        printf("%s\n", " is not an integer, please try again.");
        return input_menu_selection();
    }
    if (selection < 1 || selection > 5)
    {
        printf("%s\n", "Selection must be between 1 and 5, please try again.");
        return input_menu_selection();
    }
    else return selection;
}

/*
 * Print Menu:
 * Prints the main menu, and does nothing else.
 */
void print_menu()
{
    printf("\n%s\n", "Employee DB Main Menu");
    printf("%s\n", "------------------------------");
    printf("%s\n", "  (1) Print Database");
    printf("%s\n", "  (2) Lookup by ID");
    printf("%s\n", "  (3) Lookup by Last Name");
    printf("%s\n", "  (4) Add New Employee");
    printf("%s\n", "  (5) Quit");
    printf("%s\n", "------------------------------");
}

/*
 * Load Employees:
 * Uses the methods read_int() and read_string() from
 * the library readfile.c to read data from the input
 * file and populate emps array with Employee structs.
 *
 * After loading the employee data, passes the array
 * of Employee structs, along with the count i, to the
 * sort_employees() method.
 *
 * emps - pointer to the empty array of Employee structs
 *          to populate with initial data and pass to sort
 */
void load_employees(struct Employee *emps)
{
    int i = 0;
    int ret;
    do
    {
        struct Employee newEmp;

        ret = read_int(&newEmp.id);
        if (ret == -1) break;
        ret = read_string(newEmp.firstName);
        ret = read_string(newEmp.lastName);
        ret = read_int(&newEmp.salary);
        emps[i] = newEmp;
        i++;
    }
    while (ret != -1);
    sort_employees(i, emps);
}

/*
 * Print Employees:
 * Called by main_menu() when the user selects option 1.
 * Iterates over the array of Employee structs and prints
 * each employee's name, salary and 6-digit ID number in
 * tabular format, plus the total number of employees.
 *
 * emps - pointer to the array of Employee structs to print
 */
void print_employees(struct Employee *emps)
{
    int i;

    printf("\n%-32s %7s          %6s\n", "NAME", "SALARY", "ID");
    printf("%s\n", "-----------------------------------------------------------");

    for (i = 0; emps[i].id != 0; i++) /* Stops when it reaches an uninitialized Employee */
    {
        printf("%-12s%-20s $%6d          %6d\n", emps[i].firstName, emps[i].lastName, emps[i].salary, emps[i].id);
    }

    printf("%s\n", "-----------------------------------------------------------");
    printf(" %s%d%s\n", "Number of Employees (", i, ")");
}

/*
 * Add New Employee:
 * Adds a new employee to the array of Employee structs.
 * Calls the functions input_salary(), input_first_name()
 * and input_last_name() to store the user's input for
 * the respective fields, then prompts the user to confirm
 * the employee's information before adding to the database.
 *
 * Upon confirmation, creates a new Employee struct, copies
 * the first name, last name and salary into the appropriate
 * memory locations. It then iterates over the current list
 * of employees, setting the new Employee's ID equal to the
 * last Employee's ID plus 1 before adding it to the array.
 *
 * emps - pointer to the array of Employee structs
 * returns -1 on failure, 0 otherwise
 */
int add_new_employee(struct Employee *emps)
{
    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    int salary, id;

    input_first_name(first_name);
    input_last_name(last_name);
    salary = input_salary();
    printf("\n%s\n", "Please confirm the following information:");
    printf(" Name: %s, %s\n Salary: $%d\nAdd this employee to the database?\nEnter 1 for Yes, 0 for No: ",
           last_name, first_name, salary);
    int selection;
    if (scanf("%d", &selection) && selection == 1)
    {
        struct Employee new_emp;
        strcpy(new_emp.firstName, first_name);
        strcpy(new_emp.lastName, last_name);
        new_emp.salary = salary;
        int i;
        for (i = 0; emps[i].id != 0; i++)
        {
            id = emps[i].id + 1;
        }
        new_emp.id = id;
        emps[i] = new_emp;
        return 0;
    }
    else return -1;
}

/*
 * Search by ID:
 * Calls input_id() to retrieve an employee ID to search for.
 * Performs a linear search of the array of Employee structs,
 * already sorted by ID, and prints the employee's info if a
 * match is found, or else informs the user that an employee
 * with the ID provided could not be found. Stops if it
 * encounters an ID that is greater than the search target.
 *
 * emps - pointer to the array of Employee structs to search
 */
void search_by_id(struct Employee *emps)
{
    int id = input_id();
    int i = 0;

    while (emps[i].id != 0)
    {
        if (emps[i].id == id)
        {
            printf("\n%-32s %7s          %6s\n", "NAME", "SALARY", "ID");
            printf("%s\n", "-----------------------------------------------------------");
            printf("%-12s%-20s $%6d          %6d\n", emps[i].firstName, emps[i].lastName, emps[i].salary, emps[i].id);
            printf("%s\n", "-----------------------------------------------------------");
            break;
        }
        else if (emps[i].id > id)
        {
            printf("%s%d%s\n", "Could not find employee with ID ", id, " in the database.");
            break;
        }
        else i++;
    }
    if (emps[i].id != id)
        printf("%s%d%s\n", "Could not find employee with ID ", id, " in the database.");
}

/*
 * Input ID:
 * Prompts the user to enter a 6-digit employee ID to
 * search for. Validates user input, first to ensure
 * that input is an integer, and then to check that it
 * is between 100000 and 999999. Prompts the user to
 * try again if either check fails.
 *
 * returns the ID as an integer
 */
int input_id()
{
    int id;
    char ch;
    printf("%s", "Enter a 6-digit employee ID: ");
    while (scanf("%d", &id) != 1)
    {
        while ((ch = getchar()) != '\n')
            putchar(ch);
        printf("%s\n", " is not an integer, please try again.");
        return input_id();
    }
    if (id < MIN_ID || id > MAX_ID)
    {
        printf("%s\n", "Input must be between 100000 and 999999, please try again.");
        return input_id();
    }
    else return id;
}

/*
 * Search by Name:
 * Calls input_last_name() to retrieve a name to search for.
 * Performs a linear search of the array of Employee structs
 * and prints the employee's info if a match is found, or else
 * informs the user that an employee with the last name provided
 * could not be found.
 *
 * emps - pointer to the array of Employee structs to search
 */
void search_by_name(struct Employee *emps)
{
    char name[MAX_NAME];
    input_last_name(name);
    int i = 0;
    while (emps[i].id != 0)
    {
        if (*emps[i].lastName == *name)
        {
            printf("\n%-32s %7s          %6s\n", "NAME", "SALARY", "ID");
            printf("%s\n", "-----------------------------------------------------------");
            printf("%-12s%-20s $%6d          %6d\n", emps[i].firstName, emps[i].lastName, emps[i].salary, emps[i].id);
            printf("%s\n", "-----------------------------------------------------------");
            return;
        }
        else i++;
    }

    printf("%s%s\n", "Could not find employee with the last name ", name);
}

/*
 * Input Last Name:
 * Prompts the user to enter a last name, and stores the input
 * string at the location provided, unless there is an error.
 *
 * name - the location at which to store the name
 */
int input_last_name(char name[MAX_NAME])
{
    printf("%s", "Enter the employee's last name: ");
    if (scanf("%s", name) != 1)
    {
        printf("%s\n", "Input not recognized, please try again.");
        return input_last_name(name);
    }
    else return 1;

}

/*
 * Input First Name:
 * Prompts the user to enter a first name, and stores the input
 * string at the location provided, unless there is an error.
 *
 * name - the location at which to store the name
 */
int input_first_name(char name[MAX_NAME])
{
    printf("\n%s", "Enter the employee's first name: ");
    if (scanf("%s", name) != 1)
    {
        printf("%s\n", "Input not recognized, please try again.");
        return input_first_name(name);
    }
    else return 1;

}

/*
 * Input Salary:
 * Prompts the user to enter a salary for a new employee.
 * Validates user input, first to ensure it is an integer,
 * and then to check that it is between 30000 and 150000.
 * Prompts the user to try again if either check fails.
 *
 * returns the salary as an integer
 */
int input_salary()
{
    int salary;
    printf("%s", "Enter the employee's salary (30000 to 150000): ");
    if (scanf("%d", &salary) != 1)
    {
        printf("%s\n", "Input not recognized as an integer, please try again.");
        return input_salary();
    }
    else if (salary < MIN_SALARY || salary > MAX_SALARY)
    {
        printf("%s\n", "Input must be between 30000 and 150000, please try again.");
        return input_salary();
    }
    else return salary;
}

/*
 * Sort Employees:
 * Called once by load_employees() once it has populated
 * the array of Employee structs. Simply calls qsort(),
 * passing it the array to sort, the number of elements.
 * the size of an Employee struct, and a comparator function.
 *
 * n - the number of Employee structs in the array
 * emps - pointer to the array of Employee structs
 */
void sort_employees(int n, struct Employee *emps)
{
    qsort(emps, n, sizeof(struct Employee), emp_comparator);
    return;
}

/*
 * Employee Comparator:
 * Used by qsort() in sort_employees() to be used when
 * comparing any two Employee structs according to ID.
 *
 * v1, v2 - generic arguments required for any comparator
 *          function intended to be used by qsort()
 * returns -1 if emp[1].id < emp[2].id
 *          1 if emp[1].id > emp[2].id
 *          0 otherwise
 */
int emp_comparator(const void *v1, const void *v2)
{
    const struct Employee *p1 = v1;
    const struct Employee *p2 = v2;
    if (p1->id < p2->id)
        return -1;
    else if (p1->id > p2->id)
        return +1;
    else
        return 0;
}
