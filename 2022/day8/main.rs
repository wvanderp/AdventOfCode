use std::{fs, vec};
fn main() {
    // read a file
    let input = fs::read_to_string("input.txt").expect("Something went wrong reading the file");

    let map: Vec<Vec<i32>> = input
        .lines()
        .map(|line| {
            line.chars()
                .map(|c| c.to_digit(10).unwrap() as i32)
                .collect()
        })
        .collect();

    // part1(&map);
    part2(&map);

    // println!("{}", scenic_score(&vec![5,2], 5))
    // 3 -> 1
    // 1,2 -> 2
    // 3,5,3 -> 2
    // 5,2 -> 1
}

fn get(map: &Vec<Vec<i32>>, x: i32, y: i32) -> Option<i32> {
    let local_x = x as usize;
    let local_y = y as usize;

    // println!("local_x: {}, local_y: {}", local_x, local_y);

    if local_x > map.len() - 1 || local_y > map[0].len() - 1 {
        return None;
    }

    if local_x < 0 || local_y < 0 {
        return None;
    }

    return Some(map[local_x][local_y]);
}

fn get_line(map: &Vec<Vec<i32>>, start_x: usize, start_y: usize, dx: i32, dy: i32) -> Vec<i32> {
    let mut ret: Vec<i32> = vec![];

    let mut x: i32 = start_x.try_into().unwrap();
    let mut y: i32 = start_y.try_into().unwrap();

    x += dx;
    y += dy;

    loop {
        let val = get(&map, x, y);
        if val.is_none() {
            break;
        }
        ret.push(val.unwrap());
        x += dx;
        y += dy;
    }

    return ret;
}

fn part1(map: &Vec<Vec<i32>>) {
    let mut x: i32 = 0;
    let mut y: i32 = 0;
    let mut trees: i32 = 0;

    loop {
        println!("x: {}, y: {}", x, y);
        for direction in vec![(1, 0), (0, 1), (-1, 0), (0, -1)] {
            let line = get_line(&map, x as usize, y as usize, direction.0, direction.1);

            if line.len() == 0 {
                trees += 1;
                println!("added tree becasue of egdge case");
                break;
            }

            let max_of_line = line.iter().max().unwrap().to_owned();
            let height = get(map, x, y).unwrap();

            println!(
                "Direction: {:?}, max: {}, height: {}",
                direction, max_of_line, height
            );

            if line.iter().max().unwrap().to_owned() < get(map, x, y).unwrap() {
                trees += 1;
                println!("added tree");
                break;
            }
        }

        x += 1;

        if x > map.len() as i32 - 1 {
            x = 0;
            y += 1;
        }

        if y > map[0].len() as i32 - 1 {
            break;
        }
    }

    println!("part1: {} trees", trees);
}

fn scenic_score(line: &Vec<i32>, height: i32) -> i32 {
    let mut score: i32 = 0;
    for i in 0..line.len() {
        score += 1;
        if height > line[i] {
            continue;
        }
        break;
    }
    return score;
}

fn part2(map: &Vec<Vec<i32>>) {
    let mut outer_tree_score = 0;

    for (y, row) in map.iter().enumerate() {
        for (x, col) in row.iter().enumerate() {
            let mut tree_score = 1;
            let height = col.to_owned();

            for direction in vec![(1, 0), (0, 1), (-1, 0), (0, -1)] {
                let line = get_line(&map, y as usize, x as usize, direction.0, direction.1);

                let score = scenic_score(&line, height);

                print!("{} ", score);

                tree_score *= score;
            }

            // if the tree is on the edge the score is 0
            if y == 0 || y == map.len() - 1 || x == 0 || x == map[0].len() - 1 {
                continue;
            }



            if tree_score > outer_tree_score {
                outer_tree_score = tree_score;
            }
        }
    }

    println!("part 2: {}", outer_tree_score);
}
