
class LibraryItem
    attr_accessor :title, :author, :publication_year
  
    def initialize(title, author, publication_year)
      @title = title
      @author = author
      @publication_year = publication_year
    end

    def display_info
      puts " Title: #{@title},\n Author: #{@author},\n Year: #{@publication_year}."
    end
  end
  
  #  #
  class Book < LibraryItem
    attr_accessor :genre
  
    def initialize(title, author, publication_year, genre)
      super(title, author, publication_year)
      @genre = genre
    end
  
    def display_info
      super
      puts " Genre: #{@genre}"
    end
  end
  
  #  #
  class DVD < LibraryItem
    attr_accessor :director
  
    def initialize(title, author, publication_year, director)
      super(title, author, publication_year)
      @director = director
    end
  
    def display_info
      super
      puts " Director: #{@director}"
    end
  end
  
  #  #
  class CD < LibraryItem
    attr_accessor :artist
  
    def initialize(title, author, publication_year, artist)
      super(title, author, publication_year)
      @artist = artist
    end
  
    def display_info
      super
      puts " Artist: #{@artist}"
    end
  end
  
  #  #
  class Library
    def initialize
      @items = []
    end
  
    def add_item(item)
      @items << item
    end
  
    def remove_item(item)
      @items.delete(item)
    end
  
    def display_all_items
      @items.each do |item|
        item.display_info
        puts "\n"
      end
    end
  end
  
  # main #
  book = Book.new('The Headless Horseman', 'Mayne Reid', 1866, 'novel')
  dvd = DVD.new('Nightmares Never End', 'JT Music', 2021, 'feat Andrea Storm Kaden')
  cd = CD.new('Russian Roulette Plus - 2', 'Jafar Mustafazade', 2024, 'endergfungames.com/rrp2')
  
  library = Library.new
  library.add_item(book)
  library.add_item(dvd)
  library.add_item(cd)

  puts 'Library Items:'
  library.display_all_items

  while true
    sleep(1)
  end
  