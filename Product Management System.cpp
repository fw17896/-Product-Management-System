#include <iostream>
#include <string>

using namespace std;

struct Product {
    int productID;
    string name;
    int price;
    Product* left;
    Product* right;

    Product(int id, string n, int p) {
        productID = id; 
        name = n; 
        price = p; 
        left = NULL;
        right = NULL;  
    }    
};

Product* addProduct(Product* node, int productID, const string& name, int price) {
    if (node == NULL) {
        cout << "ID=" << productID << ", Name=" << name << ", Price=$" << price << endl;
        return new Product(productID, name, price);
    }

    if (productID < node->productID || (productID == node->productID && price < node->price)) {
        node->left = addProduct(node->left, productID, name, price);
    } else if (productID > node->productID || (productID == node->productID && price > node->price)) {
        node->right = addProduct(node->right, productID, name, price);
    }
    return node;
}

Product* update(Product* node, int productID, const string& name, int price) {
    if (node == NULL) {
        cout << "Product with ID " << productID << " not found for updating.\n";
        return NULL;
    }

    if (productID == node->productID) {
        cout << "Updating Product: ID=" << productID << "\n";
        cout << "Old Name: " << node->name << ", Old Price: $" << node->price << endl;
        node->name = name;
        node->price = price;
        cout << "New Name: " << node->name << ", New Price: $" << node->price << endl;
        return node;
    }

    if (productID < node->productID) {
        return update(node->left, productID, name, price);
    } else {
        return update(node->right, productID, name, price);
    }
}

Product* search(Product* node, int productID) {
    if (node == NULL) {
        return NULL;
    }

    if (productID == node->productID) {
        return node;
    } else if (productID < node->productID) {
        return search(node->left, productID);
    } else {
        return search(node->right, productID);
    }
}

Product* findMin(Product* node) {
    if (node == NULL) {
        return NULL;
    }

    Product* minProduct = node;

    if (node->left != NULL) {
        Product* leftMin = findMin(node->left);
        if (leftMin && leftMin->price < minProduct->price) {
            minProduct = leftMin;
        }
    }

    if (node->right != NULL) {
        Product* rightMin = findMin(node->right);
        if (rightMin && rightMin->price < minProduct->price) {
            minProduct = rightMin;
        }
    }

    return minProduct;
}

Product* findMax(Product* node) {
    if (node == NULL) {
        return NULL;
    }

    Product* maxProduct = node;

    if (node->left != NULL) {
        Product* leftMax = findMax(node->left);
        if (leftMax && leftMax->price > maxProduct->price) {
            maxProduct = leftMax;
        }
    }

    if (node->right != NULL) {
        Product* rightMax = findMax(node->right);
        if (rightMax && rightMax->price > maxProduct->price) {
            maxProduct = rightMax;
        }
    }

    return maxProduct;
}



int main() {
    Product* root = NULL;

    cout << "Adding Products...\n";
    root = addProduct(root, 1, "Suit", 1000);
    root = addProduct(root, 2, "Shirt", 500);
    root = addProduct(root, 3, "Trouser", 300);
    root = addProduct(root, 4, "Ring", 200);
    cout << endl;

    root = update(root, 1, "Laptop", 1200);
    cout << endl;

    cout << "Search Products\n";
    Product* foundProduct = search(root, 2);
    if (foundProduct != NULL) {
        cout << "Product Found: \n";
        cout << "ID: " << foundProduct->productID << ", Name: " << foundProduct->name << ", Price: $" << foundProduct->price << endl;
    } else {
        cout << "Product with ID=2 not found.\n";
    }
    cout << endl;

    Product* highestPrice = findMax(root);
    if (highestPrice != NULL) {
        cout << "Product with the highest price: \n";
        cout << "ID: " << highestPrice->productID << ", Name: " << highestPrice->name << ", Price: $" << highestPrice->price << endl;
    } else {
        cout << "No products available.\n";
    }
    cout << endl;

    Product* lowestPrice = findMin(root);
    if (lowestPrice != NULL) {
        cout << "Product with the lowest price: \n";
        cout << "ID: " << lowestPrice->productID << ", Name: " << lowestPrice->name << ", Price: $" << lowestPrice->price << endl;
    } else {
        cout << "No products available\n";
    }
    cout << endl;

    return 0;
}
