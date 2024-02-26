//
//
//  habibe.koseoglu_Koseoglu_Habibe_hw3.cpp
//
//
//

#include <iostream>
#include <fstream>       // for ifstream
#include <cctype>
#include <string>
#include <vector>
#include <sstream>      // std::stringstream
using namespace std;

struct costnode{             // the struct of the costvector in order to store total cost
    string name;
    int ID;
    int payment;
    
    costnode(){ };
    costnode(string name1, int id, int pym){
        name= name1;
        ID= id;
        payment= pym;
    }
};
struct node {       // the node of linked list which includes statements like call, define , print stack
    
    string statement;
    node* next;
};

struct nodefunc {    // the node of linked list which includes function names
    
    string name;
    nodefunc* next;
    node* statements;
};

struct StackNode    // struct of the sharedstack
{
    string functionname;
    string definevalues;
    StackNode *next;
};

class DynIntStack       // in order to make sharedstack
{
private:
    StackNode *top;

public:
    DynIntStack(void);
    void push(string, string);
    void pop(string &, string &);
    bool isEmpty(void);
};

DynIntStack::DynIntStack()
{
    top = nullptr;
}
void DynIntStack::push(string func, string dvalue)
{
    StackNode *newNode;
    // Allocate a new node & store Num
    newNode = new StackNode;
    newNode->functionname = func;
    newNode->definevalues= dvalue;

    // If there are no nodes in the list
    // make newNode the first node
    if (isEmpty())
    {
        top = newNode;
        newNode->next = nullptr;
    }
    else    // Otherwise, insert NewNode before top
    {
        newNode->next = top;
        top = newNode;
    }
}
void DynIntStack::pop(string &func, string &dvalue)
{
    StackNode *temp;

    if (isEmpty())
    {
        cout << "The stack is empty.\n";
    }
    else    // pop value off top of stack
    {
        func = top->functionname;
        dvalue = top->definevalues;
        temp = top->next;
        delete top;
        top = temp;
    }
}
bool DynIntStack::isEmpty(void)
{
    bool status;

    if (top == nullptr)
        status = true;
    else
        status = false;

    return status;
}


struct inst{        // struct for instructor queue
    
    string name;
    int ID;
    string request;

    inst(){
        
    }
    inst (string name1, int id, string reqst){
        name= name1;
        ID= id;
        request= reqst;
    }
};

class IntQueue            // in order to make instructor queue
{
private:
    inst *queueArray;
    int queueSize;  //capacity of queue
    int front;        // holds index in an array
    int rear;
    int numItems;  //# of elements currently in the queue
public:
    IntQueue(int);  //constructor, parameter is capacity
    void enqueue(inst);
    void dequeue(inst &);
    bool isEmpty() const;
    bool isFull() const;
};


IntQueue::IntQueue(int s)
{
    queueArray = new inst[s];
    queueSize = s;
    front = -1;
    rear = -1;
    numItems = 0;

}

void IntQueue::enqueue(inst num)
{
    if (isFull())
   {
      cout << "The queue is full. " << endl;
   }
    else
    {
        // Calculate the new rear position circularly.
        rear = (rear + 1) % queueSize;
        // Insert new item.
        queueArray[rear] = num;
        // Update item count.
        numItems++;
    }
}

void IntQueue::dequeue(inst &num)
{
    if (isEmpty())
    {
        cout << "Attempting to dequeue on empty queue, exiting program...\n";
        exit(1);
   }
    else
    {
        // Move front.
        front = (front + 1) % queueSize;
        // Retrieve the front item.
        num = queueArray[front];
        // Update item count.
        numItems--;
    }
}

bool IntQueue::isEmpty() const
{
    if (numItems > 0)
        return false;
    else
        return true;
}

bool IntQueue::isFull() const
{
    if (numItems < queueSize)
        return false;
    else
        return true;
}

struct QueueNode        // struct for students queue
{
    string name;
    int ID;
    string request;
    QueueNode *next;
    QueueNode(string name1, int num, string func, QueueNode *ptr = nullptr)
    {
        name = name1;
        ID = num;
        request = func;
        next = ptr;
    }
};

class DynIntQueue        // in order to make students queue
{
private:
    // These track the front and rear of the queue.
    QueueNode *front;
    QueueNode *rear;
public:
    DynIntQueue(); // Constructor.
    // Member functions.
    void enqueue(string, int, string);
    void dequeue(string &, int &, string &);
    bool isEmpty() const;
};

DynIntQueue::DynIntQueue()
{
    front = nullptr;
    rear = nullptr;
}

void DynIntQueue::enqueue(string name1, int num, string func)
{
    if (isEmpty())   //if the queue is empty
    {    //make it the first element
        front = new QueueNode(name1, num, func);
        rear = front;
    }
    else  //if the queue is not empty
    {    //add it after rear
        rear->next = new QueueNode(name1, num, func);
        rear = rear->next;
    }
}
void DynIntQueue::dequeue(string &name1, int &num, string &func)
{
    QueueNode *temp;
    if (isEmpty())
    {
        cout << "Attempting to dequeue on empty queue, exiting program...\n";
        exit(1);
    }
    else //if the queue is not empty
    {    //return front's value, advance front and delete old front
        name1 = front-> name;
        num = front->ID;
        func = front-> request;
        temp = front;
        front = front->next;
        delete temp;
    }
}

bool DynIntQueue::isEmpty() const
{
    if (front == nullptr)
        return true;
    else
        return false;
}


void addInstructorWorkload(nodefunc* headfunc, IntQueue &instructorsQueue, vector <costnode> &costvector){
    // gets head of the linkedlist, instructors' queue and costvector as parameter
    string service, ss;
    cout << "Add a service (function) that the instructor wants to use:"<< endl;
    cin >> service;
    
    bool isthere = false;   // to check if the given function name is exist
    nodefunc* ptr = headfunc;
    while (ptr) {
        if ((ptr->name)== (service)) {
            isthere = true;
            break;
        }
        else {
            ptr= ptr->next;
        }
    }
    if (!isthere) { // if the function name does not exist
        cout << "The requested service (function) does not exist."<< endl;
        cout << "GOING BACK TO MAIN MENU" << endl;
    }
    else {
        string nm;
        int id;
        cout << "Give instructor's name: " ;
        cin >> nm;
        cout << "Give instructor's ID (an int): " ;
        cin >> id;
        inst temp(nm, id, service);
        bool isinvector =false;  // to check if the instuctor with same id and name is given before
        for (int j=0; j<costvector.size(); j++) {
            if (costvector[j].name==nm && costvector[j].ID==id) {
                isinvector = true;
            }
        }
        if (!isinvector) {   // if it is not given append it to the costvector
            costnode costnodetemp(nm, id, 0);
            costvector.push_back(costnodetemp);
        }
        
        instructorsQueue.enqueue(temp);   // enqueue the request of instructor
     
        cout << "Prof. "<< nm <<"'s service request of " << service << endl;
        cout << "has been put in the instructor's queue." << endl << "Waiting to be served..."<< endl;
        
    }
}
void addStudentWorkload(nodefunc* headfunc, DynIntQueue &studentsQueue, vector <costnode> &costvector){
    
    string service;
    cout << "Add a service (function) that the student wants to use:" << endl;
    cin >> service;
    bool isthere = false;   // to check if the given function name is exist
    nodefunc* ptr = headfunc;
    while (ptr) {
        if ((ptr->name)== (service)) {
            isthere = true;
            break;
        }
        else {
            ptr= ptr->next;
        }
    }
    if (!isthere) {    // if the function name does not exist
        cout << "The requested service (function) does not exist."<< endl;
        cout << "GOING BACK TO MAIN MENU" << endl;
    }
    else {
        string nm;
        int id;
        cout << "Give student's name: " ;
        cin >> nm;
        cout << "Give student's ID (an int): " ;
        cin >> id;
        
        studentsQueue.enqueue(nm, id, service);
        
        bool isinvector =false; // to check if the student with same id and name is given before
        for (int j=0; j<costvector.size(); j++) {
            if (costvector[j].name==nm && costvector[j].ID==id) {
                isinvector = true;
            }
        }
        if (!isinvector) {   // if it is not given append it to costvector
            costnode costnodetemp(nm, id, 0);
            costvector.push_back(costnodetemp);
        }

        cout << nm << "'s service request of "<< service <<" has been put in the student's queue." << endl;
        cout << "Waiting to be served..." << endl;
    }
 
}
void printstack(DynIntStack & sharedstack){  // to print the stack without changing its structure
    if (sharedstack.isEmpty()) {
        return;
    }
    string func, command;
    sharedstack.pop(func, command);
    printstack(sharedstack);
    cout << func << " " <<command << endl;
    sharedstack.push(func, command);
}
void processWorkload(nodefunc* headfunc, string functionn, DynIntStack & sharedstack, int & cost){

    int countstack=0;
    nodefunc* ptr = headfunc;
    while (ptr) {
        if (ptr->name == functionn) {
            
            node* ptr2 = ptr->statements;
            
            while (ptr2) {
                
                if ((ptr2->statement).substr(0,6)=="define") {         // check if it is "define"
                    sharedstack.push(functionn+":", ptr2->statement);
                    countstack++;
                    cost++;
                }
                else if ((ptr2->statement).substr(0,11)== "print stack") {    // check if it is print stack
                    cout << "Executing " << ptr2->statement << " command from " << functionn << endl;
                    cout << "PRINTING THE STACK TRACE:" << endl;
                    if (sharedstack.isEmpty()) {
                        cout << "The stack is empty" << endl;
                        cost = cost+2;
                    }
                    else{
                        printstack(sharedstack);
                        cost = cost+2;
                    }
                }
                else if ((ptr2->statement).substr(0,4) == "call") {      // check if it is function call
                    cost = cost + 5;
                    string rfunc = (ptr2->statement).substr(5,10);   // called function = rfunc
                    cout << "Calling " << rfunc << " from " << functionn << endl;
                    processWorkload(headfunc, rfunc, sharedstack, cost); // process the function recursively
                }
                
                if (!(ptr2->next)) {           // if function is about to finish clear stack from its data
                    cout << functionn << " is finished. Clearing the stack from it's data..." << endl;
                    for (int i=0; i<countstack; i++) {
                        string ff, cc;        // function and command
                        sharedstack.pop(ff, cc);
                    }
                }
                ptr2= ptr2->next;
            }
            
        }
        ptr= ptr->next;
    }
    
    
    
    
}
void displayUsers(vector <costnode> &costvector){
    if (costvector.empty()) {
        cout << "No payments defined." << endl;
    }
    for (int k=0; k< costvector.size(); k++) {
        cout << "Name: "<< costvector[k].name <<" ID: " << costvector[k].ID << " "<< costvector[k].payment <<" TRY"<< endl;
    }

}
//TODO: Modify this part to make sure to impelement the logic for 10 requests for instructors and 1 request for students
void processWorkload(IntQueue &instructorsQueue, DynIntQueue &studentsQueue, int &count,nodefunc* headfunc, DynIntStack & sharedstack, vector<costnode> &costvector)
{
    if ((!instructorsQueue.isEmpty()) && count!=10 )
    {
        int cost=0;
        cout<<"Processing instructors queue..."<<endl;
        inst temp;
        instructorsQueue.dequeue(temp);
        cout<<"Processing prof."<< temp.name <<"'s request (with ID "<< temp.ID <<") of service (function):\n"<< temp.request << endl;
        cout << "-------------------------------------------------------" << endl;
        processWorkload(headfunc, temp.request, sharedstack, cost); // to process the given function
        for (int k=0; k< costvector.size(); k++) {  // check every element in the cost vector
            if((costvector[k].ID == temp.ID) && (costvector[k].name == temp.name)){   // if the element has same and same id with given instructor
                costvector[k].payment= costvector[k].payment + cost;                  // add the cost to it
            }
        }
        count++;
        
        cout<<"GOING BACK TO MAIN MENU"<<endl;
    }
    else if (!studentsQueue.isEmpty())
    {
        if (count==10) {
            int cost=0;
            cout<<"10 instructors are served. Taking 1 student from the queue..."<<endl;
            string name1, func;
            int num;
            studentsQueue.dequeue(name1, num, func);
            cout <<"Processing "<< name1 <<"'s request (with ID "<< num <<") of service (function):\n"<< func <<endl;
            cout <<"-------------------------------------------------------" << endl;
            processWorkload(headfunc, func, sharedstack, cost);   // same logic with for instructors
            for (int k=0; k< costvector.size(); k++) {
                if((costvector[k].ID == num) && (costvector[k].name == name1)){
                    costvector[k].payment= costvector[k].payment + cost;
                }
            }
            count++;
            
        }

        else {
            int cost=0;
            string name1, func;
            int num;
            studentsQueue.dequeue(name1, num, func);
            cout<<"Instructors queue is empty. Proceeding with students queue..."<<endl;
            cout<<"Processing "<< name1 <<"'s request (with ID "<< num <<") of service (function):\n"<< func <<endl;
            cout<<"-------------------------------------------------------"<<endl;
            processWorkload(headfunc, func, sharedstack, cost);   // same logic with for instructors
            for (int k=0; k< costvector.size(); k++) {
                if((costvector[k].ID == num) && (costvector[k].name == name1)){
                    costvector[k].payment= costvector[k].payment + cost;
                }
            }
        }
        
        cout<<"GOING BACK TO MAIN MENU"<<endl;
    }
    else
    {
        cout<<"Both instructor's and student's queue is empty.\nNo request is processed."<<endl<<"GOING BACK TO MAIN MENU"<<endl;
    }
}

int main()
{
    string filename, key;
    cout << "If you want to open a service (function) defining file," << endl << "then press (Y/y) for 'yes', otherwise press any single key"<< endl;
    cin >> key;
    if (key== "y" || key=="Y") {
        cout << "Enter the input file name: ";
        cin >> filename;
        ifstream input(filename);
        if (input.fail()) {
            
            cout << "Could not open the file " << filename << endl;
        }
        else{
            int count = 0; // to check processing 10 instuctor
            vector <costnode> costvector;
            DynIntStack sharedstack;
            DynIntQueue studentsQueue;
            IntQueue instructorsQueue(500);
            string line;
            getline(input, line);                    // for making linked list
            string funcname= line.substr(0,line.length()-2);    // to delete \r and ":"
            nodefunc* tempfunc = new nodefunc;
            nodefunc* headfunc = new nodefunc;
            tempfunc->name = funcname;
            tempfunc->next= nullptr;        // for the first input
            headfunc= tempfunc;
            getline(input, line);
            node* headnode = new node;
            headnode->statement = line.substr(0,line.length()-1);  // to delete \r
            tempfunc->statements = headnode;
            while (getline(input, line)) {
                node* tempnode = new node;
                tempnode->statement= line.substr(0,line.length()-1);    // to delete "\r" but at the end of the input to delete ";"
                tempnode->next=nullptr;
                headnode->next= tempnode;
                headnode= tempnode;
            }
            
            do {
                cout << "Do you want to open another service defining file?" << endl << "Press (Y/y) for 'yes', otherwise press anykey" << endl;
                cin >> key;
                if (key== "y" || key=="Y") {
                    cout << "Enter the input file name: ";
                    cin >> filename;
                    ifstream input2(filename);
                    if (input2.fail()) {
                        
                        cout << "Could not open the file " << filename << endl;
                        break;
                    }
                    else {
                        getline(input2, line);                         // for making linked list
                        funcname= line.substr(0,line.length()-2);          // to delete \r and ":"
                        nodefunc* tempfunc2 = new nodefunc;
                        tempfunc2->name = funcname;
                        tempfunc2->next= nullptr;
                        tempfunc->next= tempfunc2;
                        getline(input2, line);
                        node* headnode2 = new node;
                        headnode2->statement = line.substr(0,line.length()-1);       // to delete \r
                        tempfunc2->statements = headnode2;
                        while (getline(input2, line)) {
                            node* tempnode2 = new node;
                            tempnode2->statement= line.substr(0,line.length()-1);        // to delete "\r" but at the end of the input to delete ";"
                            tempnode2->next=nullptr;
                            headnode2->next= tempnode2;
                            headnode2= tempnode2;
                        }
                        tempfunc= tempfunc2;
                    }
                }

            } while (key== "y" || key=="Y");
            
            cout << "------------------------------------------------------------------" << endl;
            cout << "PRINTING AVAILABLE SERVICES (FUNCTIONS) TO BE CHOSEN FROM THE USERS" << endl;
            cout << "------------------------------------------------------------------" << endl << endl;
            
            nodefunc* ptr = headfunc;                                    // print linked list
            while (ptr) {
                cout << "\n" << ptr->name << ":" <<endl;
                node* ptr2 = ptr->statements;
                while (ptr2->next!=nullptr) {
                    cout << ptr2->statement << ", ";
                    ptr2= ptr2->next;
                }
                cout << ptr2->statement << "." << endl ;
                ptr= ptr->next;
            }
            while (true){
                
                cout << endl;
                cout<<"**********************************************************************"<<endl
                <<"**************** 0 - EXIT PROGRAM                        *************"<<endl
                <<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST   *************"<<endl
                <<"**************** 2 - ADD A STUDENT SERVICE REQUEST       *************"<<endl
                <<"**************** 3 - SERVE (PROCESS) A REQUEST           *************"<<endl
                <<"**************** 4 - DISPLAY USER PAYMENTS               *************"<<endl
                <<"**********************************************************************"<<endl;
                cout << endl;
                int option;
                cout << "Pick an option from above (int number from 0 to 3): ";
                cin>>option;
                switch (option)
                {
                    case 0:
                        cout<<"PROGRAM EXITING ... "<<endl;
                        exit(0);
                    case 1:
                        addInstructorWorkload(headfunc, instructorsQueue, costvector);
                        break;
                    case 2:
                        addStudentWorkload(headfunc, studentsQueue, costvector);
                        break;
                    case 3:
                        processWorkload(instructorsQueue, studentsQueue, count, headfunc, sharedstack, costvector);
                        if (count==11) {   //if 10 instructors and after that 1 student are served make count=0
                            count=0;
                        }
                        break;
                    case 4:
                        displayUsers(costvector);
                        break;
                    default:
                        cout<<"INVALID OPTION!!! Try again"<<endl;
                }
            }
            
            
            
        }
    }

    

    return 0;
}
