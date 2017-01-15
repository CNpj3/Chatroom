#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"
 
void init_storage(Employee **storage, int n)
{
         // allocate memory space to store employee data
             // no need to understand this function now.
              
                  (*storage) = (Employee *)malloc(sizeof(Employee) * n);
}  
void free_storage(Employee **storage)
{
          free(*storage);
              *storage = 0;
}
Employee* find_employee_by_id(Employee *set, int n, int id)
{
    for (int i=0;i<n;i++)
        if (set[i].id==id) return set[i];
    return NULL;
}
Employee* find_employee_by_name(Employee *set, int n, 
                            const char *first_name, const char *last_name)
{
    for (int i=0;i<n;i++)
        if (strcmp(set[i].first_name,first_name)==0 &&
            strcmp(set[i].last_name,last_name)==0) return set[i];
    return NULL;
}
Employee* find_root_boss(Employee *set, int n, Employee *employee)
{
    if (employee->boss_id == employee->id) return employee;
    Employee boss = find_root_boss(set, n, find_employee_by_id(employee->boss_id));
    return boss;
}
int isSub(Employee *set, int n, Employee *A, Employee *B)
{
    if (A->boss_id == B->id) return 1;
    if (A->boss_id == A->id) return 0;
    if (isSub(set, find_employee_by_id(set,n,A->boss_id),B)) return 1;
}
int check_relationship(Employee *set, int n, Employee *A, Employee *B)
{
    if (find_root_boss(set, n, A)!=find_root_boss(set,n,B)) return 0;
    if (isSub(set,n,A,B)) return 1;
    if (isSub(set,n,B,A)) return 2;
}
