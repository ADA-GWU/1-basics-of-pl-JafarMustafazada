namespace JafarMustafazade1;

class Library
{
    private List<LibraryItem> _items = new();
    
    // //
    public void AddItem(LibraryItem item)
    {
        _items.Add(item);
    }

    public void RemoveItem(LibraryItem item)
    {
        _items.Remove(item);
    }

    public void DisplayAllItems()
    {
        foreach (var item in _items)
        {
            Console.WriteLine("[");
            item.DisplayInfo("\t");
            Console.WriteLine("]");
        }
    }
}

