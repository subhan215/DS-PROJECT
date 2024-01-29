#include <set>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>
#include <limits.h>
#include <list>
#include <fstream>
#include <string>
#include <string.h>
#include <stack>
using namespace std;
struct browseHistory
{
public:
    char point1[100];
    char point2[100];
};
struct busRoute
{
public:
    char point1[100], point2[100];
    int distance;
    char bus[100];
};
void verifyBus(string *bus)
{
    FILE *fp;
    while (1)
    {
        bool flag = false;
        fp = fopen("routes.bin", "rb");
        busRoute temp;
        while (fread(&temp, sizeof(busRoute), 1, fp))
        {
            if (strcmp(temp.bus, (*bus).c_str()) == 0)
            {
                flag = true;
            }
        }
        fclose(fp);
        if (flag)
        {
            break;
        }
        cout << "\nError in bus!Enter again: ";
        fflush(stdin);
        cin >> *(bus);
    }
}

void verifySrcOrDest(string *coming)
{
    FILE *fp;
    while (1)
    {
        bool flag = false;
        fp = fopen("routes.bin", "rb");
        busRoute temp;
        while (fread(&temp, sizeof(busRoute), 1, fp))
        {
            if (strcmp(temp.point1, (*coming).c_str()) == 0 || strcmp(temp.point2, (*coming).c_str()) == 0)
            {
                flag = true;
            }
        }
        fclose(fp);
        if (flag)
        {
            break;
        }
        cout << "\nError in src/dest!Enter again: ";
        getline(cin, (*coming));
    }
}
class IntersectionPoint
{
public:
    std::string name;
    IntersectionPoint(std::string n)
    {
        name = n;
    }
    IntersectionPoint()
    {
    }
};
class node
{
public:
    IntersectionPoint data;
    node *next;
    int distance;
    string bus;
    node() {}
    node(IntersectionPoint dta, int d, string b)
    {
        data = dta;
        next = NULL;
        distance = d;
        bus = b;
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

    void insert(IntersectionPoint data, int d, string b)
    {
        node *n = new node(data, d, b);
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
    IntersectionPoint *points;
    int currentIndex;
    custom_unordered_map(int vertices)
    {
        number_of_vertices = vertices + 1;
        vertex = new SinglyLinkedList[number_of_vertices];
        points = new IntersectionPoint[number_of_vertices];
        currentIndex = -1;
    }
    // as we are dealing with undirected graphs so when an edge is added it will be inserted in the corresponding list of both verices
    void add_edge(IntersectionPoint vertex_1, IntersectionPoint vertex_2, int distance, string b)
    {
        int index = -1;
        for (int i = 0; i <= currentIndex; i++)
        {
            if (vertex_1.name == points[i].name)
            {
                index = i;
                break;
            }
        }
        if (index != -1)
        {
            node *tempPtr = vertex[index].head;
            while (tempPtr != NULL)
            {
                if (tempPtr->data.name == vertex_2.name)
                {
                    break; // Found the existing edge
                }
                tempPtr = tempPtr->next;
            }

            if (tempPtr == NULL)
            {
                vertex[index].insert(vertex_2, distance, b);
            }
        }
        else
        {
            currentIndex++;
            vertex[currentIndex].insert(vertex_2, distance, b);
            points[currentIndex] = vertex_1;
        }

        index = -1;
        for (int i = 0; i <= currentIndex; i++)
        {
            if (vertex_2.name == points[i].name)
            {
                index = i;
                break;
            }
        }
        if (index != -1)
        {
            node *tempPtr = vertex[index].head;
            while (tempPtr != NULL)
            {
                if (tempPtr->data.name == vertex_1.name)
                {
                    break; // Found the existing edge
                }
                tempPtr = tempPtr->next;
            }

            if (tempPtr == NULL)
            {
                vertex[index].insert(vertex_1, distance, b);
            }
        }
        else
        {
            currentIndex++;
            vertex[currentIndex].insert(vertex_1, distance, b);
            points[currentIndex] = vertex_2;
        }
    }

    void view_edge_list()
    {
        for (int i = 0; i < number_of_vertices; i++)
        {
            if (vertex[i].head != NULL)
            {
                cout << points[i].name << "->";
                vertex[i].display_list();
            }
        }
    }
    void addingEdges()
    {
        FILE *fp;
        busRoute temp;

        fp = fopen("routes.bin", "rb");
        while (fread(&temp, sizeof(busRoute), 1, fp) == 1)
        {
            // string point1, point2, bus;
            // point1 = temp.point1 ;
            // point2 = temp.point2 ;
            // bus = temp.bus ;
            IntersectionPoint tempPoint1(temp.point1), tempPoint2(temp.point2);
            // cout << "Adding edge: " << temp.point1 << " to " << temp.point2 << ", Bus: " << temp.bus << ", Distance: " << temp.distance << endl;

            try
            {
                add_edge(tempPoint1, tempPoint2, temp.distance, temp.bus);
            }
            catch (const std::exception &e)
            {
                cerr << "Exception caught: " << e.what() << endl;
            }
        }
    }
};
class Admin
{
public:
    Admin(){};
    void deleteRoute()
    {
        char point1[100], point2[100], bus[100];
        cout << "\nEnter the starting point of a route: ";
        // cin.ignore(); // Add this line to clear input buffer
        cin.getline(point1, sizeof(point1));

        cout << "\nEnter the ending point of a route: ";
        // cin.ignore(); // Add this line to clear input buffer
        cin.getline(point2, sizeof(point2));

        cout << "\nEnter the bus from which you have to remove this route: ";
        // cin.ignore(); // Add this line to clear input buffer
        cin.getline(bus, sizeof(bus));
        int getNoOfRoutes;
        ifstream ReadRoutesNo("noOfRoutes.txt", std::ios::binary);
        if (ReadRoutesNo.is_open())
        {
            ReadRoutesNo >> getNoOfRoutes;
            ReadRoutesNo.close();
        }
        FILE *fp = fopen("routes.bin", "rb");
        busRoute *routes = new busRoute[getNoOfRoutes];
        for (int i = 0; i < getNoOfRoutes; i++)
        {
            fread(&routes[i], sizeof(busRoute), 1, fp);
        }
        fclose(fp);
        fp = fopen("routes.bin", "wb");
        for (int i = 0; i < getNoOfRoutes; i++)
        {
            // Print the values for debugging

            if ((strcmp(point1, routes[i].point1) == 0 && strcmp(point2, routes[i].point2) == 0 && strcmp(bus, routes[i].bus) == 0) ||
                (strcmp(point1, routes[i].point2) == 0 && strcmp(point2, routes[i].point1) == 0 && strcmp(bus, routes[i].bus)))
            {
                continue;
            }
            fwrite(&routes[i], sizeof(busRoute), 1, fp);
        }

        fclose(fp);
        getNoOfRoutes--;
        cout << getNoOfRoutes << "\n";
        ofstream writeRoutesNo("noOfRoutes.txt", std::ios::binary);
        writeRoutesNo << getNoOfRoutes;
        writeRoutesNo.close();
    }
    void updateRouteOrBus()
    {
        std::cout << "\nWhat do you want to do: \n1: Update Route of a Bus \n2: Update Bus on a Route";
        int choice;
        std::cin >> choice;
        char point1[100], point2[100], bus[100], newPoint1[100], newPoint2[200], newBus[100];
        if (choice == 1)
        {
            cout << "\nEnter the starting point of the route which you want to update on the bus: ";
        }
        else
        {
            cout << "\nEnter the starting point of the route on which you want to update the Bus:   ";
        }
        // cin.ignore(); // Add this line to clear input buffer
        fflush(stdin);
        cin.getline(point1, sizeof(point1));
        if (choice == 1)
        {
            cout << "\nEnter the ending point of the route which you want to update on the bus: ";
        }
        else
        {
            cout << "\nEnter the ending point of the route on which you want to update the Bus:   ";
        }

        // cin.ignore(); // Add this line to clear input buffer
        cin.getline(point2, sizeof(point2));

        if (choice == 1)
        {
            cout << "\nEnter the bus of which you want to update route: ";
        }
        else
        {
            cout << "\nEnter the bus which you want to update on the route:   ";
        }
        // cin.ignore(); // Add this line to clear input buffer
        cin.getline(bus, sizeof(bus));
        if (choice == 1)
        {
            cout << "Enter the new starting point: ";
            cin.getline(newPoint1, sizeof(newPoint1));
            cout << "Enter the new ending point: ";
            cin.getline(newPoint1, sizeof(newPoint2));
        }
        else
        {
            cout << "\nEnter the new bus: ";
            cin.getline(newBus, sizeof(newBus));
        }
        int getNoOfRoutes;
        ifstream ReadRoutesNo("noOfRoutes.txt", std::ios::binary);
        if (ReadRoutesNo.is_open())
        {
            ReadRoutesNo >> getNoOfRoutes;
            ReadRoutesNo.close();
        }
        FILE *fp = fopen("routes.bin", "rb");
        busRoute *routes = new busRoute[getNoOfRoutes];
        for (int i = 0; i < getNoOfRoutes; i++)
        {
            fread(&routes[i], sizeof(busRoute), 1, fp);
        }
        fclose(fp);
        fp = fopen("routes.bin", "wb");
        for (int i = 0; i < getNoOfRoutes; i++)
        {
            // Print the values for debugging
            if ((strcmp(point1, routes[i].point1) == 0 && strcmp(point2, routes[i].point2) == 0 && strcmp(bus, routes[i].bus) == 0) ||
                (strcmp(point1, routes[i].point2) == 0 && strcmp(point2, routes[i].point1) == 0 && strcmp(bus, routes[i].bus)))
            {
                if (choice == 1)
                {
                    strcpy(routes[i].point1, newPoint1);
                    strcpy(routes[i].point2, newPoint2);
                }
                else
                {
                    strcpy(routes[i].bus, newBus);
                }
            }
            fwrite(&routes[i], sizeof(busRoute), 1, fp);
        }

        fclose(fp);
    }
    void addANewRoute()
    {
        cout << "\nEnter source : ";
        string source, dest;
        fflush(stdin) ; 
        getline(cin, source);
        cout << "\nEnter destination: ";
        fflush(stdin) ; 
        getline(cin, dest);
        cout << "\nEnter distance: ";
        int dist;
        fflush(stdin);
        cin >> dist;
        busRoute temp;
        FILE *fp;
        fp = fopen("routes.bin", "ab");
        while (1)
        {
            temp.distance = dist;
            strcpy(temp.point1, source.c_str());
            strcpy(temp.point2, dest.c_str());
            fwrite(&temp, sizeof(busRoute), 1, fp);
            bool flag = false;
            while (1)
            {

                cout << "\nWant to continue adding new route: ";
                int choice;

                fflush(stdin);
                cin >> choice;
                if (choice == 1)
                {
                    flag = true;
                    break;
                }
                else if (choice == 2)
                {
                    break;
                }
                else
                {
                    cout << "\nInvalid Choice!Enter again: ";
                }
            }
            if (flag == false)
            {
                fclose(fp);
                break;
            }
            else
            {
                cout << "\nEnter source : ";
                getline(cin, source);
                cout << "\nEnter destination: ";
                getline(cin, dest);
                cout << "\nEnter distance: ";
                int dist;
                fflush(stdin);
                cin >> dist;
            }
        }
    }
};
vector<pair<int, vector<string>>> dijik(custom_unordered_map &graph, string source, string dest)
{
    int index = -1;
    // finding the index of source from intersectionPoint points array

    for (int i = 0; i <= graph.currentIndex; i++)
    {
        if (source == graph.points[i].name)
        {
            index = i;
            break;
        }
    }
    // cout << index << endl;

    // cout << graph.currentIndex << endl;
    // this will store pair which will contain distance and string name of the stop
    vector<pair<int, string>> distances(graph.currentIndex + 1);
    // this is for finding all the paths from the source
    vector<int> parent(graph.currentIndex + 1, -1);

    // initializing distance vector with max or infinty value and assigning names for each node for further use
    for (int i = 0; i < graph.currentIndex + 1; i++)
    {
        distances[i].first = INT_MAX;
        distances[i].second = graph.points[i].name;
    }

    /*for (int i = 0; i < graph.currentIndex + 1; i++)
    {
        cout << distances[i].first << " " << distances[i].second << endl;
    }*/
    // cout << endl;
    distances[index].first = 0;

    /*for (int i = 0; i < graph.currentIndex + 1; i++)
    {
        cout << distances[i].first << " " << distances[i].second << endl;
    }*/
    // cout << endl;
    // this is like a min heap the first in set is the distance and the second is tells the index
    set<pair<int, int>> sorted_data;
    // first inserting the source with distance 0 and its index which we calculated earlier
    sorted_data.insert(make_pair(0, index));
    while (!sorted_data.empty())
    {
        // now we extract the top of the set
        auto topp = *(sorted_data.begin());
        int top_distance = topp.first; // mentioned earlier that fisrt is distance
        int top_index = topp.second;   // and second is index
        // removing the top
        sorted_data.erase(sorted_data.begin());

        // now we will traverse all the edges , which are saved in vertex array, of the element that we extracted from set i.e. top
        node *temp1 = graph.vertex[top_index].head;
        while (temp1 != NULL)
        {
            int find = 0;
            for (int i = 0; i <= graph.currentIndex; i++)
            {
                if (temp1->data.name == distances[i].second)
                {
                    find = i;
                    break;
                }
            }
            if (top_distance + temp1->distance < distances[find].first)
            {
                auto search_for_duplicate = sorted_data.find(make_pair(distances[find].first, find));
                if (search_for_duplicate != sorted_data.end())
                {
                    sorted_data.erase(search_for_duplicate);
                }
                distances[find].first = top_distance + temp1->distance;
                // here we store parent of this vertex
                parent[find] = top_index;
                sorted_data.insert(make_pair(distances[find].first, find));
            }
            // going to next edge
            temp1 = temp1->next;
        }
    }
    // now this is the main stuff i.e. paths_with_distance
    // this vector has a pair which has a minimum distance and against that distance there is a vector which has path followed for that minimum distance in string from but that is stored in reverse order so when using it later in project keep that in mind to access that properly
    vector<pair<int, vector<string>>> paths_with_distance(graph.currentIndex + 1);
    for (int i = 0; i <= graph.currentIndex; i++)
    {
        paths_with_distance[i].first = distances[i].first;
        int parent_of_current = parent[i];
        paths_with_distance[i].second.push_back(distances[i].second);
        while (parent_of_current != -1)
        { //-1 means source as the source will have -1
            paths_with_distance[i].second.push_back(distances[parent_of_current].second);
            parent_of_current = parent[parent_of_current];
        }
    }
    /*
    for (int i = 0; i <= graph.currentIndex; i++)
    {
       cout << "Distance:" << paths_with_distance[i].first << "  Path is: ";
        for (int j = paths_with_distance[i].second.size() - 1; j >= 0; j--)
        {
            cout << paths_with_distance[i].second[j] << "   ";
        }
        cout << endl;
    } */
    return paths_with_distance;
    /*int j ; 
    index = -1 ; 
    for(int i = 0 ; i < paths_with_distance.size() ; i++) {
        j = paths_with_distance[i].second.size() - 1 ; 
        std::cout <<"\n j: " << j ; 
        string temp = paths_with_distance[i].second[j] ; 
        if(paths == dest) {
           
            index = i ; 
            break ; 
        }
    }
    std::cout <<"\ni value: " << index ; 
    std::cout <<"\nShortest Distance from " << source << " to " << dest << " is: " << 
    paths_with_distance[index].first ; 
*/}

    void dfs(string src, string dest, vector<unordered_map<string, string>> &routes,
             unordered_map<string, string> &currRoute, custom_unordered_map &mapp,
             unordered_map<string, bool> &visited)
    {
        visited[src] = true;

        if (src == dest)
        {
            routes.push_back(currRoute);
            // Add debug print statements
            /* cout << "Found route: ";
             for (const auto &entry : currRoute)
             {
                 cout << entry.first << " -> " << entry.second << ", ";
             }
             cout << endl; */
        }
        else
        {
            int index = -1;
            for (int i = 0; i <= mapp.currentIndex; i++)
            {
                if (mapp.points[i].name == src)
                {
                    index = i;
                    break;
                }
            }

            if (index != -1)
            {
                node *temp = mapp.vertex[index].head;
                while (temp != NULL)
                {
                    if (!visited[temp->data.name])
                    {
                        currRoute[src] = temp->data.name;
                        // Add debug print statements
                        // cout << "DFS: Going from " << src << " to " << temp->data.name << endl;
                        dfs(temp->data.name, dest, routes, currRoute, mapp, visited);
                    }
                    temp = temp->next;
                }
            }
        }

        visited[src] = false; // Backtrack
        currRoute.erase(src); // Remove current node from the current route
    }

    void function_that_finds_the_shortest_path_and_distance(string source, string destination, custom_unordered_map mapp)
    {
        vector<pair<int, vector<string>>> paths_with_distance(mapp.currentIndex + 1);
        //  mapp.view_edge_list();
        paths_with_distance = dijik(mapp, source, destination);
        // cout << paths_with_distance[0].first << endl;
        // cout << endl;
        // cout << paths_with_distance[0].second.size() << endl;
        // cout << paths_with_distance[0].second[0] << endl;
        // cout << paths_with_distance[0].second[paths_with_distance[0].second.size() - 1] << endl;
        int index = 0;
        for (int i = 0; i < paths_with_distance.size(); i++)
        {
            if (destination == paths_with_distance[i].second[0])
            {
                index = i;
                break;
            }
        }
        cout << index << endl;
        cout << "Your path will be: ";
        for (int i = paths_with_distance[index].second.size() - 1; i >= 0; i--)
        {
            cout << paths_with_distance[index].second[i] << " ";
        }
        cout << "and The distance will be :" << paths_with_distance[index].first << endl;
    }
    // ye subhan jo tunay banaya tha na wo ha function ke andar band kardia
    void function_that_finds_all_the_paths(string source, string destination, custom_unordered_map mapp)
    {
        string src = source;
        string dest = destination;
        vector<unordered_map<string, string>> routes;
        unordered_map<string, bool> visited;
        unordered_map<string, string> currRoute;
        dfs(src, dest, routes, currRoute, mapp, visited);
        if (routes.empty())
        {
            cout << "No route found from " << src << " to " << dest << endl;
        }
        else
        {
            cout << "\nRoutes from " << src << " to " << dest << ":\n";
            std::string tempSrc = src;
            for (const auto &route : routes)
            {
                std::cout << src;
                cout << "--> ";
                auto it = route.find(src);
                while (it != route.end())
                {
                    cout << it->second << " -> ";
                    src = it->second;
                    it = route.find(src);
                }
                src = tempSrc;
                cout << endl;
            }
        }
        string point1;
        string point2;
        int routeCount = 0;
        for (const auto &route : routes)
        {
            routeCount++;
            std::cout << "\nRoute " << routeCount;

            std::string currentStop = src;
            std::string nextStop = "";

            std::string prevBus = "";
            while (true)
            {
                auto it = route.find(currentStop);

                if (it == route.end())
                {
                    // Reached the destination
                    break;
                }
                nextStop = it->second;

                int stopIndex = -1;

                for (int i = 0; i <= mapp.currentIndex; i++)
                {
                    if (currentStop == mapp.points[i].name)
                    {
                        stopIndex = i;
                        break;
                    }
                }

                if (stopIndex != -1)
                {
                    node *currentNode = mapp.vertex[stopIndex].head;

                    while (currentNode != NULL && currentNode->data.name != nextStop)
                    {
                        currentNode = currentNode->next;
                    }

                    if (currentNode != NULL)
                    {
                        if (currentNode->bus != prevBus)
                        {
                            std::cout << "\nFrom " << currentStop << " to " << nextStop << ": " << currentNode->bus;
                            prevBus = currentNode->bus;
                        }
                        else
                        {
                            std::cout << "\nFrom " << currentStop << " to " << nextStop << ": " << prevBus;
                        }
                    }
                }

                currentStop = nextStop;
            }
        }
    }
    class user
    {
    private:
        string user_name;
        string user_id;
        string user_email;
        string user_password;

    public:
        void browsingHistoryFunc()
        {
            stack<browseHistory> s;
            string browsing_history;
            browsing_history = user_id + "_history.txt";
            FILE *fp;
            char cStr[100];
            browsing_history.copy(cStr, sizeof(cStr), 0);
            cStr[sizeof(cStr) - 1] = '\0'; // Ensure null-termination
            fp = fopen(cStr, "rb");
            browseHistory temp;
            while (fread(&temp, sizeof(browseHistory), 1, fp))
            {
                s.push(temp);
            }
            fclose(fp);
            cout << "\nBrowsing History! ";
            int count = 1;
            while (!s.empty())
            {
                temp = s.top();
                cout << count << "1.\n";
                cout << "\nPoint 1: " << temp.point1;
                cout << "\nPoint 2: " << temp.point2;
                s.pop();
                count++;
            }
        }
        user() {}
        string login()
        {
            bool check = false;
            string email, password;
            cout << "email :";
            cin >> email;
            // email = "Email : " + email;

            cout << "password :";
            cin >> password;
            // password = "Password : " + password;

            ifstream read;
            read.open("All_app_users.txt");

            getline(read, user_name);
            getline(read, user_id);
            getline(read, user_email);
            getline(read, user_password);

            if (read.is_open())
            {
                cout << "Verifying details in the system\n\n";
                while (!read.eof())
                {
                    if (email == user_email && password == user_password)
                    {
                        cout << "Welcome back " << user_name << endl;
                        check = true;
                        return user_id;
                        break;
                    }
                    else
                    {
                        getline(read, user_name);
                        getline(read, user_id);
                        getline(read, user_email);
                        getline(read, user_password);
                    }
                }
                if (check == false)
                {
                    cout << "No account exist for this email and password . Enter correct email and password." << endl;
                    return "";
                }
            }
            return user_id;
        }
        string get_name()
        {
            return user_name;
        }
        string get_email()
        {
            return user_email;
        }
        string get_password()
        {
            return user_password;
        }
        string get_id()
        {
            return user_id;
        }
        void set_id(string id)
        {
            this->user_id = id;
        }
        void set_name(string name)
        {
            this->user_name = name;
        }
        void set_email(string email)
        {
            this->user_email = email;
        }
        void set_password(string password)
        {
            this->user_password = password;
        }
        // This Fucntion will add data to file
        void Add_to_file()
        {
            ofstream write;
            write.open("All_app_users.txt", ios::binary | ios::app);
            write << user_name << endl;
            write << user_id << endl;
            write << user_email << endl;
            write << user_password << endl;
            // Similar to the above work, we will write every attribute into file , or only those that are of our need
            write.close();
            cout << "Data Saved to file\n";
        }
        void routeOfASpecificBus()
        {
            std::cout << "\nWhich bus route do you want to see: ";
            string busToSee;
            fflush(stdin);
            std::cin >> busToSee;
            verifyBus(&busToSee);
            FILE *fp;
            fp = fopen("routes.bin", "rb");
            busRoute temp;
            std::cout << "\nRoute: \n";
            while (fread(&temp, sizeof(busRoute), 1, fp))
            {
                if (temp.bus == busToSee)
                {
                    std::cout << "\nPoint 1: " << temp.point1 << ", Point 2: " << temp.point2;
                    std::cout << " , Distance: " << temp.distance << ", Bus: " << temp.bus;
                }
            }

            fclose(fp);
        }
        void markFavourite(string src, string dest)
        {
            string favourite = user_id + "_favourites.txt";
            FILE *fp;
            bool flag = false;
            fp = fopen(favourite.c_str(), "rb");
            browseHistory temp;
            while (fread(&temp, sizeof(browseHistory), 1, fp))
            {
                if ((strcmp(temp.point1, src.c_str()) == 0 && strcmp(temp.point2, dest.c_str()) == 0) ||
                    (strcmp(temp.point2, src.c_str()) == 0 && strcmp(temp.point1, dest.c_str()) == 0))
                {
                    std::cout << "\nThis route already exists as favourite!";
                    flag = true;
                    break;
                }
            }
            fclose(fp);
            if (flag)
            {
                return;
            }
            fp = fopen(favourite.c_str(), "ab");
            strcpy(temp.point1, src.c_str());
            strcpy(temp.point2, dest.c_str());
            fwrite(&temp, sizeof(browseHistory), 1, fp);
            fclose(fp);
        }
        void routesOfFavourites(custom_unordered_map mapp)
        {
            int count = 1;
            string favourite = user_id + "_favourites.txt";
            FILE *fp;
            fp = fopen(favourite.c_str(), "rb");
            browseHistory temp;
            while (fread(&temp, sizeof(browseHistory), 1, fp))
            {
                string src(temp.point1), dest(temp.point2);
                cout << "\n"
                     << count << ": "
                     << "source: " << src << "destination: " << dest;
                count++;
            }
            fclose(fp);
            cout << "\nWhich favourite source and destination route/routes you";
            cout << "want to see: ";
            cout << "\nEnter your choice in number: ";
            int choice;

            while (1)
            {
                count = 0;
                fflush(stdin);
                cin >> choice;
                fp = fopen(favourite.c_str(), "rb");
                while (fread(&temp, sizeof(browseHistory), 1, fp))
                {
                    count++;
                    if (count == choice)
                    {
                        break;
                    }
                }
                fclose(fp);
                if (count == choice)
                {
                    int innerChoice;
                    cout << "\nEnter your choice: \n1.Want to see all the routes\n2.Shortest Route";
                    cout << "\n3.Back";
                    while (1)
                    {
                        cin >> innerChoice;
                        string src(temp.point1), dest(temp.point2);
                        if (innerChoice == 1)
                        {
                            function_that_finds_all_the_paths(src, dest, mapp);
                            break;
                        }
                        else if (innerChoice == 2)
                        {
                            function_that_finds_the_shortest_path_and_distance(src, dest, mapp);
                            break;
                        }
                        else if (innerChoice == 3)
                        {
                            break;
                        }
                        else
                        {
                            cout << "\nInvalid Choice!\nEnter again: ";
                        }
                    }
                    break;
                }
                else
                {
                    cout << "\nInvalid Choice!\nEnter again: ";
                }
            }
        }
    };

    // This function will check the validity of password
    bool isPasswordValid(string password)
    {
        // Password should be at least 8 characters long
        if (password.length() < 8)
        {
            return false;
        }

        // Check if password contains at least one uppercase letter, one lowercase letter and one digit
        bool hasUppercase = false;
        bool hasLowercase = false;
        bool hasDigit = false;

        for (int i = 0; i < password.length(); i++)
        {
            if (isupper(password[i]))
            {
                hasUppercase = true;
            }
            else if (islower(password[i]))
            {
                hasLowercase = true;
            }
            else if (isdigit(password[i]))
            {
                hasDigit = true;
            }
        }

        if (!hasUppercase || !hasLowercase || !hasDigit)
        {
            return false;
        }

        return true;
    }
    // This function will check string
    bool check_string(string s)
    {
        bool check = false;
        for (int i = 0; i < s.length(); i++)
        {
            if (!isalpha(s[i]))
            {
                check = true;
            }
        }
        if (check == true)
        {
            return false;
        }
        return true;
    }

    void sign_up_of_person()
    {
        // read ID from file "ID" then assign to user then write user's data in file then write incremented ID in file of "ID"

        int IDint;
        string IDstring, first_name, last_name, email, password, name;
        bool dot_present = false, rate_present = false;

        // reading  ID from file "ID.txt"
        ifstream read;
        read.open("ID.txt");
        if (!read.is_open())
        {
            cout << "ID error\n";
            return;
        }
        else
        {
            cout << "Reading ID from file\n";
            read >> IDstring;
            cout << "ID:" << IDstring << endl;
        }
        read.close();

        // incrementing ID by typecasting into int
        IDint = stoi(IDstring);
        IDint++;
        IDstring = to_string(IDint);

        user person;

        // ID of person has been set
        person.set_id(IDstring);

        do
        {

            cout << "Email:";
            fflush(stdin);
            cin >> email;
            for (int i = 0; i < email.length(); i++)
            {
                if (email[i] == '@')
                {
                    rate_present = true;
                }
                if (email[i] == '.')
                {
                    dot_present = true;
                }
            }
            if (dot_present == false || rate_present == false)
            {
                cout << "invalid mail,enter again\n";
            }
        } while (dot_present == false || rate_present == false);

        person.set_email(email);
        //    cout<<person.get_email()<<endl;

        do
        {
            cout << "Password(Password should be at least 8 characters long and contain at least one uppercase letter, one lowercase letter, and one digit.):";
            cin >> password;

            if (isPasswordValid(password) == false)
            {
                cout << "Invalid Format.Enter again.\n";
            }
        } while (isPasswordValid(password) == false);

        person.set_password(password);
        //	cout<<person.get_password();
        do
        {
            cout << "Fist name:";
            cin >> first_name;
            if (check_string(first_name) == false)
            {
                cout << "Invalid character\n";
            }
        } while (check_string(first_name) == false);

        do
        {
            cout << "Last Name:";
            cin >> last_name;
            if (check_string(last_name) == false)
            {
                if (check_string(first_name) == false)
                {
                    cout << "Invalid character\n";
                }
            }
        } while (check_string(last_name) == false);

        string fname = first_name + " " + last_name;
        person.set_name(fname);

        person.Add_to_file();

        // writing incremented ID in file "ID"
        ofstream writeID;
        writeID.open("ID.txt");
        writeID << IDint;
        writeID.close();

        // making browsing history file
        string browsing_history;
        browsing_history = IDstring + "_history.txt";
        ofstream browsing_history_file;
        browsing_history_file.open(browsing_history);
        browsing_history_file.close();
    }

    void user_interface()
    {
        custom_unordered_map mapp(500);
        mapp.addingEdges();

        int choice1;
        int choice2;
        int choice3;
        int choice4;
        int choice5;
        string starting_point;
        string destination_point;
        user user_object;
        Admin a;
        int adminChoice;
        for (;;)
        {
            cout << "Login as : \n1. Admin  \n2. User  \n3.Exit\n Your choice :";
            fflush(stdin) ; 
            cin >> choice1;
            if(choice1 == 1)
            {
                cout << "\n1. Add New Route \n2.Delete Route \n3. Update Route \n4.Back";
                cout << "\nEnter your choice: ";
            for(;;){
                   // fflush(stdin);
                    cin >> adminChoice;
                    if (adminChoice == 1)
                    {
                      //  a.addANewRoute();
                        break ; 
                    }
                    else if (adminChoice == 2)
                    {
                        a.deleteRoute();
                        break ; 
                    }
                    else if (adminChoice == 3)
                    {
                        a.updateRouteOrBus();
                        break ; 
                    }
                    else if (adminChoice == 4)
                    {
                        break;
                    }
                    else
                    {
                        cout << "\nInvalid!Enter again: ";
                    }
                }
                // cout
            }
            else if(choice1 ==2) {
                for (;;)
                {
                    string userId;
                    cout << "1. Login \n2. Sign Up \n3.Back\nYour Choice:";
                    cin >> choice3;
                    if (choice3 == 1)
                    {
                        if ((userId = user_object.login()) != "")
                        {
                            for (;;)
                            {
                                cout << "\n1.View routes of all People's Bus Service in Karachi.\n";
                                cout << "2.Search for a desire route.\n";
                                cout << "3.View previously searched routes.\n";
                                cout << "4.View Routes Of Specific Bus\n";
                                cout << "5.View Routes of favourite source and destination:\n";
                                cout << "6.Logout\nYour choice:";

                                // user ko baki options dekhanay hain
                                cin >> choice4;
                                if (choice4 == 1)
                                {
                                    cout << "to be added\n";
                                    // function showing all the routes of all the buses in karachi
                                }
                                else if (choice4 == 2)
                                {
                                    cout << "Enter below information\n1. Starting point:";
                                    fflush(stdin);
                                    getline(cin, starting_point);
                                    verifySrcOrDest(&starting_point);
                                    cout << "2. Destination point:";
                                    fflush(stdin);
                                    getline(cin, destination_point);
                                    verifySrcOrDest(&destination_point);
                                    for (;;)
                                    {
                                        cout << "1.View all the possible routes\n2.View the shortest route\n3.Back\nYour choice:";
                                        fflush(stdin);
                                        cin >> choice5;
                                        if (choice5 == 1)
                                        {
                                            function_that_finds_all_the_paths(starting_point, destination_point, mapp);
                                        }
                                        else if (choice5 == 2)
                                        {
                                            function_that_finds_the_shortest_path_and_distance(starting_point, destination_point, mapp);
                                        }
                                        else if (choice5 == 3)
                                        {
                                            break;
                                        }
                                        else
                                        {
                                            cout << "Invalid Choice.\n";
                                            continue;
                                        }
                                    }

                                    string browsing_history = userId + "_history.txt";
                                    FILE *fp;
                                    fp = fopen(browsing_history.c_str(), "ab");
                                    browseHistory temp;
                                    strcpy(temp.point1, starting_point.c_str());
                                    strcpy(temp.point2, destination_point.c_str());
                                    fwrite(&temp, sizeof(browseHistory), 1, fp);
                                    fclose(fp);
                                    int favChoice;
                                    std::cout << "\nWant to mark current source and destination as favourites: \n1.Yes \n2.No\nEnter choice: ";

                                    while (1)
                                    {
                                        fflush(stdin);
                                        cin >> favChoice;

                                        if (favChoice == 1)
                                        {
                                            user_object.markFavourite(starting_point, destination_point);
                                            break;
                                        }
                                        else if (favChoice == 2)
                                        {
                                            break;
                                        }
                                        else
                                        {
                                            std::cout << "\nInvalid Choice! Enter again: ";
                                        }
                                    }
                                }
                                else if (choice4 == 3)
                                {
                                    user_object.browsingHistoryFunc();
                                }
                                else if (choice4 == 4)
                                {
                                    user_object.routeOfASpecificBus();
                                }

                                else if (choice4 == 5)
                                {
                                    user_object.routesOfFavourites(mapp);
                                }
                                else if (choice4 == 6)
                                {
                                    break;
                                }
                                else
                                {
                                    cout << "Invalid choice.\n";
                                    continue;
                                }
                            }
                        }
                        else
                        {
                            cout << "Try Again.\n";
                        }
                    }
                    else if (choice3 == 2)
                    {
                        sign_up_of_person();
                        cout << "Your account has been created successfully.\n";
                    }
                    else if (choice3 == 3)
                    {
                        break;
                    }
                }
            }
            else if(choice1 == 3) {
                return ;
            }
            else {
                cout << "Invalid Choice.\n";
            }
        }
    }

    int main()
    {
        user_interface();
    }