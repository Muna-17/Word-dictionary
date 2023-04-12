#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int n=0;
int y=0;

char ch='"';

struct node{
char word[20];
char wordM[20];
struct node *right;
struct node *left;
};

struct node *rootD=NULL;
struct node *temp2=NULL;
struct node *temp1=NULL;
struct node *temp=NULL;

struct node* insert(struct node* root, char data[], char mean[])
{
    if(root==NULL)
    {
        n++;
        struct node *cur;
        cur=(struct node*)malloc(sizeof(struct node));
        strcpy(cur->word,data);
        strcpy(cur->wordM,mean);
//        cur->word=data;
        cur->right=NULL;
        cur->left=NULL;
        root=cur;
        return root;
    }
    else if(strcmp(root->word,data)>0)
    {
        root->left=insert(root->left,data,mean);
    }
    else if(strcmp(root->word,data)<0)
    {
        root->right=insert(root->right,data,mean);
    }

    return root;
}

void inOrder(struct node* root)
{

    if(root->left != NULL)
        inOrder(root->left);

    printf("%s  = %s\n",root->word,root->wordM);

    if(root->right != NULL)
        inOrder(root->right);
}

void preOrder(struct node* root)
{
    printf("%s  = %s\n",root->word,root->wordM);
    if(root->left != NULL)
        preOrder(root->left);

    if(root->right != NULL)
        preOrder(root->right);
}
void preOrderFileInsert(struct node* root,FILE *fp)
{
    fprintf(fp,"%s %s\n",root->word,root->wordM);

    if(root->left != NULL)
        preOrderFileInsert(root->left,fp);

    if(root->right != NULL)
        preOrderFileInsert(root->right,fp);
}

struct node* search(struct node * root,char data[])
{
    if(root!=NULL)
    {
        if(strcmp(root->word,data)==0)
            return root;
        else if(strcmp(root->word,data)>0)
            return search(root->left,data);
        else if(strcmp(root->word,data)<0)
            return search(root->right,data);
    }
    else
    {
        return root;
    }
}
struct node* findMinChar(struct node* root)
{
    if(root!=NULL)
    {
        if(root->left==NULL)
            return root;
        else
            return findMinChar(root->left);
    }
}
//char min[10];
struct node* deleteNode(struct node *root,char data[])
{

    if(root == NULL)
        return  root;
    else if (strcmp(root->word,data) > 0 )
    {
        root->left =  deleteNode(root->left,data);
        return root;
    }
    else if (strcmp(root->word,data)<0)
    {
        root->right= deleteNode(root->right,data);
        return root;
    }
    else
    {
        if(root->right==NULL && root->left==NULL)
        {
            temp=root;
            root=NULL;
            free(temp);
            n--;
            return root;
        }
        else if (root->left == NULL )
        {
            temp = root;
            root = root->right;
            free(temp);
            n--;
            return root;
        }
        else if (root->right == NULL )
        {
            temp = root;
            root = root->left;
            free(temp);
            n--;
            return root;
        }
        else
        {
            temp2=findMinChar(root->right);
            strcpy(root->word,temp2->word);
            strcpy(root->wordM,temp2->wordM);
            root->right = deleteNode(root->right,temp2->word);
            return root;
        }
    }
}
                        ///similar spelling word
char dic[20];
void searchSimilar(struct node* root,char st[],int prntf)
{
    if(root!=NULL)
    {
        strcpy(dic,root->word);
        int i,sum=0,len;
        len=strlen(st);
        len=len/2;
      //  printf("len %d %s\n",len,dic);
        for(i=0; i<len; i++)
        {
            if(dic[i]==st[i])
                sum+=1;
           // printf("%d %d\n",i,sum);
        }
        if(sum==len)
        {
            if(prntf==0)
            {
                printf("Did you mean ");
                prntf=1;
                printf(" %c%s%c",ch,dic,ch);
            }
            else
                printf(", %c%s%c",ch,dic,ch);
        }
        searchSimilar(root->left,st,prntf);
        searchSimilar(root->right,st,prntf);
    }
}
                                                ///#### Synonym ####
void synonym(struct node* root,struct node* sRoot)
{
    if(root!=NULL )
    {
        if(strcmp(root->wordM,sRoot->wordM)==0 && root!=sRoot)
        {
            if(y==0)
            {
                printf("The given words have similiar meaning of our searched word: ");
                printf(" %c%s%c",ch,root->word,ch);
                y=1;
            }
            else
                printf(", %c%s%c",ch,root->word,ch);
        }
        synonym(root->left,sRoot);
        synonym(root->right,sRoot);
    }
}
void header()
{
    system("cls");
    printf("==================   DICTIONARY =====================\n");
    printf("====== There are %d words in our dictionary  ========\n\n",n);
}
void tail()
{
    system("cls");
    printf("====================   DICTIONARY =====================\n");
    printf("====== There are %d words in our dictionary  ========\n\n\n",n);
    printf("======================  <EXIT> =========================\n");
}


                                                ///main function
int main()
{
    int s,i;
    char w[20];
    char wm[20];
    char str[20];
    FILE *fl;

    fl=fopen("word_dictionary.txt","r");              ///inserting words from file
    while(fscanf(fl,"%s%s",w,wm)!=EOF)
    {
        rootD=insert(rootD,w,wm);
    }
    fclose(fl);

    int operation;
    while(1)
    {
        header();
        printf("\n\n1. To add any word\n2. To search any word\n3. To delete a word\n0. To exit.\n");
        printf("\nChoose any option from above: ");
        scanf("%d",&operation);
        if(operation==0)
            break;
        else if(operation==1)
        {
            header();                                ///insert
            printf("Enter a word: ");
            scanf("%s",w);
            printf("Enter %c%s%c meaning: ",ch,w,ch);
            scanf("%s",wm);
            struct node* check;
            check=search(rootD,w);
            if(check==NULL)
            {
                rootD=insert(rootD,w,wm);
                header();
                printf("\n\n\nThe word %c%s%c is being added to the dictionary.\n\n",ch,w,ch);
            }
            else
            {
                printf("The searched word %c%s%c is in the dictionary.\n\n",ch,w,ch);
            }
            printf("Press any key to go back.");
            continue;
        }
        else if(operation==2)
        {
            header();                               ///searching code
            struct node* searchValue;
            printf("\nEnter a word to search: ");
            scanf("%s",str);

            searchValue=search(rootD,str);
            if(searchValue==NULL)
            {
                 printf("Sorry! %c%s%c could not be found.\n",ch,str,ch);
                if(strcmp(str,rootD->word)<0)
                    searchSimilar(rootD->left,str,0);
                else
                    searchSimilar(rootD->right,str,0);
                printf("\n");
            }
            else
            {
                printf("%c%s%c means %c%s%c.\n",ch,searchValue->word,ch,ch,searchValue->wordM,ch);
                y=0;
                synonym(rootD,searchValue);
                printf(" \n");
            }
            printf("\n\n\n\nPress any key to go back.");
            getch();
            continue;
        }
        else if(operation==3)
        {
            header();
            printf("\nEnter a word to delete: ");      ///deleting string
            scanf("%s",str);
            struct node* check;
            check=search(rootD,str);
            if(check==NULL)
            {
                 printf("\n\n\nThe word %c%s%c is not in the Dictionary.\n\n",ch,str,ch);
            }
            else
            {
                rootD=deleteNode(rootD,str);
                header();
                printf("\n\n\nThe word %c%s%c is deleted from the dictionary.\n\n",ch,str,ch);
            }

            printf("Press any key to go back.");
            getch();
            continue;
        }
        else
        {
            printf("Error!The option does not exists.\n\n");
            printf("Press any key to go back.");
            getch();
            continue;
        }
    }
    tail();

    fl=fopen("word_dictionary.txt","w");          ///Updating Dictionary word
    preOrderFileInsert(rootD,fl);
    fclose(fl);


    return 0;
}

