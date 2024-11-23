use std::io::{self, Write};

fn main() {
    let mut x = 5;
    println!("The value of x is: {}", x);
    x = 6;
    println!("The value of x is: {}", x);
    for i in 1..5 {
        print!("{} ", i);
        io::stdout().flush().unwrap();
    }
}
