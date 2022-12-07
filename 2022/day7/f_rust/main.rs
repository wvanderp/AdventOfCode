use std::collections::HashMap;
use std::fs;

fn main() {
    // read a file
    let input = fs::read_to_string("input.txt").expect("Something went wrong reading the file");

    let mut tree = Inode {
        name: Box::from("/"),
        s: 0,
        c: Vec::new(),
    };

    tree.c.push(Inode {
        name: Box::from("bin"),
        s: 0,
        c: vec![Inode {
            name: Box::from("bash"),
            s: 5514,
            c: Vec::new(),
        }],
    });

    print_tree(&tree, Some(0));

    // part1(&input);
    // part2(&input);
}

struct Inode {
    name: Box<str>,
    s: i32,
    c: Vec<Inode>,
}

fn print_tree(tree: &Inode, indentArg: Option<i32>) {
    let mut indent = indentArg.unwrap_or(0);

    for _ in 0..indent {
        print!(" ");
    }

    if tree.s == 0 {
        println!("{} (dir)", tree.name);
    } else {
        println!("{} (file, {} bytes)", tree.name, tree.s);
    }

    for child in tree.c.iter() {
        print_tree(child, Some(indent + 1));
    }
}

fn ls(i: usize, lines: &Vec<&str>) -> (Inode, i32) {
    let mut node = Inode {
        name: Box::from(""),
        s: 0,
        c: Vec::new(),
    };

    let name = lines[i].split(" ").collect::<Vec<&str>>()[2];
    node.name = Box::from(name);

    // loop over the next lines till we find a $
    while lines[i].chars().nth(0) != Some("$") {
        let line = lines[i];

        let size = line.split(" ").collect::<Vec<&str>>()[0];

        if size == "dir" 

        let name = line.split(" ").collect::<Vec<&str>>()[1];


    }
}

fn part1(input: &String) {
    let lines = input.split("\n").collect::<Vec<&str>>();

    let tree: Inode = Inode {
        name: Box::from("/"),
        s: 0,
        c: Vec::new(),
    };

    let mut i: usize = 0;

    while i < lines.len().try_into().unwrap() {
        let line = lines[i];
        if line.chars().nth(0) != Some('$') {
            panic!("Invalid line");
        }

        if line.contains("$ ls") {
            let (inode, i) = ls(i, &lines);
            tree.c.push(inode);
        }

        i += 1;
    }
}

fn part2(input: &String) {}
