use std::io;

fn hanoi_tower(n: usize, x: char, y: char, z: char) {
    if n > 1 {
        hanoi_tower(n - 1, x, z, y);
        println!("{} -> {}", x, z);
        hanoi_tower(n - 1, y, x, z);
    } else {
        println!("{} -> {}", x, z);
    }
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    let n: usize = input.trim().parse().expect("Please enter a number");

    let a = 'A';
    let b = 'B';
    let c = 'C';

    hanoi_tower(n, a, b, c);
    println!("{}", 2_usize.pow(n as u32) - 1);
}
