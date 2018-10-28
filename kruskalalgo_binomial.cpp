#include<stdio.h>
#include<malloc.h>

#include<bits/stdc++.h>

using namespace std;


//node structure
struct node 
{
    int u,v;
    int w;
    int degree;
    struct node* parent;
    struct node* child;
    struct node* sibling;
}*H=NULL,*Hr=NULL;


//node creation 
struct node* create_node(int v1,int v2,int weight) 
{
    struct node* p;
    p=new node;
    p->u =v1;
    p->v =v2;
    p->w =weight;
    return p;
}


//heap initialisation 
struct node* initialise_heap() 
{
    struct node* np;
    np = NULL;
    return np;
}


// print function for Binomial Tree 
void printTree(node *h) 
{ 
    while (h) 
    { 
        cout << h->w << " "; 
        printTree(h->child); 
        h = h->sibling; 
    }
  //  cout<<endl; 
} 
 
//merging two heaps 
struct node* simply_merging(struct node* H1, struct node* H2) 
{
    

    // cout<<"\nin simply merging\n";
    // cout<<"unmerged (H1): ";
    //             printTree(H1);

    // cout<<"unmerged (Hr): ";
    //             printTree(H2);
     
    // cout<<endl;


    struct node* H = initialise_heap();
    struct node* y;
    struct node* z;
    struct node* a;
    struct node* b;
    y = H1;
    z = H2;
   
        if (y!=NULL && z != NULL && y->degree <= z->degree)
            H = y;
        else if (y!=NULL && z != NULL && y->degree > z->degree)
            H = z;
        else if (z==NULL )
            H = y;
        else
            H = z;
    
    while (y != NULL && z != NULL) 
    {
        if (y->degree < z->degree) 
        {
            y = y->sibling;
        }
        else if(z->sibling && z->degree<z->sibling->degree && z->sibling->degree < y->degree)
        {
           z = z->sibling;  
        } 
        else if (y->degree == z->degree) 
        {
            a = y->sibling;
            y->sibling = z;
            y = a;
        } 
        else 
        {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }


    
     // cout<<"\nin simply merging\n";
    // cout<<"merged heap is (H1+Hr): ";
    //             printTree(H);
    //             cout<<endl;

  

   
    return H;
}

//merging two same degree nodes
int linking_same_degnodes(struct node* y, struct node* z) 
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}
 

// union of two heaps 
struct node* union_of_heaps (struct node* H1, struct node* H2) 
{
   // cout<<"union_of_heaps";
    
    struct node* prev_x;
    struct node* next_x;
    struct node* x;
    struct node* H = initialise_heap();
    // struct node* H = new node;
    H = simply_merging(H1, H2);
    if (H == NULL)
        return H;
   
    prev_x = NULL;
    x = H;
    next_x = x->sibling;
   
    while (next_x != NULL) 
    {
        if ((x->degree != next_x->degree) ) 
        {
            prev_x = x;
            x = next_x;
        } 
        else if ((x->degree == next_x->degree) && (next_x->sibling != NULL) && (next_x->sibling)->degree == x->degree)
        {
             prev_x = x;
             x = next_x;
        }
        else 
        {
            if (x->w <= next_x->w) 
            {
                x->sibling = next_x->sibling;
                linking_same_degnodes(next_x, x);
            } 
            else 
            {
                if (prev_x == NULL)
                { 
                    H = next_x;
                }
                else
                {
                    prev_x->sibling = next_x;
                }

                linking_same_degnodes(x, next_x);
                x = next_x;
            }
        }
        
        next_x = x->sibling;
    }
    return H;
}

//insert operation 
struct node* insert(struct node* H, struct node* x) 
{
     struct node* H1 = initialise_heap();
    // struct node* H1 = new node;

    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = union_of_heaps(H, H1);
    return H;
}


//printing only root elements 
int display_root_elements(struct node* H) 
{
    struct node* p;
    if (H == NULL) {
        printf("\nheap is empty\n");
        return 0;
    }
    printf("\nroots are-\n");
    p = H;
    while (p != NULL) {
        printf("%d", p->w);
        cout<<"("<<p->degree<<")";
        if (p->sibling != NULL)
            printf("-->");
        p = p->sibling;
    }
    printf("\n");
}
 
//reverting children in list once root deleted 
void reverting_list(struct node* y) 
{
    if (y->sibling != NULL) {
        reverting_list(y->sibling);
        (y->sibling)->sibling = y;
    } 
    else 
    {
        Hr = y;
    }
}


//extracting min node operation 
struct node* extract_min_node(struct node* H1) 
{
    int min;
    struct node* t = NULL;
    struct node* x = H1;
    struct node* p;
  
    Hr = NULL;
    if (x == NULL) 
    {
        printf("\nnode not found");
        return x;
    }

    p = x;
    
    ///
    min=p->w;

    while (p->sibling != NULL) 
    {
        if ((p->sibling)->w < min) 
        {
            min = (p->sibling)->w;
            t = p;
            x = p->sibling;
        }

        p = p->sibling;
    }
    
  
    ///removing the extracred node from sibling
    ///and making next to extracted as sibling
    if (t == NULL && x->sibling == NULL)
        H1 = NULL;
    else if (t == NULL)
        H1 = x->sibling;
    else if (t->sibling == NULL)
        t = NULL;
    else
        t->sibling = x->sibling;


   
    
    if (x->child != NULL) 
    {
        reverting_list(x->child);
        (x->child)->sibling = NULL;

    }

    

     if(!H1)
     {
        swap(H1,Hr);
     }

     // cout<<"extracted heap is (Hr): ";
     //            printTree(Hr);
     //            cout<<endl;

     // cout<<"extracted heap is (H1): ";
     //            printTree(H1);
     //            cout<<endl;


    
     H = union_of_heaps(H1, Hr);

    return x;
}
 



//search operation 
struct node* search_element(struct node* H, int k) 
{
    struct node* x = H;
    struct node* p = NULL;
    if (x->w == k) {
        p = x;
        return p;
    }
    if (x->child != NULL && p == NULL) {
        p = search_element(x->child, k);
    }
 
    if (x->sibling != NULL && p == NULL) {
        p = search_element(x->sibling, k);
    }
    return p;
}
 
int decrease_key(struct node* H, int i, int k) 
{
    int temp;
    struct node* p;
    struct node* y;
    struct node* z;
    p = search_element(H, i);
    if (p == NULL) {
        printf("\ninvalid choice\n");
        return 0;
    }
    if (k > p->w) {
        printf("\nnew key cannot be greater than previous key ");
        return 0;
    }
    p->w = k;
    y = p;
    z = p->parent;
    while (z != NULL && y->w < z->w) {
        temp = y->w;
        y->w = z->w;
        z->w = temp;
        y = z;
        z = z->parent;
    }
    printf("\nkey reduced!");
}
 
int delete_key(struct node* H, int k) 
{
    struct node* np;
    if (H == NULL) {
        printf("\nheap is empty\n");
        return 0;
    }
 
    decrease_key(H, k, -1000);
    np = extract_min_node(H);
    if (np != NULL)
        printf("\nnode deleted");
}



  
// print function for binomial heap 
void printHeap(struct node *H) 
{ 
    while(H!=NULL)
    {
      
            printTree(H); 
        

        H=H->sibling; 
    }
} 


 
int main() {
    int v1,v2,weight;
    int edges,vertices;

    struct node* p;
    struct node* np;
    
    cout<<"enter number of vertices :";
    cin>>vertices;

    cout<<"enter number of edges (u,v,w) :";
    cin>>edges;
    cout<<"enter elements :\n";
    for (int i = 1; i <= edges; i++) 
    { 
      cout<<"i"<<" :"<<i<<"\n";

        cin>>v1;
        cin>>v2;
        cin>>weight;
      
        np = create_node(v1,v2,weight);
        H = insert(H, np);
      

    }

    display_root_elements(H);
    cout<<"\ncuurent heap is: ";
    printTree(H);
    cout<<endl;

    int edgecount=0;

    std::vector<int> x;
    std::vector<int> y;

     int sum=0;
     while(edgecount<(vertices-1))
     {
       int flagx1=0;
       int flagx2=0;
       int flagy1=0;
       int flagy2=0;

       p = extract_min_node(H);
       
      

       for(int i=0;i<x.size();i++)
       {
           if(x[i]==p->u)
            flagx1=1;
           // if(x[i]==p->v)
           //  flagx2=1;    
       }


       for(int i=0;i<y.size();i++)
       {
           // if(y[i]==p->u)
           //  flagy1=1;
           if(y[i]==p->v)
            flagy2=1;       
      }


       x.push_back(p->u);
       y.push_back(p->v);

        // if((!flagx1 || !flagx2) && (!flagy1 || !flagy2))
        if((!flagx1 ) && (!flagy2))
        {
            edgecount++; 
          // cout<<"\nmin : "<<p->w;
            cout<<"\nv1 :"<<p->u<<" v2 :"<<p->v<<"\n";
            sum=sum+p->w;
            //cout<<"\nv2  : "<<p->v;
                    
            // display_root_elements(H);
            // cout<<"cuurent heap is: ";
            // printTree(H);
            cout<<endl;
        }
        else
        {
            x.pop_back();
            y.pop_back();
        }
    }

    cout<<"MST :"<<sum<<endl;    

    
}

