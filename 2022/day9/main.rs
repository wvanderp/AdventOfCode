use std::{fs, collections::{HashSet, HashMap}};

fn main() {
    // read a file
    let input = fs::read_to_string("input.txt").expect("Something went wrong reading the file");

    part1(&input);
    // part2(&input);

}





// a vector with enums for all the directions
fn move_tail(tx: i32, ty: i32, hx: i32, hy: i32) -> (i32, i32) {
    let dx = hx - tx;
    let dy = hy - ty;

    let mut hashmap: HashMap<(i32, i32), (i32, i32)> =  HashMap::new();

    hashmap.insert((0, 0), (0, 0));
    hashmap.insert((1, 0), (1, 0));




    let result = hashmap.get(&(dx, dy));



    if result.is_none() {
        println!("direction not found in hashmap: {:?}", (dx, dy));
        return (tx, ty);
    }

    return *result.unwrap();
}


// print the relative position of the tail and head
// make the grid 20 x 20
// make sure the head is always in the middle
// make sure to use usize for the grid
fn print_situation(tx: i32, ty: i32, hx: i32, hy: i32) {
    let mut grid: Vec<Vec<char>> = vec![vec!['.'; 20]; 20];

    let mut hx = hx + 10;
    let mut hy = hy + 10;
    let mut tx = tx + 10;
    let mut ty = ty + 10;

    grid[hy as usize][hx as usize] = 'H';
    grid[ty as usize][tx as usize] = 'T';

    for row in grid {
        for col in row {
            print!("{}", col);
        }
        println!();
    }
}

fn part1(input: &String) {
    let moves = input.lines().map(|line| {
        let mut split = line.split(" ");
        let direction = split.next().unwrap();
        let distance = split.next().unwrap().parse::<i32>().unwrap();

        (direction, distance)
    });

    let mut hx = 0;
    let mut hy = 0;
    let mut tx = 0;
    let mut ty = 0;

    //set of visited points
    let mut positions: HashSet<(i32, i32)> = HashSet::new();

    println!("Initial situation");
    print_situation(tx, ty, hx, hy);

    for m in moves {
        for i in 0..m.1 {
            match m.0 {
                "R" => {
                    hx += 1;
                }
                "L" => {
                    hx -= 1;
                }
                "U" => {
                    hy += 1;
                }
                "D" => {
                    hy -= 1;
                }
                _ => {
                    println!("Unknown direction");
                }
            }
    
            // println!("head moved {:?}", m);
            // print_situation(tx, ty, hx, hy);
    
            (tx, ty) = move_tail(tx, ty, hx, hy);
    
            // println!("tail moved");
            // print_situation(tx, ty, hx, hy);
    
            positions.insert((tx, ty));
        }

    }

    println!("Part 1: {}", positions.len());
}

// fn part2(input: &String){

// }
