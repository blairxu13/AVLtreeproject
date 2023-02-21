#include <iostream>
#include <queue>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

//regex search
class TreeNode {
public:
    int val;
    string name;
    TreeNode *left;
    TreeNode *right;
    int height = 0;

    TreeNode(int x, string y) : val(x), name(y), left(nullptr), right(nullptr), height(0) {}
//build a class for each node in the tree

};


class AVLtree {
public:
    TreeNode *rRotate(TreeNode *curr) {
        TreeNode *curr2 = curr->left;
        TreeNode *curr3 = curr2->right;
        curr2->right = curr;
        curr->left = curr3;
        return curr2;
    }

    TreeNode *lRotate(TreeNode *curr1) {
        TreeNode *curr2 = curr1->right;
        TreeNode *curr3 = curr2->left;
        curr2->left = curr1;
        curr1->right = curr3;
        return curr2;
    }

    TreeNode *root_ = nullptr;
    int count = 0;
    vector<TreeNode *> storenode;
//vector is for removenthfunction
    int findHeight(TreeNode *temp) {
        if (!temp) {
            return 0;
        }
        return 1 + max(findHeight(temp->left), findHeight(temp->right));
    }

    int getDiff(TreeNode *x) {
        if (x == nullptr) {
            return 0;
        } else {
            return (findHeight(x->left) - findHeight(x->right));
        }
    }
//get the balance factor to see if we need to rotate it or not

    TreeNode *insert(TreeNode *root, string name, int gatorid) {

        // cout<<"run"<<endl;
        //first insertion
        if (root == nullptr) {
            count++;
            cout << "successful" << endl;
            return new TreeNode(gatorid, name);
        }

        //if id already exist
        if (root->val == gatorid) {
            cout << "unsuccessful" << endl;
            return root;
        } else {
            //left child
            if (root->val < gatorid) {
                if (root->right == nullptr) {
                    root->right = new TreeNode(gatorid, name);
                    cout << "successful" << endl;
                    count++;
                    return root;
                } else {
                    root->right = insert(root->right, name, gatorid);
                }
            } else {
                if (root->left == nullptr) {
                    root->left = new TreeNode(gatorid, name);
                    cout << "successful" << endl;
                    count++;
                    return root;
                } else {
                    root->left = insert(root->left, name, gatorid);
                }
            }
        }
//normal building up a tree
        int diff = getDiff(root);

        if (diff < -1) {
            if (findHeight(root->right->left) - findHeight(root->right->right) > 0) {
                root->right = rRotate(root->right);
                root = lRotate(root);
                root->height = findHeight(root);
            } else {
                root = lRotate(root);
                root->height = findHeight(root);
            }


        }
        if (diff > 1) {
            if (findHeight(root->left->left) - findHeight(root->left->right) < 0) {
                root->left = lRotate(root->left);
                root->height = findHeight(root);

            } else {
                root = rRotate(root);
                root->height = findHeight(root);
            }

        }

        return root;
    }


    void preOrder(TreeNode *root, int &curr) {
        if (root == nullptr) {
            return;
        }
        cout << root->name;
        if (++curr <= count - 1) { cout << ", "; }
        preOrder(root->left, curr);
        preOrder(root->right, curr);
    }

    void inOrder(TreeNode *root, int &curr) {
        if (root == nullptr) {
            return;
        }

        inOrder(root->left, curr);

        storenode.push_back(root);
        cout << root->name;
        if (++curr <= count - 1) { cout << ", "; }

        inOrder(root->right, curr);
    }

    void postOrder(TreeNode *root, int &curr) {
        if (root == nullptr) {
            return;
        }
        postOrder(root->left, curr);
        postOrder(root->right, curr);
        cout << root->name;
        if (++curr <= count - 1) { cout << ", "; }
    }
//all the print statement
    void print() {
        cout << "unsuccessful" << endl;
    }
//search id and search name function will return bool type which helps me print out unsuccessful after
    bool searchId(TreeNode *root, int id) {

        if (root == nullptr) {
            return false;
        } else if (root != nullptr) {
            if (root->val == id) {

                cout << root->name << endl;
                return true;

            }
            return searchId(root->left, id) || searchId(root->right, id);

        }


    }

    void searchName(TreeNode *root, string name, bool &find) {
        if (root == nullptr) {
            return;
        } else if (root != nullptr) {
            if (root->name == name) {
                find = true;
                cout << root->val << endl;


            }

            searchName(root->left, name, find);
            searchName(root->right, name, find);
        }

    }
//find the node is for find the successor for removeid function when the node we need to delete have 2 child

    TreeNode *findNode(TreeNode *temp) {
        if (temp->left == nullptr) {
            return temp;
        }
        findNode(temp->left);
    }

    TreeNode *removeId(TreeNode *root1, int id) {
        //TreeNode* curr = searchnode(root,id);
        if (root1 == nullptr) {
            print();
            return nullptr;
        }
        if (root1->val == id) {


            if (root1->left == nullptr && root1->right != nullptr) {
                TreeNode *temp = root1->right;
                delete root1;
                cout << "successful" << endl;
                count--;
                return temp;

            }
            if (root1->left == nullptr && root1->right == nullptr) {
                delete root1;
                cout << "successful" << endl;
                count--;
                return nullptr;

            }
            if (root1->left != nullptr && root1->right == nullptr) {

                //cout << "successful" << endl;
//                return root1;
                TreeNode *temp = root1->left;
                delete root1;
                cout << "successful" << endl;
                count--;
                return temp;
            }
            if (root1->left != nullptr && root1->right != nullptr) {
                TreeNode *curr = findNode(root1->right);
                root1->val = curr->val;
                root1->name = curr->name;
                root1->right = removeId(root1->right, curr->val);
                //cout << "successful" << endl;
                count--;
                return root_;

            }

        }
        if (id > root1->val) {
            root1->right = removeId(root1->right, id);

        }
        if (id < root1->val) {
            root1->left = removeId(root1->left, id);
        }
        return root1;

    }
//since we already found the height, we simply just have to return the funtion
    int printLevel(TreeNode *curr) {
        if (curr == nullptr) {
            return 0;
        } else {
            return findHeight(curr);
        }
    }

    void inorderRemove(TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        inorderRemove(root->left);
        storenode.push_back(root);
        inorderRemove(root->right);
    }

    bool removeNth(TreeNode *temp, int nth) {
        storenode.clear();
        //cout<<"we are here"<<endl;
        if (temp == nullptr) {
            return false;
        }
        inorderRemove(temp);
        //cout<<"size:"<<storenode.size()<<endl;
        if (nth > storenode.size() || nth < 0) {
            return false;
        } else {

            int userid = storenode[nth]->val;
            root_ = removeId(temp, userid);
            count++;
            return true;
        }

    }


};
//check if the string fits in the constraints
bool checkString(string pass) {
    std::regex pattern("^[a-zA-Z\\s]+$");
    return std::regex_match(pass, pattern);
}
//check if the id fits in the constraints
bool checkNumber(std::string &num) {
    std::regex regex("^[0-9]{8}$");
    return std::regex_match(num, regex);
}


int main() {
    AVLtree obj1;

    int run;
    string inputrun;

    getline(cin, inputrun);
    run = stoi(inputrun);

    for (int i = 0; i < run; i++) {
        string input;

        getline(cin, input);
        istringstream in(input);
        string command;
        in >> command;
        if (command == "insert") {
            string namecommand;
            getline(in, namecommand, '"');
            string namecommand1;
            getline(in, namecommand1, '"');
//          int s= input.find('"');
//        namecommand=input.substr(n,s);
            // namecommand = input;
            //cout << "namecommand" << namecommand << endl;
            in.ignore(1);
            string userid;
            getline(in, userid);
            if (!checkString(namecommand) || !checkNumber(userid)) {
                cout << "unsuccessful" << endl;


//                }
            } else {
                obj1.root_ = obj1.insert(obj1.root_, namecommand1, stoi(userid));

            }
        } else if (command == "printInorder") {
            int x = 0;
            obj1.inOrder(obj1.root_, x);
            cout << endl;
        } else if (command == "remove") {
            in.ignore(1);
            string userid;
            getline(in, input);
            userid = input;
            if (checkNumber(userid)) {
                obj1.root_ = obj1.removeId(obj1.root_, stoi(userid));
            }
        } else if (command == "search") {
            in.ignore(1);
            string name1;
            getline(in, name1);
            if (name1[0] == '\"') {
                string namecommand;
                getline(in, input, '"');
                getline(in, namecommand, '"');
                namecommand = name1.substr(1, name1.length() - 2);
                bool found = false;
                if (checkString(namecommand)) {
                    obj1.searchName(obj1.root_, namecommand, found);
                    if (!found) {
                        cout << "unsuccessful" << endl;
                    }
                }

            } else {
                string userid;
                getline(in, input);
                userid = input.substr(7);
                if (checkNumber(userid)) {
                    // obj1.searchid(obj1.root_, );
                    if (obj1.searchId(obj1.root_, stoi(userid)) == false) {
                        cout << "unsuccessful" << endl;
                    }
                } else {
                    cout << "unsuccessful" << endl;
                }

            }

            //id or name
        } else if (command == "printPreorder") {
            int x = 0;
            obj1.preOrder(obj1.root_, x);
            cout << endl;
        } else if (command == "printPostorder") {
            int x = 0;
            obj1.postOrder(obj1.root_, x);
            cout << endl;
        } else if (command == "printLevelCount") {
            cout << obj1.printLevel(obj1.root_) << endl;

        } else if (command == "removeInorder") {
            in.ignore(1);
            string nth;
            getline(in, input);
            nth = input;

            if (obj1.removeNth(obj1.root_, stoi(nth))) {
                //cout << "successful" << endl;
            } else {
                cout << "unsuccessful" << endl;
            }

        } else {
            cout << "unsuccessful" << endl;
        }


    }
    return 0;
}

