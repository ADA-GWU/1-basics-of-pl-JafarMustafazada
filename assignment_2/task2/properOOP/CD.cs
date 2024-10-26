using JafarMustafazade1;

namespace JafarMustafazade1;

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
