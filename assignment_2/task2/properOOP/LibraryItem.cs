namespace JafarMustafazade1;

abstract class LibraryItem
{
    private static int _idCounter = 0;
    private int _year;


    // methods-property //
    public int Id { get; private set; }
    public string Title { get; set; }
    public string Author { get; set; }
    public int PublicationYear  {
        get => _year;
        set 
        { 
            if (value > 100) _year = value; // first book appeared in the 2-5nd generation
        }
    }


    // methods-constructor //
    public LibraryItem()
    {
        Id = GenerateId();
    }


    // methods-private //
    protected virtual int GenerateId()
    {
        _idCounter += 1;
        return _idCounter;
    }


    // methods-public //
    public virtual void DisplayInfo(string beforeline = "")
    {
        Console.Write(beforeline);
        Console.WriteLine($"ID: {Id}");
        Console.Write(beforeline);
        Console.WriteLine($"Title: {Title}");
        Console.Write(beforeline);
        Console.WriteLine($"Author: {Author}");
        Console.Write(beforeline);
        Console.WriteLine($"Publication Year: {PublicationYear}");
    }
}
