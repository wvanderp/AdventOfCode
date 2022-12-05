use std::fs;

fn main() {
    // read a file
    let input = fs::read_to_string("input.txt").expect("Something went wrong reading the file");
    let map_part: String = input.split("\n\n").collect::<Vec<&str>>()[0].to_string();

    // part1(&input);
    parse_map(&map_part);
    // part2(&input);
}

type Stacks = Vec<Vec<char>>;

// parse the following to a 2d vector of chars
//     [D]    
// [N] [C]    
// [Z] [M] [P]
//  1   2   3 
fn parse_map(input: &str) -> Stacks{
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
    let filterd = rows[..rows.len() - 1].to_vec();

    // flip rows and columns
    let cols: Vec<Vec<char>> = (0..filterd[0].len())
        .map(|i| filterd.iter().map(|row| row[i]).collect())
        .collect();

    println!("{:?}", cols);
}

fn print_map(map: &Stacks) {
    for row in map {
        for c in row {
            print!("{}", c);
        }
        println!();
    }
}

// fn part1(input: &String) {
//     let map_part: String = input.split("\n\n").collect::<Vec<&str>>()[0].to_string();

//     // let stacks: Vec<Vec<String>> = 
    
//     let stacks = map_part.split("\n")
//     .map(|x| {


//         let colomns = x
//         .chars()
//         .collect::<Vec<char>>()
//         .chunks(3)
//         .map(|x| x.iter().collect::<String>())
//         .map(|f| {
//             // filter out [ and ]
//             f.chars().filter(|x| *x != '[' && *x != ']').collect::<String>();

//             return f
//         });

//         println!("{:?}", colomns)
//     });

//     println!("{:?}", stacks)
//     // println!("{}", map_part);
// }

// fn part2(input: &String){

// }
