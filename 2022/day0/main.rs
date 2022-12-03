use std::fs;

fn main() {
    // read a file
    let input = fs::read_to_string("input.txt").expect("Something went wrong reading the file");

    part1(&input);
    // part2(&input);
}

fn part1(input: &String) {
    
}

// fn part2(input: &String){

// }
