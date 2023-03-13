#include <iostream>
#include <string>

using namespace std;
using std::string;

class TreeNode {
    bool isEnd;
    string meaning;
    TreeNode** children;
    friend class Tree;
public:
    TreeNode() {
        this->isEnd = false;
        this->meaning = "";
        this->children = new TreeNode*[26];
        for (int i = 0; i < 26; i++) {
            this->children[i] = NULL;
        
        }
    
    }
    ~TreeNode() {
        for (int i = 0; i < 26; i++) {
            if(this->children[i] != NULL) delete this->children[i];
        
        }
        delete this->children;
    
    }
};
class Tree {
    TreeNode* root;
public:
    Tree() {
        this->root = new TreeNode();
    
     }
    void addNewWord(string word, string meaning, TreeNode* temp) {
        if (word.length() == 0) {
            temp->isEnd = true;
            temp->meaning = meaning;
            return;
        
        }
        char letter = word[0];
        int index = int(letter) - int('a');
        if (temp->children[index] == NULL) {
            TreeNode* newNode = new TreeNode();
            temp->children[index] = newNode;
        
         }
        addNewWord(word.erase(0, 1), meaning, temp->children[index]);
    
    }
    string findTheMeaning(string word, TreeNode* temp) {
        while (temp) {
            if (word.length() == 0) {
                if (temp->isEnd) return temp->meaning;
                else return "-";
            
            }
            char letter = word[0];
            int index = int(letter) - int('a');
            if (temp->children[index] == NULL) return "-";

            word = word.erase(0, 1);
            temp = temp->children[index];
        
        }
        return "-";
    
    }
    TreeNode* getRoot() {
        return this->root;
    
}
    void printRecursively(TreeNode* node) {
        if (node->isEnd) cout << node->meaning<<endl;
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != NULL) printRecursively(node->children[i]);
        
        }
    
    }
    void printAllMeanings(string prefix, TreeNode* temp) {
        while (temp) {
            if (prefix.length() == 0) {
                printRecursively(temp);
                return;
            
            }
            char letter = prefix[0];
            int index = int(letter) - int('a');
            if (temp->children[index] == NULL) {
                cout << "-"<<endl;
            }

            prefix = prefix.erase(0, 1);
            temp = temp->children[index];
        
        }
    
    }
};

int main(){
    Tree* tree = new Tree();
    char command;
    string word, meaning;
    while (cin >> command) {
        switch (command) {
        case '*':
            cin >> word;
            tree->printAllMeanings(word, tree->getRoot());
            break;
        case '+':
            cin >> word >> meaning;
            tree->addNewWord(word, meaning, tree->getRoot());
            break;
        case '?':
            cin >> word;
            cout << tree->findTheMeaning(word, tree->getRoot()) << endl;
            break;
        
}
    
}
}
