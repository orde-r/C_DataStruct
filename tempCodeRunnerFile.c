if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                HashTable[index] = current->next;
            }
            free(current);
            return;