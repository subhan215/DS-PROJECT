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
    node() {}
    node(IntersectionPoint dta)
    {
        data = dta;
        next = NULL;
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
    SinglyLinkedList(IntersectionPoint data)
    {
        node *n = new node(data);
        head = n;
        tail = n;
    }

    void insert(IntersectionPoint data)
    {
        node *n = new node(data);
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
    void add_edge(IntersectionPoint vertex_1, IntersectionPoint vertex_2)
    {
        int index = -1 ; 
        for(int i = 0 ; i <= currentIndex ; i++) {
        	if(vertex_1.name == points[i].name) {
        		index = i ; 
			}
		}
		if(index!=-1) {
			vertex[index].insert(vertex_2) ; 
		}
		else {
			currentIndex++ ; 
			vertex[currentIndex].insert(vertex_2) ; 
			points[currentIndex] = vertex_1 ; 
		}
		
		index = -1 ; 
		for(int i = 0 ; i <= currentIndex ; i++) {
        	if(vertex_2.name == points[i].name) {
        		index = i ; 
			}
		}
		if(index!=-1) {
			vertex[index].insert(vertex_1) ; 
		}
		else {
			currentIndex++ ; 
			vertex[currentIndex].insert(vertex_1) ; 
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
    SinglyLinkedList liist;
    liist.insert(IntersectionPoint("1"));
    liist.insert(IntersectionPoint("3"));
    liist.insert(IntersectionPoint("2"));
    liist.display_list();
    liist.delete_node(IntersectionPoint("3"));
    liist.display_list();
    custom_unordered_map mapp(5);
    mapp.add_edge(IntersectionPoint("1"), IntersectionPoint("2"));
    mapp.add_edge(IntersectionPoint("1"), IntersectionPoint("3"));
    mapp.add_edge(IntersectionPoint("3"), IntersectionPoint("4"));
    mapp.add_edge(IntersectionPoint("3"), IntersectionPoint("5"));
    mapp.add_edge(IntersectionPoint("2"), IntersectionPoint("3"));
    mapp.view_edge_list();
}
