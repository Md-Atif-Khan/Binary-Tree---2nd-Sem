#include <stdio.h>
#include <stdlib.h>
struct tree
{
    int val;
    struct tree *left, *right;
};

struct tree *create_node(int n)
{
    struct tree *temp = (struct tree *)malloc(sizeof(struct tree));
    temp->val = n;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct tree *search(struct tree *root, int n)
{
    if (root == NULL)
        return NULL;
    else if (root->val == n)
        return root;
    else
    {
        struct tree *t = search(root->left, n);
        if (t == NULL)
            t = search(root->right, n);
        return t;
    }
}

struct tree *add_left(struct tree *root, int parent, int n)
{
    struct tree *temp = search(root, parent);
    if (temp == NULL)
        return NULL;
    else
    {
        if (temp->left == NULL)
        {
            temp->left = create_node(n);
            printf("Added!!\n");
        }
        else
            printf("Position already filled\n");
        return root;
    }
}

struct tree *add_right(struct tree *root, int parent, int n)
{
    struct tree *temp = search(root, parent);
    if (temp == NULL)
        return NULL;
    else
    {
        if (temp->right == NULL)
        {
            temp->right = create_node(n);
            printf("Value added!!\n");
        }
        else
            printf("Position already filled\n");
        return root;
    }
}

struct tree *delete (struct tree *root, int n)
{
    if (root == NULL)
        return NULL;
    else if (root->left == NULL && root->right == NULL && root->val == n)
        return root;
    else
    {
        struct tree *temp = delete (root->left, n);
        if (temp == root->left && root->left != NULL)
        {   
            free(root->left);   
            root->left = NULL;
        }
        else if (temp == NULL)
        {
            temp = delete (root->right, n);
            if (temp == root->right && root->right != NULL)
            {   
                free(root->right); 
                root->right = NULL;
            }
        }
        return temp;
    }
}

void display(struct tree *root)
{
    if (root != NULL)
    {
        display(root->left);
        printf("%d ", root->val);
        display(root->right);
    }
}

void main()
{
    struct tree *root = NULL;
    int n, choice, parent;
    printf("Enter the value of the root node\n");
    scanf("%d", &n);
    root = create_node(n);
    while (1)
    {
        printf("1: Find if a node exists\n");
        printf("2: Add a left son\n");
        printf("3: Add a right son\n");
        printf("4: Delete a leaf node\n");
        printf("5: Inorder display\n");
        printf("6: Quit\n");
        printf("Enter a option\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the node to be searched\n");
            scanf("%d", &n);
            if (search(root, n) == NULL)
                printf("Element not found\n");
            else
                printf("Element is present\n");
            break;

        case 2:
            printf("Enter the value of the left son\n");
            scanf("%d", &n);
            printf("Enter the value of the parent\n");
            scanf("%d", &parent);
            if (add_left(root, parent, n) == NULL)
                printf("Parent element not present\n");
            display(root);
            printf("\n");
            break;

        case 3:
            printf("Enter the value of the right son\n");
            scanf("%d", &n);
            printf("Enter the value of the parent\n");
            scanf("%d", &parent);
            if (add_right(root, parent, n) == NULL)
                printf("Parent element not present\n");
            display(root);
            printf("\n");
            break;

        case 4:
            printf("Enter the leaf node to be deleted\n");
            scanf("%d", &n);
            if (delete (root, n) == NULL)
                printf("Given leaf node doesn't exist\n");
            else if(delete (root, n) == root)
                printf("Root node cannot be deleted\n");
            else
                printf("Deleted\n");
            break;

        case 5:
            display(root);
            printf("\n");
            break;

        case 6:
            exit(0);

        default:
            printf("Enter a correct option\n");
        }
    }
}