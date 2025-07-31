//talgov44@gmail.com

#include <iostream>

#include "MyContainer.hpp"

using namespace ariel;
using namespace std;

int main()
{
    MyContainer<int> container; //The container

    // 1,5,4,3,7,2,7
    container.addElement(1);
    container.addElement(5);
    container.addElement(4);
    container.addElement(3);
    container.addElement(7);
    container.addElement(2);
    container.addElement(7);
    
    // 1,5,4,3,2
    container.removeElement(7);
    
    cout << "The size of the container: " << container.size() << endl;

    cout << endl << "Ascending Order: ";
    for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it)
    {
        cout << *it << ' '; // 1,2,3,4,5
    }
    cout << endl;

    cout << endl << "Descending Order: ";
    for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) 
    {
        cout << *it << ' '; // 5,4,3,2,1
    }
    cout << endl;

    cout << endl << "Side-Cross Order: ";
    for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) 
    {
        cout << *it << ' '; // 1,5,2,4,3
    }
    cout << endl;

    cout << endl << "Revrese Order: ";
    for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) 
    {
        cout << *it << ' '; // 2,3,4,5,1
    }
    cout << endl;

    cout << endl << "Regular Order: ";
    for (auto it = container.begin_order(); it != container.end_order(); ++it) 
    {
        cout << *it << ' '; // 1,5,4,3,2
    }
    cout << endl;

    cout << endl << "Middle-Out Order: ";
    for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) 
    {
        cout << *it << ' '; // 3,2,4,1,5
    }
    cout << endl;

    return 0;
}
