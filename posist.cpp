#include <iostream>
#include <map>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
map<int , int> nodeIDs;
int curr1 = 0;

struct Data {
    string owner_name ;
    string address ;
    string mobile_no ;
    string phone ;
    float value ;
};

struct node {
    time_t t_node ;
    string time ;
    Data data_node ;
    int nodeID ;
    int node_number ;
    node *ref_ParentID ;
    node *ref_ChildNode ;
    void putData(Data data_node, node *hdr);
    void getData(Data data_node);
};

map<int, node> map_node;
//cipher
string encrypt(string str, int key) {
    for (int i = 0 ; i < str.length() ; i++) {
        if (isupper(str[i])) {
            str[i] = (char)(((int)str[i]+key-65)%26+65);
        }else {
            str[i] = (char)(((int)str[i]+key-97)%26+97);
        }
    }
    return str;
}

//Decrypt
string decrypt(string str, int key) {
    for (int i = 0 ; i < str.length() ; i++) {
        if (isupper(str[i])) {
            str[i] = (char)(((int)str[i]-key-65)%26+65);
        }else {
            str[i] = (char)(((int)str[i]-key-97)%26+97);
        }
    }
    return str;
}

void node::getData(Data data_node) {
    cout << "Owner Name : " << data_node.owner_name << endl ;
    cout << "Address : " << data_node.address << endl ;
    cout << "Mobile number : " << data_node.mobile_no << endl ;
    cout << "Phone nymber : " << data_node.phone << endl;
    cout << "Value : " << data_node.value << endl;
}

void node::putData(Data d_node, node *hdr) {
    cout << "Enter Owner Name : " ;
    cin >> d_node.owner_name ;
    cout << "Enter Address : " ;
    cin >> d_node.address ;
    cout << "Enter Mobile Number : " ;
    cin >> d_node.mobile_no ;
    cout << "Enter Phone Number : " ;
    cin >> d_node.phone ;
    cout << "Enter value : " ;
    cin >> d_node.value ;
    hdr->data_node = d_node;
}

 //Creating new node
node *Create_newNode(node *parent) {
    // Allocating memory
    node *n = new node ;
    
    // Tme stamp of data
    n->t_node = time(0) ;
    struct tm * curr = localtime(&n->t_node) ;
    int yy = (curr->tm_year + 1900), mm = (curr->tm_mon + 1), dd = (curr->tm_mday) ;
    
    // Converting into date-time format
    n->time = yy+'-'+mm+'-'+dd ;
    
    // Retrieve data
    n->putData(n->data_node, n);
    
    // Initializing node number and the ref parent ID
    if (curr1 == 0) {
        n->node_number = 1;
        curr1 += 1;
        n->ref_ParentID = NULL;
    }else {
        n->node_number = curr1;
        curr1 += 1;
        n->ref_ParentID = parent;
    }
    
    //Generating nodeID 
    int nID ;
    do {
        nID = rand() % 100000 + 1;
    }while (nodeIDs[nID] != 0);
    nodeIDs[nID] = 1;
    n->nodeID = nID;
    
    // assigning value to ref_ChildNode
    n->ref_ChildNode = NULL;
    
    return n;
}

class Admin {
    
public:
    
    node *Hdr;
    node* childNode[];
    
    // Header node
    Admin *create_firstNode(node *new_node) {
        Admin *n1 = new Admin;
        n1->Hdr = new_node;
        return n1;
    }
    
    // Creating MultiSet of header node
    void createMultiSet(Admin *head) ;
    
    // Adding new node to multiset
    void add_newNode(Admin *head, int nodeNum,int n) ;
    
    // Encryption
    void EncryptNodeData(int node_number, int key, int password) ;
    
    // Verify owner
    bool verifyOwner(int key, int password) ;
    
    // Analysing
    void breakUpNode(int key, int password) ;
    
    // Transfer Owner
    void transferOwner(int key, int value, int nodeID) ;
    
    // Finding longer Chain
    void findLongerChain() ;
    
    // Merging two given nodes
    void mergeNode(node *node1, node *node2) ;
} ;

void Admin::createMultiSet(Admin *head) {
    cout << "Wants to create multi set of the node?\n" ;
    int n ;
    cin >> n ;
    for (int i = 0 ; i < n ; i++) {
       
        // Initialize new node
        head->childNode[i] = new node ;
        
        //Initializing reference parent node 
        head->childNode[i]->ref_ParentID = head->Hdr;
        
        //Initializing referrence child node
        head->childNode[i]->ref_ChildNode = NULL;
        
        //Initializing childnode
        head->childNode[i]->node_number = curr1 ;
        curr1++ ;
        map_node[head->childNode[i]->node_number] = *head->childNode[i];
    }
}

// taking n as multiset size
void Admin::add_newNode(Admin *head,int nodeNum, int n) {
    node *add_newNodeH = NULL ;
    for (int i = 0 ; i < n ; i++) {
        if (head->childNode[i]->node_number == nodeNum) {
            add_newNodeH = head->childNode[i];
            break;
        }
    }
    // add new node
    if (add_newNodeH != NULL) {
        node *ChildNode = new node;
        ChildNode = Create_newNode(add_newNodeH);
    }
}

	//verify owner
bool Admin::verifyOwner(int key, int password) {
    //require database
    return true;
}

void Admin::EncryptNodeData(int node_number, int key, int password) {
    //finding node_number
    node *temp = new node;
    temp = &map_node[node_number] ;
    if (temp == NULL) {
        cout << "Doesn't Exists!\n";
    }else {
        if (verifyOwner(key, password)) {
            Data dr = temp->data_node;
            encrypt(dr.owner_name , key);
            encrypt(dr.address, key);
            encrypt(dr.mobile_no, key);
            encrypt(dr.phone, key);
            encrypt(dr.phone, key);
        }
    }
}


void Admin::breakUpNode(int key, int password) {
    // require access to database
}

void Admin::transferOwner(int key, int value, int nodeID) {
    // require access to database
}

void Admin::findLongerChain() {
    // applying dfs on findingLongerChain can work
}

void Admin::mergeNode(node *node1, node *node2) {
    // Find the lowest common ancestor of the two nodes.
    // the lca found suppose x
    // merge both the nodes
}

int main(int argc, const char * argv[]) {
    Admin *d = new Admin;
    d->Hdr = new node;
    d->Hdr = Create_newNode(d->Hdr);
    d->Hdr->getData(d->Hdr->data_node);
    return 0;
}
