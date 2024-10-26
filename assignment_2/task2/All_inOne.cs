using System;
using System.Collections.Generic;

abstract class LibraryItem
{
    private static int _idCounter = 0;
    private int _year;


    // methods-property //
    public int Id { get; private set; }
    public string Title { get; set; }
    public string Author { get; set; }
    public int PublicationYear
    {
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


    // methods-private // will change with "new"
    protected virtual int GenerateId()
    {
        _idCounter += 1;
        return _idCounter;
    }


    // methods-public // will change with "override"
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


class Book : LibraryItem
{
    public string Genre { get; set; }

    public override void DisplayInfo(string beforeline = "")
    {
        base.DisplayInfo(beforeline);
        Console.Write(beforeline);
        Console.WriteLine($"Genre: {Genre}");
    }
    public new string GenerateId()
    {
        return "Book#" + Id;
    }
}


class DVD : LibraryItem
{
    public string Director { get; set; }

    public override void DisplayInfo(string beforeline = "")
    {
        base.DisplayInfo(beforeline);
        Console.Write(beforeline);
        Console.WriteLine($"Director: {Director}");
    }

    public new string GenerateId()
    {
        return "DVD#" + Id;
    }
}


class CD : LibraryItem
{
    public string Artist { get; set; }

    public override void DisplayInfo(string beforeline = "")
    {
        base.DisplayInfo(beforeline);
        Console.Write(beforeline);
        Console.WriteLine($"Artist: {Artist}");
    }

    public new string GenerateId()
    {
        return "CD#" + Id;
    }
}


class Library
{
    private List<LibraryItem> _items = new List<LibraryItem>();

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
