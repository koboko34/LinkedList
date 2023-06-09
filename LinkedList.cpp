#include <iostream>

template <typename T>
class LinkedList
{
    struct Node
    {
        T data;
        Node* next;

        Node()
        {
            next = nullptr;
        }
    };

    Node* head = nullptr;
    Node* current = nullptr;

public:

    int size = 0;

    void Push(T data)
    {
        Node* adding = new Node();
        adding->data = data;

        if (head == nullptr)
        {
            head = adding;
            size++;
            return;
        }

        current = head;

        while (current->next != nullptr)
        {
            current = current->next;
        }
        
        current->next = adding;
        size++;
    }

    void Pop()
    {
        current = head;
        for (int i = 0; i < size - 1; i++)
        {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
        size--;
    }

    void Insert(T data, int index)
    {
        Node* adding = new Node();
        adding->data = data;
        
        // if inserting as new head
        if (index == 0)
        {
            adding->next = head;
            head = adding;
            size++;
            return;
        }
        
        if (head == nullptr)
        {
            std::cout << "Head is null!\n";
            return;
        }
        
        if (index >= size)
        {
            std::cout << "Out of bounds!\n";
            return;
        }

        // if inserting as body
        current = head;
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        adding->next = current->next;
        current->next = adding;
        size++;
    }

    void Remove(int index)
    {
        Node* tail;

        if (index == 0)
        {
            tail = head->next;
            delete head;
            head = tail;
        }
        
        current = head;
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        tail = current->next->next;
        delete current->next;
        current->next = tail;
        size--;
    }

    int operator[](int index)
    {
        if (head == nullptr)
        {
            std::cout << "Head is null!\n";
            return -1;
        }
        
        if (index >= size)
        {
            std::cout << "Out of bounds!\n";
            return -1;
        }

        current = head;

        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        
        return current->data;
    }

    int Find(T data)
    {
        current = head;
        for (int i = 0; i < size; i++)
        {
            if (current->data == data)
            {
                return i;
            }
            current = current->next;
        }
        return -1;
    }

    int Length() const
    {
        return size;
    }

    int Size() const
    {
        return size;
    }

    LinkedList* Reverse()
    {
        if (size <= 1)
        {
            return this;
        }
        
        Node* prev = nullptr;
        current = head;
        Node* next = current->next;
        current->next = prev;

        while (next != nullptr)
        {
            prev = current;
            current = next;
            next = current->next;
            current->next = prev;
        }
        head = current;

        return this;
    }
};

template <typename T>
class DoublyLinkedList
{
private:

    struct Node
    {
        T data;
        Node* next;
        Node* prev;

        Node()
        {
            next = nullptr;
        }
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    Node* current = nullptr;

    void PrepIndex(int index)
    {
        if (size / 2 > index)
        {
            current = head;
            for (int i = 0; i < index; i++)
            {
                current = current->next;
            }
        }
        else
        {
            current = tail;
            for (int i = size; i > index + 1; i--)
            {
                current = current->prev;
            }
        }
    }

public:

    int size = 0;

    void Push(T data)
    {
        Node* adding = new Node();
        adding->data = data;

        if (head == nullptr)
        {
            head = adding;
            tail = adding;
            size++;
            return;
        }

        tail->next = adding;
        adding->prev = tail;
        tail = adding;
        size++;
    }

    void Pop()
    {
        Node* newTail = tail->prev;
        delete tail;
        tail = newTail;
        tail->next = nullptr;
        size--;
    }

    void Insert(T data, int index)
    {
        Node* adding = new Node();
        adding->data = data;
        
        // if inserting as new head
        if (index == 0)
        {
            adding->next = head;
            head->prev = adding;
            head = adding;
            if (size == 1)
                tail = adding;
            size++;
            return;
        }

        if (index == size)
        {
            Push(data);
            return;
        }
        
        if (head == nullptr || tail == nullptr)
        {
            std::cout << "Head/tail is null!\n";
            return;
        }
        
        if (index >= size)
        {
            std::cout << "Out of bounds!\n";
            return;
        }

        // if index is in first half, traverse forward from head, otherwise traverse back from tail
        if (size / 2 > index)
        {
            current = head;
            for (int i = 0; i < index - 1; i++)
            {
                current = current->next;
            }
        }
        else
        {
            current = tail;
            for (int i = size; i > index; i--)
            {
                current = current->prev;
            }
        }
        
        current->next->prev = adding;
        adding->next = current->next;
        adding->prev = current;
        current->next = adding;
        size++;
    }

    void Remove(int index)
    {
        PrepIndex(index);

        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        size--;
    }

    int operator[](int index)
    {
        if (head == nullptr)
        {
            std::cout << "Head is null!\n";
            return -1;
        }
        
        if (index >= size)
        {
            std::cout << "Out of bounds!\n";
            return -1;
        }

        PrepIndex(index);
        
        return current->data;
    }

    int Find(T data)
    {
        current = head;
        for (int i = 0; i < size; i++)
        {
            if (current->data == data)
            {
                return i;
            }
            current = current->next;
        }
        return -1;
    }

    int Length() const
    {
        return size;
    }

    int Size() const
    {
        return size;
    }

    // to do
    DoublyLinkedList* Reverse()
    {
        if (size <= 1)
        {
            return this;
        }
        
        Node* newNext = nullptr;
        current = head;
        tail = current;
        current->prev = current->next;
        current->next = newNext;

        while (current->prev != nullptr)
        {
            current = current->prev;
            newNext = current->prev;
            current->prev = current->next;
            current->next = newNext;
        }
        
        head = current;
        return this;
    }
};

int main()
{
    LinkedList<int> List;
    List.Push(20);
    List.Push(21);
    List.Push(22);
    List.Push(23);
    List.Push(24);
    List.Push(25);
    List.Push(26);
    List.Push(27);
    List.Push(28);
    List.Push(29);

    List.Insert(30, 3);
    List.Insert(31, 6);
    List.Insert(32, 0);

    List.Pop();

    List.Remove(4);
    List.Remove(0);
    List.Remove(9);

    List.Push(40);

    List.Reverse();

    std::cout << "\nSingly linked list tests:\n\n";

    for (int i = 0; i < List.size; i++)
    {
        std::cout << List[i] << std::endl;
    }

    std::cout << List.Find(27) << std::endl;
    std::cout << "\nLength: " << List.Length() << "\n\n";

    std::cout << "Double linked list tests:\n\n";

    DoublyLinkedList<int> DoubleList;
    
    DoubleList.Push(10);
    DoubleList.Push(11);
    DoubleList.Push(12);
    DoubleList.Push(13);
    DoubleList.Push(14);
    DoubleList.Push(15);
    DoubleList.Push(16);
    DoubleList.Push(17);

    DoubleList.Pop();

    DoubleList.Remove(5);

    DoubleList.Insert(24, 1);
    DoubleList.Insert(25, 3);
    DoubleList.Insert(26, 7);

    DoubleList.Reverse();
    
    DoubleList.Push(21);

    DoubleList.Insert(30, 8);
    DoubleList.Insert(40, 0);

    for (int i = 0; i < DoubleList.size; i++)
    {
        std::cout << DoubleList[i] << std::endl;
    }

    std::cout << DoubleList.Find(14) << std::endl;

    std::cout << "\nLength: " << DoubleList.Length() << "\n\n";

    return 0;
}