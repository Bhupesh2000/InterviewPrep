class Node{
public:
    int data;
    Node* next;
    Node(int data){
        this -> data = data;
        next = NULL;
    }
};

Node* insertAtStart(Node* root, int data){
    Node* newNode = new Node(data);
    newNode -> next = root;
    return newNode;
}

Node* insertAtEnd(Node* root, int data){
    Node* newNode = new Node(data);
    if(!root) return newNode;
    Node* temp = root;
    while(temp -> next) temp = temp -> next;
    temp -> next = newNode;
    return root;
}

Node* insertAtMid(Node* root, int data){
    Node* newNode = new Node(data);
    if(!root) return newNode;
    Node* slow = root;
    Node* fast = root -> next;
    while(fast && fast -> next){
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    Node* temp = slow -> next;
    slow -> next = newNode;
    newNode -> next = temp;
    return root;
}

Node* deleteFromStart(Node* root){
    if(!root) return root;
    Node* temp = root -> next;
    root -> next = NULL;
    delete root;
    return temp;
}

Node* deleteFromEnd(Node* root){
    if(!root) return root;
    if(!root -> next){
        delete root;
        return NULL;
    }
    Node* temp = root;
    while(temp -> next -> next){
        temp = temp -> next;
    }
    Node* temp2 = temp -> next;
    temp -> next = NULL;
    delete temp2;
    return root;
}
