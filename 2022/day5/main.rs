use regex::Regex;
use std::fs;

fn main() {
    // read a file
    let input = fs::read_to_string("input.txt").expect("Something went wrong reading the file");
    let map_part: String = input.split("\n\n").collect::<Vec<&str>>()[0].to_string();
    let moves_part: String = input.split("\n\n").collect::<Vec<&str>>()[1].to_string();

    let map = parse_map(&map_part);
    let moves = parse_moves(&moves_part);

    part1(&map, &moves);
    part2(&map, &moves);
}

type Stacks = Vec<Vec<char>>;
type Move = (i32, i32, i32);

// parse the following to a 2d vector of chars
//     [D]
// [N] [C]
// [Z] [M] [P]
//  1   2   3
fn parse_map(input: &str) -> Stacks {
    let last_line = input.lines().last().unwrap();

    // get the indexes of all the non space characters in the last line
    let indexes: Vec<usize> = last_line
        .chars()
        .enumerate()
        .filter(|(_, c)| *c != ' ')
        .map(|(i, _)| i)
        .collect();

    // map over each line and only keep the characters at the indexes
    let rows: Vec<Vec<char>> = input
        .lines()
        .map(|line| {
            line.chars()
                .enumerate()
                .filter(|(i, _)| indexes.contains(i))
                .map(|(_, c)| c)
                .collect()
        })
        .collect();

    // removed the last item from rows
    let filtered = rows[..rows.len() - 1].to_vec();

    // create a vector of vectors with the same length as the number of columns
    let mut cols: Stacks = vec![vec![]; indexes.len()];

    // iterate over the rows and add the characters to the correct column
    for (_, row) in filtered.iter().enumerate() {
        for (j, c) in row.iter().enumerate() {
            if c == &' ' {
                continue;
            }
            cols[j].push(*c);
        }
    }

    for col in cols.iter_mut() {
        col.reverse();
    }

    return cols;
}

fn print_map(map: &Stacks) {
    println!();

    // find longest stack
    let highest = map.iter().map(|x| x.len()).max().unwrap();

    // iterate over the stacks print the longest stack first
    for i in (0..highest).rev() {
        for stack in map.iter() {
            if stack.len() > i {
                print!("{} ", stack[i]);
            } else {
                print!("  ");
            }
        }
        println!();
    }
}

fn parse_moves(input: &str) -> Vec<Move> {
    let moves = input.lines().map(|line| {
        let re = Regex::new(r"move (\d+) from (\d+) to (\d+)").unwrap();
        let caps = re.captures(line).unwrap();
        let amount = caps.get(1).unwrap().as_str().parse::<i32>().unwrap();
        let from = caps.get(2).unwrap().as_str().parse::<i32>().unwrap();
        let to = caps.get(3).unwrap().as_str().parse::<i32>().unwrap();

        return (amount, from, to);
    });

    return moves.collect();
}

fn print_answer(stacks: &Stacks) {
    for stack in stacks.iter() {
        if stack.len() == 0 {
            continue;
        }
        print!("{}", stack[stack.len() - 1]);
    }
}

fn part1(stacks: &Stacks, moves: &Vec<Move>) {
    let mut stacks = stacks.clone();

    for (amount, from, to) in moves {
        for _ in 0..*amount {
            let c = stacks[*from as usize - 1].pop().unwrap();
            stacks[*to as usize - 1].push(c);
        }
    }

    print!("Part 1: ");
    print_answer(&stacks);
    println!()
}

fn part2(stacks: &Stacks, moves: &Vec<Move>) {
    let mut stacks = stacks.clone();
    for (amount, from, to) in moves {
        let from_len = stacks[*from as usize - 1].len();

        let slice = stacks[*from as usize - 1][from_len - *amount as usize..].to_vec();
        stacks[*from as usize - 1].truncate(from_len - *amount as usize);
        stacks[*to as usize - 1].append(&mut slice.clone());
    }

    print!("Part 2: ");
    print_answer(&stacks);
    println!()
}
