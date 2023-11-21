#include <iostream>
#include <vector>
#include <algorithm> // for swap

using namespace std;

class IntersectionPoint {
public:
    std::string name;
    IntersectionPoint(std::string n) {
        name = n;
    }
    IntersectionPoint() {}
};

class node {
public:
    IntersectionPoint data;
    node* next;
    int distance;
    node() {}
    node(IntersectionPoint dta, int d) {
        data = dta;
        next = NULL;
        distance = d;
    }
};

class Set {
public:
    void heapify(vector<node>& arr, int n, int i) {
        int largest = i;
        int l = 2 * i + 1; // left = 2*i + 1
        int r = 2 * i + 2; // right = 2*i + 2

        if (l < n && arr[l].distance > arr[largest].distance)
            largest = l;

        if (r < n && arr[r].distance > arr[largest].distance)
            largest = r;

        if (largest != i) {
            swap(arr[i], arr[largest]);

            heapify(arr, n, largest);
        }
    }

    void heapSort(vector<node>& arr) {
        int n = arr.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        for (int i = n - 1; i >= 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }

    void printArray(vector<node>& arr) {
        for (int i = 0; i < arr.size(); ++i)
            cout << arr[i].data.name << "(" << arr[i].distance << ") ";
        cout << "\n";
    }
};

int main() {
    vector<node> nodes;
    nodes.push_back(node(IntersectionPoint("12"), 4));
    nodes.push_back(node(IntersectionPoint("1"), 6));
    nodes.push_back(node(IntersectionPoint("3"), 7));
    nodes.push_back(node(IntersectionPoint("3"), 9));
    nodes.push_back(node(IntersectionPoint("2"), 10));

    Set s;

    for (int i = nodes.size() / 2 - 1; i >= 0; i--) {
        s.heapify(nodes, nodes.size(), i);
    }

    cout << "After heapifying array is \n";
    s.printArray(nodes);

    s.heapSort(nodes);

    cout << "Sorted array is \n";
    s.printArray(nodes);

    return 0;
}

