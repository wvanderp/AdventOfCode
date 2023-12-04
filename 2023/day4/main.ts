import fs from 'fs';
import path from 'path';

const input = fs.readFileSync(path.join(__dirname, 'input.txt'), 'utf-8');

const lines = input.split('\n');


/**
 * Calculates the result of multiplying a number by 2, a specified number of times.
 * 
 * test cases:
 * timesDouble(0) = 0
 * timesDouble(1) = 1
 * timesDouble(2) = 2
 * timesDouble(3) = 4
 * timesDouble(4) = 8
 * timesDouble(5) = 16
 * 
 * @param n - The number to be multiplied.
 * @param times - The number of times the multiplication should be performed.
 * @returns The result of multiplying the number by 2, the specified number of times.
 */
function timesDouble(times: number): number {
    if (times === 0) {
        return 0;
    }
    let result = 1;
    for (let i = 0; i < times-1; i++) {
        result *= 2;
    }
    return result;
}

interface Game {
    winningNumbers: number[];
    cardNumbers: number[];
    id: number;
    points: number;
}

const games: Game[] = [];
// line: Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
// game id: 1
// winning numbers: 41 48 83 86 17
// card numbers: 83 86  6 31 17  9 48 53
for (let line of lines) {
    const id = parseInt(line.split(':')[0].split(' ')[1]);
    const cardNumbers = line
        .split('|')[1]
        .split(' ')
        .map(n => parseInt(n))
        .filter(n => !isNaN(n));

    const winningNumbers = line
        .split(':')[1]
        .split('|')[0]
        .split(' ')
        .map(n => parseInt(n))
        .filter(n => !isNaN(n));

    
    // all of the card numbers that are also in the winning numbers
    // are the points
    const points = cardNumbers.filter(n => winningNumbers.includes(n));

    console.log(winningNumbers, cardNumbers, points)
    console.log(points.length);



    games.push({
        id,
        cardNumbers,
        winningNumbers,
        points: timesDouble(points.length)
    });
}


// sum the points
let totalPoints = 0;
for (let game of games) {
    totalPoints += game.points;
}


// check timesDouble
console.log(0, timesDouble(0), 0);
console.log(1, timesDouble(1), 1);
console.log(2, timesDouble(2), 2);
console.log(3, timesDouble(3), 4);
console.log(4, timesDouble(4), 8);


// console.log(games);
console.log(totalPoints);
