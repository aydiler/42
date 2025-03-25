#include "../../subjects/list.h"
#include <stdio.h>
#include <stdlib.h>

int ascending(int a, int b)
{
	return (a <= b);
}

int descending(int a, int b)
{
	return (a >= b);
}

void swap(t_list *ptr1, t_list *ptr2)
{
	int temp;
	temp = ptr1->data;
	ptr1->data = ptr2->data;
	ptr2->data = temp;
}

t_list  *sort_list(t_list* lst, int (*cmp)(int, int))
{
	t_list *last_sorted  = NULL;
	t_list *ptr;

	if (lst == NULL || lst->next == NULL)
		return lst;

	while(last_sorted != lst->next)
	{
		ptr = lst;
		while(ptr->next != last_sorted)
		{
			if((*cmp)(ptr->data, ptr->next->data) == 0)
			{
				swap(ptr, ptr->next);
			}
			ptr = ptr->next;
		}
		last_sorted = ptr;
	}
	return lst;
}
/*
void print_list(t_list *lst)
{
	while(lst)
	{
		printf("%d\n",lst->data);
		lst = lst->next;
	}
}

int main()
{
    t_list *lst = malloc(sizeof(t_list));
    t_list *lst2 = malloc(sizeof(t_list));
    t_list *lst3 = malloc(sizeof(t_list));
    t_list *lst4 = malloc(sizeof(t_list));

    if (!lst || !lst2 || !lst3 || !lst4)
    {
        // Handle memory allocation failure
        // Free any allocated memory and exit
        exit(1);
    }

    lst->next = lst2;
    lst2->next = lst3;
    lst3->next = lst4;
    lst4->next = NULL;

    lst->data = 4;
    lst2->data = 9;
    lst3->data = 1;
    lst4->data = 9;

    printf("Original list: ");
    print_list(lst);

    lst = sort_list(lst, &ascending);

    printf("Sorted list: ");
    print_list(lst);

    // Don't forget to free the allocated memory
    // Implement a function to free the list

    return 0;
}
*/
