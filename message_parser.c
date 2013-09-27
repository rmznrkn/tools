//#include <iostream>
//#include <string>

//using namespace std;

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*
 class Student
 {
 public:
 static const int MAX_NAME_LEN = 16;
 static const int MAX_SURNAME_LEN = 16;
 static const int MAX_PHONE_LEN = 16;
 static const int MAX_ADDRESS_LEN = 50;
 int id;
 string name;
 string surname;
 string address;
 string phone;
 };

 class Queue
 {
 public:
 ListNode *first;
 ListNode *last;
 Queue()
 {
 first = NULL;
 last = NULL;
 }
 bool enque(void *data)
 {
 ListNode *newnode = new ListNode;

 if(newnode == NULL)
 return false;

 newnode->data = data;
 newnode->next = NULL;


 newnode->pre = last;

 if(first == NULL)
 first = newnode;

 if(last != NULL)
 last->next = newnode;
 last = newnode;

 return true;
 }

 void *deque()
 {
 ListNode *node = NULL;

 void *data = NULL;

 if(first != NULL)
 {
 data = first->data;
 node = first;
 first = first->next;
 }

 if(first != NULL)
 {
 first->pre = NULL;
 }
 else
 {
 last = NULL;
 }

 if(node != NULL)
 delete node;

 return data;
 }
 };


 class TreeNode
 {
 public:

 Student student;

 TreeNode *left;
 TreeNode *right;
 };

 class BinarySearchTree
 {

 public:
 static const int BY_ID = 0;
 static const int BY_NAME = 1;
 static const int BY_SURNAME = 2;
 static const int BY_ADDRESS = 3;
 static const int BY_PHONE = 4;

 TreeNode *root;
 BinarySearchTree()
 {
 root = NULL;
 }
 virtual ~BinarySearchTree()
 {
 Queue queue;
 TreeNode *treenode;
 queue.enque((void*)root);
 while((treenode = (TreeNode*)queue.deque()) != NULL )
 {
 if(treenode->left != NULL)
 queue.enque((void*)treenode->left);
 if(treenode->right != NULL)
 queue.enque((void*)treenode->right);
 delete treenode;
 }
 }
 bool add(Student *student, int bywhich = BY_ID)
 {
 TreeNode *node = new TreeNode;
 if(node == NULL)
 return false;
 node->left = NULL;
 node->right = NULL;
 node->student = *student;
 return addLeaf(node, bywhich);
 }
 
 bool addLeaf(TreeNode *leafRoot, int bywhich=BY_ID)
 {
 bool left;
 TreeNode *parent = root;
 TreeNode *iterator = root;
 if(leafRoot == NULL)
 return false;
 while(iterator != NULL)
 {
 parent = iterator;
 if(bywhich == BY_ID)
 {
 if(leafRoot->student.id > iterator->student.id)
 {
 left = false;
 iterator = iterator->right;
 }
 else if(leafRoot->student.id < iterator->student.id)
 {
 left = true;
 iterator = iterator->left;
 }
 else
 {
 return false;
 }
 }
 else
 {
 string str1;
 string str2;
 if(bywhich == BY_NAME)
 {
 str1 = leafRoot->student.name;
 str2 = iterator->student.name;
 }
 else if(bywhich == BY_SURNAME)
 {
 str1 = leafRoot->student.surname;
 str2 = iterator->student.surname;
 }
 else if(bywhich == BY_ADDRESS)
 {
 str1 = leafRoot->student.address;
 str2 = iterator->student.address;
 }
 else if(bywhich == BY_PHONE)
 {
 str1 = leafRoot->student.phone;
 str2 = iterator->student.phone;
 }
 if(str1 > str2)
 {
 left = false;
 iterator = iterator->right;
 }
 else if(str1 < str2)
 {
 left = true;
 iterator = iterator->left;
 }
 else
 return false;
 }
 }
 if(parent == NULL)
 {
 root = leafRoot;
 return true;
 }
 if(left)
 {
 parent->left = leafRoot;
 }
 else
 {
 parent->right = leafRoot;
 }
 return true;
 }
 bool del(int id)
 {
 TreeNode *parent;
 TreeNode *node;
 TreeNode *sibling;
 if(!findByID(&parent, &node,id))
 return false;
 if(parent == NULL)
 {
 root = NULL;
 }
 else
 {
 if(node == parent->left)
 parent->left = NULL;
 else
 parent->right= NULL;
 }
 addLeaf(node->left);
 addLeaf(node->right);

 delete node;
 }
 bool del(string str, int bywhich=BY_NAME)
 {
 TreeNode *parent;
 TreeNode *node;
 TreeNode *sibling;
 if(!find(&parent, &node,str, bywhich))
 return false;
 if(parent == NULL)
 {
 root = NULL;
 }
 else
 {
 if(node == parent->left)
 parent->left = NULL;
 else
 parent->right= NULL;
 }
 addLeaf(node->left);
 addLeaf(node->right);

 delete node;
 }
 bool findByID(TreeNode **parent, TreeNode **node, int id)
 {
 *parent = NULL;
 TreeNode *iterator = root;
 while(iterator != NULL)
 {
 if(id > iterator->student.id)
 {
 *parent = iterator;
 iterator = iterator->right;
 }
 else if(id < iterator->student.id)
 {
 *parent = iterator;
 iterator = iterator->left;
 }
 else
 {
 *node = iterator;
 return true;
 }
 }
 return false;
 }
 bool find(TreeNode **parent, TreeNode **node, string str, int bywhich = BY_NAME)
 {
 *parent = NULL;
 TreeNode *iterator = root;
 string str2;
 while(iterator != NULL)
 {
 if(bywhich == BY_NAME)
 str2 = iterator->student.name;
 else if(bywhich == BY_SURNAME)
 str2 = iterator->student.surname;
 else if(bywhich == BY_ADDRESS)
 str2 = iterator->student.address;
 else if(bywhich == BY_PHONE)
 str2 = iterator->student.phone;

 if(str > str2)
 {
 *parent = iterator;
 iterator = iterator->right;
 }
 else if(str < str2)
 {
 *parent = iterator;
 iterator = iterator->left;
 }
 else
 {
 *node = iterator;
 return true;
 }
 }
 return false;
 }
 ListNode* searchByID(int id)
 {
 OrderedList list;
 TreeNode *iterator = root;
 while(iterator != NULL)
 {
 if(id > iterator->student.id)
 {
 iterator = iterator->right;
 }
 else if(id < iterator->student.id)
 {
 iterator = iterator->left;
 }
 else
 {
 list.add((void*)&iterator->student);
 return list.first;
 }
 }
 return NULL;
 }
 ListNode* searchByName(string name)
 {
 Queue squeue;
 OrderedList list;

 TreeNode *treenode;
 squeue.enque((void*)root);
 while((treenode = (TreeNode*)squeue.deque()) != NULL )
 {
 if(treenode->student.name == name)
 {
 list.add((void*)&treenode->student);
 }
 if(treenode->left != NULL)
 squeue.enque((void*)treenode->left);
 if(treenode->right != NULL)
 squeue.enque((void*)treenode->right);
 }
 return list.first;
 }
 ListNode* searchBySurname(string surname)
 {
 Queue squeue;
 OrderedList list;

 TreeNode *treenode;
 squeue.enque((void*)root);
 while((treenode = (TreeNode*)squeue.deque()) != NULL )
 {
 if(treenode->student.surname == surname)
 {
 list.add((void*)&treenode->student);
 }
 if(treenode->left != NULL)
 squeue.enque((void*)treenode->left);
 if(treenode->right != NULL)
 squeue.enque((void*)treenode->right);
 }
 return list.first;
 }
 ListNode* searchByAddress(string address)
 {
 Queue squeue;
 OrderedList list;

 TreeNode *treenode;
 squeue.enque((void*)root);
 while((treenode = (TreeNode*)squeue.deque()) != NULL )
 {
 if(treenode->student.address == address)
 {
 list.add((void*)&treenode->student);
 }

 if(treenode->left != NULL)
 squeue.enque((void*)treenode->left);
 if(treenode->right != NULL)
 squeue.enque((void*)treenode->right);
 }
 return list.first;
 }
 ListNode* searchByPhone(string phone)
 {
 Queue squeue;
 OrderedList list;

 TreeNode *treenode;
 squeue.enque((void*)root);
 while((treenode = (TreeNode*)squeue.deque()) != NULL )
 {
 if(treenode->student.phone == phone)
 {
 list.add((void*)&treenode->student);
 }

 if(treenode->left != NULL)
 squeue.enque((void*)treenode->left);
 if(treenode->right != NULL)
 squeue.enque((void*)treenode->right);
 }
 return list.first;
 }
 ListNode * getOrderedList(int bywhich=BY_ID)
 {
 OrderedList list;
 Stack stack;

 TreeNode *treenode;
 stack.push((void*)root);
 while((treenode = (TreeNode*)stack.pop()) != NULL )
 {
 if(treenode->right != NULL)
 stack.push((void*)treenode->right);
 if(treenode->left != NULL)
 stack.push((void*)treenode->left);
 if(bywhich == BY_ID)
 list.add((void*)&treenode->student);
 if(bywhich == BY_NAME)
 list.addByName((void*)&treenode->student);
 if(bywhich == BY_SURNAME)
 list.addBySurname((void*)&treenode->student);
 if(bywhich == BY_ADDRESS)
 list.addByAddress((void*)&treenode->student);
 if(bywhich == BY_PHONE)
 list.addByPhone((void*)&treenode->student);
 }
 return list.first;
 }
 };

 class Database
 {
 public:
 BinarySearchTree bstById;

 BinarySearchTree bstByName;
 BinarySearchTree bstBySurname;
 BinarySearchTree bstByAddress;
 BinarySearchTree bstByPhone;

 bool add(Student *student)
 {
 bool result1= bstById.add(student, BinarySearchTree::BY_ID);
 bool result2= bstByName.add(student, BinarySearchTree::BY_NAME);
 bool result3= bstBySurname.add(student, BinarySearchTree::BY_SURNAME);
 bool result4= bstByAddress.add(student, BinarySearchTree::BY_ADDRESS);
 bool result5= bstByPhone.add(student, BinarySearchTree::BY_PHONE);

 return (result1 || result2 || result3 || result4 || result5);
 }
 void printList(ListNode *listIterator, string msg="ByID")
 {
 Student *student;
 char str[1024];
 int i = 1;
 cout << "\n===<<Start of PRINT(LIST_"<< msg <<")>>===" << endl;

 cout << "Order    ";
 cout << "ID       ";
 cout << "Name            ";
 cout << "Surname         ";
 cout << "Phone           ";
 cout << "Adress";
 cout << endl;

 while(listIterator != NULL)
 {
 student = (Student*)listIterator->data;
 int slen = sprintf(str,"%d",i);
 i++;
 cout << str;
 for(int j = slen ; j  < 9; j++)
 cout << " ";

 slen = sprintf(str,"%d",student->id);
 cout << str;
 for(int j = slen ; j  < 9; j++)
 cout << " ";

 slen = sprintf(str,"%s",student->name.c_str());
 cout << str;
 for(int j = slen ; j  < Student::MAX_NAME_LEN; j++)
 cout << " ";
 slen = sprintf(str,"%s ",student->surname.c_str());
 cout << str;
 for(int j = slen ; j  < Student::MAX_SURNAME_LEN; j++)
 cout << " ";
 slen = sprintf(str,"%s ",student->phone.c_str());
 cout << str;
 for(int j = slen ; j  < Student::MAX_PHONE_LEN; j++)
 cout << " ";
 slen = sprintf(str,"%s ",student->address.c_str());
 cout << str << endl;

 listIterator = listIterator->next;
 }
 cout << "===<<End of PRINT(LIST_ " << msg << ")>>===\n" << endl;
 }

 ListNode *searchByID(int id)
 {
 return bstById.searchByID(id);
 }
 ListNode *searchByName(string str)
 {
 return bstByName.searchByName(str);
 }
 ListNode *searchBySurname(string str)
 {
 return bstBySurname.searchBySurname(str);
 }
 ListNode *searchByAddress(string str)
 {
 return bstByAddress.searchByAddress(str);
 }
 ListNode *searchByPhone(string str)
 {
 return bstByPhone.searchByPhone(str);
 }
 ListNode *listByID()
 {
 return bstById.getOrderedList(BinarySearchTree::BY_ID);
 }
 ListNode *listByName()
 {
 return bstByName.getOrderedList(BinarySearchTree::BY_NAME);
 }
 ListNode *listBySurname()
 {
 return bstBySurname.getOrderedList(BinarySearchTree::BY_SURNAME);
 }
 ListNode *listByAddress()
 {
 return bstByAddress.getOrderedList(BinarySearchTree::BY_ADDRESS);
 }
 ListNode *listByPhone()
 {
 return bstByPhone.getOrderedList(BinarySearchTree::BY_PHONE);
 }
 static void deleteResultList(ListNode *listIterator)
 {
 ListNode *temp;
 while(listIterator != NULL)
 {
 temp = listIterator;
 listIterator = listIterator->next;

 delete temp;
 }
 }

 bool del(Student *student)
 {
 bool result1 =  bstById.del(student->id);
 bool result2 =  bstByName.del(student->name, BinarySearchTree::BY_NAME);
 bool result3 =  bstBySurname.del(student->surname, BinarySearchTree::BY_SURNAME);
 bool result4 =  bstByAddress.del(student->address, BinarySearchTree::BY_ADDRESS);
 bool result5 =  bstByPhone.del(student->phone, BinarySearchTree::BY_PHONE);

 return (result1 || result2 || result3 || result4 || result5);
 }
 };

 int main__(void)
 {
 string choice;
 Student student;
 Database db;
 char str[256];
 while(1)
 {
 cout << " 0-> Quit" << endl;
 cout << " 1-> Add" << endl;
 cout << " 2-> Search by ID" << endl;
 cout << " 3-> Search by Name" << endl;
 cout << " 4-> Search by Surname" << endl;
 cout << " 5-> Search by Phone" << endl;
 cout << " 6-> Search by Address" << endl;
 cout << " 7-> List" << endl;
 cout << " 8-> Delete by ID" << endl;

 cout << " choice: ";

 cin.getline(str,256);
 choice = str;

 if(choice == "0")
 break;

 if(choice == "1")
 {
 cout << "ID: ";
 cin.getline(str,10);
 student.id = atoi(str);
 cout << "Name: ";
 cin.getline( str,Student::MAX_NAME_LEN);
 student.name = str;
 cout << "Surname: ";
 cin.getline( str,Student::MAX_SURNAME_LEN);
 student.surname = str;
 cout << "Address: ";
 cin.getline( str,Student::MAX_ADDRESS_LEN);
 student.address = str;
 cout << "Phone Number: ";
 cin.getline( str,Student::MAX_PHONE_LEN);
 student.phone = str;


 if(db.add(&student))
 cout << "Add succesfull" << endl;
 else
 cout << "Add failure" << endl;
 }
 else if(choice == "2")
 {
 cout << "ID: ";
 cin.getline(str,10);
 student.id = atoi(str);
 ListNode *list = db.searchByID(student.id);
 db.printList(list);
 Database::deleteResultList(list);
 }
 else if(choice == "3")
 {
 cout << "Name: ";
 cin.getline( str,Student::MAX_NAME_LEN);
 ListNode *list = db.searchByName(str);
 db.printList(list);
 Database::deleteResultList(list);
 }
 else if(choice == "4")
 {
 cout << "Surname: ";
 cin.getline( str,Student::MAX_SURNAME_LEN);
 ListNode *list = db.searchBySurname(str);
 db.printList(list);
 Database::deleteResultList(list);
 }
 else if(choice == "5")
 {
 cout << "Address: ";
 cin.getline( str,Student::MAX_ADDRESS_LEN);
 ListNode *list = db.searchByAddress(str);
 db.printList(list);
 Database::deleteResultList(list);
 }
 else if(choice == "6")
 {
 cout << "PhoneNumber: ";
 cin.getline( str,Student::MAX_PHONE_LEN);
 ListNode *list = db.searchByPhone(str);
 db.printList(list);
 Database::deleteResultList(list);
 }
 else if(choice == "7")
 {
 ListNode *list = db.listByID();
 db.printList(list,"ByID");
 Database::deleteResultList(list);

 list = db.listByName();
 db.printList(list,"ByName");
 Database::deleteResultList(list);

 list = db.listBySurname();
 db.printList(list,"BySurname");
 Database::deleteResultList(list);

 list = db.listByAddress();
 db.printList(list,"ByAddress");
 Database::deleteResultList(list);


 list = db.listByPhone();
 db.printList(list,"ByPhone");
 Database::deleteResultList(list);


 }
 else if(choice == "8")
 {
 cout << "ID: ";
 cin.getline(str,10);
 student.id = atoi(str);

 ListNode *list = db.searchByID(student.id);
 if(list != NULL)
 {
 student = *((Student*)list->data);
 Database::deleteResultList(list);

 if(db.del(&student))
 cout << "delete succesfull" << endl;
 else
 cout << "delete failure" << endl;
 }
 else
 cout << "delete failure" << endl;
 }
 }
 }
 */
#define RBUF_LEN     4096
#define SBUF_LEN     260
#define PATH_LEN_MAX 260
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define TOKEN_LEN 100
typedef struct _variable_ {
   char type[TOKEN_LEN];
   char name[TOKEN_LEN];
   char size[TOKEN_LEN];
   int array;
   struct _variable_ *next;
} Variable;

typedef struct _struct_ {
   char name[TOKEN_LEN];
   Variable *first;
   Variable *last;
   struct _struct_ *next;
} Struct;

typedef struct _field_ {
   char name[TOKEN_LEN];
   char fullName[TOKEN_LEN];
   struct _field_ *next;
} Fieldsss;

typedef struct _token_ {
   char *token;
   int len;
   struct _token_ *next;
} Token;

typedef struct {
   char path[PATH_LEN_MAX];
   int plen;
   char ident[PATH_LEN_MAX];
   int ilen;
} Directory;

typedef struct {
   char path[PATH_LEN_MAX];
   int plen;
   char name[PATH_LEN_MAX];
   int nlen;
   size_t size;
   size_t lnCount;
   size_t lrCount;
   size_t nvCount;
   size_t id;
} File;

typedef struct {
   char path[PATH_LEN_MAX];
   char searchWindow[RBUF_LEN];
   size_t atLine;
   int startIndex;
} Found;

typedef struct _ListNode_ {
   void *data;
   struct _ListNode_ *next;
   struct _ListNode_ *pre;
} ListNode;

typedef struct {
   ListNode *top;
} Stack;

typedef struct _sorted_list {
   ListNode *first;
   ListNode *last;
} SortedFileList;

void sfl_init(SortedFileList *sl) {
   sl->first = NULL;
   sl->last = NULL;
}
int sfl_add(SortedFileList *sfl, void *data) {
   ListNode *newnode = (ListNode*) malloc(sizeof(ListNode));

   if (newnode == NULL )
      return 0;

   newnode->data = data;
   newnode->next = NULL;
   newnode->pre = NULL;

   if (sfl->first == NULL ) {
      sfl->last = sfl->first = newnode;
      return 1;
   }
   File *fs = (File*) sfl->first->data;
   File *ls = (File*) sfl->last->data;
   File *file = (File*) data;

   if (file->id <= fs->id) {
      sfl->first->pre = newnode;
      newnode->next = sfl->first;
      sfl->first = newnode;
      return 1;
   }
   if (file->id >= ls->id) {
      newnode->pre = sfl->last;
      sfl->last->next = newnode;
      sfl->last = newnode;
      return 1;
   }
   if (((fs->id + ls->id) / 2) >= file->id) {
      ListNode *iterator = sfl->last;
      while (iterator != NULL ) {
         ls = (File*) iterator->data;
         if (ls->id <= file->id) {
            iterator->next->pre = newnode;
            newnode->next = iterator->next;
            newnode->pre = iterator;
            iterator->next = newnode;
            return 1;
         }
         iterator = iterator->pre;
      }
   } else {
      ListNode *iterator = sfl->first;
      while (iterator != NULL ) {
         ls = (File*) iterator->data;
         if (ls->id >= file->id) {
            iterator->pre->next = newnode;
            newnode->next = iterator;
            newnode->pre = iterator->pre;
            iterator->pre = newnode;
            return 1;
         }
         iterator = iterator->next;
      }
   }
   return 0;
}

void stack_init(Stack *stack) {
   stack->top = NULL;
}

int stack_push(Stack *stack, void *data) {
   ListNode *newnode = malloc(sizeof(ListNode));

   if (newnode == NULL )
      return 0;

   newnode->data = data;
   newnode->next = NULL;

   newnode->pre = stack->top;

   if (stack->top != NULL )
      stack->top->next = newnode;
   stack->top = newnode;

   return 1;
}

void *stack_pop(Stack *stack) {

   ListNode *node = NULL;

   void *data = NULL;

   if (stack->top != NULL ) {
      data = stack->top->data;
      node = stack->top;
      stack->top = stack->top->pre;
   }

   if (stack->top != NULL ) {
      stack->top->next = NULL;
   }

   if (node != NULL )
      free(node);

   return data;
}

int getHexValueStr(char *rbuf, int blen, char *dest, int dcapacity) {
   int i, j;
   int searchTextLen = 0;
   char searchWindow[RBUF_LEN];
   int searchWindowLen = 0;
   int searchWindowWrIdx = 0;
   int searchWindowRdIdx = 0;
   int si, wi, found;
   int startIndex = 0;

   char startWith[] = "0x";

   searchTextLen = strlen(startWith);
   found = 0;

   for (i = 0; i < blen; i++) {
      if (searchWindowLen < searchTextLen) {
         if (searchWindowWrIdx >= RBUF_LEN)
            searchWindowWrIdx = 0;
         searchWindow[searchWindowWrIdx++] = rbuf[i];
         searchWindowLen++;
      }

      if (searchWindowLen == searchTextLen) {
         found = 1;
         wi = searchWindowRdIdx;
         for (si = 0; si < searchTextLen; si++) {
            if (searchWindow[wi] != startWith[si]) {
               found = 0;
               break;
            }
            wi++;
            if (wi >= RBUF_LEN)
               wi = 0;
         }
         if (found) {
            startIndex = i;
            break;
         }

         searchWindowRdIdx++;
         if (searchWindowRdIdx >= RBUF_LEN)
            searchWindowRdIdx = 0;
         searchWindowLen--;
      }
   }

   if (!found)
      return 0;

   for (si = 1; (si + startIndex) < blen && si < dcapacity; si++) {
      if ((rbuf[si + startIndex] >= '0' && rbuf[si + startIndex] <= '9')
            || rbuf[si + startIndex] == 'a' || rbuf[si + startIndex] == 'A'
            || rbuf[si + startIndex] == 'b' || rbuf[si + startIndex] == 'B'
            || rbuf[si + startIndex] == 'c' || rbuf[si + startIndex] == 'C'
            || rbuf[si + startIndex] == 'd' || rbuf[si + startIndex] == 'D'
            || rbuf[si + startIndex] == 'e' || rbuf[si + startIndex] == 'E'
            || rbuf[si + startIndex] == 'f' || rbuf[si + startIndex] == 'F')
         dest[si - 1] = rbuf[si + startIndex];
      else
         break;
   }
   dest[si - 1] = 0;
   return 1;
}
unsigned int getHexValue(char *str) {
   int i;
   int slen = strlen(str);
   unsigned int hval = 0;

   for (i = 0; i < slen; i++) {
      if ((str[i] >= '0' && str[i] <= '9'))
         hval = hval * 16 + (str[i] - '0');
      else if (str[i] == 'a' || str[i] == 'A')
         hval = hval * 16 + 10;
      else if (str[i] == 'b' || str[i] == 'B')
         hval = hval * 16 + 11;
      else if (str[i] == 'c' || str[i] == 'C')
         hval = hval * 16 + 12;
      else if (str[i] == 'd' || str[i] == 'D')
         hval = hval * 16 + 13;
      else if (str[i] == 'e' || str[i] == 'E')
         hval = hval * 16 + 14;
      else if (str[i] == 'f' || str[i] == 'F')
         hval = hval * 16 + 15;
   }

   return hval;
}
unsigned int getNextToken(char *token, char *str, int *offset) {
   int slen = strlen(str);
   int tlen = 0;
   char delimList[] = " \n\t\r";

   int delimLen = strlen(delimList);
   int found = 0;
   int j;

   while ((*offset) < slen) {
      found = 0;
      for (j = 0; j < delimLen; j++) {
         if (delimList[j] == str[*offset]) {
            (*offset)++;
            found = 1;
            break;
         }
      }
      if (!found)
         break;
   }

   tlen = 0;
   while ((*offset) < slen) {
      for (j = 0; j < delimLen; j++) {
         if (delimList[j] == str[*offset]) {
            token[tlen++] = 0;
            (*offset)++;
            return tlen;
         }
      }
      token[tlen++] = str[*offset];
      (*offset)++;
   }
   return tlen;
}
unsigned int getNextToken2(char *token, char *str, int *offset) {
   int slen = strlen(str);
   int tlen = 0;
   struct _delim_ {
      char value;
      int special;
   } delims[] = { { ' ', 0 }, { '\n', 1 }, { '\t', 0 }, { '\r', 1 }, { '#', 1 }, { '[', 1 }, { ']',
         1 }, { '{', 1 }, { '}', 1 }, { '(', 1 }, { ')', 1 }, { ',', 1 }, { ';', 1 }, { '/', 1 }, {
         '*', 1 } };
   //char delimList[] = " \n\t\r#][;,/";
   //char specialDelimList[] = "\n\r#;,/";
   int delimLen = sizeof(delims) / sizeof(struct _delim_); //;strlen(delimList);
   int found = 0;
   int j;
   int delimIndex = 0;
   while ((*offset) < slen) {
      found = 0;
      for (j = 0; j < delimLen; j++) {
         if (delims[j].value == str[*offset]) {
            (*offset)++;
            found = 1;
            delimIndex = j;
            break;
         }
      }
      if (!found)
         break;
      else if (delims[delimIndex].special) {
         token[0] = delims[j].value;
         return 1;
      }

   }

   tlen = 0;
   while ((*offset) < slen) {
      for (j = 0; j < delimLen; j++) {
         if (delims[j].value == str[*offset]) {
            token[tlen++] = 0;
            if (!delims[j].special)
               (*offset)++;
            return tlen;
         }
      }
      token[tlen++] = str[*offset];
      (*offset)++;
   }
   return tlen;
}
Token* token_parse(char *fileName) {
   Token *root = NULL;
   Token *token = NULL;
   Token *last = NULL;
   char rbuf[RBUF_LEN];
   char line[RBUF_LEN];
   char str[RBUF_LEN];
   int slen;
   char token1[RBUF_LEN];
   int tlen;
   char token2[RBUF_LEN];
   int i, j, linelen;
   size_t blen;
   char hextText[RBUF_LEN];
   int tokenCnt = 0;
   int messageNum;
   FILE *fp = fopen(fileName, "r+b");
   FILE *fout = fopen("tokens.txt", "w+b");
   if (fp == NULL )
      return NULL ;

   fseek(fp, 0, SEEK_END);
   size_t fsize = ftell(fp);

   printf(" (size: %d byte\n\n\n", fsize);
   fseek(fp, 0, SEEK_SET);

   size_t rsize = 0;

   linelen = 0;

   while (rsize < fsize) {

      if (fsize - rsize > RBUF_LEN)
         blen = fread(rbuf, 1, RBUF_LEN, fp);
      else
         blen = fread(rbuf, 1, fsize - rsize, fp);

      rsize += blen;

      for (i = 0; i < blen; i++) {
         if (rbuf[i] == '\n') {
            line[linelen] = 0;
            int offset = 0;

            while ((tlen = getNextToken2(token1, line, &offset))) {
               token = (Token*) malloc(sizeof(Token));
               token->len = tlen;
               token->token = (char*) malloc(tlen + 2);
               token->next = NULL;

               token1[tlen] = 0;
               memcpy(token->token, token1, tlen + 1);
               if (root == NULL )
                  root = token;
               if (last != NULL )
                  last->next = token;
               last = token;

               slen = sprintf(str, "<token%d>%s</token%d>\n", tokenCnt, token1, tokenCnt);
               fwrite(str, slen, 1, fout);
               tokenCnt++;
            }

            linelen = 0;
         } else
            line[linelen++] = rbuf[i];
      }
   }
   return root;
}
int nextToken(Token **token, int *failed) {
   if (*token != NULL )
      *token = (*token)->next;

   if (*token == NULL ) {
      *failed = 1;
      return 0;
   }
   //(*token)->token[(*token)->len] = 0;
   return 1;
}
Struct *getNextStruct(Token **root) {
   Token *token = *root;
   int varStarted = 0;
   Struct *strct = NULL;
   int failed = 0;
   while (token != NULL && !failed) {
      //printf("%s\n", token->token);
      if (strcmp(token->token, "/") == 0) {

         if (strcmp(token->token, "/") == 0) {
            while (token != NULL && strcmp(token->token, "\r") != 0) {
               if (!nextToken(&token, &failed))
                  break;
            }
            if (failed)
               break;
         } else if (strcmp(token->token, "*") == 0) {
            while (token != NULL && token->next != NULL ) {
               if (strcmp(token->token, "*") == 0 && strcmp(token->next->token, "/") == 0) {
                  if (!nextToken(&token, &failed))
                     break;
                  break;
               }
               token = token->next;
            }
            if (failed)
               break;
         } else {
            failed = 1;
            break;
         }

         if (!nextToken(&token, &failed))
            break;
      } else if (strcmp(token->token, "struct") == 0) {

         printf("struct ");
         if (strct != NULL ) {
            failed = 1;
            if (!nextToken(&token, &failed))
               break;
            break;
         }
         strct = (Struct*) malloc(sizeof(Struct));
         strct->first = NULL;
         strct->last = NULL;
         strct->next = NULL;

         if (!nextToken(&token, &failed))
            break;
      } else if (strcmp(token->token, "{") == 0) {
         printf("{\n");
         if (strct == NULL ) {
            failed = 1;
            if (!nextToken(&token, &failed))
               break;
            break;
         }
         strct->last = strct->first = (Variable*) malloc(sizeof(Variable));
         strct->last->array = 0;
         strct->last->next = NULL;

         if (!nextToken(&token, &failed))
            break;

      } else if (strcmp(token->token, "}") == 0) {

         printf("}\n");
         if (strct == NULL || strct->last == NULL ) {
            failed = 1;
            if (!nextToken(&token, &failed))
               break;
            break;
         }

         if (!nextToken(&token, &failed))
            break;

         memcpy(strct->name, token->token, token->len + 1);
         if (!nextToken(&token, &failed))
            break;
         break;
      } else if (strcmp(token->token, "char") == 0) {

         printf("char ");

         if (strct == NULL || strct->last == NULL ) {
            failed = 1;
            if (!nextToken(&token, &failed))
               break;
            break;
         }
         sprintf(strct->last->type, "char");

         if (!nextToken(&token, &failed))
            break;

         memcpy(strct->last->name, token->token, token->len + 1);
         printf("%s", strct->last->name);
         if (!nextToken(&token, &failed))
            break;

         if (strcmp(token->token, "[") == 0) {
            if (!nextToken(&token, &failed))
               break;
            memcpy(strct->last->size, token->token, token->len + 1);
            //] için
            if (!nextToken(&token, &failed))
               break;
            if (strcmp(token->token, "]") != 0) {
               failed = 1;
               break;
            }
            //; için
            if (!nextToken(&token, &failed))
               break;
            if (strcmp(token->token, ";") != 0) {
               failed = 1;
               break;
            }
            strct->last->array = 1;
            strct->last->next = (Variable*) malloc(sizeof(Variable));
            strct->last = strct->last->next;
            strct->last->array = 0;
            strct->last->next = NULL;

            if (!nextToken(&token, &failed))
               break;
            printf("[%s];\n", strct->last->size);
         } else if (strcmp(token->token, ";") == 0) {

            printf(";\n");
            strct->last->size[0] = '1';
            strct->last->size[1] = '\0';

            strct->last->array = 0;
            strct->last->next = (Variable*) malloc(sizeof(Variable));
            strct->last = strct->last->next;
            strct->last->array = 0;
            strct->last->next = NULL;
            if (!nextToken(&token, &failed))
               break;
         } else {
            failed = 1;
            break;
         }
         if (!nextToken(&token, &failed))
            break;
      } else {
         if (!nextToken(&token, &failed))
            break;
      }
   }
   if (failed) {
      printf("\n:::FAILED\n");
      //exit(1);
      if (strct != NULL ) {
         while (strct->first != NULL ) {
            strct->last = strct->first;
            strct->first = strct->first->next;
            free(strct->last);
         }
         free(strct);
      }
      strct = NULL;
   }
   *root = token;
   return strct;
}
void write_setStartIndex(Variable *v, Variable *last, FILE *fp) {
   Variable *var = NULL;
   Variable *pre = NULL;
   char str[64000];
   int i;
   var = v;
   i = sprintf(str, "   m_dlen = 0;\n");
   fwrite(str, i, 1, fp);
   while (var != NULL && var != last) {
      i = sprintf(str, "   m_%s", var->name);
      fwrite(str, i, 1, fp);
      i = sprintf(str, ".setIndex(m_dlen);\n");
      fwrite(str, i, 1, fp);
      i = sprintf(str, "   m_dlen += m_%s.getMaxLen();\n", var->name);
      fwrite(str, i, 1, fp);
      /*fwrite(str, i, 1, fp);
       i = sprintf(str, ".setIndex(");
       if (v == var)
       i += sprintf(str + i, "0");
       pre = v;
       while (pre != NULL && pre != var) {
       i += sprintf(str + i, "m_%s.getMaxlen()", pre->name);
       if (pre->next != var)
       i += sprintf(str + i, " + ");
       pre = pre->next;
       }
       i += sprintf(str + i, ");\n");
       fwrite(str, i, 1, fp);
       */
      var = var->next;
   }
   var = v;
   //i = sprintf(str, "   m_dlen = startIndex");
   //fwrite(str, i, 1, fp);
   //while (var != NULL && var != last) {
   /*i = sprintf(str, "m_%s.getMaxlen()", var->name);
    fwrite(str, i, 1, fp);
    if (var->next != last) {
    i = sprintf(str, " + ");
    fwrite(str, i, 1, fp);
    }*/
   // pre = var;
   // var = var->next;
   //}
   //i = sprintf(str, ";\n");
   //fwrite(str, i, 1, fp);
   var = var->next;

}
void write_sruct_xml(Token *root) {

   FILE *fout = fopen("struct.txt", "w");
   FILE *cf = fopen("class.h", "w");
   char str[64000];
   int i;
   Struct *s;
   Variable *var = NULL;
   Variable *tv = NULL;
   Token *hold = root;
   while (root != NULL ) {
      //i = sprintf(str, "%s\n",root->token);
      //fwrite(str, i, 1, fout);{
      //fprintf(fout, "%s\n", root->token);
      root = root->next;
   }
   root = hold;

   while (root != NULL ) {
      s = getNextStruct(&root);

      if (s != NULL ) {

         i = sprintf(str, "class %s", s->name);
         i += sprintf(str + i, "ReplyMessage: public VIOP::ReplyMessageBase{\n");
         i += sprintf(str + i, "public:\n");
         i += sprintf(str + i, "int m_dlen;\n");
         i += sprintf(str + i, "public:\n");
         i += sprintf(str + i, "%sReplyMessage():ReplyMessageBase(-1)\n", s->name);
         i += sprintf(str + i, "{\n");
         fwrite(str, i, 1, cf);
         var = s->first;
         write_setStartIndex(var, s->last, cf);
         i = sprintf(str, "}\n};\n");
         fwrite(str, i, 1, cf);

         i = sprintf(str, "<class> ");
         fwrite(str, i, 1, fout);

         i = sprintf(str, "  <name>%s</name>\n", s->name);
         fwrite(str, i, 1, fout);
         var = s->first;
         while (var != NULL && var != s->last) {

            i = sprintf(str, "  <field>");
            fwrite(str, i, 1, fout);
            i = sprintf(str, " <type>%s</type>"
                  " <name>%s</name>"
                  " <size>%s</size>"
                  " <array>%d</array>", var->type, var->name, var->size, var->array);
            fwrite(str, i, 1, fout);
            i = sprintf(str, " </field>\n");
            fwrite(str, i, 1, fout);
            var = var->next;
         }
         i = sprintf(str, "</class>\n");
         fwrite(str, i, 1, fout);
         free(s);
      }

   }

}
void message_set(char *fileName) {
   char rbuf[RBUF_LEN];
   char line[RBUF_LEN];
   char token1[RBUF_LEN];
   char token2[RBUF_LEN];
   int i, j, linelen;
   size_t blen;
   char hextText[RBUF_LEN];
   int lineCnt = 0;
   int messageNum;
   FILE *fp = fopen(fileName, "r+b");

   if (fp == NULL )
      return;

   fseek(fp, 0, SEEK_END);
   size_t fsize = ftell(fp);

   printf(" (size: %d byte\n\n\n", fsize);
   fseek(fp, 0, SEEK_SET);

   size_t rsize = 0;

   linelen = 0;

   while (rsize < fsize) {

      if (fsize - rsize > RBUF_LEN)
         blen = fread(rbuf, 1, RBUF_LEN, fp);
      else
         blen = fread(rbuf, 1, fsize - rsize, fp);

      rsize += blen;

      for (i = 0; i < blen; i++) {
         if (rbuf[i] == '\n') {
            line[linelen] = 0;
            int offset = 0;

            if (getNextToken(token1, line, &offset) && strcmp(token1, "#define") == 0) {
               if (!getNextToken(token2, line, &offset))
                  continue;
               if (!getNextToken(hextText, line, &offset))
                  continue;
               messageNum = getHexValue(hextText);

               /*
                if(getHexValueStr(line, linelen,hextText, 3))
                {
                messageNum = getHexValue(hextText);
                }
                */
               while (lineCnt < messageNum) {
                  //printf("#define MSGTYPE_MESSAGE_0x%0.2X 0x%0.2X\n", lineCnt, lineCnt );
                  printf("statistics.messageDefs[%d].type = 0x%0.2X;", lineCnt, lineCnt);
                  printf("statistics.messageDefs[%d].name = \"MSGTYPE_MESSAGE_0x%0.2X\";\n",
                        lineCnt, lineCnt);
                  //printf("statistics.message_counts[%d] = 0;\n",lineCnt);

                  lineCnt++;
               }

               if (lineCnt > messageNum)
                  printf("______________ERROR_____________%0.2X\n", messageNum);

               //printf("%s\n",line);
               //printf("%s %s %s\n", token1, token2, hextText);

               printf("statistics.messageDefs[%d].type = 0x%0.2X;", lineCnt, messageNum);
               printf("statistics.messageDefs[%d].name = \"%s\";\n", lineCnt, token2);
               //printf("statistics.message_counts[%d] = 0;\n",lineCnt);

               lineCnt++;
            }

            linelen = 0;
         } else
            line[linelen++] = rbuf[i];
      }
   }

}
/*
 <message>
 <feature>
 name=""
 value=""
 </feature>
 <field>
 <feature>
 name=""
 value=""
 </feature>
 </field>
 </message>
 */
int search_keyword(char *keyword, char *text) {
   char *kwb = keyword;
   char *txtb = text;
   while (*text) {
      if (tolower(*kwb) == tolower(*text)) {
         keyword = kwb;
         txtb = text + 1;
         while (*text && *keyword) {
            if (tolower(*text) != tolower(*keyword))
               break;
            text++;
            keyword++;
         }
         if (!(*keyword) && (*text))
            return 1;
         else if (!(*keyword) && !(*text))
            return 1;
         else if ((*keyword) || !(*text))
            return 0;

         text = txtb;
      } else
         text++;
   }
   return 0;
}
typedef struct _feature_ {
   char *name;
   char *value;

   struct _feature_ *next;
} Feature;

typedef struct _msg_field_ {
   Feature *firstFeature;
   Feature *lastFeature;

   struct _msg_field_ *next;
} Field;

typedef struct __message__ {
   Feature *firstFeature;
   Feature *lastFeature;

   Field *firstField;
   Field *lastField;

   struct __message__ *next;
} Message;

typedef struct _msg_list {
   Message *firstMessage;
   Message *lastMessage;
} MessageList;

typedef struct {
   FILE *fp;
   char *fileName;
   size_t fileSize;
   size_t readLen;

   char buffer[RBUF_LEN];
   size_t blen;
   size_t boffset;
} MsgFile;

char* getNextBlock2(MsgFile *mf) {

#define MAX_BLOCK_LEN (64000)

   char delimList[] = " \n\t\r=";
   char escape = '\\';
   char blockCharsListStart[] = "\"<({[";
   char blockCharsListEnd[] = "\">)}]";

   int delimLen = strlen(delimList);

   int blockCharsLen = strlen(blockCharsListStart);
   int bBlockCharOpen;
   int openBlockCharIndex;
   int openBlockCharLevel;
   int found;
   int j;

   static char blockStart[MAX_BLOCK_LEN];
   char *blockCurrPtr = NULL;
   char *blockEndPtr = NULL;

   if (mf->readLen >= mf->fileSize)
      return NULL ;

   if (mf->blen <= mf->boffset) {
      mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
      mf->boffset = 0;
      if (mf->blen <= 0)
         return NULL ;
   }
//printf("mf->blen: %d\n",mf->blen);
   found = 0;
   while (mf->boffset < mf->blen) {
      found = 0;
      for (j = 0; j < delimLen; j++) {
         if (delimList[j] == mf->buffer[mf->boffset]) {
            mf->boffset++;
            found = 1;
            break;
         }
      }

      if (!found)
         break;

      if (mf->blen <= mf->boffset) {
         mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
         mf->boffset = 0;
         if (mf->blen <= 0)
            return NULL ;
      }
   }
//printf("mf->blen: %d\n",mf->blen);
//printf("mf->boffset: %d\n",mf->boffset);
   blockCurrPtr = blockStart;
   blockEndPtr = blockStart + MAX_BLOCK_LEN;

   while (mf->boffset < mf->blen && blockCurrPtr < blockEndPtr) {
      //printf("mf->blen: %d\n",mf->blen);
      //printf("mf->boffset: %d\n",mf->boffset);
      for (j = 0; j < delimLen; j++) {
         if (delimList[j] == mf->buffer[mf->boffset]) {
            *blockCurrPtr = '\0';
            mf->boffset++;
            return blockStart;
         }
      }

      bBlockCharOpen = 0;
      for (j = 0; j < blockCharsLen; j++) {
         if (blockCharsListStart[j] == mf->buffer[mf->boffset]) {
            bBlockCharOpen = 1;
            openBlockCharIndex = j;
            *blockCurrPtr++ = mf->buffer[mf->boffset++];
            if (mf->blen <= mf->boffset) {
               mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
               mf->boffset = 0;
               if (mf->blen <= 0) {
                  *blockCurrPtr = '\0';
                  return blockStart;
               }
            }
            break;
         }
      }

      if (bBlockCharOpen) {

         openBlockCharLevel = 1;

         while (mf->boffset < mf->blen && blockCurrPtr < blockEndPtr) {
            //printf("mf->blens: %d\n",mf->blen);
            //printf("mf->boffsets: %d\n",mf->boffset);

            if (escape != mf->buffer[mf->boffset]) {
               if (blockCharsListEnd[openBlockCharIndex] == mf->buffer[mf->boffset]) {
                  openBlockCharLevel--;
                  *blockCurrPtr++ = mf->buffer[mf->boffset++];
                  if (mf->blen <= mf->boffset) {
                     mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
                     mf->boffset = 0;
                     if (mf->blen <= 0) {
                        *blockCurrPtr = '\0';
                        return blockStart;
                     }
                  }
                  if (openBlockCharLevel <= 0) {
                     break;
                  }
               } else if (blockCharsListStart[openBlockCharIndex] == mf->buffer[mf->boffset]) {
                  openBlockCharLevel++;
                  *blockCurrPtr++ = mf->buffer[mf->boffset++];
                  if (mf->blen <= mf->boffset) {
                     mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
                     mf->boffset = 0;
                     if (mf->blen <= 0) {
                        *blockCurrPtr = '\0';
                        return blockStart;
                     }
                  }
               } else {
                  *blockCurrPtr++ = mf->buffer[mf->boffset++];
                  if (mf->blen <= mf->boffset) {
                     mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
                     mf->boffset = 0;
                     if (mf->blen <= 0) {
                        *blockCurrPtr = '\0';
                        return blockStart;
                     }
                  }
               }
            } else {
               *blockCurrPtr++ = mf->buffer[mf->boffset++];
               if (mf->blen <= mf->boffset) {
                  mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
                  mf->boffset = 0;
                  if (mf->blen <= 0) {
                     *blockCurrPtr = '\0';
                     return blockStart;
                  }
               }
               *blockCurrPtr++ = mf->buffer[mf->boffset++];
            }
            if (mf->blen <= mf->boffset) {
               mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
               mf->boffset = 0;
               if (mf->blen <= 0) {
                  *blockCurrPtr = '\0';
                  return blockStart;
               }
            }
         }
         bBlockCharOpen = 0;
      } else {
         *blockCurrPtr++ = mf->buffer[mf->boffset++];
         if (mf->blen <= mf->boffset) {
            mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
            mf->boffset = 0;
            if (mf->blen <= 0) {
               *blockCurrPtr = '\0';
               return blockStart;
            }
         }
      }
   }
   if (blockCurrPtr != blockStart) {
      *blockCurrPtr = '\0';
      //printf("%s\n",blockStart);
      return blockStart;
   } else
      return NULL ;

}

char* getNextBlock(MsgFile *mf) {

#define MAX_BLOCK_LEN (64000)

   char delimList[] = " \n\t\r=";
   char escape = '\\';
   char blockCharsListStart[] = "\"<({[";
   char blockCharsListEnd[] = "\">)}]";

   int delimLen = strlen(delimList);

   int blockCharsLen = strlen(blockCharsListStart);
   int bBlockCharOpen;
   int openBlockCharIndex;
   int openBlockCharLevel;
   int found;
   int j;

   static char blockStart[MAX_BLOCK_LEN];
   char *blockCurrPtr = NULL;
   char *blockEndPtr = NULL;

   if (mf->readLen >= mf->fileSize)
      return NULL ;

   if (mf->blen <= mf->boffset) {
      mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
      mf->boffset = 0;
      if (mf->blen <= 0)
         return NULL ;
   }
//printf("mf->blen: %d\n",mf->blen);
   found = 0;
   while (mf->boffset < mf->blen) {
      found = 0;
      for (j = 0; j < delimLen; j++) {
         if (delimList[j] == mf->buffer[mf->boffset]) {
            mf->boffset++;
            found = 1;
            break;
         }
      }

      if (!found)
         break;

      if (mf->blen <= mf->boffset) {
         mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
         mf->boffset = 0;
         if (mf->blen <= 0)
            return NULL ;
      }
   }
//printf("mf->blen: %d\n",mf->blen);
//printf("mf->boffset: %d\n",mf->boffset);
   blockCurrPtr = blockStart;
   blockEndPtr = blockStart + MAX_BLOCK_LEN;

   while (mf->boffset < mf->blen && blockCurrPtr < blockEndPtr) {
      //printf("mf->blen: %d\n",mf->blen);
      //printf("mf->boffset: %d\n",mf->boffset);
      for (j = 0; j < delimLen; j++) {
         if (delimList[j] == mf->buffer[mf->boffset]) {
            *blockCurrPtr = '\0';
            mf->boffset++;
            return blockStart;
         }
      }

      bBlockCharOpen = 0;
      for (j = 0; j < blockCharsLen; j++) {
         if (blockCharsListStart[j] == mf->buffer[mf->boffset]) {
            bBlockCharOpen = 1;
            openBlockCharIndex = j;
            *blockCurrPtr++ = mf->buffer[mf->boffset++];
            if (mf->blen <= mf->boffset) {
               mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
               mf->boffset = 0;
               if (mf->blen <= 0) {
                  *blockCurrPtr = '\0';
                  return blockStart;
               }
            }
            break;
         }
      }

      if (bBlockCharOpen) {

         openBlockCharLevel = 1;

         while (mf->boffset < mf->blen && blockCurrPtr < blockEndPtr) {
            //printf("mf->blens: %d\n",mf->blen);
            //printf("mf->boffsets: %d\n",mf->boffset);

            if (escape != mf->buffer[mf->boffset]) {
               if (blockCharsListEnd[openBlockCharIndex] == mf->buffer[mf->boffset]) {
                  openBlockCharLevel--;
                  *blockCurrPtr++ = mf->buffer[mf->boffset++];
                  if (mf->blen <= mf->boffset) {
                     mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
                     mf->boffset = 0;
                     if (mf->blen <= 0) {
                        *blockCurrPtr = '\0';
                        return blockStart;
                     }
                  }
                  if (openBlockCharLevel <= 0) {
                     break;
                  }
               } else if (blockCharsListStart[openBlockCharIndex] == mf->buffer[mf->boffset]) {
                  openBlockCharLevel++;
                  *blockCurrPtr++ = mf->buffer[mf->boffset++];
                  if (mf->blen <= mf->boffset) {
                     mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
                     mf->boffset = 0;
                     if (mf->blen <= 0) {
                        *blockCurrPtr = '\0';
                        return blockStart;
                     }
                  }
               } else {
                  *blockCurrPtr++ = mf->buffer[mf->boffset++];
                  if (mf->blen <= mf->boffset) {
                     mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
                     mf->boffset = 0;
                     if (mf->blen <= 0) {
                        *blockCurrPtr = '\0';
                        return blockStart;
                     }
                  }
               }
            } else {
               *blockCurrPtr++ = mf->buffer[mf->boffset++];
               if (mf->blen <= mf->boffset) {
                  mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
                  mf->boffset = 0;
                  if (mf->blen <= 0) {
                     *blockCurrPtr = '\0';
                     return blockStart;
                  }
               }
               *blockCurrPtr++ = mf->buffer[mf->boffset++];
            }
            if (mf->blen <= mf->boffset) {
               mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
               mf->boffset = 0;
               if (mf->blen <= 0) {
                  *blockCurrPtr = '\0';
                  return blockStart;
               }
            }
         }
         bBlockCharOpen = 0;
      } else {
         *blockCurrPtr++ = mf->buffer[mf->boffset++];
         if (mf->blen <= mf->boffset) {
            mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
            mf->boffset = 0;
            if (mf->blen <= 0) {
               *blockCurrPtr = '\0';
               return blockStart;
            }
         }
      }
   }
   if (blockCurrPtr != blockStart) {
      *blockCurrPtr = '\0';
      //printf("%s\n",blockStart);
      return blockStart;
   } else
      return NULL ;

}

void free_feature(Feature *feature) {
   if (feature == NULL )
      return;
   //printf("message->feature(free_name): %s:%d\n",feature->name, strlen(feature->name));
   if (feature->name)
      free(feature->name);
   //printf("message->feature(free valu): %s:%d\n",feature->value, strlen(feature->value));
   if (feature->value)
      free(feature->value);
   //printf("message->feature(free)\n");
   free(feature);
}
void free_field(Field *field) {
   if (field == NULL )
      return;
   while (field->firstFeature != NULL ) {
      Feature *feature = field->firstFeature;
      field->firstFeature = field->firstFeature->next;
      free_feature(feature);
   }
   free(field);
}
void free_message(Message *message) {
   if (message == NULL )
      return;
   while (message->firstFeature != NULL ) {

      Feature *feature = message->firstFeature;
      message->firstFeature = message->firstFeature->next;
      free_feature(feature);
   }
   while (message->firstField != NULL ) {
      Field *field = message->firstField;
      message->firstField = message->firstField->next;
      free_field(field);
   }
   free(message);
}
void free_message_list(MessageList *ml) {
   if (ml == NULL )
      return;
   while (ml->firstMessage != NULL ) {
      Message *message = ml->firstMessage;
      ml->firstMessage = ml->firstMessage->next;
      free_message(message);
   }
   free(ml);
}
void print_feature(char *ident, Feature *feature) {
   if (feature == NULL )
      return;
   if (feature->name)
      printf("%sNAME=%s\n", ident, feature->name);
   if (feature->value)
      printf("%sVALUE=%s\n", ident, feature->value);
   ;
}
char* find_feature(char *text, Feature *feature) {
   static char empty[] = "null";
   while (feature != NULL ) {
      //printf("%s ? %s\n",text,feature->name);
      if (strcmp(text, feature->name) == 0)
         return feature->value;
      feature = feature->next;
   }
   return NULL ;
}
void print_field(char *ident, Field *field) {
   if (field == NULL )
      return;
   Feature *feature = field->firstFeature;
   while (feature != NULL ) {
      print_feature(ident, feature);
      feature = feature->next;
   }
}
char* clear_lfcr(char *text) {
   char *dest;
   char *head;
   head = dest = text;
   while (*text) {
      if (*text != '\n' && *text != '\r') {
         *dest = *text;
         dest++;
      }
      text++;
   }
   *dest = 0;
   return head;
}
int compare_incase_sensitive(char *text, char *searchText) {
   char *tb = text;
   char *st = searchText;
   while (*text && *searchText) {
      if (tolower(*text) > tolower(*searchText))
         return 1;
      if (tolower(*text) < tolower(*searchText))
         return -1;
      text++;
      searchText++;
   }
   if (tolower(*text) > tolower(*searchText)) {
      //printf("%s ?= %s\n", tb, st);
      return 1;
   }
   if (tolower(*text) < tolower(*searchText)) {
      //printf("%s ?= %s\n", tb, st);
      return -1;
   }
   return 0;
}
char* toupper_text(char *text) {
   char *head = text;
   while (*text) {
      *text = toupper(*text);
      text++;
   }
   return head;
}
char* tolower_text(char *text) {
   char *head = text;
   while (*text) {
      *text = tolower(*text);
      text++;
   }
   return head;
}
char* clear_whitespacesWithCamelNotation(char *text) {
   char *dest = text;
   char *head = text;
   int toUpper = 0;
   while (*text) {
      if (isalnum(*text) || *text == '_') {
         if (toUpper)
            *text = toupper(*text);
         *dest = *text;
         dest++;
         toUpper = 0;
      } else {
         toUpper = 1;
      }
      text++;
   }
   *dest = 0;
   return head;
}
char* clear_typeName(char *dest, char *text) {
   char *head = dest;
   char *textBegin = text;
   int toUpper = 0;

   while (*text && *text != '_')
      text++;

   if (!*text)
      text = textBegin;

   while (*text) {
      if (isalnum(*text)) {
         if (toUpper)
            *dest = toupper(*text);
         else
            *dest = tolower(*text);
         toUpper = 0;
         dest++;
      } else {
         toUpper = 1;
      }
      text++;
   }
   *dest = 0;
   return head;
}
char* clear_typeNameFirstUpper(char *dest, char *text) {
   char *head = dest;
   int toUpper = 1;
   while (*text) {
      if (isalnum(*text)) {
         if (toUpper)
            *dest = toupper(*text);
         else
            *dest = *text;
         toUpper = 0;
         dest++;
      } else {
         toUpper = 1;
      }
      text++;
   }
   *dest = 0;
   return head;
}
void fout_field(char *ident, Field *field, FILE* fp) {
   if (field == NULL )
      return;

   Feature *feature = field->firstFeature;
   char *name = find_feature("name", feature);
   char *mandatory = find_feature("mandatory", feature);
   char *length = find_feature("length", feature);
   char *description = find_feature("description", feature);
   if (length && name) {
      if (compare_incase_sensitive("char", length) != 0)
         fprintf(fp, "%schar ac_%s [%s];//", ident, clear_whitespacesWithCamelNotation(name),
               clear_whitespacesWithCamelNotation(length));
      else
         fprintf(fp, "%schar c_%s;//", ident, clear_whitespacesWithCamelNotation(name));

      if (description)
         fprintf(fp, "%s\n", clear_lfcr(description));
      else
         fprintf(fp, "DESCRIPTION: NULL\n");
   } else {
      fprintf(fp, "%s// :", ident);
      if (name)
         fprintf(fp, "name=%s;", clear_whitespacesWithCamelNotation(name));
      else
         fprintf(fp, "name=NULL;");
      if (length)
         fprintf(fp, "length=%s;", clear_whitespacesWithCamelNotation(length));
      else
         fprintf(fp, "length=NULL;");
      fprintf(fp, "\n");
   }
   return;
   while (feature != NULL ) {
      print_feature(ident, feature);
      feature = feature->next;
   }
}
void fout_class_addfields(char *ident, Field *field, FILE* fp) {
   if (field == NULL )
      return;
   char typeName[256];
   Feature *feature = field->firstFeature;
   char *name = find_feature("name", feature);
   char *mandatory = find_feature("mandatory", feature);
   char *length = find_feature("length", feature);
   char *description = find_feature("description", feature);
   if (length && name) {

      if (compare_incase_sensitive("char", length) != 0) {

         fprintf(fp, "%sFIELDDEFS::%sField m_%s;\n", ident,
               clear_typeName(typeName, clear_whitespacesWithCamelNotation(length)),
               clear_whitespacesWithCamelNotation(name));
         fprintf(fp, "%s//char ac_%s [%s];\n", ident, clear_whitespacesWithCamelNotation(name),
               clear_whitespacesWithCamelNotation(length));
      } else
         fprintf(fp, "%sFIELDDEFS::ByteField m_%s;\n", ident,
               clear_whitespacesWithCamelNotation(name));

      //if (description)
      //   fprintf(fp, "%s\n", clear_lfcr(description));
      //else
      //   fprintf(fp, "DESCRIPTION: NULL\n");
   } else {
      fprintf(fp, "%s// :", ident);
      if (name)
         fprintf(fp, "name=%s;", clear_whitespacesWithCamelNotation(name));
      else
         fprintf(fp, "name=NULL;");
      if (length)
         fprintf(fp, "length=%s;", clear_whitespacesWithCamelNotation(length));
      else
         fprintf(fp, "length=NULL;");
      fprintf(fp, "\n");
   }
   return;
}
void fout_class_set_func_writefields(char *ident, Field *field, FILE* fp) {
   if (field == NULL )
      return;
   char typeName[256];
   Feature *feature = field->firstFeature;
   char *name = find_feature("name", feature);
   char *mandatory = find_feature("mandatory", feature);
   char *length = find_feature("length", feature);
   char *description = find_feature("description", feature);
   if (length && name) {

      if (compare_incase_sensitive("char", length) != 0) {

         fprintf(fp, "%s  m_%s.setString(data.ac_%s);\n", ident,
               clear_whitespacesWithCamelNotation(name), clear_whitespacesWithCamelNotation(name));
      } else
         fprintf(fp, "%s  m_%s.setString((char*)&data.c_%s);\n", ident,
               clear_whitespacesWithCamelNotation(name), clear_whitespacesWithCamelNotation(name));

      //if (description)
      //   fprintf(fp, "%s\n", clear_lfcr(description));
      //else
      //   fprintf(fp, "DESCRIPTION: NULL\n");
   } else {
      fprintf(fp, "%s// :", ident);
      if (name)
         fprintf(fp, "name=%s;", clear_whitespacesWithCamelNotation(name));
      else
         fprintf(fp, "name=NULL;");
      if (length)
         fprintf(fp, "length=%s;", clear_whitespacesWithCamelNotation(length));
      else
         fprintf(fp, "length=NULL;");
      fprintf(fp, "\n");
   }
   return;
}
void fout_class_set_fieldtofield(char *ident, Field *field, FILE* fp) {
   if (field == NULL )
      return;
   Feature *feature = field->firstFeature;
   char *name = find_feature("name", feature);
   if (name) {
         fprintf(fp, "%sm_%s = m.m_%s;\n", ident,clear_whitespacesWithCamelNotation(name),clear_whitespacesWithCamelNotation(name));

   }
   return;
}
void fout_class_fill_func_writefields(char *ident, Field *field, FILE* fp) {
   if (field == NULL )
      return;
   char typeName[256];
   Feature *feature = field->firstFeature;
   char *name = find_feature("name", feature);
   char *mandatory = find_feature("mandatory", feature);
   char *length = find_feature("length", feature);
   char *description = find_feature("description", feature);
   if (length && name) {

      if (compare_incase_sensitive("char", length) != 0) {

         fprintf(fp, "%s  if(m_%s.isUpdated())\n"
               "      m_%s.fillField(m_messageData.ac_%s);\n", ident,
               clear_whitespacesWithCamelNotation(name), clear_whitespacesWithCamelNotation(name),
               clear_whitespacesWithCamelNotation(name));
      } else

         fprintf(fp, "%s  if(m_%s.isUpdated())\n"
               "      m_%s.fillField((char*)&m_messageData.c_%s);\n", ident,
               clear_whitespacesWithCamelNotation(name), clear_whitespacesWithCamelNotation(name),
               clear_whitespacesWithCamelNotation(name));
      //if (description)
      //   fprintf(fp, "%s\n", clear_lfcr(description));
      //else
      //   fprintf(fp, "DESCRIPTION: NULL\n");
   } else {
      fprintf(fp, "%s// :", ident);
      if (name)
         fprintf(fp, "name=%s;", clear_whitespacesWithCamelNotation(name));
      else
         fprintf(fp, "name=NULL;");
      if (length)
         fprintf(fp, "length=%s;", clear_whitespacesWithCamelNotation(length));
      else
         fprintf(fp, "length=NULL;");
      fprintf(fp, "\n");
   }
   return;
}
void fout_class_print_func_writefields(char *ident, Field *field, FILE* fp) {
   if (field == NULL )
      return;
   char typeName[256];
   Feature *feature = field->firstFeature;
   char *name = find_feature("name", feature);
   char *mandatory = find_feature("mandatory", feature);
   char *length = find_feature("length", feature);
   char *description = find_feature("description", feature);
   if (length && name) {

      if (compare_incase_sensitive("char", length) != 0) {

         fprintf(fp, "%s  std::cout << \"%s:\" << m_%s;\n", ident,
               clear_whitespacesWithCamelNotation(name), clear_whitespacesWithCamelNotation(name));
      } else

         fprintf(fp, "%s  std::cout << \"%s:\" << m_%s;\n", ident,
               clear_whitespacesWithCamelNotation(name), clear_whitespacesWithCamelNotation(name));
   } else {
      fprintf(fp, "%s// :", ident);
      if (name)
         fprintf(fp, "name=%s;", clear_whitespacesWithCamelNotation(name));
      else
         fprintf(fp, "name=NULL;");
      if (length)
         fprintf(fp, "length=%s;", clear_whitespacesWithCamelNotation(length));
      else
         fprintf(fp, "length=NULL;");
      fprintf(fp, "\n");
   }
   return;
}

void fout_class_getter_setter_func_writefields(char *ident, Field *field, FILE* fp) {
   if (field == NULL )
      return;
   //clear_typeNameFirstUpper
   char typeName[256];
   char funcName[256];
   Feature *feature = field->firstFeature;
   char *name = find_feature("name", feature);
   char *mandatory = find_feature("mandatory", feature);
   char *length = find_feature("length", feature);
   char *description = find_feature("description", feature);
   if (length && name) {

      if (compare_incase_sensitive("char", length) != 0) {
         clear_typeNameFirstUpper(funcName, clear_whitespacesWithCamelNotation(name));
         clear_typeName(typeName, clear_whitespacesWithCamelNotation(length));

         fprintf(fp, "%svoid setf%s(MSG::FIELDDEFS::%sField& value){\n", ident, funcName, typeName);
         fprintf(fp, "%s   m_%s.setString(value.getString());\n", ident,
               clear_whitespacesWithCamelNotation(name));
         fprintf(fp, "%s}\n", ident);

         fprintf(fp, "%svoid setf%s(std::string value){\n", ident, funcName);
         fprintf(fp, "%s   m_%s.setString(value);\n", ident,
               clear_whitespacesWithCamelNotation(name));
         fprintf(fp, "%s}\n", ident);

         fprintf(fp, "%sFIELDDEFS::%sField& getf%s(){\n", ident, typeName, funcName);
         fprintf(fp, "%s   return m_%s;\n", ident, clear_whitespacesWithCamelNotation(name));
         fprintf(fp, "%s}\n", ident);
      } else {

         clear_typeNameFirstUpper(funcName, clear_whitespacesWithCamelNotation(name));
         //clear_typeName(typeName, clear_whitespacesWithCamelNotation(length));

         fprintf(fp, "%svoid setf%s(MSG::FIELDDEFS::ByteField& value){\n", ident, funcName);
         fprintf(fp, "%s   m_%s.setString(value.getString());\n", ident,
               clear_whitespacesWithCamelNotation(name));
         fprintf(fp, "%s}\n", ident);

         fprintf(fp, "%svoid setf%s(std::string value){\n", ident, funcName);
         fprintf(fp, "%s   m_%s.setString(value);\n", ident,
               clear_whitespacesWithCamelNotation(name));
         fprintf(fp, "%s}\n", ident);

         fprintf(fp, "%sMSG::FIELDDEFS::ByteField& getf%s(){\n", ident, funcName);
         fprintf(fp, "%s   return m_%s;\n", ident, clear_whitespacesWithCamelNotation(name));
         fprintf(fp, "%s}\n", ident);
      }
   } else {
      fprintf(fp, "%s// :", ident);
      if (name)
         fprintf(fp, "name=%s;", clear_whitespacesWithCamelNotation(name));
      else
         fprintf(fp, "name=NULL;");
      if (length)
         fprintf(fp, "length=%s;", clear_whitespacesWithCamelNotation(length));
      else
         fprintf(fp, "length=NULL;");
      fprintf(fp, "\n");
   }
   return;
}
void fout_class_constructor_write_init_fields(char *ident, Field *field, FILE* fp) {
   if (field == NULL )
      return;
   //clear_typeNameFirstUpper
   char typeName[256];
   char funcName[256];
   Feature *feature = field->firstFeature;
   char *name = find_feature("name", feature);
   char *mandatory = find_feature("mandatory", feature);
   char *length = find_feature("length", feature);
   char *description = find_feature("description", feature);
   if (name) {
      if (mandatory && search_keyword("Y", mandatory))
         fprintf(fp, "%sm_%s(true)", ident, clear_whitespacesWithCamelNotation(name));
      else
         fprintf(fp, "%sm_%s(false)", ident, clear_whitespacesWithCamelNotation(name));

      if (field->next)
         fprintf(fp, ",\n", ident, clear_whitespacesWithCamelNotation(name));
   }
   return;
}
void fout_fielddefs(char *ident, Field *field, FILE* fp) {
   static int err = 0;
   if (field == NULL )
      return;
   char typeName[256];
   Feature *feature = field->firstFeature;
   char *name = find_feature("name", feature);
   char *value = find_feature("value", feature);
   char *description = find_feature("description", feature);
   if (value && name) {
      fprintf(fp, "#ifndef %-30s\n", clear_whitespacesWithCamelNotation(name));
      fprintf(fp, "%s#define %-30s %-24s\n%s//<%s>", ident,
            clear_whitespacesWithCamelNotation(name), value, ident, clear_typeName(typeName, name));
      if (description)
         fprintf(fp, "%-10s\n", clear_lfcr(description));
      else
         fprintf(fp, "DESCRIPTION: NULL\n");
      fprintf(fp, "#endif\n");
   } else {
      fprintf(fp, "/*DEFINE ERROR %d*/\n", err++);
   }
}
void fout_defineFieldsTypes(char *ident, Field *field, FILE* fp) {
   static int err = 0;
   int numeric = 0;
   if (field == NULL )
      return;
   char typeName[256];
   Feature *feature = field->firstFeature;
   char *name = find_feature("name", feature);
   char *value = find_feature("value", feature);
   char *description = find_feature("description", feature);
   if (value && name) {
      fprintf(fp, "#ifdef %s\n", clear_whitespacesWithCamelNotation(name));
      //fprintf(fp, "#ifndef %sField\n", clear_typeName(typeName, name));
      if (description)
         numeric = search_keyword("SAYISALDEGER", description);
      if (numeric)
         fprintf(fp, "%sVIOP_DEFINE_NUMFIELD(%s, %s);\n", ident, clear_typeName(typeName, name),
               clear_whitespacesWithCamelNotation(name));
      else
         fprintf(fp, "%sVIOP_DEFINE_CHARFIELD(%s, %s);\n", ident, clear_typeName(typeName, name),
               clear_whitespacesWithCamelNotation(name));
      //fprintf(fp, "#endif\n");
      fprintf(fp, "#endif\n");
   } else {
      fprintf(fp, "/*DEFINE ERROR %d*/\n", err++);
   }
}
void print_message(Message *message) {
   if (message == NULL )
      return;
   Feature *feature = message->firstFeature;
   while (feature != NULL ) {
      print_feature("  ", feature);
      feature = feature->next;
   }
   Field *field = message->firstField;
   while (field != NULL ) {
      printf("\n");
      print_field("    ", field);
      field = field->next;
   }
}
void clear_classname(char *classname) {
   char *dest = classname;
   int toUpper = 0;
   while (*classname) {
      if (isalnum(*classname)) {
         if (toUpper)
            *classname = toupper(*classname);
         *dest = *classname;
         dest++;
         toUpper = 0;
      } else {
         toUpper = 1;
      }
      classname++;
   }
   *dest = 0;
}
void clear_messagetype(char *classname, char *messageType, char *category, char *reqrep) {
   int strLen;
   char *dest = messageType;

   while (*messageType) {
      if (isalnum(*messageType) || *messageType == '_') {
         *dest = *messageType;
         dest++;
      } else
         break;
      messageType++;
   }
   classname = classname + strlen(classname) - 1;
   if (strcmp(category, "Query") == 0) {
      if (strcmp(reqrep, "Request") == 0) {
         *dest = 'Q';
         *(classname++) = 'R';
         *(classname++) = 'e';
         *(classname++) = 'q';
         *(classname++) = 'u';
         *(classname++) = 'e';
         *(classname++) = 's';
         *(classname++) = 't';
         *(classname) = 0;

      } else {
         *dest = 'P';
         *(classname++) = 'R';
         *(classname++) = 'e';
         *(classname++) = 'p';
         *(classname++) = 'l';
         *(classname++) = 'y';
         *(classname) = 0;
      }
      dest++;
   }
   *dest = 0;
}
void clear_rightNonAlfaNum(char *text) {
   char *dest = text;

   while (*text) {
      if (isalnum(*text) || *text == '_') {
         *dest = *text;
         dest++;
      } else
         break;
      text++;
   }
   *dest = 0;
}

char* get_namespace(char *dest, Message *message) {
   char *category = find_feature("category", message->firstFeature);
   if (category)
      strcpy(dest, category);
   else
      sprintf(dest, "NULLNAMESPACE");
   return toupper_text(dest);
}
char* get_baseclass(char *dest, Message *message) {
   char *requestReplyType = find_feature("requestReplyType", message->firstFeature);
   if (requestReplyType) {
      if (compare_incase_sensitive("request", requestReplyType) == 0)
         sprintf(dest, "VIOP::RequestMessageBase");
      else if (compare_incase_sensitive("reply", requestReplyType) == 0)
         sprintf(dest, "VIOP::ReplyMessageBase");
   } else
      sprintf(dest, "/*BASE_CLASS_ERROR_UNKNOWN_REQUEST_REPLY_TYPE*/");
   return dest;
}
#define NSPACE_MAX 500
#define NCLASS_MAX 500

int isClassDefined(char spaceList[][NSPACE_MAX], char classList[][NCLASS_MAX], int lcnt,
      char *spaceName, char *className) {
   int i;
   for (i = 0; i < lcnt; i++) {
      if (compare_incase_sensitive(spaceName, spaceList[i]) == 0
            && compare_incase_sensitive(className, classList[i]) == 0)
         return 1;
   }

   return 0;
}
char* get_classname(char *dest, Message *message) {
   static int err = 0;
   char *className = find_feature("classname", message->firstFeature);
   char *category = find_feature("category", message->firstFeature);
   char *requestReplyType = find_feature("requestReplyType", message->firstFeature);
   //char *messagetype = find_feature("messagetype", message->firstFeature);
   //char *operatorMsgType = find_feature("operatorMsgType",
   //      message->firstFeature);
   char *replyIndex = find_feature("replyIndex", message->firstFeature);
   //char *deff_error = find_feature("deff_error", message->firstFeature);
   int sindex = 0;
   if (className) {
      clear_whitespacesWithCamelNotation(className);
      sindex += sprintf(dest + sindex, "%s", className);
   } else
      sindex += sprintf(dest + sindex, "CLASS_NAME_ERROR_%d", err++);
   if (category) {
      if (compare_incase_sensitive("query", category) == 0) {
         if (requestReplyType) {
            if (compare_incase_sensitive("request", requestReplyType) == 0) {
               sindex += sprintf(dest + sindex, "Request");
            } else {
               if (replyIndex) {
                  if (compare_incase_sensitive("1", replyIndex) == 0) {
                     sindex += sprintf(dest + sindex, "Reply");
                  } else {
                     sindex += sprintf(dest + sindex, "Reply%s", replyIndex);
                  }
               } else {
                  sindex += sprintf(dest + sindex, "_REPLY_INDEX_ERROR_%d", err++);
               }
            }
         } else {
            sindex += sprintf(dest + sindex, "_QUERY_REPLY_REQUEST_TYPE_ERROR_%d", err++);
         }
      } else {
         sindex += sprintf(dest + sindex, "Request");
      }
   } else {
      sindex += sprintf(dest + sindex, "_CATEGORY_TYPE_ERROR_%d", err++);
   }
   return dest;
}
char* get_structname(char *dest, Message *message) {
   get_classname(dest, message);
   int slen = strlen(dest);
   sprintf(dest + slen, "_TAG");
   return dest;
}
char* get_messagetype(char *dest, Message *message, int *notOk) {
   static int err = 0;
   int sindex = 0;
   char *head = dest;
   char *messagetype = find_feature("messagetype", message->firstFeature);
   char *category = find_feature("category", message->firstFeature);
   char *requestReplyType = find_feature("requestReplyType", message->firstFeature);
   if (notOk)
      *notOk = 0;
   if (messagetype) {
      while (*messagetype) {
         if (isalnum(*messagetype) || *messagetype == '_') {
            *dest = *messagetype;
            dest++;
         } else if (*messagetype != ' ')
            break;
         messagetype++;
      }
      *dest = 0;
   } else {
      dest += sprintf(head, "MESSAGE_TYPE_ERROR_%d", err++);
      if (notOk)
         *notOk = 1;
   }
   if (category) {
      if (compare_incase_sensitive("query", category) == 0) {
         if (requestReplyType) {
            if (compare_incase_sensitive("request", requestReplyType) == 0) {
               sindex += sprintf(dest + sindex, "Q");
            } else {
               sindex += sprintf(dest + sindex, "P");
            }
         } else {
            sindex += sprintf(dest + sindex, "_QUERY_REPLY_REQUEST_TYPE_ERROR_%d", err++);
            if (notOk)
               *notOk = 1;
         }
      }
   } else {
      sindex += sprintf(dest + sindex, "_CATEGORY_TYPE_ERROR_%d", err++);
      if (notOk)
         *notOk = 1;
   }
   return head;
}
int get_isMessageRequest(Message *message) {
   char *messagetype = find_feature("messagetype", message->firstFeature);
   char *category = find_feature("category", message->firstFeature);
   char *requestReplyType = find_feature("requestReplyType", message->firstFeature);

   if (category) {
      if (compare_incase_sensitive("query", category) == 0) {
         if (requestReplyType) {
            if (compare_incase_sensitive("request", requestReplyType) == 0) {
               return 1;
            } else {
               return 0;
            }
         } else {
            return 0;
         }
      } else
         return 1;
   } else {
      return 0;
   }

}
char *get_operatortype(char *dest, Message *message) {
   static int err = 0;
   char *head = dest;
   char *messagetype = find_feature("operatorMsgType", message->firstFeature);
   if (messagetype) {
      while (*messagetype) {
         if (isalnum(*messagetype) || *messagetype == '_') {
            *dest = *messagetype;
            dest++;
         } else if (*messagetype != ' ')
            break;
         messagetype++;
      }
      *dest = 0;
   } else {
      dest += sprintf(head, "OPR_MESSAGE_TYPE_ERROR_%d", err++);
   }
   return head;
}
char *get_messageNumber(char *dest, char *messagetype) {
   static int err = 0;
   char *head = dest;
   if (messagetype) {
      while (*messagetype) {
         if (*messagetype == '(') {
            break;
         }
         messagetype++;
      }
      while (*messagetype) {
         if (isalnum(*messagetype)) {
            *dest = *messagetype;
            dest++;
         }
         messagetype++;
      }
      *dest = 0;
   } else {
      dest += sprintf(head, "-1 /*ERROR_MSG_NUMBER_%d*/", err++);
   }
   return head;
}
char *get_operatorMessageTypeNumber(char *dest, Message *message) {
   return get_messageNumber(dest, find_feature("operatorMsgType", message->firstFeature));
}
char *get_messageTypeNumber(char *dest, Message *message) {
   return get_messageNumber(dest, find_feature("messagetype", message->firstFeature));
}
int is_operatortype(Message *message) {
   char *messagetype = find_feature("operatorMsgType", message->firstFeature);
   if (messagetype) {
      return 1;
   } else {
      return 0;
   }
}

#define NAME_LIST_SIZE 1000
char nameSpaceList[NAME_LIST_SIZE][NSPACE_MAX];
char classNameList[NAME_LIST_SIZE][NCLASS_MAX];
char classTypeList[NAME_LIST_SIZE][NCLASS_MAX];

int is_class_duzenlenecek(char *text) {
#define HATA_KEY_WORD_NUM 4
   static char _hatali_word_arama_[HATA_KEY_WORD_NUM][100] = { "DYNAMIC", "DUZENLE", "KONTROL",
         "RAMAZAN" };
   int i;
   for (i = 0; i < HATA_KEY_WORD_NUM; i++) {
      if (search_keyword(_hatali_word_arama_[i], text))
         return 1;
   }
   return 0;
}
int is_field_description_include_hata_belirteci(char *ident, Field *field, FILE* fp) {
   if (field == NULL )
      return 0;
   Feature *feature = field->firstFeature;
   char *description = find_feature("description", feature);
   if (description) {
      if (is_class_duzenlenecek(description))
         return 1;
   }
   return 0;
}
void fout_message2(Message *message, FILE *fph, FILE *fpcpp, char *namespace) {
#define LBUF_LEN 256
   static int lcnt = 0;
   static int rdcnt = 0;
   int hata_belirten_kelime_var = 0;
   static int hata_belirten_kelime_var_adet = 0;
   char UYARI[LBUF_LEN] = "";
   if (message == NULL )
      return;

   char nameSpace[LBUF_LEN];
   Feature *feature = message->firstFeature;
   char className[LBUF_LEN];
   char structName[LBUF_LEN];
   char baseClass[LBUF_LEN];
   char messageType[LBUF_LEN];
   char operatorType[LBUF_LEN];
   char classTypeName[LBUF_LEN];
   int isOperator;
   int isSructEmpty = 0;
   int isMsgTypeNotOk;

   char *deff_error = find_feature("deff_error", feature);
   char *requestReplyType = find_feature("requestReplyType", feature);
   if (deff_error) {
      printf("ERROR: deff_error FOUND\n");
      return;
   }
   get_namespace(nameSpace, message);
   if (compare_incase_sensitive(namespace, nameSpace) != 0)
      return;

   get_classname(className, message);
   get_structname(structName, message);
   get_baseclass(baseClass, message);
   get_messagetype(messageType, message, &isMsgTypeNotOk);
   if (isMsgTypeNotOk) {
      printf("Class declaretion failure: MSG_TYPE_NOT_SET\n");
      return;
   }
   get_operatortype(operatorType, message);
   isOperator = is_operatortype(message);
   if (isClassDefined(nameSpaceList, classNameList, lcnt, nameSpace, className)) {
      sprintf(className + strlen(className), "_redef%d", rdcnt);
      sprintf(structName + strlen(structName), "_redef%d", rdcnt);
      rdcnt++;
   }

   sprintf(nameSpaceList[lcnt], "%s", nameSpace);
   sprintf(classNameList[lcnt], "%s", className);

   if (isOperator)
      clear_typeName(classTypeName, operatorType);
   else
      clear_typeName(classTypeName, messageType);

   if (isClassDefined(nameSpaceList, classTypeList, lcnt, nameSpace, classTypeName)) {
      sprintf(classTypeName + strlen(classTypeName), "_redef%d", rdcnt);
      rdcnt++;
   }

   sprintf(classTypeList[lcnt], "%s", classTypeName);
   lcnt++;
   isSructEmpty = 0;
   Field *field = message->firstField;
   if (field == NULL ) {
      isSructEmpty = 1;
   }
   hata_belirten_kelime_var = 0;

   field = message->firstField;
   while (field != NULL ) {
      if (is_field_description_include_hata_belirteci("  ", field, fph)) {
         hata_belirten_kelime_var = 1;
         break;
      }
      field = field->next;
   }
   if (hata_belirten_kelime_var) {
      fprintf(fph, "namespace GOZDENGECIR\n{\n");
      fprintf(fph, "\n/////////////////////////////////////////////////////////////////////\n"
            "// DIKKAT_BU_CLASS_GOZDEN_GECIRILECEK(START_OF_%d)!!!\n"
            "/////////////////////////////////////////////////////////////////////\n",
            ++hata_belirten_kelime_var_adet);
      sprintf(UYARI, "GOZDENGECIR::");
      printf("Duzenleme yalılacak namespace: %s className: %s, classType: %s %d\n", nameSpace,
            className, classTypeName, hata_belirten_kelime_var_adet);
   }
   if (!isSructEmpty) {
      fprintf(fph, "\n#pragma pack(1)\ntypedef struct { \n");

      field = message->firstField;
      while (field != NULL ) {
         fout_field("  ", field, fph);
         field = field->next;
      }

      fprintf(fph, "} %s ;\n", structName);
      fprintf(fph, "#pragma pack()\n\n");
      fprintf(fph, "namespace  STRUCTS\n{\n");
      fprintf(fph, "typedef %s %s;\n}\n", structName, classTypeName);
   }
   //
   fprintf(fph, "class %s : public %s { \n", className, baseClass);
   fprintf(fph, "public:\n");
   if (!isSructEmpty) {
      fprintf(fph, "  %s ( %s &messageData) /*m_messageData(messageData),*/\n", className,
            structName);
      fprintf(fph, "  :");

      fprintf(fph, " %s(%s),\n", baseClass, messageType);

      field = message->firstField;
      while (field != NULL ) {
         fout_class_constructor_write_init_fields("   ", field, fph);
         field = field->next;
      }
      fprintf(fph, "  {\n"
            "    set(messageData);\n"
            "  }\n");
   }
   //------------------------------------------------------------------------
   //0
   fprintf(fph, "  %s ()", className);

   fprintf(fph, ": %s(%s)", baseClass, messageType);
   if (message->firstField)
      fprintf(fph, ",\n");

   field = message->firstField;
   while (field != NULL ) {
      fout_class_constructor_write_init_fields("   ", field, fph);
      field = field->next;
   }

   fprintf(fph, "  {  }\n");
   //--------------------------------------------------------------------------
   //------------------------------------------------------------------------
   //0
   fprintf(fph, "  %s (char *data, int dlen)", className);

   fprintf(fph, ": %s(%s)", baseClass, messageType);
   if (message->firstField)
      fprintf(fph, ",\n");

   field = message->firstField;
   while (field != NULL ) {
      fout_class_constructor_write_init_fields("   ", field, fph);
      field = field->next;
   }

   //fprintf(fph, "  {  }\n");
   if(message->firstField)
   fprintf(fph, "\n"
            "  {\n"
            "    if(data != NULL && dlen == sizeof(%s)){\n"
            "      set(*((%s*)data));\n"
            "    }\n"
            "  }\n",structName,structName);
   else
   fprintf(fph, "  {  }\n");
   //--------------------------------------------------------------------------
   //------------------------------------------------------------------------
   //1
   fprintf(fph, "  %s (const TSMR::MessageBase&m)", className);

   fprintf(fph, ": %s(m)", baseClass);
   if (message->firstField)
      fprintf(fph, ",\n");

   field = message->firstField;
   while (field != NULL ) {
      fout_class_constructor_write_init_fields("   ", field, fph);
      field = field->next;
   }
   if(message->firstField)
   fprintf(fph, "\n"
         "  {\n"
         "    if(m.m_dataBuffer != NULL && m.m_dataLen == sizeof(%s)){\n"
         "      this->set(*((%s*)m.m_dataBuffer));\n"
         "    }\n"
         "  }\n",structName,structName);

   else
   fprintf(fph, "\n  {  }\n");
   //--------------------------------------------------------------------------
   //2
   if (get_isMessageRequest(message)) {
      fprintf(fph, "  %s (const TSMR::HostRequestMessage&m)\n", className);
   } else {
      fprintf(fph, "  %s (const TSMR::HostReplyMessage&m)\n", className);
   }

   fprintf(fph, ": %s(m)", baseClass);
   if (message->firstField)
       fprintf(fph, ",\n");

   field = message->firstField;
   while (field != NULL ) {
      fout_class_constructor_write_init_fields("   ", field, fph);
      field = field->next;
   }
   //fprintf(fph, "\n  {  }\n");
   if(message->firstField)
      fprintf(fph, "\n"
            "  {\n"
            "    if(m.m_dataBuffer != NULL && m.m_dataLen == sizeof(%s)){\n"
            "      this->set(*((%s*)m.m_dataBuffer));\n"
            "    }\n"
            "  }\n",structName,structName);

      else
      fprintf(fph, "\n  {  }\n");
   //--------------------------------------------------------------------------
   //3
   fprintf(fph, "  %s (const %s&m)\n", className, baseClass);

   fprintf(fph, ": %s(m)", baseClass);
   if (message->firstField)
       fprintf(fph, ",\n");

   field = message->firstField;
   while (field != NULL ) {
      fout_class_constructor_write_init_fields("   ", field, fph);
      field = field->next;
   }
   fprintf(fph, "\n  {  }\n");
   //--------------------------------------------------------------------------
   //4
   fprintf(fph, "  %s (const %s&m)\n", className, className);

   fprintf(fph, ": %s(m)", baseClass);
   if (message->firstField)
       fprintf(fph, "\n");

   fprintf(fph, "  {\n");
      field = message->firstField;
      while (field != NULL ) {
         fout_class_set_fieldtofield("    ", field, fph);
         field = field->next;
      }

      fprintf(fph, "  }\n");

/*
   field = message->firstField;
   while (field != NULL ) {
      fout_class_constructor_write_init_fields("   ", field, fph);
      field = field->next;
   }
   fprintf(fph, "\n  {  }\n");
   */
   //--------------------------------------------------------------------------

   //fprintf(fph, "  virtual ~%s(){}\n",className);
   /*
    ReplyMessageBase(int type = -1, int bufCapacity = -1, char *buffer = NULL,
    u_int32 clientRef = 0): TSMR::HostReplyMessage(type,bufCapacity,buffer,clientRef){}
    ReplyMessageBase(const TSMR::MessageBase&m): TSMR::HostReplyMessage(m){}
    ReplyMessageBase(const TSMR::HostReplyMessage&m): TSMR::HostReplyMessage(m){}
    ReplyMessageBase(const ReplyMessageBase&m): TSMR::HostReplyMessage(m){}
    */
   if (!isSructEmpty) {
      fprintf(fph, "public:\n"
            "   void set(%s &data){\n", structName);
      field = message->firstField;
      while (field != NULL ) {
         fout_class_set_func_writefields("  ", field, fph);
         field = field->next;
      }

      fprintf(fph, "  }\n");
   }
   if (!isSructEmpty) {
      fprintf(fph, "public:\n"
            "  virtual char *getDataRef(){\n"
            "    fillDataBuffer();\n"
            "    return (char*)&m_messageData;\n"
            "  }\n");
      fprintf(fph, "  virtual int getDataLength(){\n"
            "     return ( sizeof( %s ) );\n"
            "  }\n", structName);
   } else {
      fprintf(fph, "public:\n"
            "  virtual char *getDataRef(){\n"
            "    return (char*)NULL;\n"
            "  }\n");
      fprintf(fph, "  virtual int getDataLength(){\n"
            "     return (0);\n"
            "  }\n", structName);
   }

   fprintf(fph, "  virtual int getType(){\n"
         "    return m_messageType;\n"
         "  }\n");
   if (compare_incase_sensitive("transaction", nameSpace) == 0) {
      fprintf(fph, "  virtual bool isTransactionRequest(){\n"
            "    return true;\n"
            "  }\n");
   }
   if (compare_incase_sensitive("query", nameSpace) == 0) {
      if (requestReplyType) {
         if (compare_incase_sensitive("request", nameSpace) == 0)
            fprintf(fph, "  virtual bool isQueryRequest(){\n"
                  "    return true;\n"
                  "  }\n");
         else
            fprintf(fph, "  virtual bool isQueryReply(){\n"
                  "    return true;\n"
                  "  }\n");
      }
   }

   if (isOperator) {
      fprintf(fph, "  virtual bool isOperator(){\n"
            "    return true;\n"
            "  }\n");
      fprintf(fph, "  virtual int getOperatorType(){\n"
            "    return m_operatorMsgType;\n"
            "  }\n");
   }

   fprintf(fph, "  virtual std::string getMessageName(){\n"
         "    return \"<%s>\";\n"
         "  }\n", className);

   if (!isSructEmpty) {
      fprintf(fph, " void fillDataBuffer(){\n");
      field = message->firstField;
      while (field != NULL ) {
         fout_class_fill_func_writefields("  ", field, fph);
         field = field->next;
      }
      fprintf(fph, "  }\n");
   }

   fprintf(fph, "public:\n");
   field = message->firstField;
   while (field != NULL ) {
      fout_class_getter_setter_func_writefields("  ", field, fph);
      field = field->next;
   }

   fprintf(fph, "public:\n");
   if (!isSructEmpty) {
      fprintf(fph, " void print(){\n");
      field = message->firstField;
      while (field != NULL ) {
         fout_class_print_func_writefields("  ", field, fph);
         field = field->next;
      }
      fprintf(fph, "    std::cout << std::endl;\n"
            "  }\n");
   } else {
      fprintf(fph, " void print(){\n");
      if (isOperator)
         fprintf(fph, "    std::cout <<\"%s message type HAS_NO_FIELD\" << std::endl;\n",
               operatorType);
      else
         fprintf(fph, "    std::cout <<\"%s message type HAS_NO_FIELD\" << std::endl;\n",
               messageType);
      fprintf(fph, "  }\n");
   }

   fprintf(fph, "public:\n"
         "  static const int m_messageType;\n");

   fprintf(fpcpp, "const int %s%s::m_messageType = %s ; \n", UYARI, className, messageType);
   if (isOperator) {
      fprintf(fph, "  static const int m_operatorMsgType;\n");

      fprintf(fpcpp, "const int %s%s::m_operatorMsgType = %s ;\n", UYARI, className, operatorType);
   }
   if (!isSructEmpty) {
      fprintf(fph, "  %s m_messageData;\n"
            "\n", structName);
   } else {
      if (isOperator)
         printf("Class defined without any data field %s\n", operatorType);
      else
         printf("Class defined without any data field %s\n", messageType);
   }
//fout_class_addfields
   fprintf(fph, "  //MESSAGE_DETAIL_DEFS\n");
   field = message->firstField;
   while (field != NULL ) {
      fout_class_addfields("  ", field, fph);
      field = field->next;
   }
   fprintf(fph, "};\n");
   fprintf(fph, "namespace  CLASSES\n{\n");
   fprintf(fph, "typedef %s %s;\n}\n", className, classTypeName);

   if (hata_belirten_kelime_var) {
      fprintf(fph, "\n/////////////////////////////////////////////////////////////////////\n"
            "// DIKKAT_BU_CLASS_GOZDEN_GECIRILECEK(END_OF_%d)!!!\n"
            "/////////////////////////////////////////////////////////////////////\n",
            hata_belirten_kelime_var_adet);
      fprintf(fph, "}/*namespace GOZDENGECIR*/\n");
   }
   fflush(fph);
   fflush(fpcpp);

}
void fout_FieldDefs(Message *message, FILE *fph, char *namespace) {
   if (message == NULL )
      return;
#define LBUF_LEN 256
   char nameSpace[LBUF_LEN];
   Feature *feature = message->firstFeature;
   char className[LBUF_LEN];
   char structName[LBUF_LEN];
   char baseClass[LBUF_LEN];
   char messageType[LBUF_LEN];
   char operatorType[LBUF_LEN];
   int isOperator;
   char *deff_error = find_feature("deff_error", feature);

   if (deff_error) {
      printf("ERROR: deff_error FOUND\n");
      return;
   }
   get_namespace(nameSpace, message);
   if (compare_incase_sensitive(namespace, nameSpace) != 0)
      return;

   Field *field = message->firstField;
   while (field != NULL ) {
      fout_fielddefs("", field, fph);
      field = field->next;
   }
   fflush(fph);
}
void fout_defineFields(Message *message, FILE *fph, char *namespace) {
   if (message == NULL )
      return;
#define LBUF_LEN 256
   char nameSpace[LBUF_LEN];
   Feature *feature = message->firstFeature;
   char className[LBUF_LEN];
   char structName[LBUF_LEN];
   char baseClass[LBUF_LEN];
   char messageType[LBUF_LEN];
   char operatorType[LBUF_LEN];
   int isOperator;
   char *deff_error = find_feature("deff_error", feature);

   if (deff_error) {
      printf("ERROR: deff_error FOUND\n");
      return;
   }
   get_namespace(nameSpace, message);
   if (compare_incase_sensitive(namespace, nameSpace) != 0)
      return;

   Field *field = message->firstField;
   while (field != NULL ) {
      fout_defineFieldsTypes("", field, fph);
      field = field->next;
   }
   fflush(fph);
}
void fout_messageTypeDefs(Message *message, FILE *fph) {
   if (message == NULL )
      return;
#define LBUF_LEN 256
   char nameSpace[LBUF_LEN];
   Feature *feature = message->firstFeature;
   char className[LBUF_LEN];
   char structName[LBUF_LEN];
   char baseClass[LBUF_LEN];
   char messageType[LBUF_LEN];
   char messageTypeNumber[LBUF_LEN];
   char operatorType[LBUF_LEN];
   char operatorTypeNumber[LBUF_LEN];
   char typeName[LBUF_LEN];

   int isOperator;
   int isNotOk;
   static int operatorMsgTypePrinted = 0;
   char *deff_error = find_feature("deff_error", feature);
   char *replyIndex = find_feature("replyIndex", feature);

   if (deff_error) {
      printf("ERROR: deff_error FOUND\n");
      return;
   }
   if (replyIndex && compare_incase_sensitive("1", replyIndex) != 0)
      return;

   get_classname(className, message);
   get_structname(structName, message);
   get_baseclass(baseClass, message);
   get_messagetype(messageType, message, &isNotOk);
   get_messageTypeNumber(messageTypeNumber, message);
   get_operatortype(operatorType, message);
   get_operatorMessageTypeNumber(operatorTypeNumber, message);
   isOperator = is_operatortype(message);

   if (isNotOk) {
      printf("MSG_TYPE_isNotOk\n");
      return;
   }
   if (isOperator) {
      if (!operatorMsgTypePrinted) {
         fprintf(fph, "#ifndef %-50s\n", messageType);
         fprintf(fph, "#define %-50s %-10s //<%s>\n", messageType, messageTypeNumber,
               clear_typeName(typeName, messageType));
         fprintf(fph, "#endif\n");
      }
      operatorMsgTypePrinted = 1;

      fprintf(fph, "#ifndef %-50s\n", operatorType);
      fprintf(fph, "#define %-50s %-10s//<%s>\n", operatorType, operatorTypeNumber,
            clear_typeName(typeName, operatorType));
      fprintf(fph, "#endif\n");
   } else {
      fprintf(fph, "#ifndef %-50s\n", messageType);
      fprintf(fph, "#define %-50s %-10s//<%s>\n", messageType, messageTypeNumber,
            clear_typeName(typeName, messageType));
      fprintf(fph, "#endif\n");
   }
}
void print_message_list(MessageList *ml) {
   if (ml == NULL )
      return;
   Message *message = ml->firstMessage;
   while (message != NULL ) {
      print_message(message);
      message = message->next;
   }
}
void fout_message_list(MessageList *ml, FILE *fph, FILE *fpcpp, char *nspace) {
   if (ml == NULL )
      return;
   Message *message = ml->firstMessage;
   while (message != NULL ) {
      fout_message2(message, fph, fpcpp, nspace);
      message = message->next;
      //break;
   }
}

void fout_message_fiedldefs(MessageList *ml, FILE *fph, char *nspace) {
   if (ml == NULL )
      return;
   Message *message = ml->firstMessage;
   while (message != NULL ) {
      fout_FieldDefs(message, fph, nspace);
      message = message->next;
   }
}
void fout_message_definefields(MessageList *ml, FILE *fph, char *nspace) {
   if (ml == NULL )
      return;
   Message *message = ml->firstMessage;
   while (message != NULL ) {
      fout_defineFields(message, fph, nspace);
      message = message->next;
   }
}
void fout_message_list_types(MessageList *ml, FILE *fph) {
   if (ml == NULL )
      return;
   Message *message = ml->firstMessage;
   while (message != NULL ) {
      fout_messageTypeDefs(message, fph);
      message = message->next;
   }
}
Feature *get_feature(MsgFile *mf) {
   char *block;
   int err = 0;
   int len;
   Feature * feature = malloc(sizeof(Feature));
   if (feature == NULL )
      return NULL ;
   feature->next = NULL;
   while ((block = getNextBlock(mf)) != NULL ) {
      if (strcmp(block, "</feature>") == 0) {
         //printf("</feature>\n");
         break;
      } else if (strcmp(block, "name") == 0) {
         //printf("name=");
         block = getNextBlock(mf);
         if (block == NULL ) {
            err = 1;
            break;
         }
         //printf("%s\n",block);
         len = strlen(block);
         feature->name = malloc(sizeof(char) * len + 100);
         if (feature->name == NULL ) {
            err = 1;
            break;
         }
         memcpy(feature->name, block + 1, len + 1);
         feature->name[len - 2] = 0;
         if (len - 2 <= 0)
            sprintf(feature->name, "NULLSTRING");
      } else if (strcmp(block, "value") == 0) {
         //printf("value=");
         block = getNextBlock(mf);
         if (block == NULL ) {
            err = 1;
            break;
         }
         //printf("%s\n",block);
         len = strlen(block);
         feature->value = malloc(sizeof(char) * len + 100);
         if (feature->value == NULL ) {
            err = 1;
            break;
         }
         memcpy(feature->value, block + 1, len + 1);
         feature->value[len - 2] = 0;
         if (len - 2 <= 0)
            sprintf(feature->value, "NULLSTRING");
      } else {
         err = 1;
         break;
      }
   }
   if (err) {
      free_feature(feature);
      return NULL ;
   }
   return feature;
}
Field *get_field(MsgFile *mf) {
   char *block;
   int err = 0;

   Field *field = malloc(sizeof(Field));
   if (field == NULL )
      return NULL ;
   field->firstFeature = NULL;
   field->lastFeature = NULL;
   field->next = NULL;
   while ((block = getNextBlock(mf)) != NULL ) {
      if (strcmp(block, "</field>") == 0) {
         //printf("</field>\n");
         break;
      } else if (strcmp(block, "<feature>") == 0) {
         //printf("<feature>\n");
         if (field->lastFeature) {
            field->lastFeature->next = get_feature(mf);
            if (field->lastFeature->next == NULL ) {
               err = 1;
               break;
            }
            field->lastFeature = field->lastFeature->next;
         } else {
            field->firstFeature = field->lastFeature = get_feature(mf);
            if (field->lastFeature == NULL ) {
               err = 1;
               break;
            }
         }
      } else {
         err = 1;
         break;
      }
   }
   if (err) {
      free_field(field);
      return NULL ;
   }
   return field;
}

Message *get_message(MsgFile *mf) {
   char *block;
   int err = 0;

   Message *message = malloc(sizeof(Message));
   if (message == NULL )
      return NULL ;
   message->firstFeature = NULL;
   message->lastFeature = NULL;
   message->firstField = NULL;
   message->lastField = NULL;
   message->next = NULL;
   while ((block = getNextBlock(mf)) != NULL ) {

      if (strcmp(block, "</message>") == 0)
         break;
      else if (strcmp(block, "<feature>") == 0) {
         //printf("<feature>\n");
         if (message->lastFeature) {
            message->lastFeature->next = get_feature(mf);
            if (message->lastFeature->next == NULL ) {
               err = 1;
               break;
            }
            message->lastFeature = message->lastFeature->next;
         } else {
            message->firstFeature = message->lastFeature = get_feature(mf);
            if (message->lastFeature == NULL ) {
               err = 1;
               break;
            }
         }
      } else if (strcmp(block, "<field>") == 0) {
         //printf("<field>\n");
         if (message->lastField) {
            message->lastField->next = get_field(mf);
            if (message->lastField->next == NULL ) {
               err = 1;
               break;
            }
            message->lastField = message->lastField->next;
         } else {
            message->firstField = message->lastField = get_field(mf);
            if (message->lastField == NULL ) {
               err = 1;
               break;
            }
         }
      } else {
         err = 1;
         break;
      }
   }
   if (err) {
      free_message(message);
      return NULL ;
   }
   return message;
}

MessageList* get_message_list(char *fileName) {
   char *block;
   int tindex = 0;
   MsgFile mf;
   int err = 0;
   mf.fp = fopen(fileName, "r+b");
   if (mf.fp == NULL )
      return NULL ;

   mf.fileName = fileName;

   fseek(mf.fp, 0, SEEK_END);
   mf.fileSize = ftell(mf.fp);

   fseek(mf.fp, 0, SEEK_SET);

   mf.readLen = 0;
   mf.blen = 0;
   mf.boffset = 0;

   MessageList *ml = malloc(sizeof(MessageList));
   if (ml == NULL )
      return NULL ;

   ml->firstMessage = NULL;
   ml->lastMessage = NULL;

   while ((block = getNextBlock(&mf)) != NULL ) {
//printf("<token>%s</token>\n", block);
      if (strcmp(block, "<message>") == 0) {
         //printf("<message>\n");
         if (ml->lastMessage) {
            ml->lastMessage->next = get_message(&mf);
            if (ml->lastMessage->next == NULL ) {
               err = 1;
               break;
            }
            ml->lastMessage = ml->lastMessage->next;
         } else {
            ml->firstMessage = ml->lastMessage = get_message(&mf);
            if (ml->lastMessage == NULL ) {
               err = 1;
               break;
            }
         }
      } else {
         //err = 1;
         //break;
      }
   }

   if (err) {
      free_message_list(ml);
      return NULL ;
   }

   return ml;
}

MessageList* get_message_list2(char *fileName) {
   char *block;
   int tindex = 0;
   MsgFile mf;
   int err = 0;
   mf.fp = fopen(fileName, "r+b");
   if (mf.fp == NULL )
      return NULL ;

   mf.fileName = fileName;

   fseek(mf.fp, 0, SEEK_END);
   mf.fileSize = ftell(mf.fp);

   fseek(mf.fp, 0, SEEK_SET);

   mf.readLen = 0;
   mf.blen = 0;
   mf.boffset = 0;

   MessageList *ml = malloc(sizeof(MessageList));
   if (ml == NULL )
      return NULL ;

   ml->firstMessage = NULL;
   ml->lastMessage = NULL;

   while ((block = getNextBlock2(&mf)) != NULL ) {
      printf("<token%d>%s</token%d>\n", tindex, block, tindex);
      tindex++;
      if (strcmp(block, "<message>") == 0) {
         if (ml->lastMessage) {
            ml->lastMessage->next = get_message(&mf);
            if (ml->lastMessage->next == NULL ) {
               err = 1;
               break;
            }
            ml->lastMessage = ml->lastMessage->next;
         } else {
            ml->firstMessage = ml->lastMessage = get_message(&mf);
            if (ml->lastMessage == NULL ) {
               err = 1;
               break;
            }
         }
      } else {
         //err = 1;
         //break;
      }
   }

   if (err) {
      free_message_list(ml);
      return NULL ;
   }

   return ml;
}

char get_gps_cmd_parity(char *cmd) {
   char parity = 0;

   while (*cmd)
      parity ^= *cmd++;

   return parity;
}

/*
 Token* getTokenList(FILE *fp) {

 Token *troot;
 Token *token;
 char block[1024*64];
 int  blockSize;
 char delimList[] = " \t";
 char byte;
 char nextbyte;
 int ignoreLine;
 int nextByteRead;
 linesize = 0;
 ignoreLine = 0;

 while (fread(&byte, 1, 1, fp) > 0) {
 nextByteRead = 0;
 if (byte == '#')
 ignoreLine = 1;
 if (byte == '/') {
 nextByteRead = fread(&nextbyte, 1, 1, fp);
 if (nextByteRead){
 if (nextbyte == '/' || nextbyte == '*')
 ignoreLine = 1;
 }
 }
 }

 char delimList[] = " \n\t\r=";
 char escape = '\\';
 char blockCharsListStart[] = "\"<({[";
 char blockCharsListEnd[] = "\">)}]";

 int delimLen = strlen(delimList);

 int blockCharsLen = strlen(blockCharsListStart);
 int bBlockCharOpen;
 int openBlockCharIndex;
 int openBlockCharLevel;
 int found;
 int j;

 static char blockStart[MAX_BLOCK_LEN];
 char *blockCurrPtr = NULL;
 char *blockEndPtr = NULL;

 if (mf->readLen >= mf->fileSize)
 return NULL ;

 if (mf->blen <= mf->boffset) {
 mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
 mf->boffset = 0;
 if (mf->blen <= 0)
 return NULL ;
 }
 //printf("mf->blen: %d\n",mf->blen);
 found = 0;
 while (mf->boffset < mf->blen) {
 found = 0;
 for (j = 0; j < delimLen; j++) {
 if (delimList[j] == mf->buffer[mf->boffset]) {
 mf->boffset++;
 found = 1;
 break;
 }
 }

 if (!found)
 break;

 if (mf->blen <= mf->boffset) {
 mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
 mf->boffset = 0;
 if (mf->blen <= 0)
 return NULL ;
 }
 }
 //printf("mf->blen: %d\n",mf->blen);
 //printf("mf->boffset: %d\n",mf->boffset);
 blockCurrPtr = blockStart;
 blockEndPtr = blockStart + MAX_BLOCK_LEN;

 while (mf->boffset < mf->blen && blockCurrPtr < blockEndPtr) {
 //printf("mf->blen: %d\n",mf->blen);
 //printf("mf->boffset: %d\n",mf->boffset);
 for (j = 0; j < delimLen; j++) {
 if (delimList[j] == mf->buffer[mf->boffset]) {
 *blockCurrPtr = '\0';
 mf->boffset++;
 return blockStart;
 }
 }

 bBlockCharOpen = 0;
 for (j = 0; j < blockCharsLen; j++) {
 if (blockCharsListStart[j] == mf->buffer[mf->boffset]) {
 bBlockCharOpen = 1;
 openBlockCharIndex = j;
 *blockCurrPtr++ = mf->buffer[mf->boffset++];
 if (mf->blen <= mf->boffset) {
 mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
 mf->boffset = 0;
 if (mf->blen <= 0) {
 *blockCurrPtr = '\0';
 return blockStart;
 }
 }
 break;
 }
 }

 if (bBlockCharOpen) {

 openBlockCharLevel = 1;

 while (mf->boffset < mf->blen && blockCurrPtr < blockEndPtr) {
 //printf("mf->blens: %d\n",mf->blen);
 //printf("mf->boffsets: %d\n",mf->boffset);

 if (escape != mf->buffer[mf->boffset]) {
 if (blockCharsListEnd[openBlockCharIndex] == mf->buffer[mf->boffset]) {
 openBlockCharLevel--;
 *blockCurrPtr++ = mf->buffer[mf->boffset++];
 if (mf->blen <= mf->boffset) {
 mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
 mf->boffset = 0;
 if (mf->blen <= 0) {
 *blockCurrPtr = '\0';
 return blockStart;
 }
 }
 if (openBlockCharLevel <= 0) {
 break;
 }
 } else if (blockCharsListStart[openBlockCharIndex] == mf->buffer[mf->boffset]) {
 openBlockCharLevel++;
 *blockCurrPtr++ = mf->buffer[mf->boffset++];
 if (mf->blen <= mf->boffset) {
 mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
 mf->boffset = 0;
 if (mf->blen <= 0) {
 *blockCurrPtr = '\0';
 return blockStart;
 }
 }
 } else {
 *blockCurrPtr++ = mf->buffer[mf->boffset++];
 if (mf->blen <= mf->boffset) {
 mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
 mf->boffset = 0;
 if (mf->blen <= 0) {
 *blockCurrPtr = '\0';
 return blockStart;
 }
 }
 }
 } else {
 *blockCurrPtr++ = mf->buffer[mf->boffset++];
 if (mf->blen <= mf->boffset) {
 mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
 mf->boffset = 0;
 if (mf->blen <= 0) {
 *blockCurrPtr = '\0';
 return blockStart;
 }
 }
 *blockCurrPtr++ = mf->buffer[mf->boffset++];
 }
 if (mf->blen <= mf->boffset) {
 mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
 mf->boffset = 0;
 if (mf->blen <= 0) {
 *blockCurrPtr = '\0';
 return blockStart;
 }
 }
 }
 bBlockCharOpen = 0;
 } else {
 *blockCurrPtr++ = mf->buffer[mf->boffset++];
 if (mf->blen <= mf->boffset) {
 mf->blen = fread(mf->buffer, 1, RBUF_LEN, mf->fp);
 mf->boffset = 0;
 if (mf->blen <= 0) {
 *blockCurrPtr = '\0';
 return blockStart;
 }
 }
 }
 }
 if (blockCurrPtr != blockStart) {
 *blockCurrPtr = '\0';
 return blockStart;
 } else
 return NULL ;

 }
 */

char *toupper_string(char *dest, char *src) {
   char *destStart = dest;
   while (*src) {
      *dest = toupper(*src);
      dest++;
      src++;
   }
   *dest = 0;
   return destStart;
}
char *tolover_string(char *dest, char *src) {
   char *destStart = dest;
   while (*src) {
      *dest = tolower(*src);
      dest++;
      src++;
   }
   *dest = 0;
   return destStart;
}
void openfile(FILE **fp, int header, int defs, char *fileName, char *namespace, char *usenamespace1,
      char *usenamespace2, char *usenamespace3) {
   static const char pathHeader[] = "Y:\\workspace\\olts\\src\\efe\\inc\\Host\\VIOP\\";
   static const char pathCpp[] = "Y:\\workspace\\olts\\src\\efe\\Host\\VIOP\\";
#define BUF_LEN 500
   char temp[BUF_LEN];
   if (strlen(fileName) >= BUF_LEN) {
      printf("Error: filename çok uzun\n");
      exit(EXIT_FAILURE);
   }

   if (header)
      sprintf(temp, "%s%s.h", pathHeader, fileName);
   else
      sprintf(temp, "%s%s.cpp", pathCpp, fileName);

   *fp = fopen(temp, "w");
   if (header) {
      fprintf(*fp, "#ifndef _VIOP_%s_H_\n", toupper_string(temp, fileName));
      fprintf(*fp, "#define _VIOP_%s_H_\n", toupper_string(temp, fileName));
   }
   fprintf(*fp, "#include <iostream>\n");
   fprintf(*fp, "#include <cctype>\n");
   fprintf(*fp, "#include <locale>\n");
   fprintf(*fp, "#include <algorithm>\n");
   fprintf(*fp, "#include <functional>\n");
   fprintf(*fp, "#include <sstream>\n");
   fprintf(*fp, "#include <string.h>\n");
   fprintf(*fp, "#include <stdio.h>\n");
   fprintf(*fp, "#include \"Host/TSMR/Exception.h\"\n");
   fprintf(*fp, "#include \"Host/TSMR/MessageBase.h\"\n");
   fprintf(*fp, "#include \"Host/TSMR/HostReplyMessage.h\"\n");
   fprintf(*fp, "#include \"Host/TSMR/HostRequestMessage.h\"\n");
   fprintf(*fp, "#include \"Host/VIOP/constant.h\"\n");
   fprintf(*fp, "#include \"Host/VIOP/temsg.h\"\n");
   fprintf(*fp, "#include \"Host/VIOP/Fields.h\"\n");
   fprintf(*fp, "#include \"Host/VIOP/fieldTypeLengthDefs.h\"\n");
   fprintf(*fp, "#include \"Host/VIOP/messageTypeDefs.h\"\n");
   if (!defs) {
      fprintf(*fp, "#include \"Host/VIOP/RequestMessages.h\"\n");
      fprintf(*fp, "#include \"Host/VIOP/ReplyMessages.h\"\n");
   }
   if (!header)
      fprintf(*fp, "#include \"Host/VIOP/%s.h\"\n", fileName);
   fprintf(*fp, "namespace VIOP\n");
   fprintf(*fp, "{\n");
   fprintf(*fp, "namespace MSG\n");
   fprintf(*fp, "{\n");
   if (namespace) {
      fprintf(*fp, "namespace %s\n", toupper_string(temp, namespace));
      fprintf(*fp, "{\n");
   }
   if (usenamespace1)
      fprintf(*fp, "using namespace %s;\n", toupper_string(temp, usenamespace1));
   if (usenamespace2)
      fprintf(*fp, "using namespace %s;\n", toupper_string(temp, usenamespace2));
   if (usenamespace3)
      fprintf(*fp, "using namespace %s;\n", toupper_string(temp, usenamespace3));
   fprintf(*fp, "using namespace std;\n");
}
void closefile(FILE *fp, int header, char *fileName, char *namespace, char *usenamespace1,
      char *usenamespace2, char *usenamespace3) {

#define BUF_LEN 500
   char temp[BUF_LEN];
   if (strlen(fileName) >= BUF_LEN) {
      printf("Error: filename çok uzun\n");
      exit(EXIT_FAILURE);
   }

   fprintf(fp, "}/*namespace VIOP*/\n");
   fprintf(fp, "}/*namespace MSG*/\n");
   if (namespace) {
      fprintf(fp, "} /*namespace %s*/\n", toupper_string(temp, namespace));
   }
   if (header)
      fprintf(fp, "#endif /*_VIOP_%s_H_*/\n", toupper_string(temp, fileName));
   fclose(fp);
}
int main(int argc, char *argv[]) {

   Directory *newDirEntry;
   Directory *dirEntry;
   Stack stack;
   Stack foundStack;
   DIR *dp = NULL;
   DIR *subDir = NULL;
   struct dirent *dptr = NULL;
   char subDirPath[PATH_LEN_MAX];
   FILE *fp;
   size_t fsize;
   size_t lnCount = 0, lnCoutnInFileX = 0;
   size_t lrCount = 0, lrCoutnInFileX = 0;
   size_t nvCount = 0, nvCoutnInFileX = 0;
   size_t totalFileCount = 0;
   size_t hFileCount = 0;
   size_t cFileCount = 0;
   size_t cppFileCount = 0;
   size_t rsize;
   size_t blen;
   size_t boolCountLines;
   File *fe = NULL;
   SortedFileList sfl;
   ListNode *fln;

   char rbuf[RBUF_LEN];
   int i, j;
   int maxFileNameLen = 0;
   int maxFilePathLen = 0;
   int bSearchText = 0;
   int bSearchText2 = 0;
   char searchText[RBUF_LEN];
   char searchText2[RBUF_LEN];
   int searchTextLen = 0;
   int searchTextLen2 = 0;
   char searchWindow[RBUF_LEN];
   char searchWindow2[RBUF_LEN];

   int searchWindowLen = 0;
   int searchWindowWrIdx = 0;
   int searchWindowRdIdx = 0;
   int si, wi, found;
   Found *foundKayit = NULL;
   int writeOutEnable = 0;
   MessageList *ml;
   FILE *foundOutFile = NULL; // fopen("fout.h", "w+b");
   int namespaceOpened = 0;
   int writeStartted = 0;
   int kk;
   char xstr[100];
   FILE *fph = fopen("fph.h", "w");
   FILE *fpcpp = fopen("fpcpp.cpp", "w");

   FILE *hOpr;
   FILE *hMsgTypeDef;
   FILE *hFieldTypeDef;
   FILE *cppOpr;
   FILE *hTrans;

   FILE *cppTrans;
   FILE *hQuery;
   FILE *cppQuery;

   openfile(&hQuery, 1, 0, "queryMessageDefs", "query", "FIELDDEFS", "MSGTYPEDEFS", NULL );
   openfile(&cppQuery, 0, 0, "queryMessageDefs", "query", "FIELDDEFS", "MSGTYPEDEFS", NULL );
   openfile(&hOpr, 1, 0, "operatorMessageDefs", "opr", "FIELDDEFS", "MSGTYPEDEFS", NULL );
   openfile(&cppOpr, 0, 0, "operatorMessageDefs", "opr", "FIELDDEFS", "MSGTYPEDEFS", NULL );
   openfile(&hTrans, 1, 0, "transactionMessageDefs", "transaction", "FIELDDEFS", "MSGTYPEDEFS",
         NULL );
   openfile(&cppTrans, 0, 0, "transactionMessageDefs", "transaction", "FIELDDEFS", "MSGTYPEDEFS",
         NULL );
   openfile(&hMsgTypeDef, 1, 1, "messageTypeDefs", "MSGTYPEDEFS", NULL, NULL, NULL );
   openfile(&hFieldTypeDef, 1, 1, "fieldTypeLengthDefs", "FIELDDEFS", NULL, NULL, NULL );

   if (argc < 2) {
      printf("\n Please pass in the directory name \n");
      return 1;
   }

   if (argc > 2) {
      bSearchText = 1;
      strcpy(searchText, argv[2]);
      searchTextLen = strlen(searchText);

//printf("Argc: %d, %s\n", argc, argv[2]);
//return 0;
   }
   if (argc > 3) {
      bSearchText = 0;
      bSearchText2 = 1;
      strcpy(searchText2, argv[3]);
      searchTextLen2 = strlen(searchText2);
   }
//printf("parity: %0.2X\n",get_gps_cmd_parity(argv[1]));
//message_set(argv[1]);

//Token *token = token_parse(argv[1]);
//write_sruct_xml(token);
//return 0;

   ml = get_message_list(argv[1]);
   if (ml) {
//print_message_list(ml);
//fout_message_list(ml,stdout, stdout);
      fout_message_list(ml, hOpr, cppOpr, "Operator");
      fout_message_list(ml, hTrans, cppTrans, "Transaction");
      fout_message_list(ml, hQuery, cppQuery, "Query");
      fout_message_list_types(ml, hMsgTypeDef);
      //fprintf(hFieldTypeDef, "namespace LIMITS\n{\n");
      fout_message_fiedldefs(ml, hFieldTypeDef, "fielddef");
      //fprintf(hFieldTypeDef, "}/*namespace LIMITS*/\n");

      fprintf(hFieldTypeDef, "\n/*FIELD DEFINITIONS*/\n");
      //fprintf(hFieldTypeDef, "using namespace LIMITS;\n");
      fout_message_definefields(ml, hFieldTypeDef, "fielddef");
   }

   closefile(hQuery, 1, "queryMessageDefs", "query", "FIELDDEFS", "MSGTYPEDEFS", NULL );
   closefile(cppQuery, 0, "queryMessageDefs", "query", "FIELDDEFS", "MSGTYPEDEFS", NULL );
   closefile(hOpr, 1, "operatorMessageDefs", "opr", "FIELDDEFS", "MSGTYPEDEFS", NULL );
   closefile(cppOpr, 0, "operatorMessageDefs", "opr", "FIELDDEFS", "MSGTYPEDEFS", NULL );
   closefile(hTrans, 1, "transactionMessageDefs", "transaction", "FIELDDEFS", "MSGTYPEDEFS", NULL );
   closefile(cppTrans, 0, "transactionMessageDefs", "transaction", "FIELDDEFS", "MSGTYPEDEFS",
         NULL );
   closefile(hMsgTypeDef, 1, "messageTypeDefs", "MSGTYPEDEFS", NULL, NULL, NULL );
   closefile(hFieldTypeDef, 1, "fieldTypeLengthDefs", "FIELDDEFS", NULL, NULL, NULL );

   printf("finish\n");
   free_message_list(ml);
   return 0;

   sfl_init(&sfl);

   newDirEntry = malloc(sizeof(Directory));
   if (newDirEntry == NULL ) {
      printf("Bellekte yer kalmadı!\n");
      exit(EXIT_FAILURE);
   }

   stack_init(&stack);
   stack_init(&foundStack);

   newDirEntry->plen = strlen(argv[1]) + 1;
   memcpy(newDirEntry->path, argv[1], newDirEntry->plen);

   sprintf(newDirEntry->ident, " ");
   newDirEntry->ilen = strlen(newDirEntry->ident) + 1;

   stack_push(&stack, newDirEntry);

   printf("BuiltTime: %s\n", __TIME__);

   while ((dirEntry = stack_pop(&stack)) != NULL ) {
      if (NULL == (dp = opendir(dirEntry->path))) {
         printf("\n Cannot open Input directory [%s]\n", dirEntry->path);
         exit(EXIT_FAILURE);
      }

      printf("%s[dr: %s]\n", dirEntry->ident, dirEntry->path);
      namespaceOpened = 0;
      while (NULL != (dptr = readdir(dp))) {
         strncpy(subDirPath, dirEntry->path, dirEntry->plen);

         if (subDirPath[dirEntry->plen - 2] == '/') {
            sprintf(subDirPath + dirEntry->plen - 1, "%s", dptr->d_name);
         } else {
            sprintf(subDirPath + dirEntry->plen - 1, "/%s", dptr->d_name);
         }

         if ((subDir = opendir(subDirPath)) != NULL ) {

            if (strcmp(dptr->d_name, ".") != 0 && strcmp(dptr->d_name, "..") != 0) {
               //printf(" %s[dr: %s]\n",dirEntry->ident,dptr->d_name);

               newDirEntry = malloc(sizeof(Directory));
               if (newDirEntry == NULL ) {
                  printf("Bellekte yer kalmadı!\n");
                  exit(EXIT_FAILURE);
               }

               newDirEntry->plen = strlen(subDirPath) + 1;
               memcpy(newDirEntry->path, subDirPath, newDirEntry->plen);

               sprintf(newDirEntry->ident, "%s  ", dirEntry->ident);
               newDirEntry->ilen = strlen(newDirEntry->ident) + 1;

               stack_push(&stack, newDirEntry);
            }

            closedir(subDir);
         } else {

            totalFileCount++;
            lnCoutnInFileX = 0;
            lrCoutnInFileX = 0;
            nvCoutnInFileX = 0;
            i = strlen(dptr->d_name);

            if ((dptr->d_name[i - 2] == '.' && dptr->d_name[i - 1] == 'h')
                  || (dptr->d_name[i - 2] == '.' && dptr->d_name[i - 1] == 'H')) {
               hFileCount++;
               boolCountLines = 1;
            } else if ((dptr->d_name[i - 2] == '.' && dptr->d_name[i - 1] == 'c')
                  || (dptr->d_name[i - 2] == '.' && dptr->d_name[i - 1] == 'C')) {
               cFileCount++;
               boolCountLines = 1;
            } else if ((dptr->d_name[i - 4] == '.' && dptr->d_name[i - 3] == 'c'
                  && dptr->d_name[i - 2] == 'p' && dptr->d_name[i - 1] == 'p')
                  || (dptr->d_name[i - 4] == '.' && dptr->d_name[i - 3] == 'C'
                        && dptr->d_name[i - 2] == 'P' && dptr->d_name[i - 1] == 'P')) {
               cppFileCount++;
               boolCountLines = 1;
            } else if ((dptr->d_name[i - 4] == '.' && dptr->d_name[i - 3] == 't'
                  && dptr->d_name[i - 2] == 'x' && dptr->d_name[i - 1] == 't')
                  || (dptr->d_name[i - 4] == '.' && dptr->d_name[i - 3] == 'T'
                        && dptr->d_name[i - 2] == 'X' && dptr->d_name[i - 1] == 'T')) {

               boolCountLines = 1;
            } else if ((dptr->d_name[i - 2] == '.' && dptr->d_name[i - 1] == 'o')
                  || (dptr->d_name[i - 2] == '.' && dptr->d_name[i - 1] == 'a')) {
               boolCountLines = 0;
            } else {
               boolCountLines = 1;
            }

            if (boolCountLines) {
               printf("%s ", subDirPath);

               fp = fopen(subDirPath, "r+b");

               if (fp != NULL ) {
                  fseek(fp, 0, SEEK_END);
                  fsize = ftell(fp);

                  printf(" (size: %d byte", fsize);
                  fseek(fp, 0, SEEK_SET);

                  rsize = 0;

                  fe = (File*) malloc(sizeof(File));
                  if (fe == NULL ) {
                     printf("Bellek hatası\n");
                     exit(EXIT_FAILURE);
                  }

                  memset(fe, 0, sizeof(File));

                  fe->plen = strlen(subDirPath) + 1;
                  strncpy(fe->path, subDirPath, fe->plen);

                  fe->nlen = strlen(dptr->d_name) + 1;
                  strncpy(fe->name, dptr->d_name, fe->nlen);

                  fe->size = fsize;

                  if (maxFilePathLen < fe->plen)
                     maxFilePathLen = fe->plen;

                  if (maxFileNameLen < fe->nlen)
                     maxFileNameLen = fe->nlen;

                  searchWindowLen = 0;
                  searchWindowWrIdx = 0;
                  searchWindowRdIdx = 0;
                  namespaceOpened = 0;
                  writeStartted = 0;
                  while (rsize < fsize) {

                     if (fsize - rsize > RBUF_LEN)
                        blen = fread(rbuf, 1, RBUF_LEN, fp);
                     else
                        blen = fread(rbuf, 1, fsize - rsize, fp);

                     rsize += blen;

                     for (i = 0; i < blen; i++) {
                        if (rbuf[i] == '\n') {
                           lnCount++;
                           lnCoutnInFileX++;
                           fe->lnCount++;
                        }
                        if (rbuf[i] == '\r') {
                           lrCount++;
                           lrCoutnInFileX++;
                           fe->lrCount++;
                        }
                        if (rbuf[i] == ';') {
                           nvCount++;
                           nvCoutnInFileX++;
                           fe->nvCount++;
                        }

                        if (bSearchText) {
                           if (searchWindowLen < searchTextLen) {
                              if (searchWindowWrIdx >= RBUF_LEN)
                                 searchWindowWrIdx = 0;

                              searchWindow[searchWindowWrIdx++] = rbuf[i];
                              searchWindowLen++;
                           }

                           if (searchWindowLen == searchTextLen) {
                              found = 1;
                              wi = searchWindowRdIdx;
                              for (si = 0; si < searchTextLen; si++) {
                                 if (searchWindow[wi] != searchText[si]) {
                                    found = 0;
                                    break;
                                 }
                                 wi++;
                                 if (wi >= RBUF_LEN)
                                    wi = 0;

                              }
                              if (found) {
                                 foundKayit = (Found*) malloc(sizeof(Found));
                                 if (foundKayit == NULL ) {
                                    printf("Bellek hatası!\n");
                                    exit(EXIT_FAILURE);
                                 }
                                 foundKayit->atLine = fe->lnCount;
                                 memcpy(foundKayit->path, fe->path, PATH_LEN_MAX);
                                 memcpy(foundKayit->searchWindow, searchWindow, RBUF_LEN);

                                 for (si = 1; si <= 50; si++) {
                                    if (si + i >= blen)
                                       break;
                                    foundKayit->searchWindow[(searchWindowWrIdx + si - 1) % RBUF_LEN] =
                                          rbuf[si + i];
                                 }

                                 foundKayit->startIndex = searchWindowRdIdx;
                                 stack_push(&foundStack, (void*) foundKayit);
                              }
                              searchWindowRdIdx++;
                              if (searchWindowRdIdx >= RBUF_LEN)
                                 searchWindowRdIdx = 0;
                              searchWindowLen--;
                           }
                        }

                        if (bSearchText2) {

                           if (searchWindowLen < searchTextLen) {
                              if (searchWindowWrIdx >= RBUF_LEN)
                                 searchWindowWrIdx = 0;

                              searchWindow[searchWindowWrIdx++] = rbuf[i];
                              searchWindowLen++;
                           }
                           if (!writeStartted) {
                              if (searchWindowLen == searchTextLen) {
                                 found = 1;
                                 wi = searchWindowRdIdx;
                                 for (si = 0; si < searchTextLen; si++) {
                                    if (searchWindow[wi] != searchText[si]) {
                                       found = 0;
                                       break;
                                    }
                                    wi++;
                                    if (wi >= RBUF_LEN)
                                       wi = 0;

                                 }
                                 if (found) {
                                    writeStartted = 1;
                                    if (!namespaceOpened) {
                                       sprintf(xstr, "namespace ");
                                       fwrite(xstr, strlen(xstr), 1, foundOutFile);
                                       for (kk = 0; kk < strlen(fe->name); kk++) {
                                          if (fe->name[kk] == '.' || fe->name[kk] == '\0')
                                             break;
                                          sprintf(xstr, "%c", toupper(fe->name[kk]));
                                          fwrite(xstr, 1, 1, foundOutFile);
                                       }
                                       sprintf(xstr, "\n{\n");
                                       fwrite(xstr, strlen(xstr), 1, foundOutFile);
                                       namespaceOpened = 1;
                                    }
                                    fprintf(foundOutFile, "%s", searchText);
                                    searchWindowLen = 0;
                                    searchWindowWrIdx = 0;
                                    searchWindowRdIdx = 0;
                                 } else {
                                    searchWindowRdIdx++;
                                    if (searchWindowRdIdx >= RBUF_LEN)
                                       searchWindowRdIdx = 0;
                                    searchWindowLen--;
                                 }
                              }
                           } else {
                              sprintf(xstr, "%c", rbuf[i]);
                              fwrite(xstr, 1, 1, foundOutFile);
                              if (searchWindowLen == searchTextLen2) {
                                 found = 1;
                                 wi = searchWindowRdIdx;
                                 for (si = 0; si < searchTextLen2; si++) {
                                    if (searchWindow[wi] != searchText2[si]) {
                                       found = 0;
                                       break;
                                    }
                                    wi++;
                                    if (wi >= RBUF_LEN)
                                       wi = 0;

                                 }
                                 if (found) {
                                    writeStartted = 0;
                                    sprintf(xstr, "\n");
                                    fwrite(xstr, 1, 1, foundOutFile);
                                    searchWindowLen = 0;
                                    searchWindowWrIdx = 0;
                                    searchWindowRdIdx = 0;
                                 } else {
                                    searchWindowRdIdx++;
                                    if (searchWindowRdIdx >= RBUF_LEN)
                                       searchWindowRdIdx = 0;
                                    searchWindowLen--;
                                 }
                              }
                           }
                        }
                     }
                  }
                  if (namespaceOpened) {
                     //printf(foundOutFile, "\n}\n");
                     sprintf(xstr, "\n}\n");
                     fwrite(xstr, strlen(xstr), 1, foundOutFile);
                     namespaceOpened = 0;
                  }

                  fe->id = fe->lnCount;
                  sfl_add(&sfl, fe);

                  printf(", ln: %d, lr: %d, nv: %d)\n", lnCoutnInFileX, lrCoutnInFileX,
                        nvCoutnInFileX);
                  fclose(fp);
               } else {
                  printf("!open\n");
               }
            }

         }
      }
      closedir(dp);
   }

   j = 0;

   while (sfl.first != NULL ) {

      fln = sfl.first;

      fe = (File*) fln->data;

      sfl.first = sfl.first->next;
      i = sprintf(rbuf, "%s", fe->name);
      while (i < maxFileNameLen + 1)
         i += sprintf(rbuf + i, " ");
      i += sprintf(rbuf + i, ":");
      printf(rbuf);

      j += fe->lnCount;

      printf("= size: %6d, ln: %5d, cln: %6d, yzd: %0.2f, cyzd: %0.2f , lr: %d, nv: %5d\n",
            fe->size, fe->lnCount, j, ((double) fe->lnCount) / ((double) lnCount) * 100.0,
            ((double) j) / ((double) lnCount) * 100.0, fe->lrCount, fe->nvCount);

      free(fe);
      free(fln);
   }

   printf("fileCount: %d, *.h: %d, *.c: %d, *.cpp: %d, lnCount: %d, lrCount: %d, nvCount: %d\n",
         totalFileCount, hFileCount, cFileCount, cppFileCount, lnCount, lrCount, nvCount);

   if (bSearchText) {
      i = 0;
      while ((foundKayit = stack_pop(&foundStack)) != NULL ) {
         printf("%0.3d: at line %0.4d in file: %s\n", ++i, foundKayit->atLine, foundKayit->path);
         si = foundKayit->startIndex - 10;
         if (si < 0)
            si = RBUF_LEN - 10;
         for (wi = 0; wi < searchTextLen + 30; wi++) {
            printf("%c", foundKayit->searchWindow[si]);

            si++;

            if (si >= RBUF_LEN)
               si = 0;
         }
         printf("\n");
         free(foundKayit);
      }

   }
   return 0;
}
