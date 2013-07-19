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
typedef struct
{
  char path[PATH_LEN_MAX];
  int  plen;
  char ident[PATH_LEN_MAX];
  int  ilen;
}Directory;

typedef struct
{
  char path[PATH_LEN_MAX];
  int  plen;
  char name[PATH_LEN_MAX];
  int  nlen;
  size_t size;
  size_t lnCount;
  size_t lrCount;
  size_t nvCount;
  size_t id;
}File;

typedef struct
{
  char path[PATH_LEN_MAX];
  char searchWindow[RBUF_LEN];
  size_t atLine;
  int  startIndex;
}Found;

typedef struct _ListNode_
{
  void *data;
  struct _ListNode_ *next;
  struct _ListNode_ *pre;
}ListNode;


typedef struct 
{
  ListNode *top;
}Stack;

typedef struct _sorted_list
{
  ListNode *first;
  ListNode *last;
}SortedFileList;

void sfl_init(SortedFileList *sl)
{
    sl->first = NULL;
    sl->last = NULL;
}
int sfl_add(SortedFileList *sfl, void *data)
{
    ListNode *newnode =  (ListNode*) malloc( sizeof(ListNode) );

    if(newnode == NULL)
      return 0;

    newnode->data = data;
    newnode->next = NULL;
    newnode->pre = NULL;

    if(sfl->first == NULL)
    {
      sfl->last = sfl->first = newnode;
      return 1;
    }    
    File *fs = (File*)sfl->first->data;
    File *ls = (File*)sfl->last->data;
    File *file = (File*)data;

    if(file->id <= fs->id)
    {
      sfl->first->pre = newnode;
      newnode->next = sfl->first;
      sfl->first = newnode;
      return 1;
    }
    if(file->id >= ls->id)
    {
      newnode->pre = sfl->last;
      sfl->last->next = newnode;
      sfl->last = newnode;
      return 1;
    }
    if(((fs->id + ls->id) / 2) >= file->id)
    {
      ListNode *iterator = sfl->last;
      while(iterator != NULL)
      {
        ls = (File*)iterator->data;
        if(ls->id <= file->id)
        {
          iterator->next->pre = newnode;
          newnode->next = iterator->next;
          newnode->pre = iterator;
          iterator->next = newnode;
          return 1;
        }
        iterator = iterator->pre;
      }  
    }
    else
    {
      ListNode *iterator = sfl->first;
      while(iterator != NULL)
      {
        ls = (File*)iterator->data;
        if(ls->id >= file->id)
        {
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

void stack_init( Stack *stack)
{
    stack->top = NULL;
}

int stack_push(Stack *stack,void *data)
{
    ListNode *newnode = malloc(sizeof(ListNode));

    if(newnode == NULL)
      return 0;

    newnode->data = data;
    newnode->next = NULL;

    newnode->pre = stack->top;

    if(stack->top != NULL)
      stack->top->next = newnode;
    stack->top = newnode;

    return 1;
}

void *stack_pop(Stack *stack)
{
    
    ListNode *node = NULL;

    void *data = NULL;

    if(stack->top != NULL)
    {
      data = stack->top->data;
      node = stack->top;
      stack->top = stack->top->pre;
    }

    if(stack->top != NULL)
    {
      stack->top->next = NULL;
    }
   
    if(node != NULL)
      free(node);

    return data;
}

int getHexValueStr(char *rbuf, int blen, char *dest, int dcapacity)
{
  int            i,j;
    int            searchTextLen = 0;
    char           searchWindow[RBUF_LEN];
    int            searchWindowLen = 0;
    int            searchWindowWrIdx = 0;
    int            searchWindowRdIdx = 0;
    int            si, wi, found;
    int            startIndex =0;

    char           startWith[] = "0x";

    searchTextLen = strlen(startWith);
    found = 0;

	for(i = 0; i < blen; i++)
	{
		if(searchWindowLen < searchTextLen)
		{
		  if(searchWindowWrIdx >= RBUF_LEN)
			  searchWindowWrIdx = 0;
		  searchWindow[searchWindowWrIdx++] = rbuf[i];
		  searchWindowLen++;
		}

		if(searchWindowLen == searchTextLen)
		{
		  found = 1;
		  wi = searchWindowRdIdx;
		  for(si = 0; si < searchTextLen; si++)
		  {
			  if(searchWindow[wi] != startWith[si])
			  {
				  found = 0;
				  break;
			  }
			  wi++;
			  if(wi >= RBUF_LEN)
				  wi = 0;
		  }
		  if(found)
		  {
			 startIndex = i;
			 break;
		  }

		  searchWindowRdIdx++;
		  if(searchWindowRdIdx >= RBUF_LEN)
			  searchWindowRdIdx = 0;
		  searchWindowLen--;
		}
	}

	if(!found) return 0;

	for(si = 1; (si+startIndex) < blen && si < dcapacity; si++)
	{
		if((rbuf[si+startIndex] >= '0' && rbuf[si+startIndex] <= '9')||
			rbuf[si+startIndex] == 'a' || rbuf[si+startIndex] == 'A' ||
			rbuf[si+startIndex] == 'b' || rbuf[si+startIndex] == 'B' ||
			rbuf[si+startIndex] == 'c' || rbuf[si+startIndex] == 'C' ||
			rbuf[si+startIndex] == 'd' || rbuf[si+startIndex] == 'D' ||
			rbuf[si+startIndex] == 'e' || rbuf[si+startIndex] == 'E' ||
			rbuf[si+startIndex] == 'f' || rbuf[si+startIndex] == 'F')
		   dest[si-1] = rbuf[si+startIndex];
		else
		   break;
	}
	dest[si-1] = 0;
	return 1;
}
unsigned int getHexValue(char *str)
{
  int i;
  int slen = strlen(str);
  unsigned int hval = 0;

  for(i = 0; i < slen; i++)
  {
	  if((str[i] >= '0' && str[i]  <= '9'))
		  hval = hval * 16 + (str[i] - '0');
	  else if(str[i]== 'a' || str[i] == 'A')
		  hval = hval * 16 + 10;
	  else if(str[i] == 'b' || str[i]  == 'B')
  		  hval = hval * 16 + 11;
	  else if(str[i] == 'c' || str[i]== 'C')
  		  hval = hval * 16 + 12;
	  else if(str[i] == 'd' || str[i] == 'D')
    	  hval = hval * 16 + 13;
	  else if(str[i] == 'e' || str[i] == 'E')
		  hval = hval * 16 + 14;
	  else if(str[i] == 'f' || str[i] == 'F')
    	  hval = hval * 16 + 15;
  }

  return hval;
}
unsigned int getNextToken(char *token, char *str, int *offset)
{
  int slen = strlen(str);
  int tlen = 0;
  char delimList[] = " \n\t\r";

  int delimLen = strlen(delimList);
  int found = 0;
  int j;

  while((*offset) < slen)
  {
	  found = 0;
	  for(j = 0 ; j < delimLen; j++)
	  {
	 	 if(delimList[j] == str[*offset])
	 	 {
	 		(*offset)++;
	 		found = 1;
	 		break;
	 	 }
	  }
	  if(!found)
		  break;
  }

  tlen = 0;
  while((*offset) < slen)
  {
	 for(j = 0 ; j < delimLen; j++)
	 {
		 if(delimList[j] == str[*offset])
		 {
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
void message_set(char *fileName)
{
	char           rbuf[RBUF_LEN];
	char           line[RBUF_LEN];
	char           token1[RBUF_LEN];
	char           token2[RBUF_LEN];
	int            i,j, linelen;
	size_t         blen;
	char           hextText[RBUF_LEN];
	int lineCnt = 0;
	int messageNum;
	FILE *fp = fopen(fileName, "r+b");


	if(fp == NULL)
		return;


	fseek ( fp , 0 , SEEK_END );
	size_t fsize = ftell ( fp );

	printf(" (size: %d byte\n\n\n", fsize);
	fseek ( fp , 0 , SEEK_SET );

    size_t rsize = 0;

	linelen = 0;

    while(rsize < fsize)
    {

	   if(fsize - rsize > RBUF_LEN)
		  blen  = fread (rbuf, 1, RBUF_LEN     , fp);
	   else
		  blen  = fread (rbuf, 1, fsize - rsize, fp);

	   rsize += blen;


	   for(i = 0; i < blen; i++)
	   {
		  if(rbuf[i] == '\n')
		  {
			  line[linelen] = 0;
			  int offset = 0;

			  if(getNextToken(token1, line, &offset) && strcmp(token1,"#define") == 0)
			  {
				  if(!getNextToken(token2, line, &offset))
					  continue;
				  if(!getNextToken(hextText, line, &offset))
				  	  continue;
				  messageNum = getHexValue(hextText);

				  /*
				  if(getHexValueStr(line, linelen,hextText, 3))
				  {
					  messageNum = getHexValue(hextText);
				  }
	              */
				  while(lineCnt < messageNum)
				  {
					//printf("#define MSGTYPE_MESSAGE_0x%0.2X 0x%0.2X\n", lineCnt, lineCnt );
					printf("statistics.messageDefs[%d].type = 0x%0.2X;",lineCnt,lineCnt);
					printf("statistics.messageDefs[%d].name = \"MSGTYPE_MESSAGE_0x%0.2X\";\n",lineCnt,lineCnt);
					//printf("statistics.message_counts[%d] = 0;\n",lineCnt);

					lineCnt++;
				  }

				  if(lineCnt > messageNum)
					  printf("______________ERROR_____________%0.2X\n", messageNum);

				  //printf("%s\n",line);
				  //printf("%s %s %s\n", token1, token2, hextText);

				  printf("statistics.messageDefs[%d].type = 0x%0.2X;",lineCnt,messageNum);
				  printf("statistics.messageDefs[%d].name = \"%s\";\n",lineCnt,token2);
				  //printf("statistics.message_counts[%d] = 0;\n",lineCnt);

				  lineCnt++;
			  }

			  linelen = 0;
		  }
		  else
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

typedef struct _feature_
{
  char *name;
  char *value;

  struct _feature_ *next;
}Feature;

typedef struct _msg_field_
{
  Feature *firstFeature;
  Feature *lastFeature;

  struct _msg_field_ *next;
}Field;

typedef struct __message__
{
  Feature *firstFeature;
  Feature *lastFeature;

  Field *firstField;
  Field *lastField;

  struct __message__ *next;
}Message;

typedef struct _msg_list
{
   Message *firstMessage;
   Message *lastMessage;
}MessageList;

typedef struct
{
	FILE *fp;
	char *fileName;
	size_t fileSize;
	size_t readLen;

	char buffer[RBUF_LEN];
	size_t blen;
	size_t boffset;
}MsgFile;

char* getNextBlock(MsgFile *mf)
{

#define MAX_BLOCK_LEN (64000)

  char delimList[] = " \n\t\r=";
  char escape = '\\';
  char blockCharsListStart[] = "\"<({[";
  char blockCharsListEnd[]   = "\">)}]";

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

  if(mf->readLen >= mf->fileSize)
	  return NULL;

  if(mf->blen <= mf->boffset){
	  mf->blen  = fread (mf->buffer, 1, RBUF_LEN     , mf->fp);
	  mf->boffset = 0;
	  if(mf->blen <= 0)
		  return NULL;
  }
  //printf("mf->blen: %d\n",mf->blen);
  found = 0;
  while(mf->boffset < mf->blen)
  {
	  found = 0;
	  for(j = 0 ; j < delimLen; j++){
	 	 if(delimList[j] == mf->buffer[mf->boffset]){
	 		mf->boffset++;
	 		found = 1;
	 		break;
	 	 }
	  }

	  if(!found)
		  break;

	  if(mf->blen <= mf->boffset){
	  	  mf->blen  = fread (mf->buffer, 1, RBUF_LEN     , mf->fp);
	  	  mf->boffset = 0;
	  	  if(mf->blen <= 0)
	  		  return NULL;
	  }
  }
  //printf("mf->blen: %d\n",mf->blen);
  //printf("mf->boffset: %d\n",mf->boffset);
  blockCurrPtr = blockStart;
  blockEndPtr = blockStart + MAX_BLOCK_LEN;

  while(mf->boffset < mf->blen && blockCurrPtr < blockEndPtr){
	 //printf("mf->blen: %d\n",mf->blen);
	 //printf("mf->boffset: %d\n",mf->boffset);
	 for(j = 0 ; j < delimLen; j++){
		 if(delimList[j] == mf->buffer[mf->boffset]){
			 *blockCurrPtr = '\0';
			 mf->boffset++;
			 return blockStart;
		 }
	 }

	 bBlockCharOpen = 0;
	 for(j = 0 ; j < blockCharsLen; j++){
	 	 if(blockCharsListStart[j] == mf->buffer[mf->boffset]){
	 		bBlockCharOpen = 1;
	 		openBlockCharIndex = j;
	 	    *blockCurrPtr++ = mf->buffer[mf->boffset++];
	 	    if(mf->blen <= mf->boffset){
				  mf->blen  = fread (mf->buffer, 1, RBUF_LEN     , mf->fp);
				  mf->boffset = 0;
				  if(mf->blen <= 0){
					*blockCurrPtr = '\0';
					return blockStart;
				  }
	 		}
	 		break;
	 	 }
	 }

	 if(bBlockCharOpen){

	     openBlockCharLevel = 1;

	     while(mf->boffset < mf->blen && blockCurrPtr < blockEndPtr){
	   	  //printf("mf->blens: %d\n",mf->blen);
	   	  //printf("mf->boffsets: %d\n",mf->boffset);

	    	if(escape != mf->buffer[mf->boffset]){
			    if(blockCharsListEnd[openBlockCharIndex] == mf->buffer[mf->boffset]){
					openBlockCharLevel--;
					*blockCurrPtr++ = mf->buffer[mf->boffset++];
					if(mf->blen <= mf->boffset){
						  mf->blen  = fread (mf->buffer, 1, RBUF_LEN     , mf->fp);
						  mf->boffset = 0;
						  if(mf->blen <= 0){
							*blockCurrPtr = '\0';
							return blockStart;
						  }
					}
					if(openBlockCharLevel <= 0){
						break;
					}
			    }else if(blockCharsListStart[openBlockCharIndex] == mf->buffer[mf->boffset]){
					openBlockCharLevel++;
					*blockCurrPtr++ = mf->buffer[mf->boffset++];
					if(mf->blen <= mf->boffset){
						  mf->blen  = fread (mf->buffer, 1, RBUF_LEN     , mf->fp);
						  mf->boffset = 0;
						  if(mf->blen <= 0){
							*blockCurrPtr = '\0';
							return blockStart;
						  }
					}
				}else{
					*blockCurrPtr++ = mf->buffer[mf->boffset++];
					if(mf->blen <= mf->boffset){
						  mf->blen  = fread (mf->buffer, 1, RBUF_LEN     , mf->fp);
						  mf->boffset = 0;
						  if(mf->blen <= 0){
							*blockCurrPtr = '\0';
							return blockStart;
						  }
				   }
				}
	    	}else{
				*blockCurrPtr++ = mf->buffer[mf->boffset++];
				if(mf->blen <= mf->boffset){
					  mf->blen  = fread (mf->buffer, 1, RBUF_LEN     , mf->fp);
					  mf->boffset = 0;
					  if(mf->blen <= 0){
						*blockCurrPtr = '\0';
						return blockStart;
					  }
				}
				*blockCurrPtr++ = mf->buffer[mf->boffset++];
	    	}
			if(mf->blen <= mf->boffset){
				  mf->blen  = fread (mf->buffer, 1, RBUF_LEN     , mf->fp);
				  mf->boffset = 0;
				  if(mf->blen <= 0){
					*blockCurrPtr = '\0';
					return blockStart;
				  }
			}
	     }
	     bBlockCharOpen = 0;
	 }else{
		 *blockCurrPtr++ = mf->buffer[mf->boffset++];
		  if(mf->blen <= mf->boffset){
			  mf->blen  = fread (mf->buffer, 1, RBUF_LEN     , mf->fp);
			  mf->boffset = 0;
			  if(mf->blen <= 0){
				*blockCurrPtr = '\0';
				return blockStart;
			  }
		  }
	 }
  }
  if(blockCurrPtr != blockStart){
	  *blockCurrPtr = '\0';
	    return blockStart;
  }else
	  return NULL;

}

void free_feature(Feature *feature)
{
    if(feature == NULL) return;
	if(feature->name) free(feature->name);
	if(feature->value) free(feature->value);
	free(feature);
}
void free_field(Field  *field)
{
	if(field == NULL) return;
	while(field->firstFeature != NULL){
		Feature *feature = field->firstFeature;
		field->firstFeature = field->firstFeature->next;
		free_feature(feature);
	}
	free(field);
}
void free_message(Message *message)
{
	if(message == NULL)
   	   return;
	while(message->firstFeature != NULL){
		Feature *feature = message->firstFeature;
		message->firstFeature = message->firstFeature->next;
		free_feature(feature);
	}
	while(message->firstField != NULL){
		Field *field = message->firstField;
		message->firstField = message->firstField->next;
		free_field(field);
	}
	free(message);
}
void free_message_list(MessageList *ml)
{
	if(ml == NULL)
   	   return;
	while(ml->firstMessage != NULL){
		Message *message = ml->firstMessage;
		ml->firstMessage = ml->firstMessage->next;
		free_message(message);
	}
	free(ml);
}
void print_feature(char *ident, Feature *feature)
{
    if(feature == NULL) return;
	if(feature->name) printf("%sNAME=%s\n",ident,feature->name);
	if(feature->value) printf("%sVALUE=%s\n",ident,feature->value);;
}
void print_field(char *ident, Field  *field)
{
	if(field == NULL) return;
	Feature *feature = field->firstFeature;
	while(feature != NULL){
		print_feature(ident, feature);
		feature = feature->next;
	}
}
void print_message(Message *message)
{
	if(message == NULL)
   	   return;
	Feature *feature = message->firstFeature;
	while(feature != NULL){
		print_feature("  ", feature);
		feature = feature->next;
	}
	Field *field = message->firstField;
	while(field != NULL){
		printf("\n");
		print_field("    ", field);
		field = field->next;
	}
}
void print_message_list(MessageList *ml)
{
	if(ml == NULL)
   	   return;
	Message *message = ml->firstMessage;
	while(message != NULL){
		print_message(message);
		message = message->next;
	}
}
Feature *get_feature(MsgFile *mf)
{
	char *block;
	int err = 0;
	Feature * feature = malloc(sizeof(Feature));
	if(feature == NULL)
		return NULL;
	feature->next = NULL;
	while((block = getNextBlock(mf)) != NULL)
	{
	   if(strcmp(block, "</feature>") == 0)
		   break;
	   else if(strcmp(block, "name") == 0){
		   block = getNextBlock(mf);
		   if(block == NULL){
			   err = 1;
			   break;
		   }
		   feature->name = malloc(sizeof(char)*strlen(block)+1);
		   if(feature->name == NULL){
		   	   err = 1;
		   	   break;
		   }
		   memcpy(feature->name, block, strlen(block)+1);
	   }else if(strcmp(block, "value") == 0){
		   block = getNextBlock(mf);
		   if(block == NULL){
			   err = 1;
			   break;
		   }
		   feature->value = malloc(sizeof(char)*strlen(block)+1);
		   if(feature->value == NULL){
			   err = 1;
			   break;
		   }
		   memcpy(feature->value, block, strlen(block)+1);
	   }else{
		   err = 1;
		   break;
	   }
	}
	if(err){
		free_feature(feature);
		return NULL;
	}
	return feature;
}
Field *get_field(MsgFile *mf)
{
	char *block;
	int err = 0;

	Field *field = malloc(sizeof(Field));
	if(field == NULL)
		return NULL;
	field->firstFeature = NULL;
	field->lastFeature = NULL;
	field->next = NULL;
	while((block = getNextBlock(mf)) != NULL)
	{
	   if(strcmp(block, "</field>") == 0)
		   break;
	   else if(strcmp(block, "<feature>") == 0){
		   if(field->lastFeature){
		     field->lastFeature->next = get_feature(mf);
		     if(field->lastFeature->next == NULL){
		    	 err = 1;
		    	 break;
		     }
		     field->lastFeature = field->lastFeature->next;
		   }else{
			   field->firstFeature = field->lastFeature = get_feature(mf);
			   if(field->lastFeature == NULL){
			   	  err = 1;
			   	  break;
			   }
		   }
	   }else{
		   err = 1;
		   break;
	   }
	}
	if(err){
		free_field(field);
		return NULL;
	}
	return field;
}

Message *get_message(MsgFile *mf)
{
	char *block;
	int err = 0;

	Message *message = malloc(sizeof(Message));
	if(message == NULL)
		return NULL;
	message->firstFeature = NULL;
	message->lastFeature = NULL;
	message->firstField = NULL;
	message->lastField = NULL;
	message->next = NULL;
	while((block = getNextBlock(mf)) != NULL)
	{
	   if(strcmp(block, "</message>") == 0)
		   break;
	   else if(strcmp(block, "<feature>") == 0){
		   if(message->lastFeature){
			   message->lastFeature->next = get_feature(mf);
		     if(message->lastFeature->next == NULL){
		    	 err = 1;
		    	 break;
		     }
		     message->lastFeature = message->lastFeature->next;
		   }else{
			   message->firstFeature = message->lastFeature = get_feature(mf);
			   if(message->lastFeature == NULL){
			   	  err = 1;
			   	  break;
			   }
		   }
	   }else if(strcmp(block, "<field>") == 0){
		   if(message->lastField){
			   message->lastField->next = get_field(mf);
		     if(message->lastField->next == NULL){
		    	 err = 1;
		    	 break;
		     }
		     message->lastField = message->lastField->next;
		   }else{
			   message->firstField = message->lastField = get_field(mf);
			   if(message->lastField == NULL){
			   	  err = 1;
			   	  break;
			   }
		   }
	   }else{
		   err = 1;
		   break;
	   }
	}
	if(err){
		free_message(message);
		return NULL;
	}
	return message;
}

 MessageList* get_message_list(char *fileName)
 {
    char *block;
    MsgFile mf;
    int err = 0;
    mf.fp = fopen(fileName, "r+b");
	if(mf.fp == NULL)
		return NULL;

    mf.fileName = fileName;


	fseek ( mf.fp , 0 , SEEK_END );
	mf.fileSize = ftell ( mf.fp );

	fseek ( mf.fp , 0 , SEEK_SET );

	mf.readLen = 0;
    mf.blen = 0;
    mf.boffset = 0;

    MessageList *ml = malloc(sizeof(MessageList));
    if(ml == NULL)
    	return NULL;

    ml->firstMessage = NULL;
    ml->lastMessage = NULL;

    while((block = getNextBlock(&mf)) != NULL)
    {
	    if(strcmp(block, "<message>") == 0){
		   if(ml->lastMessage){
			   ml->lastMessage->next = get_message(&mf);
			 if(ml->lastMessage->next == NULL){
				 err = 1;
				 break;
			 }
			 ml->lastMessage = ml->lastMessage->next;
		   }else{
			   ml->firstMessage = ml->lastMessage = get_message(&mf);
			   if(ml->lastMessage == NULL){
				  err = 1;
				  break;
			   }
		   }
	   }else{
		   err = 1;
		   break;
	   }
    }

    if(err){
    	free_message_list(ml);
    	return NULL;
    }

    return ml;
 }

 char get_gps_cmd_parity(char *cmd)
 {
    char parity = 0;

	while(*cmd)
		parity ^= *cmd++;

	return parity;
 }

int main (int argc, char *argv[])
{
	Directory     *newDirEntry;
	Directory     *dirEntry;
	Stack         stack;	
	Stack         foundStack;
    DIR           *dp = NULL;
	DIR           *subDir = NULL;
    struct dirent *dptr = NULL;    
	char          subDirPath[PATH_LEN_MAX];
	FILE          *fp;
	size_t         fsize;
	size_t         lnCount = 0, lnCoutnInFileX = 0;
	size_t         lrCount = 0, lrCoutnInFileX = 0;
	size_t         nvCount = 0, nvCoutnInFileX = 0;
	size_t         totalFileCount = 0;
	size_t         hFileCount = 0;
	size_t         cFileCount = 0;
	size_t         cppFileCount = 0;
    size_t         rsize;
	size_t         blen;
	size_t         boolCountLines;
	File          *fe = NULL;
	SortedFileList sfl;
	ListNode      *fln;

	char           rbuf[RBUF_LEN];
	int            i,j;
	int            maxFileNameLen = 0;
	int            maxFilePathLen = 0;
    int            bSearchText = 0;
    char           searchText[RBUF_LEN];
    int            searchTextLen = 0;
    char           searchWindow[RBUF_LEN];
    int            searchWindowLen = 0;
    int            searchWindowWrIdx = 0;
    int            searchWindowRdIdx = 0;
    int            si, wi, found;
    Found         *foundKayit = NULL;
    MessageList *ml;
    if(argc < 2)
    {
        printf("\n Please pass in the directory name \n");
        return 1;
    }

    if(argc > 2)
    {
    	bSearchText = 1;
    	strcpy(searchText, argv[2]);
    	searchTextLen = strlen(searchText);

    	//printf("Argc: %d, %s\n", argc, argv[2]);
    	//return 0;
    }
	//printf("parity: %0.2X\n",get_gps_cmd_parity(argv[1]));
    //message_set(argv[1]);
    ml = get_message_list(argv[1]);
    if(ml){
    	print_message_list(ml);
    }
    free_message_list(ml);
    return 0;

	sfl_init(&sfl);

	newDirEntry = malloc(sizeof(Directory));
    if(newDirEntry == NULL)
	{
	  printf("Bellekte yer kalmadı!\n");
	  exit(EXIT_FAILURE);
	}

    stack_init(&stack);
    stack_init(&foundStack);

	newDirEntry->plen = strlen(argv[1])+1;
	memcpy(newDirEntry->path, argv[1], newDirEntry->plen);
	
	sprintf(newDirEntry->ident, " ");
	newDirEntry->ilen = strlen(newDirEntry->ident) + 1;

	stack_push(&stack, newDirEntry);

	printf("BuiltTime: %s\n", __TIME__);
	
	while((dirEntry = stack_pop(&stack)) != NULL)
	{
		if(NULL == (dp = opendir(dirEntry->path)) )
		{
			printf("\n Cannot open Input directory [%s]\n",dirEntry->path);
			exit(EXIT_FAILURE);
		}

		printf("%s[dr: %s]\n",dirEntry->ident,dirEntry->path);

		while(NULL != (dptr = readdir(dp)) )
		{
			strncpy(subDirPath, dirEntry->path, dirEntry->plen);

			if(subDirPath[dirEntry->plen-2]=='/')
			{
			   sprintf(subDirPath + dirEntry->plen-1, "%s", dptr->d_name);
			}
			else
			{
			   sprintf(subDirPath + dirEntry->plen-1, "/%s", dptr->d_name);
			}

			if((subDir = opendir(subDirPath)) != NULL)
			{
			    
			    if(strcmp(dptr->d_name, ".") != 0 &&
				   strcmp(dptr->d_name, "..") != 0)
				{
					//printf(" %s[dr: %s]\n",dirEntry->ident,dptr->d_name);

					newDirEntry = malloc(sizeof(Directory));
					if(newDirEntry == NULL)
					{
					  printf("Bellekte yer kalmadı!\n");
					  exit(EXIT_FAILURE);
					}

					newDirEntry->plen = strlen(subDirPath)+1;
					memcpy(newDirEntry->path, subDirPath, newDirEntry->plen);
	
					sprintf(newDirEntry->ident, "%s  ", dirEntry->ident);
					newDirEntry->ilen = strlen(newDirEntry->ident) + 1;

					stack_push(&stack, newDirEntry);
				}

			    closedir(subDir);
			}
			else
			{  

				totalFileCount++;
				lnCoutnInFileX = 0;
				lrCoutnInFileX = 0;
				nvCoutnInFileX = 0;
				i = strlen(dptr->d_name);

				if((dptr->d_name[i-2] == '.' && dptr->d_name[i-1] == 'h' ) ||
				   (dptr->d_name[i-2] == '.' && dptr->d_name[i-1] == 'H' ))
				{			
				   hFileCount++;
				   boolCountLines = 1;
				}
				else if((dptr->d_name[i-2] == '.' && dptr->d_name[i-1] == 'c' ) ||
				   (dptr->d_name[i-2] == '.' && dptr->d_name[i-1] == 'C' ))
				{				   
				   cFileCount++;
				   boolCountLines = 1;
				}
				else if((dptr->d_name[i-4] == '.' && dptr->d_name[i-3] == 'c' && dptr->d_name[i-2] == 'p' && dptr->d_name[i-1] == 'p') ||
				   (dptr->d_name[i-4] == '.' && dptr->d_name[i-3] == 'C' && dptr->d_name[i-2] == 'P' && dptr->d_name[i-1] == 'P') )
				{				
				   cppFileCount++;
				   boolCountLines = 1;
				}
				else if((dptr->d_name[i-4] == '.' && dptr->d_name[i-3] == 't' && dptr->d_name[i-2] == 'x' && dptr->d_name[i-1] == 't') ||
					   (dptr->d_name[i-4] == '.' && dptr->d_name[i-3] == 'T' && dptr->d_name[i-2] == 'X' && dptr->d_name[i-1] == 'T') )
			    {

				    boolCountLines = 1;
				}
				else if((dptr->d_name[i-2] == '.' && dptr->d_name[i-1] == 'o' ) ||
				   (dptr->d_name[i-2] == '.' && dptr->d_name[i-1] == 'a' ))
				{
				   boolCountLines = 0;
				}
				else
				{
				   boolCountLines = 1;
				}

				if(boolCountLines)
				{
					printf("%s ",subDirPath);

					fp = fopen(subDirPath, "r+b");
					
					if(fp != NULL)
					{
					   fseek ( fp , 0 , SEEK_END );
				       fsize = ftell ( fp );

					   printf(" (size: %d byte", fsize);
					   fseek ( fp , 0 , SEEK_SET );
				   
					   rsize = 0;
					   
					   fe = (File*) malloc( sizeof(File) );
					   if(fe == NULL)
					   {
					      printf("Bellek hatası\n");
						  exit(EXIT_FAILURE);
					   }

					   memset(fe, 0 , sizeof(File));

					   fe->plen = strlen(subDirPath) + 1;
					   strncpy(fe->path, subDirPath, fe->plen);
					   
					   fe->nlen = strlen(dptr->d_name) + 1;
					   strncpy(fe->name, dptr->d_name, fe->nlen);
					   
					   fe->size = fsize;
					   
					   if( maxFilePathLen < fe->plen )
						   maxFilePathLen = fe->plen;

					   if( maxFileNameLen < fe->nlen )
						   maxFileNameLen = fe->nlen;

					   searchWindowLen   = 0;
					   searchWindowWrIdx = 0;
					   searchWindowRdIdx = 0;

					   while(rsize < fsize)
					   {
						   
						   if(fsize - rsize > RBUF_LEN)
							  blen  = fread (rbuf, 1, RBUF_LEN     , fp);
						   else
							  blen  = fread (rbuf, 1, fsize - rsize, fp);
					   
						   rsize += blen;
					       
						   for(i = 0; i < blen; i++)
						   {
							  if(rbuf[i] == '\n')
							  { 
								  lnCount++;
								  lnCoutnInFileX++;
								  fe->lnCount++;
							  }
							  if(rbuf[i] == '\r')
							  {
								  lrCount++;
								  lrCoutnInFileX++;
								  fe->lrCount++;
							  }
							  if(rbuf[i] == ';')
							  {
								  nvCount++;
								  nvCoutnInFileX++;
								  fe->nvCount++;
							  }
							  if(bSearchText)
							  {
								  if(searchWindowLen < searchTextLen)
								  {
									  if(searchWindowWrIdx >= RBUF_LEN)
										  searchWindowWrIdx = 0;

									  searchWindow[searchWindowWrIdx++] = rbuf[i];
									  searchWindowLen++;
								  }

								  if(searchWindowLen == searchTextLen)
								  {
									  found = 1;
									  wi = searchWindowRdIdx;
									  for(si = 0; si < searchTextLen; si++)
									  {
										  if(searchWindow[wi] != searchText[si])
										  {
											  found = 0;
											  break;
										  }
										  wi++;
										  if(wi >= RBUF_LEN)
											  wi = 0;

									  }
									  if(found)
									  {
										  foundKayit = (Found*)malloc(sizeof(Found));
										  if(foundKayit == NULL)
										  {
											  printf("Bellek hatası!\n");
											  exit(EXIT_FAILURE);
										  }
										  foundKayit->atLine = fe->lnCount;
										  memcpy(foundKayit->path, fe->path, PATH_LEN_MAX);
										  memcpy(foundKayit->searchWindow, searchWindow, RBUF_LEN);

										  for(si = 1; si <= 50; si++)
										  {
											  if(si + i >= blen)
												  break;
											  foundKayit->searchWindow[(searchWindowWrIdx+si-1)%RBUF_LEN] = rbuf[si+i];
										  }

                                          foundKayit->startIndex = searchWindowRdIdx;
										  stack_push(&foundStack, (void*)foundKayit);
									  }
									  searchWindowRdIdx++;
									  if(searchWindowRdIdx >= RBUF_LEN)
										  searchWindowRdIdx = 0;
									  searchWindowLen--;
								  }
							  }
						   }
					   }

					   fe->id = fe->lnCount;
					   sfl_add(&sfl, fe);

					   printf(", ln: %d, lr: %d, nv: %d)\n", lnCoutnInFileX, lrCoutnInFileX, nvCoutnInFileX);
					   fclose(fp);
					}
					else
					{
					  printf("!open\n");
					}
				}
			    
			}
		}
		closedir(dp);
	}


	j = 0;

	while(sfl.first != NULL)
	{

	  fln = sfl.first;

	  fe = (File*)fln->data;

	  sfl.first = sfl.first->next;
	  i = sprintf(rbuf, "%s", fe->name);
	  while(i < maxFileNameLen+1)
	    i += sprintf(rbuf + i, " ");
	  i += sprintf(rbuf + i, ":");
	  printf(rbuf);

	  j += fe->lnCount;
	  
	  printf("= size: %6d, ln: %5d, cln: %6d, yzd: %0.2f, cyzd: %0.2f , lr: %d, nv: %5d\n", fe->size, fe->lnCount,j,
		  ((double)fe->lnCount)/((double)lnCount)*100.0,((double)j)/((double)lnCount)*100.0, fe->lrCount, fe->nvCount);

	  free(fe);
	  free(fln);
	}

	printf("fileCount: %d, *.h: %d, *.c: %d, *.cpp: %d, lnCount: %d, lrCount: %d, nvCount: %d\n",
		    totalFileCount, hFileCount, cFileCount, cppFileCount, lnCount, lrCount, nvCount);

	if(bSearchText)
	{
		i = 0;
		while((foundKayit = stack_pop(&foundStack)) != NULL)
		{
			printf("%0.3d: at line %0.4d in file: %s\n", ++i, foundKayit->atLine, foundKayit->path);
			si = foundKayit->startIndex - 10;
			if(si < 0)
				si = RBUF_LEN - 10;
			for(wi = 0 ; wi < searchTextLen + 30; wi++)
			{
				printf("%c", foundKayit->searchWindow[si]);

				si++;

				if(si >= RBUF_LEN)
					si = 0;
			}
			printf("\n");
			free(foundKayit);
		}

	}
    return 0;
}
