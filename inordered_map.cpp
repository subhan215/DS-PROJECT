#include <iostream>
using namespace std;
class IntersectionPoint{
	public:
	std::string name ; 
	IntersectionPoint(std::string n) {
		name = n ; 
	}
	IntersectionPoint() {
		
	}
};
class node
{
public:
    IntersectionPoint data;
    node *next;
    int distance ; 
    node() {}
    node(IntersectionPoint dta , int d)
    {
        data = dta;
        next = NULL;
        distance = d ; 
    }
};

class SinglyLinkedList
{
public:
    node *head;
    node *tail;
    SinglyLinkedList()
    {
        head = NULL;
    }

    void insert(IntersectionPoint data , int d)
    {
        node *n = new node(data , d);
        if (head == NULL)
        {
            head = n;
            head->next = NULL;
        }
        else
        {
            node *temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = n;
            n->next = NULL;
        }
    }
    void delete_node(IntersectionPoint key)
    {
        if (head == NULL)
        {
            return;
        }
        if (head->data.name == key.name)
        {
            node *temp = head;
            head = head->next;
            delete temp;
        }
        else
        {
            node *current = head->next;
            node *previous = head;
            while (current->data.name != key.name && current != NULL)
            {
                previous = current;
                current = current->next;
            }
            if (current != NULL)
            {
                previous->next = current->next;
                delete current;
            }
        }
    }
    void display_list()
    {
        node *temp = head;
        while (temp != NULL)
        {
            cout << temp->data.name << " ";
            temp = temp->next;
        }
        cout << endl;
        delete temp;
    }
    ~SinglyLinkedList()
    {
        delete head;
        head = NULL;
        delete tail;
        tail = NULL;
    }
};

class custom_unordered_map
{
public:
    SinglyLinkedList *vertex;
    int number_of_vertices;
    IntersectionPoint *points ;
    int currentIndex ; 
    custom_unordered_map(int vertices)
    {
        number_of_vertices = vertices+1;
        vertex = new SinglyLinkedList[number_of_vertices];
        points = new IntersectionPoint[number_of_vertices]; 
        currentIndex = -1; 
    }
    // as we are dealing with undirected graphs so when an edge is added it will be inserted in the corresponding list of both verices
    void add_edge(IntersectionPoint vertex_1, IntersectionPoint vertex_2 , int distance)
    {
        int index = -1 ; 
        for(int i = 0 ; i <= currentIndex ; i++) {
        	if(vertex_1.name == points[i].name) {
        		index = i ; 
			}
		}
		if(index!=-1) {
			vertex[index].insert(vertex_2 , distance) ; 
		}
		else {
			currentIndex++ ; 
			vertex[currentIndex].insert(vertex_2 , distance) ; 
			points[currentIndex] = vertex_1 ; 
		}
		
		index = -1 ; 
		for(int i = 0 ; i <= currentIndex ; i++) {
        	if(vertex_2.name == points[i].name) {
        		index = i ; 
			}
		}
		if(index!=-1) {
			vertex[index].insert(vertex_1 , distance) ; 
		}
		else {
			currentIndex++ ; 
			vertex[currentIndex].insert(vertex_1 , distance) ; 
			points[currentIndex] = vertex_2 ; 
		}
		
    }
    void view_edge_list()
    {
        for (int i = 0; i < number_of_vertices; i++)
        {
            if (vertex[i].head != NULL)
            {
                cout<<points[i].name<<"->";vertex[i].display_list();
            }
        }
    }
};

int main()
{
	
	
    custom_unordered_map mapp(5);
    mapp.add_edge(IntersectionPoint("Power House"), IntersectionPoint("Liaquatabad-10") , 4);
    mapp.add_edge(IntersectionPoint("Liaquatabad-10"), IntersectionPoint("Maritime Museum") , 6);
    mapp.add_edge(IntersectionPoint("3"), IntersectionPoint("4") , 7);
    mapp.add_edge(IntersectionPoint("3"), IntersectionPoint("5") , 9);
    mapp.add_edge(IntersectionPoint("2"), IntersectionPoint("3") , 10);
    mapp.view_edge_list();
}
