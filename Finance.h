#include "Product.h"

void ProductList::sell() {
    string name;
    int amount=0;
    int stock;
    displayAll();
    cout << "Enter name: ";
    cin >> name;
    while(amount<=0) {
    cout << "Enter amount: ";
    cin >> amount;
    }
    ProductNode* current = head;
    while (current) {
        if(current->product->getName() == name) {
            stock = current->product->getStock();
            if(amount > stock) {
                cout << "Not enough stock" << endl;
            }else {
                current->product->setStock(stock-amount);
                cout << "Sold" << amount << "of" << name << "Reamining in stock: " << stock - amount << endl;
                saveToFile("products.txt");
            }
            return;
        }
        current = current->next;
    }
    cout << "Product \"" << name << "\" not found." << endl;
}
