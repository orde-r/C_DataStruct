//Succesor 
        node *temp = findMin(root->right); //Succ
        root->value = temp->value;
        root->right = delete(root->right, temp->value); //Succ