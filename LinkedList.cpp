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

        // if inserting as tail
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

    for (int i = 0; i < List.size; i++)
    {
        std::cout << List[i] << std::endl;
    }

    std::cout << List.Find(27) << std::endl;
    std::cout << "Length: " << List.Length() << std::endl;
    
    return 0;
}