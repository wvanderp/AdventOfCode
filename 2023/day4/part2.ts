import fs from 'fs';
import path from 'path';

const input = fs.readFileSync(path.join(__dirname, 'input.txt'), 'utf-8');

const lines = input.split('\n');


interface Card {
    // the id of the card
    id: number;
    // the cards won by this card (pointer to the id of the card)
    winningNumbers: number;
}

const games: Card[] = [];

for (let line of lines) {
    const id = parseInt(line.split(':')[0].split(' ').reverse()[0].trim());
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


    games.push({
        id,
        winningNumbers: cardNumbers.filter(n => winningNumbers.includes(n)).length
    });
}

console.log(games);

const toProcess: number[] = [...games.map(g => g.id)].reverse();

let cardsWon: number = toProcess.length;

while (toProcess.length > 0) {
    const cardID = toProcess.pop();

    // console.log('processing ', cardID);

    if (cardID === undefined) {
        throw new Error('card was undefined');
    }
    const cardWon = games.find(g => g.id === cardID);
    if (cardWon === undefined) {
        throw new Error('cardWon was undefined');
    }

    for(let i = cardID+1; i < cardID + cardWon.winningNumbers +1; i++) {
        // console.log('adding ', i);
        toProcess.push(i);
        cardsWon++;
    }


}

console.log(cardsWon);
