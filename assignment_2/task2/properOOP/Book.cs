namespace JafarMustafazade1;

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
