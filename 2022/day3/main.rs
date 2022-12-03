use array_tool::vec::Intersect;
use std::fs;

fn main() {
    // read a file
    let input = fs::read_to_string("input.txt").expect("Something went wrong reading the file");

    part1(&input);
    part2(&input);
}

fn part1(input: &String) {
    let result = input
        .split("\n")
        // .collect::<Vec<&str>>()
        .fold(0, |acc, x| {
            let half = x.len() / 2;
            let full = x.len();

            let part_a = x[0..half].chars().collect::<Vec<char>>();
            let part_b = x[half..full].chars().collect::<Vec<char>>();

            let intersection = part_a.intersect(part_b);

            let letter = intersection[0];



            if (letter as i32) < ('a' as i32) {
                println!("{} {}", letter, (letter as i32 - 'A' as i32) + 27);
                return acc + (letter as i32 - 'A' as i32) + 27;
            } else {
                println!("{} {}", letter, (letter as i32 - 'a' as i32) + 1);

                return acc + (letter as i32 - 'a' as i32) + 1;
            }
        });

    println!("{:?}", result);
}

fn part2(input: &String){
    let result = input
    .split("\n")
    .collect::<Vec<&str>>()
    .chunks(3)
    .fold(0, |acc, x| {
        let a = x[0].chars().collect::<Vec<char>>();
        let b = x[1].chars().collect::<Vec<char>>();
        let c = x[2].chars().collect::<Vec<char>>();

        let all = a.intersect(b).intersect(c);

        let letter = all[0];

        if (letter as i32) < ('a' as i32) {
            println!("{} {}", letter, (letter as i32 - 'A' as i32) + 27);
            return acc + (letter as i32 - 'A' as i32) + 27;
        } else {
            println!("{} {}", letter, (letter as i32 - 'a' as i32) + 1);

            return acc + (letter as i32 - 'a' as i32) + 1;
        }
    });

    println!("{:?}", result);
}
