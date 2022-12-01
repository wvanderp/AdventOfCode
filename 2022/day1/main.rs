
use regex::Regex;
use std::fs;

fn main(){
    // read a file
    let input = fs::read_to_string("input.txt")
        .expect("Something went wrong reading the file");

    part1(&input);
    part2(&input);
}

fn map_function(x: String) -> i32 {
    let weights = x.split("\n")
        .filter(|x| x.len() != 0)
        .map(|x| x.trim().parse::<i32>().unwrap())
        .collect::<Vec<i32>>();

    return weights.iter().fold(0, |acc, x| acc + x);
}

fn part1(input: &String){
    // split on empty line regex
    let elfs: Vec<i32> = Regex::new(r"(?m)^.$")
        .unwrap()
        .split(&input.to_owned())
        .map(|x| map_function(x.to_string()))
        .collect::<Vec<i32>>();

    println!("Part 1: {}", elfs.iter().fold(0, |acc, x| acc.max(*x)));
}

fn part2(input: &String){
    // split on empty line regex
    let mut elfs: Vec<i32> = Regex::new(r"(?m)^.$")
        .unwrap()
        .split(&input.to_owned())
        .map(|x| map_function(x.to_string()))
        .collect::<Vec<i32>>();

    elfs.sort();
    elfs.reverse();

    println!("Part 2: {}", elfs[0] + elfs[1] + elfs[2]);
}