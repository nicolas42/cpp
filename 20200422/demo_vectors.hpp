#include <iostream>
#include <vector>
#include <string>
 
int demo_vectors()
{
    using namespace std;

	vector<int> ix = {1, 2, 4, 8, 16};
	vector<string> fruits = {"orange", "apple", "raspberry"};
	vector<char> empty;
 
    ix.push_back(25);
    ix.push_back(13);
 
    // Iterate and print values of vector
    for(int i : ix) {
        cout << i << '\n';
    }

    cout << "OMG my thing\n";
    for(auto f : fruits) {
        cout << "fruit " << f << endl;
    }

    return 0;
}
