namespace JafarMustafazade1;

internal class Program
{
    static void Main(string[] args)
    {
        Book book = new Book
        {
            Title = "Professor Dowell's Head",
            Author = "Alexander Belyaev",
            PublicationYear = 1925,
            Genre = "science fiction"
        };

        DVD dvd = new DVD
        {
            Title = "Never Gonna Give You Up",
            Author = "Rick Astley",
            PublicationYear = 2009,
            Director = "Rick Astley"
        };

        CD cd = new CD
        {
            Title = "Grand Theft Auto: San Andreas",
            Author = "Rockstar",
            PublicationYear = 2004,
            Artist = "Rockstar"
        };

        Console.WriteLine("\nDirectly calling CD's DisplayInfo (static binding):");
        cd.DisplayInfo();
        Console.WriteLine($"Custom id: {cd.GenerateId()}");

        Library library = new Library();
        library.AddItem(book);
        library.AddItem(dvd);
        library.AddItem(cd);

        Console.WriteLine("\nLibrary Items (dynamic binding):");
        library.DisplayAllItems();
    }
}
