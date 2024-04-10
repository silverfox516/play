use std::fmt;

// debug 1
#[derive(Debug)]
struct Structure(i32);

#[derive(Debug)]
struct Deep(Structure);

// debug 2
#[derive(Debug)]
struct Person<'a> {
    name: &'a str,
    age: u8
}

// display 1
struct StructureDisplay(i32);

impl fmt::Display for StructureDisplay {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "aya:{}", self.0)
    }
}

// display 2
#[derive(Debug)]
struct MinMax(i64, i64);

impl fmt::Display for MinMax {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "({}, {})", self.0, self.1)
    }
}

#[derive(Debug)]
struct Point2D {
    x: f64,
    y: f64,
}

impl fmt::Display for Point2D {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "x: {}, y: {}", self.x, self.y)
    }
}

// display, testcase:list
struct List(Vec<i32>);

impl fmt::Display for List {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let vec = &self.0;

        write!(f, "[")?;
        for (count, v) in vec.iter().enumerate() {
            if count != 0 { write!(f, ", ")?; }
            write!(f, "{}", v)?;
        }
        write!(f, "]")
    }
}

// formatting
struct City {
    name: &'static str,
    lat: f32,
    lon: f32,
}

impl fmt::Display for City {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let lat_c = if self.lat >= 0.0 { 'N' } else { 'S' };
        let lon_c = if self.lon >= 0.0 { 'E' } else { 'W' };

        write!(f, "{}: {:.3}°{} {:.3}°{}",
               self.name, self.lat.abs(), lat_c, self.lon.abs(), lon_c)
    }
}

#[derive(Debug)]
struct Color {
    red: u8,
    green: u8,
    blue: u8,
}

impl fmt::Display for Color {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "RGB ({}, {}, {}) 0x{:02X}{:02X}{:02X}",
        self.red, self.green, self.blue,
        self.red, self.green, self.blue)
    }
}


fn main() {
    // debug 1
    println!("{:?} month in a year.", 12);
    println!("{1:?} {0:?} is the {actor:?} name.",
             "Slater",
             "Christian",
             actor="actor's");
    println!("Now {:?} will print!", Structure(3));
    println!("Now {:?} will print!", Deep(Structure(7)));

    // debug 2
    let name = "Peter";
    let age = 27;
    let peter = Person { name, age };
    println!("{:?}", peter);
    println!("{:#?}", peter);

    // dislapy 1
    println!("Now {} will print!", StructureDisplay(5));

    // display 2
    let minmax = MinMax(0, 14);

    println!("Compare structures:");
    println!("Display: {}", minmax);
    println!("Debug: {:?}", minmax);

    let big_range = MinMax(-300, 300);
    let small_range = MinMax(-3, 3);

    println!("The big range is {big} and the small is {small}",
             small = small_range,
             big = big_range);

    let point = Point2D { x: 3.3, y: 7.2 };

    println!("Compare points:");
    println!("Display: {}", point);
    println!("Debug: {:?}", point);
    //println!("What does Point2D look like in binary: {:b}?", point);

    // display, testcase:list
    let v = List(vec![1, 2, 3]);
    println!("{}", v);

    // formatting
    for city in [
        City { name: "Dublin", lat: 53.347778, lon: -6.259722 },
        City { name: "Oslo", lat: 59.95, lon: 10.75 },
        City { name: "Vancouver", lat: 49.25, lon: -123.1 },
    ] {
        println!("{}", city);
    }

    for color in [
        Color { red: 128, green: 255, blue: 90 },
        Color { red: 0, green: 3, blue: 254 },
        Color { red: 0, green: 0, blue: 0 },
    ] {
        println!("{}", color);
    }
}
