namespace JafarMustafazade1;

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
