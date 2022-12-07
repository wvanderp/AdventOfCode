import fs from 'fs';

interface Inode {
    name: string;
    children: Inode[];
    size: number;
}

function ls(lines: string[], i: number, dir_Inode: Inode): number {
    i++;

    while (lines[i] != undefined && lines[i][0] !== '$') {
        const line = lines[i];

        if (line.slice(0, 3) === 'dir') {
            dir_Inode.children.push({
                name: line.slice(4),
                children: [],
                size: 0,
            });

            i++;
            continue;
        }

        const size = parseInt(line.split(" ")[0], 10);
        const name = line.split(" ")[1];

        dir_Inode.children.push({
            name: name,
            children: [],
            size: size,
        });

        i++;
    }

    return i;
}

function find_Inode(path: string[], inode: Inode): Inode {
    if(path.length === 0) {
        return inode;
    }

    if (path[0] === '/') {
        return find_Inode(path.slice(1), inode);
    }

    const child = inode.children.find((child) => child.name === path[0]);

    if (!child) {
        throw new Error('Invalid path');
    }

    return find_Inode(path.slice(1), child);
}

function print_tree(tree: Inode, indent: number = 0): void {

    let indent_str = ' '.repeat(indent);
    for (let i = 0; i < indent; i++) {
        process.stdout.write(' ');
    }

    if (tree.size === 0) {
        console.log(`${indent_str}${tree.name} (dir)`);
    } else {
        console.log(`${indent_str}${tree.name} (file, ${tree.size} bytes)`);
    }

    for (const child of tree.children) {
        print_tree(child, indent + 1);
    }
}

function build_tree(str: string): Inode {
    const tree: Inode = {
        name: '/',
        children: [],
        size: 0,
    };

    const lines = str.split('\n').map((line) => line.trim());
    let i = 0;
    const path = []

    while (i < lines.length) {
        if(lines[i][0] !== '$') {
            throw new Error('Invalid input');
        }

        if (lines[i].includes('$ ls')){
            i = ls(lines, i, find_Inode(path, tree));
            continue;
        }

        if (lines[i].includes('$ cd')) {
            const param = lines[i].split(' ')[2].trim();
            if (param === '..') {
                path.pop();
            } else {
                path.push(param);
            }
            i++;
            continue;
        }
    }

    return tree;
}


function calc_size(tree: Inode): number {
    let size = tree.size;

    for (const child of tree.children) {
        size += calc_size(child);
    }

    return size;
}

function find_all_dirs(tree: Inode): Inode[] {
    const dirs = [];

    if (tree.size === 0) {
        dirs.push(tree);
    }

    for (const child of tree.children) {
        dirs.push(...find_all_dirs(child));
    }

    return dirs;
}


function part1(str: string): void {
    const tree = build_tree(str);
    const dirs = find_all_dirs(tree);

    // return
    const sizes = dirs
        .map((dir) => calc_size(dir))
        .filter((size) => size < 100000)
        .reduce((acc, size) => acc + size, 0);

    console.log(`part 1: ${sizes}`)
}


function part2(str: string): void {
    const tree = build_tree(str);
    const disk_size = 70000000;
    const used_space = calc_size(tree);
    const space_needed = 30000000;
    const free_space = used_space + space_needed - disk_size;

    const sizes = find_all_dirs(tree)
    .map((dir) => calc_size(dir))
    .filter((size) => size > free_space)
    .sort((a, b) => a-b)[0];

    console.log(`part 2: ${sizes}`)

}

// ------------------------------

const file = fs.readFileSync('./input.txt', 'utf8');

part1(file);
part2(file);