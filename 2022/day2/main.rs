use std::fs;

enum Moves {
    Rock,
    Paper,
    Scissors
}

enum Results {
    Win,
    Lose,
    Draw
}

fn who_wins(opponent: &Moves, player: &Moves) -> Results {
    match (opponent, player) {
        (Moves::Rock, Moves::Rock) => Results::Draw,
        (Moves::Rock, Moves::Paper) => Results::Win,
        (Moves::Rock, Moves::Scissors) => Results::Lose,
        (Moves::Paper, Moves::Rock) => Results::Lose,
        (Moves::Paper, Moves::Paper) => Results::Draw,
        (Moves::Paper, Moves::Scissors) => Results::Win,
        (Moves::Scissors, Moves::Rock) => Results::Win,
        (Moves::Scissors, Moves::Paper) => Results::Lose,
        (Moves::Scissors, Moves::Scissors) => Results::Draw,
    }
}

fn main(){
    // read a file
    let input = fs::read_to_string("input.txt")
        .expect("Something went wrong reading the file");

    part1(&input);
    part2(&input);
}


fn part1(input: &String){
    let result = input
        .lines()
        .map(|line| {
            let opponent = match line.chars().nth(0).unwrap() {
                'A' => Moves::Rock,
                'B' => Moves::Paper,
                'C' => Moves::Scissors,
                _ => panic!("Invalid input")
            };

            let player = match line.chars().nth(2).unwrap() {
                'X' => Moves::Rock,
                'Y' => Moves::Paper,
                'Z' => Moves::Scissors,
                _ => panic!("Invalid input")
            };

            let result = who_wins(&opponent, &player);

            let result_score = match result {
                Results::Win => 6,
                Results::Lose => 0,
                Results::Draw => 3
            };

            let choice_score = match player {
                Moves::Rock => 1,
                Moves::Paper => 2,
                Moves::Scissors => 3
            };

            return result_score + choice_score;
        })
        .sum::<i32>();

    println!("Part 1: {}", result);
}

fn part2(input: &String){
    let result = input
        .lines()
        .map(|line| {
            let opponent = match line.chars().nth(0).unwrap() {
                'A' => Moves::Rock,
                'B' => Moves::Paper,
                'C' => Moves::Scissors,
                _ => panic!("Invalid input")
            };

            let result = match line.chars().nth(2).unwrap() {
                'X' => Results::Lose,
                'Y' => Results::Draw,
                'Z' => Results::Win,
                _ => panic!("Invalid input")
            };

            let player = match (opponent, &result) {
                (Moves::Rock, Results::Lose) => Moves::Scissors,
                (Moves::Rock, Results::Draw) => Moves::Rock,
                (Moves::Rock, Results::Win) => Moves::Paper,
                (Moves::Paper, Results::Lose) => Moves::Rock,
                (Moves::Paper, Results::Draw) => Moves::Paper,
                (Moves::Paper, Results::Win) => Moves::Scissors,
                (Moves::Scissors, Results::Lose) => Moves::Paper,
                (Moves::Scissors, Results::Draw) => Moves::Scissors,
                (Moves::Scissors, Results::Win) => Moves::Rock,
            };

            let result_score = match result {
                Results::Win => 6,
                Results::Lose => 0,
                Results::Draw => 3
            };

            let choice_score = match player {
                Moves::Rock => 1,
                Moves::Paper => 2,
                Moves::Scissors => 3
            };

            return result_score + choice_score;
        })
        .sum::<i32>();

    println!("Part 2: {:?}", result);
}