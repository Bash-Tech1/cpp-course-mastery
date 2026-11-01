#include <iostream>
using namespace std;
struct myPair{
    int dragonHealth;
    int bouns;
};
bool compare(myPair a, myPair b){
    if(a.dragonHealth != b.dragonHealth)
        return a.dragonHealth < b.dragonHealth;
    return a.bouns > b.bouns;
}
int main(){
    int myHelath, numberOfDragons;
    cin >> myHelath >> numberOfDragons;
    myPair arrayOfDragons[numberOfDragons];
    for (int i = 0; i < numberOfDragons; ++i) {
        myPair p;
        cin >> p.dragonHealth >> p.bouns;
        arrayOfDragons[i] = p;
    }
    sort(arrayOfDragons,arrayOfDragons+numberOfDragons, compare);
    for (int i = 0; i < numberOfDragons; ++i) {
        cout << arrayOfDragons[i].dragonHealth << " " << arrayOfDragons[i].bouns << endl;
    }
    return 0;
}