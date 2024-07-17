/*
  Second attempt of interactive linked list implementation;
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Node
{
  int data;
  struct Node* next;
} Node;

int count_nodes(Node**);
int data_insertion_dialog();
void add_node(Node**, int);
void remove_node(Node**, int);
void pop_node(Node**);
void pop_all(Node**, int);

int main(int argc, char** argv)
{
  char opt = '\0';
  Node* node = NULL;

  while (opt != 'x')
  {
    system("clear");

    if (node)
    {
      Node* current = node;
      int i = 0;
      while (current != NULL)
      {
        printf("#%d = %d\n", ++i, current->data);
        current = current->next;
      }
    }
    else
      printf("Select '1' to create your first node");

    printf("\n");
    printf("1. Add node\n");
    printf("2. Delete node\n");
    printf("3. Toggle display address\n");
    printf("\nSelect operation (or 'x' to exit): ");

    opt = getchar();
    while (getchar() != '\n');

    switch (opt)
    {
    case '1':
      if (node)
      {
        bool opt_invalid = false;
        char pos_opt = '\0';

        int i = count_nodes(&node);

        while (!((pos_opt-'0' > 0 && pos_opt-'0' < i) || pos_opt == 'x'))
        {
          system("clear");
          Node* current = node;
          int j = 0;
          while (current != NULL)
          {
            printf("#%d = %d\n", ++j, current->data);
            current = current->next;
          }

          printf("\nSelect position to insert (1-%d) (or 'x' to cancel): ", j);
          pos_opt = getchar();
          while (getchar() != '\n');

          if (j > 1 && pos_opt-'0' == 1)
            add_node(&node, 0);
          if (pos_opt-'0' > 0 && pos_opt-'0' < i)
            add_node(&node, pos_opt-'0');
        }
      }
      else
        add_node(&node, 0);
      
      break;
    case '2':
      if (node)
      {
        bool opt_invalid = false;
        char pos_opt = '\0';

        int i = count_nodes(&node);

        while (!((pos_opt-'0' > 0 && pos_opt-'0' < i) || pos_opt == 'x'))
        {
          system("clear");
          printf("#0 = DELETE ALL\n");
          Node* current = node;
          int j = 0;
          while (current != NULL)
          {
            printf("#%d = %d\n", ++j, current->data);
            current = current->next;
          }

          printf("\nSelect position to delete (0-%d) (or 'x' to cancel): ", j);
          pos_opt = getchar();
          while (getchar() != '\n');

          if (pos_opt-'0' == 0)
            pop_all(&node, i);
          if (j > 0 && pos_opt-'0' == 1)
            pop_node(&node);
          if (pos_opt-'0' > 1 && pos_opt-'0' < i)
            remove_node(&node, pos_opt-'0');
        }
      }
      else
      {
        system("clear");
        char del_opt = '\0';
        printf("Lists are empty! ('x'to back): ");
        del_opt = getchar();
        while (getchar() != '\n');

        if (del_opt = 'x')
          break;
      }
      break;
    default:
      break;
    }

  }
  
  system("clear");
  if (node)
    pop_all(&node, count_nodes(&node));
  return 0;
}

int data_insertion_dialog()
{
  system("clear");
  int data;
  printf("Insert data: ");
  scanf("%d", &data);
  while (getchar() != '\n');

  return data;
}

void add_node(Node** origin, int add_pos)
{
  Node* node = *origin;
  if (add_pos)
  {
    Node* prev = NULL;
    Node* selected = *origin;

    int i = 0;
    while (++i != add_pos)
    {
      prev = selected;
      selected = selected->next;
    }

    Node* new = (Node*) malloc(sizeof(Node));
    new->data = data_insertion_dialog();

    if (prev && selected->next)
    {
      prev->next = new;
      new->next = selected;
    }

    if ((prev == NULL && selected->next == NULL) || (prev && selected->next == NULL))
    {
      selected->next = new;
      new->next = NULL;
    }
  }
  else
  {
    if (*origin)
    {
      Node* node = (Node*) malloc(sizeof(Node));
      node->data = data_insertion_dialog();
      node->next = *origin;
      *origin = node;
    }
    else
    {
      *origin = (Node*) malloc(sizeof(Node));
      (*origin)->data = data_insertion_dialog();
      (*origin)->next = NULL;
    }
  }
}

void remove_node(Node** origin, int add_pos)
{
  Node* node = *origin;
  if (add_pos)
  {
    Node* prev = NULL;
    Node* selected = *origin;
    int i = 0;
    while (++i != add_pos)
    {
      prev = selected;
      selected = selected->next;
    }
    
    if (prev && selected->next)
    {
      prev->next = selected->next;
      free(selected);
    }
    if ((prev == NULL && selected->next == NULL) || (prev && selected->next == NULL))
    {
      prev->next = NULL;
      free(selected);
    }
  }
}

void pop_node(Node** origin)
{
  Node* next_origin = (*origin)->next;
  if (*origin)
  {
    free(*origin);
    (*origin) = next_origin;
  }
  return;
}

void pop_all(Node** origin, int n)
{
  while (--n != 0)
    pop_node(origin);
}

int count_nodes(Node** origin)
{
  Node* node = *origin;
  int i = 1;
  while (node != NULL)
  {
    node = node->next;
    i++;
  }
  return i;
}